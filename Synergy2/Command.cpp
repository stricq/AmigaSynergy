#include "Command.hpp"

#include <stdio.h>


long ICommand::clipSequence = 0;


ICommand::~ICommand() {

  delete packet;

}


IReaderCommand *IReaderCommand::readerFactory(Sockets::Packet *pkt) {

  std::string cmd = pkt->getString(4);

  if (cmd == "Syne") return(new RHelloCommand(pkt,cmd));
  else if (cmd == "CALV") return(new RKeepAlive(pkt,cmd));
  else if (cmd == "CBYE") return(new RGoodbye(pkt,cmd));
  else if (cmd == "CINN") return(new RScreenEnter(pkt,cmd));
  else if (cmd == "COUT") return(new RScreenLeave(pkt,cmd));
  else if (cmd == "CCLP") return(new RGrabClipboard(pkt,cmd));
  else if (cmd == "CSEC") return(new RScreenSaver(pkt,cmd));
  else if (cmd == "CIAK") return(new RScreenAck(pkt,cmd));
  else if (cmd == "DKDN") return(new RKeyDown(pkt,cmd));
  else if (cmd == "DKRP") return(new RKeyRepeat(pkt,cmd));
  else if (cmd == "DKUP") return(new RKeyUp(pkt,cmd));
  else if (cmd == "DMDN") return(new RMouseDown(pkt,cmd));
  else if (cmd == "DMUP") return(new RMouseUp(pkt,cmd));
  else if (cmd == "DMWM") return(new RMouseWheel(pkt,cmd));
  else if (cmd == "DSOP") return(new RSetOptions(pkt,cmd));
  else if (cmd == "CROP") return(new RResetOptions(pkt,cmd));
  else if (cmd == "DCLP") return(new RClipboard(pkt,cmd));
  else if (cmd == "DMMV") return(new RMouseMove(pkt,cmd));
  else if (cmd == "QINF") return(new RScreenInfo(pkt,cmd));
  else if (cmd == "EICV") return(new RErrorVersion(pkt,cmd));
  else if (cmd == "EBSY") return(new RErrorBusy(pkt,cmd));
  else if (cmd == "EUNK") return(new RErrorUnknown(pkt,cmd));
  else if (cmd == "EBAD") return(new RErrorProtocol(pkt,cmd));

  pkt->printHex(std::string("Unknown incoming Packet:"));

  pkt->resetIndex();

  throw UnknownPacketException();

}


void RHelloCommand::parse() {

  packet->resetIndex();

  type = packet->getString(7);

  major = packet->getInt16();
  minor = packet->getInt16();

  if (major < 1 || (major == 1 && minor < 3)) {
    closed = true;
    fatal  = true;
  }
  else response = IWriterCommand::writerFactory(type);

}


void RGoodbye::parse() {

  Intuition::Pointer::restorePointer();

  closed = true;

}


void RScreenEnter::parse() {

  mouseX = packet->getInt16();
  mouseY = packet->getInt16();

  sequence = packet->getInt32();

  modifiers = packet->getInt16();

//printf("RScreenEnter::Mouse entered my screen at %d,%d; sequence = %ld, modifiers = 0x%04X.\n",mouseX,mouseY,sequence,modifiers);

  Intuition::Pointer::restorePointer();

  InputInjector::instance()->setQualifiers(modifiers);
  InputInjector::instance()->injectMouse(mouseX,mouseY);

  clipSequence = sequence;

}


void RScreenLeave::parse() {

//printf("Mouse has left my screen.\n");

  Intuition::Pointer::blankPointer();

}


void RGrabClipboard::parse() {

  clipID = packet->getInt8();

  sequence = packet->getInt32();

//packet->printHex("Grab Clipboard");

}


void RScreenSaver::parse() { }


void RScreenAck::parse() {

  InputInjector::instance()->setIgnoreMouse(false);

}


void RKeyDown::parse() {

  keyID     = packet->getInt16();
  modifiers = packet->getInt16();
  button    = packet->getInt16();

//printf("Key down.  keyID = 0x%04x, modifiers = 0x%04x, button = 0x%04x\n",keyID,modifiers,button);

  InputInjector::instance()->injectKeyboard(button,modifiers,true);

}


void RKeyRepeat::parse() {

  keyID     = packet->getInt16();
  modifiers = packet->getInt16();
  repeats   = packet->getInt16();
  button    = packet->getInt16();

//printf("Key down.  keyID = 0x%04x, modifiers = 0x%04x, button = 0x%04x\n",keyID,modifiers,button);

  InputInjector::instance()->injectKeyboard(button,modifiers,true);

}


void RKeyUp::parse() {

  keyID     = packet->getInt16();
  modifiers = packet->getInt16();
  button    = packet->getInt16();

//printf("Key up.    keyID = 0x%04x, modifiers = 0x%04x, button = 0x%04x\n",keyID,modifiers,button);

  InputInjector::instance()->injectKeyboard(button,modifiers,false);

}


void RMouseDown::parse() {

  button = packet->getInt8();

//printf("Mouse button %d down.\n",button);

  InputInjector::instance()->injectMouseButton(button,true);

}


void RMouseUp::parse() {

  button = packet->getInt8();

//printf("Mouse button %d up.\n",button);

  InputInjector::instance()->injectMouseButton(button,false);

}


