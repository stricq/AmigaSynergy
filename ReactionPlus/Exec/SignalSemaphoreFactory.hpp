#ifndef REACTIONPLUS_EXEC_SIGNALSEMAPHOREFACTORY_HPP
#define REACTIONPLUS_EXEC_SIGNALSEMAPHOREFACTORY_HPP

#include "Exception.hpp"

#include "SignalSemaphore.hpp"

#include <exec/exec.h>

#include <map>
#include <string>


namespace RAPlus {


  class SignalSemaphoreFactory {

    public:

      static SignalSemaphoreFactory *instance();

      static void removeSignalSemaphoreFactory();

     ~SignalSemaphoreFactory();

      SignalSemaphore *getSignalSemaphore(const std::string &semaphoreName, uint32 priority = 0, bool unique = false);

      void deleteSignalSemaphore(const std::string &semaphoreName);

    private:

      SignalSemaphoreFactory() : reference(0), semaphore("SignalSemaphoreFactory",0) { }

      int reference;

      static SignalSemaphoreFactory *semaphoreFactoryInstance;

      SignalSemaphore semaphore;

      std::map<std::string, SignalSemaphore *> semaphoreList;

  };


  class UniqueSignalSemaphoreException : public Exception {

    public:

      UniqueSignalSemaphoreException(const std::string &msg) : Exception(msg) { }
     ~UniqueSignalSemaphoreException() { }
  };


}


#endif // REACTIONPLUS_EXEC_SIGNALSEMAPHOREFACTORY_HPP


