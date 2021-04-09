#ifndef RAPLUS_EXEC_CLIPBOARDDEVICE_HPP
#define RAPLUS_EXEC_CLIPBOARDDEVICE_HPP

#include <proto/exec.h>

#include "ClipboardRequest.hpp"

#include "Utility/Hook.hpp"


namespace RAPlus {

  class ClipboardDeviceException { };

  namespace Exec {

    class ClipboardDevice {

      public:

                 ClipboardDevice();
        virtual ~ClipboardDevice();

        virtual uint32 getSignal() const { return(clipBit); }

        virtual void enableCallbacks();
        virtual void disableCallbacks();

        virtual struct Task *getTaskAddress() const { return(taskAddr); }

      private:

        bool hookEnabled;

        uint32 clipBit;
      	uint32 clipStat;

      	struct Task *taskAddr;

        ClipboardRequest *clipRequest;

        Utility::Hook clipHook;

    };

  }
}


#endif // RAPLUS_EXEC_CLIPBOARDDEVICE_HPP

