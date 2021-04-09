#ifndef REACTIONPLUS_EXEC_CLIPBOARDREQUEST_HPP
#define REACTIONPLUS_EXEC_CLIPBOARDREQUEST_HPP

#include <devices/clipboard.h>

#include <exec/io.h>

#include "IOBase.hpp"


namespace RAPlus {
  namespace Exec {

    class ClipboardRequest : public IOBase {

      public:

        enum ClipboardCommand { ChangeHook = CBD_CHANGEHOOK };

                 ClipboardRequest() : IOBase(sizeof(struct ::IOClipReq)) { }
        virtual ~ClipboardRequest() { }

        struct ::IOClipReq *getIOClipReq() { return(reinterpret_cast<struct ::IOClipReq *>(ioRequest)); }

        void setCommand(ClipboardCommand cmd) { getIOClipReq()->io_Command = cmd; }

        void setLength(uint32 len)            { getIOClipReq()->io_Length  = len; }
        void setData(char *data)              { getIOClipReq()->io_Data    = data; }

      private:

    };

  }
}


#endif // REACTIONPLUS_EXEC_CLIPBOARDREQUEST_HPP

