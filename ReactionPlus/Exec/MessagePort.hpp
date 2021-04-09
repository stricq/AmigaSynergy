#ifndef REACTIONPLUS_EXEC_MESSAGEPORT_HPP
#define REACTIONPLUS_EXEC_MESSAGEPORT_HPP

#include <exec/exec.h>

#include <string>


namespace RAPlus {
  namespace Exec {

    typedef uint32 IMessageType;

    class IMessage {

      public:

                 IMessage() { }
        virtual ~IMessage() { }

        virtual IMessage    *clone() = 0;
        virtual IMessageType getType() = 0;

        virtual void setMessage(struct Message *message) { msg = message; }

        virtual struct Message *getMessage() { return(msg); }

      protected:

        struct Message *msg;

    };


    class MessagePort {

      public:

        MessagePort();
        MessagePort(const std::string &portName, int8 priority = 0);
       ~MessagePort();

        std::string getPortName() { return(name); }

        uint32 getSignal() { return(1 << (port->mp_SigBit)); }

        struct MsgPort *getMsgPort() { return(port); }

        void addReference() { referenceCount++; }
        void subReference() { referenceCount--; }

        int getReferenceCount() { return(referenceCount); }

        bool sendMessage(MessagePort *peerPort, IMessage *message);

        IMessage *recvMessage();

        bool   getMessage(IMessage *message);
        void replyMessage(IMessage *message);

        MessagePort *getReplyPort();

        static MessagePort *getMessagePort(const std::string &portName);

        static bool findMessagePort(const std::string &portName);

      private:

        MessagePort(struct MsgPort *msgPort, const std::string &portName);

        bool portOwner;

        int referenceCount;

        struct IPCMessage {
          struct Message msg;
          IMessage *message;
        };

        struct MsgPort *port;
        struct MsgPort *replyPort;

        std::string name;

    };

  }
}

#endif // REACTIONPLUS_EXEC_MESSAGEPORT_HPP

