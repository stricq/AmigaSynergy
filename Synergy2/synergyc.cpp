#include "synergyc.hpp"

#include "asynergyc_rev.h"

#include <stdio.h>


static __attribute__((used)) char  versionString[] = VERSTAG;


int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("\nWelcome to asynergyc v%d.%d, Synergy Client for Amiga OS4.\n\n",VERSION,REVISION);
    printf("Usage: asynergyc <synergy-host> <host-os(windows|linux|mac)>\nExample: asynergyc 192.168.1.2 windows\n\n");
    printf("My screen name to use with the server is: %s\n\n",Sockets::Socket::getHostName().c_str());
    return(20);
  }

  Exec::Task task = Exec::Exec::findTask();

  int8 taskOldPri = task.setTaskPriority(20);

  synergyc client;

  client.run(argv[1],argv[2]);

  task.setTaskPriority(taskOldPri);

//printf("\n");

  return(0);

}


synergyc::synergyc() {

//printf("synergyc\n");

  socket = new Sockets::Socket(Sockets::Socket::InterNetwork,Sockets::Socket::Stream);

  timer = new Exec::TimerDevice(Exec::TimerDevice::MicroHertz);

  commodity = new Commodities::Commodity("Synergy",0);

  clip = new Exec::ClipboardDevice();

  injector = InputInjector::instance();

}


synergyc::~synergyc() {

//printf("~synergyc\n");

  delete injector;

  delete clip;

  delete commodity;

  delete timer;

  delete socket;

}


void synergyc::run(char *hostname, char *os) {

  fatal = false;
  enabled = true;

  int delay = 0;

  std::string host(hostname);
  std::string osName(os);

  Sockets::SocketEvents *loop = 0;

  Exec::TimerEvent event = 0;

  if (osName == "linux") injector->setOS(InputInjector::OS_LINUX);
  else if (osName == "mac") injector->setOS(InputInjector::OS_MAC);
  else injector->setOS(InputInjector::OS_WINDOWS);

  commodity->setTitle("Synergy v2.0");
  commodity->setDescription("Amiga OS4 Synergy Client");
  commodity->hasGUI(false);
  commodity->onEnable(this,(Commodities::CommodityEventMethod)&synergyc::commodity_OnEnable);
  commodity->onDisable(this,(Commodities::CommodityEventMethod)&synergyc::commodity_OnDisable);
  commodity->onKill(this,(Commodities::CommodityEventMethod)&synergyc::commodity_OnKill);
  commodity->enable();

  event = timer->addTimer(0,250000,true,this,(Exec::TimerEventMethod)&synergyc::timer_OnEvent);

  loop = new Sockets::SocketEvents();

  loop->addReader(socket,this,(Sockets::SocketEventMethod)&synergyc::socket_OnRead);
  loop->addListener(clip->getSignal(),this,(Exec::EventMethod)&synergyc::clip_OnClipboardChange);
  loop->addListener(commodity);
  loop->addListener(timer);

  while(!fatal) {
    try {
      socket->connect(host,24800);
      Intuition::Pointer::blankPointer();
    }
    catch(HostNotFoundException &) {
      printf("Your host %s was not found.\n",hostname);
      fatal = true;
    }
    catch(SocketException &se) {
      printf("Socket Error: %s\n",se.getMessage().c_str());
    }
    if (socket->isConnected()) {
      clip->enableCallbacks();
      timer->enableTimer(event);
      uint32 signals = loop->waitSignals();
      timer->disableTimer(event);
      clip->disableCallbacks();
      if (signals & SIGBREAKF_CTRL_C) fatal = true;
      delay = 0;
    }
    socket->disconnect();
    if (!fatal) {
      if (delay < 30) ++delay;
      fatal = !timer->wait(delay,0);
    }
  }

  delete loop;

}


bool synergyc::socket_OnRead(Sockets::Socket *socket) {

  bool done = false;

  Sockets::Packet *packet = new Sockets::Packet();

  IReaderCommand *rCommand;
  IWriterCommand *wCommand;

//printf("synergyc::socket_OnRead()\n");

  if (socket->getAvailable() == 0) done = true;

  while(!done && socket->getAvailable() > 0) {
    try {
      packet->readPacket(socket);
      if (enabled) {
        rCommand = IReaderCommand::readerFactory(packet);
        if ((wCommand = (IWriterCommand *)rCommand->getResponse()) != 0) {
          if (wCommand->prepareResponse()) wCommand->writePacket(socket);
        }
        done  = rCommand->isClosed();
        fatal = rCommand->isFatal();
      }
    }
    catch(UnknownPacketException &) {
      std::string cmd = packet->getString(4);
      printf("  Caught an unknown Packet exception. (%s)\n",cmd.c_str());
    }
    catch(Exception &e) {
      printf("Error: %s\n",e.getMessage().c_str());
      fatal = true;
      done = true;
    }
    catch(...) {
      fatal = true;
      done = true;
    }
  }

  return(done);

}


bool synergyc::commodity_OnEnable() {

  enabled = true;

  return(false);

}


bool synergyc::commodity_OnDisable() {

  enabled = false;

  return(false);

}


bool synergyc::commodity_OnKill() {

  fatal = true;

  return(true);

}


bool synergyc::timer_OnEvent(Exec::TimerEvent) {

//printf("synergyc::timer_OnEvent()\n");

  Intuition::Rectangle dim = Intuition::IntuitionBase::getFirstScreen().getRectangle();

  if (lastDim.getWidth() != 0) {
    if (lastDim.getWidth() != dim.getWidth() || lastDim.getHeight() != dim.getHeight()) {
      IWriterCommand *wCommand = IWriterCommand::writerFactory(std::string("DINF"));
      if (wCommand->prepareResponse()) wCommand->writePacket(socket);
    }
  }

  lastDim = dim;

  return(false);

}


bool synergyc::clip_OnClipboardChange(uint32) {

//printf("synergyc::clip_OnClipboardChange()\n");

  IWriterCommand *wCommand = IWriterCommand::writerFactory(std::string("CCLP"));

  if (wCommand->prepareResponse()) wCommand->writePacket(socket);

  wCommand = IWriterCommand::writerFactory(std::string("DCLP"));

  if (wCommand->prepareResponse()) wCommand->writePacket(socket);

  return(false);

}

