#ifndef RAPLUS_EXEC_INPUTDEVICE_HPP
#define RAPLUS_EXEC_INPUTDEVICE_HPP

#include <devices/input.h>
#include <devices/timer.h>

#include "StandardIORequest.hpp"
#include "InputEvent.hpp"
#include "Interrupt.hpp"


namespace RAPlus {

  class InputDeviceException { };

  namespace Exec {

    class InputDevice {

      public:

        InputDevice();
       ~InputDevice();

        uint32 getSignal() { return(inputBit); }

        void addEvent(InputEvent &event);
        void addHandler(Interrupt &interrupt);
        void writeEvent(InputEvent &event);

      private:

        uint32 inputBit;
        uint32 inputStat;

        StandardIORequest *stdRequest;

    };

  }
}


#endif // RAPLUS_EXEC_INPUTDEVICE_HPP

