#include "ClipboardDevice.hpp"

uint32 _ChangeHook(struct Hook *hook, void *object, struct ClipHookMsg *msg);


namespace RAPlus {
  namespace Exec {


    ClipboardDevice::ClipboardDevice() :
      hookEnabled(false) {

      clipRequest = new ClipboardRequest();

      clipBit = clipRequest->getSignal();

      clipStat = IExec->OpenDevice("clipboard.device",0,clipRequest->getIORequest(),0);

      if (clipStat != 0) {
        delete clipRequest;
        throw ClipboardDeviceException();
      }

      taskAddr = IExec->FindTask(NULL);

    }


    ClipboardDevice::~ClipboardDevice() {

      disableCallbacks();

      if (clipStat == 0) IExec->CloseDevice(clipRequest->getIORequest());

      delete clipRequest;

    }


    void ClipboardDevice::enableCallbacks() {

      clipHook.setEntry((HOOKFUNC)_ChangeHook);
      clipHook.setData(this);

      clipRequest->setCommand(ClipboardRequest::ChangeHook);
      clipRequest->setData((char *)clipHook.getHook());
      clipRequest->setLength(1);

      IExec->DoIO(clipRequest->getIORequest());

      hookEnabled = true;

    }


    void ClipboardDevice::disableCallbacks() {

      if (!hookEnabled) return;

      clipRequest->setCommand(ClipboardRequest::ChangeHook);
      clipRequest->setData((char *)&clipHook);
      clipRequest->setLength(0);

      IExec->DoIO(clipRequest->getIORequest());

      hookEnabled = false;

    }


  }
}


uint32 _ChangeHook(struct Hook *hook, void *, struct ClipHookMsg *) {

  RAPlus::Exec::ClipboardDevice *clipboard = (RAPlus::Exec::ClipboardDevice *)hook->h_Data;

  IExec->Signal(clipboard->getTaskAddress(),clipboard->getSignal());

  return(0);

}

