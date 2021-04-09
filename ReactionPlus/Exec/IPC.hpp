#ifndef REACTIONPLUS_EXEC_IPC_HPP
#define REACTIONPLUS_EXEC_IPC_HPP

#include <dos/dosextens.h>
#include <exec/exec.h>

#include "MessagePortFactory.hpp"
#include "SignalSemaphoreFactory.hpp"

#include "Exception.hpp"
#include "OutOfMemoryException.hpp"

#include <string>



namespace RAPlus {
  namespace Exec {


    class IPC {

      public:

        virtual ~IPC();

        uint32 getSignal()    { return(mainPort->getSignal()); }
        uint32 getPortIndex() { return(index); }

        bool spawnChild(std::string childName, int32 (*func)(char *, int32, APTR), uint32 priority = 0);

        bool isChildReady() { return(peerPort != 0); }

        bool sendMessage(IMessage *message);

        IMessage *recvMessage();

        virtual void obtain() = 0;
        virtual void release() = 0;

      protected:

        IPC(const std::string &portName, uint32 portIndex);

        std::string name;

        MessagePortFactory *portFactory;

        MessagePort *mainPort;
        MessagePort *peerPort;

      private:

        template<class T> std::string toString(const T &n);

        char args[64];

        uint32 index;

        std::string child;

        struct Process *childProcess;

    };


    class IPCParent : public IPC {

      public:

        IPCParent(const std::string &portName, uint32 portIndex);
       ~IPCParent();

        void obtain();
        void release();

      private:

        SignalSemaphoreFactory *semaphoreFactory;

        SignalSemaphore *semaphore;

    };


    class IPCChild : public IPC {

      public:

        IPCChild(const std::string &childName, const std::string &parentName);
       ~IPCChild();

        void obtain();
        void release();

      private:

        SignalSemaphoreFactory *semaphoreFactory;

        SignalSemaphore *semaphore;

    };


  }
}

#endif // REACTIONPLUS_EXEC_IPC_HPP

