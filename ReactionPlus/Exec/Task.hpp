#ifndef RAPLUS_EXEC_TASK_HPP
#define RAPLUS_EXEC_TASK_HPP

#include <exec/tasks.h>

#include "InvalidArgumentException.hpp"

#include "Exec.hpp"


namespace RAPlus {
  namespace Exec {

    class Task {

      public:

        Task(struct ::Task *task);
        Task(const Task &task);
       ~Task() { }

        int8 setTaskPriority(int8 priority);

        Task &operator=(const Task &rhs);

      private:

        struct ::Task *task;

    };

  }
}

#endif // RAPLUS_EXEC_TASK_HPP

