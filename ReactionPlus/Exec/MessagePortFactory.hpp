#ifndef REACTIONPLUS_EXEC_MESSAGEPORTFACTORY_HPP
#define REACTIONPLUS_EXEC_MESSAGEPORTFACTORY_HPP

#include <exec/exec.h>

#include "Exception.hpp"
#include "OutOfMemoryException.hpp"

#include "MessagePort.hpp"
#include "SignalSemaphore.hpp"

#include <map>
#include <string>


namespace RAPlus {
  namespace Exec {

    class MessagePortFactory {

      public:

        static MessagePortFactory *instance();

        static void removeMessagePortFactory();

       ~MessagePortFactory();

        MessagePort *getMessagePort(const std::string &portName, int8 priority = 0, bool unique = false);

        MessagePort *addMessagePort(MessagePort *msgPort);

        void deleteMessagePort(const std::string &portName);

      private:

        MessagePortFactory() : reference(0), semaphore("MessagePortFactory",0) { }

        int reference;

        static MessagePortFactory *portFactoryInstance;

        SignalSemaphore semaphore;

        std::map<std::string, MessagePort *> portList;

    };


    class UniqueMessagePortException : public Exception {

      public:

        UniqueMessagePortException(const std::string &msg) : Exception(msg) { }
       ~UniqueMessagePortException() { }

    };

  }
}


#endif // REACTIONPLUS_EXEC_MESSAGEPORTFACTORY_HPP

