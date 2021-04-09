#ifndef REACTIONPLUS_EXEC_STANDARDIOREQUEST_HPP
#define REACTIONPLUS_EXEC_STANDARDIOREQUEST_HPP

#include <exec/io.h>

#include "IOBase.hpp"


namespace RAPlus {
  namespace Exec {

    class StandardIORequest : public IOBase {

      public:

                 StandardIORequest() : IOBase(sizeof(::IOStdReq)) { }
        virtual ~StandardIORequest() { }

        struct ::IOStdReq *getIOStdReq() { return(reinterpret_cast<struct ::IOStdReq *>(ioRequest)); }

        void setCommand(uint16 cmd) { getIOStdReq()->io_Command = cmd; }

        void setData(APTR data)     { getIOStdReq()->io_Data = data; }
        void setLength(uint32 len)  { getIOStdReq()->io_Length = len; }

      private:

    };

  }
}


#endif // REACTIONPLUS_EXEC_STANDARDIOREQUEST_HPP