void RMouseMove::parse() {

  mouseX = packet->getInt16();
  mouseY = packet->getInt16();

//printf("RMouseMove::Mouse moved to %d,%d.\n",mouseX,mouseY);

  InputInjector::instance()->injectMouse(mouseX,mouseY);

}


void RMouseWheel::parse() {

  deltaX = packet->getInt16();
  deltaY = packet->getInt16();

//printf("Mouse wheel delta Y %d, delta X %d.\n",deltaY,deltaX);

  InputInjector::instance()->injectMouseWheel(deltaY,deltaX);

}


void RClipboard::parse() {

  char *clip = 0;

  long formats;
  long formatType;
  long clipLen;
  long totalLen;

  IFFParse::IFFClipboard *iffClip = new IFFParse::IFFClipboard(0);

  clipID = packet->getInt8();

  sequence = packet->getInt32();

//packet->printHex("Clipboard Data");

//if (clipID != 0x00) return;  // This 0x00 is hardcoded based on v1.2 of the protocol.

  totalLen = packet->getInt32();

  formats = packet->getInt32();

  for(long i = 0; i < formats; i++) {
    formatType = packet->getInt32();
    clipLen    = packet->getInt32();
    clip = new char[clipLen];
    packet->getData(clip,clipLen);
    if (formatType == 0x00000000) { // As well, this 0x00000000 is based on v1.2 of the protocol.
      std::string strClip(clip,clipLen);
      iffClip->setText(strClip);
    }
    delete clip;
  }

  delete iffClip;

}


void RSetOptions::parse() { }


void RResetOptions::parse() { }


void RScreenInfo::parse() {

  response = IWriterCommand::writerFactory(std::string("DINF"));

}


void RKeepAlive::parse() {

  response = IWriterCommand::writerFactory(std::string("CALV"));

}


void RErrorVersion::parse() {

  printf("It seems the Synergy server is incompatible with me.  Exiting...\n");

  major = packet->getInt16();
  minor = packet->getInt16();

  closed = true;
  fatal  = true;

}


void RErrorBusy::parse() {

  closed = true;

}


void RErrorUnknown::parse() {

  printf("It seems the Synergy server does not know me.  Exiting...\n");

  closed = true;

}


void RErrorProtocol::parse() {

  printf("It seems I violated the protocol specifications.  Exiting...\n");

  closed = true;
  fatal  = true;

}


// ------------------------ Writer Commands


IWriterCommand *IWriterCommand::writerFactory(std::string cmd) {

  if (cmd == "Synergy") return(new WHelloCommand(new Sockets::Packet(),cmd));
  else if (cmd == "CALV") return(new WKeepAlive(new Sockets::Packet(),cmd));
  else if (cmd == "DINF") return(new WScreenInfo(new Sockets::Packet(),cmd));
  else if (cmd == "CCLP") return(new WGrabClipboard(new Sockets::Packet(),cmd));
  else if (cmd == "DCLP") return(new WSendClipboard(new Sockets::Packet(),cmd));

  throw UnknownPacketException();

}


bool WHelloCommand::prepareResponse() {

  std::string name = Sockets::Socket::getHostName();

  packet->setBuffer(type.length() + 8 + name.length());

  packet->setString(type);

  packet->setInt16(0x0001);
  packet->setInt16(0x0003);

  packet->setInt32(name.length());

  packet->setData(name.c_str(),name.length());

  return(true);

}


bool WKeepAlive::prepareResponse() {

  packet->setBuffer(type.length());

  packet->setString(type);

  return(true);

}


bool WScreenInfo::prepareResponse() {

  Intuition::Rectangle info = Intuition::IntuitionBase::getFirstScreen().getRectangle();
  Intuition::Point    mouse = Intuition::IntuitionBase::getMousePoint();

  packet->setBuffer(type.length() + 14);

  packet->setString(type);

  packet->setInt16(0x0000);
  packet->setInt16(0x0000);
  packet->setInt16(info.getWidth());
  packet->setInt16(info.getHeight());
  packet->setInt16(0x0000);
  packet->setInt16(mouse.getX());
  packet->setInt16(mouse.getY());

  InputInjector::instance()->setIgnoreMouse(true);

  return(true);

}


bool WGrabClipboard::prepareResponse() {

  packet->setBuffer(type.length() + 5);

  packet->setString(type);

  packet->setInt8(0x00);

  packet->setInt32(clipSequence);

//packet->printHex("GrabClipboard");

  return(true);

}


bool WSendClipboard::prepareResponse() {

  IFFParse::IFFClipboard *clipboard = new IFFParse::IFFClipboard(0);

  std::string text;

  clipboard->getText(text);

  delete clipboard;

  long formats = 1;

  packet->setBuffer(type.length() + 5 + 8 + (formats * (8 + text.length())));

  packet->setString(type);

  packet->setInt8(0x00);

  packet->setInt32(clipSequence);
  packet->setInt32(4 + (formats * (8 + text.length())));
  packet->setInt32(formats);

  for(long i = 0; i < formats; i++) {
    packet->setInt32(0x00000000);
    packet->setInt32(text.length());
    packet->setData(text.c_str(),text.length());
  }

//packet->printHex("SendClipboard");

  return(true);

}

