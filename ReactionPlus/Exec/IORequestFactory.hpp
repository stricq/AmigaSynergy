#ifndef REACTIONPLUS_EXEC_IOREQUESTFACTORY_HPP
#define REACTIONPLUS_EXEC_IOREQUESTFACTORY_HPP

#include "TimerRequest.hpp"
#include "IORequest.hpp"
#include "StandardIORequest.hpp"
#include "ClipboardRequest.hpp"


namespace RAPlus {
  namespace Exec {

    enum IORequestType { IOType, StandardIOType, ClipboardIOType, TimerIOType };


    class IORequestFactory {

      public:

        static IOBase *createIORequest(IORequestType ioType);

      private:

    };

  }
}


#endif // REACTIONPLUS_EXEC_IOREQUESTFACTORY_HPP

