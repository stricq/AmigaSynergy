#include "InputDevice.hpp"

#include <proto/exec.h>


namespace RAPlus {
  namespace Exec {


    InputDevice::InputDevice() {

      stdRequest = new StandardIORequest();

      inputBit = stdRequest->getSignal();

      inputStat = IExec->OpenDevice("input.device",0,stdRequest->getIORequest(),0);

      if (inputStat != 0) {
        delete stdRequest;
        throw InputDeviceException();
      }

    }


    InputDevice::~InputDevice() {

    	if (inputStat == 0) IExec->CloseDevice(stdRequest->getIORequest());

      delete stdRequest;

    }


    void InputDevice::addEvent(InputEvent &event) {

      stdRequest->setCommand(IND_ADDEVENT);
      stdRequest->setData(event.getInputEvent());
      stdRequest->setLength(event.getLength());

      IExec->DoIO(stdRequest->getIORequest());

    }


    void InputDevice::writeEvent(InputEvent &event) {

      stdRequest->setCommand(IND_WRITEEVENT);
      stdRequest->setData(event.getInputEvent());
      stdRequest->setLength(event.getLength());

      IExec->DoIO(stdRequest->getIORequest());

    }


    void InputDevice::addHandler(Interrupt &interrupt) {

      stdRequest->setCommand(IND_ADDHANDLER);
      stdRequest->setData(interrupt.getInterrupt());

      IExec->DoIO(stdRequest->getIORequest());

    }


  }
}

