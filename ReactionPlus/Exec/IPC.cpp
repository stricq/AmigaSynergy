#include "IPC.hpp"

#include <proto/dos.h>
#include <proto/exec.h>

#include <stdio.h>

#include <sstream>


namespace RAPlus {
  namespace Exec {


    IPC::IPC(const std::string &portName, uint32 portIndex) :
      mainPort(0),
      peerPort(0),
      index(portIndex) {

      printf("IPC::IPC(%s,%u)\n",portName.c_str(),static_cast<uint>(portIndex));

      portFactory = MessagePortFactory::instance();

      if (index == 0) {
        bool flag = true;
        while(flag) {
          name = portName + ("." + toString(++index));
          printf("  Trying port %s\n",name.c_str());
          try {
            mainPort = portFactory->getMessagePort(name,0,true);
            flag = false;
          }
          catch(UniqueMessagePortException) {
            printf("  Port name was not unique, trying one up\n");
          }
        }
      }
      else {
        name = portName + ("." + toString(index));
        printf("  Using existing port %s\n",name.c_str());
        mainPort = portFactory->getMessagePort(name);
      }

      printf("IPC::IPC - Done\n");

    }


    IPC::~IPC() {

  //  printf("IPC::~IPC\n");

      if (childProcess) {
        for(int i = 0; IExec->FindTask((char *)child.c_str()) && i < 20; i++) {
          printf("Waiting for %s to disappear...\n",child.c_str());
          IDOS->Delay(12);
        }
        if (IExec->FindTask((char *)child.c_str())) IExec->Signal((struct Task *)childProcess,SIGBREAKF_CTRL_C);
      }

      if (mainPort) portFactory->deleteMessagePort(mainPort->getPortName());
      if (peerPort) portFactory->deleteMessagePort(peerPort->getPortName());

      MessagePortFactory::removeMessagePortFactory();

  //  printf("IPC::~IPC - Done\n");

    }


    template<class T>
    std::string IPC::toString(const T &n) {

      std::stringstream sout;

      sout << n;

      return(sout.str());

    }


    bool IPC::sendMessage(IMessage *message) {

      if (peerPort == 0) return(false);

  //  printf("IPC::sendMessage(%s [%u] -> %s)\n",mainPort->getPortName().c_str(),message->getType(),peerPort->getPortName().c_str());

      obtain();

      mainPort->sendMessage(peerPort,message);

      release();

  //  printf("IPC::sendMessage() - Done\n");

      return(true);

    }


    IMessage *IPC::recvMessage() {

      IMessage *message = mainPort->recvMessage();

  //  printf("IPC::recvMessage - type = %u\n",message->getType());

      if (peerPort == 0) {
        peerPort = portFactory->addMessagePort(mainPort->getReplyPort());
  //    printf("  peerPort was 0, set up new as %s\n",peerPort->getPortName().c_str());
      }

  //  printf("IPC::recvMessage - Done\n");

      return(message);

    }


    bool IPC::spawnChild(std::string childName, int32 (*func)(char *, int32, APTR), uint32 priority) {

      BPTR inp = 0;

      child = childName + ("." + toString(index));

      struct TagItem procTags[] = {
        { NP_Arguments,   0 },
        { NP_Input,       0 },
        { NP_Output,      0 },
  //    { NP_Error,       0 },
        { NP_Entry,       (uint32)func },
        { NP_Child,       TRUE },
        { NP_StackSize,   65536 },
        { NP_Name,        (uint32)child.c_str() },
        { NP_Priority,    priority },
        { NP_CopyVars,    TRUE },
        { TAG_DONE,       0 }
      };

      sprintf(args,"%s",name.c_str());

      if ((inp = IDOS->Open("CONSOLE:",MODE_OLDFILE)) != 0) {
        procTags[0].ti_Data = (uint32)args;
        procTags[1].ti_Data = (uint32)inp;
  //    procTags[3].ti_Data = (uint32)inp;
        childProcess = IDOS->CreateNewProc(procTags);
        if (childProcess == 0) IDOS->Close(inp);
      }

      return(childProcess != 0);

    }


  // ==================================== class IPCParent


    IPCParent::IPCParent(const std::string &portName, uint32 portIndex) : IPC(portName,portIndex),
      semaphore(0) {

      printf("IPCParent::IPCParent(%s,%u)\n",portName.c_str(),static_cast<uint>(portIndex));

      semaphoreFactory = SignalSemaphoreFactory::instance();

  //  printf("  Using Semaphore name %s\n",name.c_str());

      semaphore = semaphoreFactory->getSignalSemaphore(name);

      printf("IPCParent::IPCParent - Done\n");

    }


    IPCParent::~IPCParent() {

      if (semaphore) semaphoreFactory->deleteSignalSemaphore(semaphore->getSemaphoreName());

      SignalSemaphoreFactory::removeSignalSemaphoreFactory();

    }


    void IPCParent::obtain() {

      if (semaphore) semaphore->obtain();

    }


    void IPCParent::release() {

      if (semaphore) semaphore->release();

    }


  // ==================================== class IPCChild


    IPCChild::IPCChild(const std::string &childName, const std::string &parentName) : IPC(childName,0),
      semaphore(0) {

      printf("IPCChild::IPCChild(%s,%s)\n",childName.c_str(),parentName.c_str());

      semaphoreFactory = SignalSemaphoreFactory::instance();

  //  printf("  Using Semaphore name %s\n",parentName.c_str());

      semaphore = semaphoreFactory->getSignalSemaphore(parentName);

      peerPort = portFactory->getMessagePort(parentName);

      printf("IPCChild::IPCChild - Done\n");

    }


    IPCChild::~IPCChild() {

      if (semaphore) semaphoreFactory->deleteSignalSemaphore(semaphore->getSemaphoreName());

      SignalSemaphoreFactory::removeSignalSemaphoreFactory();

    }


    void IPCChild::obtain() {

      if (semaphore) semaphore->obtain();

    }


    void IPCChild::release() {

      if (semaphore) semaphore->release();

    }


  }
}

