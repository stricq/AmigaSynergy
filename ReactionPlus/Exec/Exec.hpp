#ifndef RAPLUS_EXEC_EXEC_HPP
#define RAPLUS_EXEC_EXEC_HPP

#include "Task.hpp"
#include "Interrupt.hpp"


namespace RAPlus {
  namespace Exec {

    class Exec {

      public:

        static Task findTask(const std::string &taskName);
        static Task findTask();

        static void addResetCallback(Interrupt &interrupt);
        static void remResetCallback(Interrupt &interrupt);

//      static void *allocVec

      private:

        Exec() { }
       ~Exec() { }

    };

  }
}

#endif // RAPLUS_EXEC_EXEC_HPP

