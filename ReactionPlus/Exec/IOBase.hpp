#ifndef REACTIONPLUS_EXEC_IOBASE_HPP
#define REACTIONPLUS_EXEC_IOBASE_HPP

#include <exec/io.h>

#include "MessagePort.hpp"

#include "Exception.hpp"


namespace RAPlus {
  namespace Exec {

    class IOBase {

      public:

        virtual ~IOBase();

        virtual ::IORequest *getIORequest() { return(ioRequest); }

        virtual uint32 getSignal() { return(ioPort->getSignal()); }

      protected:

        IOBase(uint32 size);
        IOBase(const IOBase *ioBase);
        IOBase(const IOBase &ioBase);

        bool owner;

        uint32 ioSize;

        ::IORequest *ioRequest;

        MessagePort *ioPort;

        MessagePort *getMessagePort() { return(ioPort); }

    };

  }
}


#endif // REACTIONPLUS_EXEC_IOBASE_HPP

