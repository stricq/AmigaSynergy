#include "IORequestFactory.hpp"


namespace RAPlus {
  namespace Exec {


    IOBase *createIORequest(IORequestType type) {

      switch(type) {
        case          IOType: { return(new IORequest()); }
        case  StandardIOType: { return(new StandardIORequest()); }
        case ClipboardIOType: { return(new ClipboardRequest()); }
        case     TimerIOType: { return(new TimerRequest()); }
      }

      return(0);

    }


  }
}

