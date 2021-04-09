#ifndef REACTIONPLUS_EXEC_SIGNALSEMAPHORE_HPP
#define REACTIONPLUS_EXEC_SIGNALSEMAPHORE_HPP

#include <exec/exec.h>

#include <string>


namespace RAPlus {


  class SignalSemaphore {

    public:

      SignalSemaphore(const std::string &semaphoreName, uint32 priority);
     ~SignalSemaphore();

      std::string getSemaphoreName() { return(name); }

      void addReference() { referenceCount++; }
      void subReference() { referenceCount--; }

      int getReferenceCount() { return(referenceCount); }

      void obtain();
      void release();

      static SignalSemaphore *getSignalSemaphore(const std::string &semaphoreName);

      static bool findSignalSemaphore(const std::string &semaphoreName);

    private:

      SignalSemaphore(struct ::SignalSemaphore *semaphore, const std::string &semaphoreName);

      bool owner;

      int referenceCount;
      int internalCount;

      struct ::SignalSemaphore *semaphore;

      struct Task *task;

      std::string name;

  };


}

#endif // REACTIONPLUS_EXEC_SIGNALSEMAPHORE_HPP


