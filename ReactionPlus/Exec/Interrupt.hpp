#ifndef RAPLUS_EXEC_INTERRUPT_HPP
#define RAPLUS_EXEC_INTERRUPT_HPP

#include <exec/exectags.h>
#include <exec/interrupts.h>

#include "Exception.hpp"


namespace RAPlus {
  namespace Exec {

    class Interrupt {

      public:

        Interrupt();
       ~Interrupt();

        struct ::Interrupt *getInterrupt() { return(interrupt); }

        void setCallback(void (*code)()) { interrupt->is_Code = code; }

        void setData(APTR data) { interrupt->is_Data = data; }

        void setNodePriority(int8 priority) { interrupt->is_Node.ln_Pri = priority; }

      private:

        struct ::Interrupt *interrupt;

    };

  }
}

#endif // RAPLUS_EXEC_INTERRUPT_HPP

