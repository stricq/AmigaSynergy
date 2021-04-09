#include "Exec.hpp"

#include <proto/exec.h>


namespace RAPlus {
  namespace Exec {


    Task Exec::findTask(const std::string &taskName) {

      return(Task(IExec->FindTask(taskName.c_str())));

    }


    Task Exec::findTask() {

      return(Task(IExec->FindTask(0)));

    }


    void Exec::addResetCallback(Interrupt &interrupt) {

      IExec->AddResetCallback(interrupt.getInterrupt());

    }


    void Exec::remResetCallback(Interrupt &interrupt) {

      IExec->RemResetCallback(interrupt.getInterrupt());

    }


  }
}

