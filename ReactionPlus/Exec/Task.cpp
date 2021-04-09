#include "Task.hpp"

#include <proto/exec.h>


namespace RAPlus {
  namespace Exec {


    Task::Task(struct ::Task *task) :
      task(task) {

      if (task == 0) throw InvalidArgumentException("Task is NULL.");

    }


    Task::Task(const Task &task) :
      task(task.task) {
    }


    int8 Task::setTaskPriority(int8 priority) {

      return(IExec->SetTaskPri(task,priority));

    }


    Task &Task::operator=(const Task &rhs) {

      task = rhs.task;

      return(*this);

    }


  }
}

