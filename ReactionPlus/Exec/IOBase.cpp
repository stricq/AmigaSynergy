#include "IOBase.hpp"

#include <proto/exec.h>


namespace RAPlus {
  namespace Exec {


    IOBase::IOBase(uint32 size) :
      owner(true),
      ioSize(size),
      ioRequest(0) {

      ioPort = new MessagePort();

      struct TagItem ioTags[] = {
        { ASOIOR_Size,      ioSize },
        { ASOIOR_ReplyPort, reinterpret_cast<uint32>(ioPort->getMsgPort()) },
        { ASO_NoTrack,      FALSE },
        { TAG_DONE,         0 }
      };

      ioRequest = (struct ::IORequest *)IExec->AllocSysObject(ASOT_IOREQUEST,ioTags);

      if (ioRequest == 0) throw Exception("Unable to create an IO Request.");

    }


    IOBase::IOBase(const IOBase *ioBase) :
      owner(false),
      ioSize(ioBase->ioSize),
      ioRequest(0),
      ioPort(ioBase->ioPort) {

      struct TagItem ioTags[] = {
        { ASOIOR_Duplicate, reinterpret_cast<uint32>(ioBase->ioRequest) },
        { TAG_DONE,         0 }
      };

      ioRequest = (struct ::IORequest *)IExec->AllocSysObject(ASOT_IOREQUEST,ioTags);

      if (ioRequest == 0) throw Exception("Unable to create an IO Request.");

    }


    IOBase::IOBase(const IOBase &ioBase) :
      owner(false),
      ioSize(ioBase.ioSize),
      ioRequest(0),
      ioPort(ioBase.ioPort) {

      struct TagItem ioTags[] = {
        { ASOIOR_Duplicate, reinterpret_cast<uint32>(ioBase.ioRequest) },
        { TAG_DONE,         0 }
      };

      ioRequest = (struct ::IORequest *)IExec->AllocSysObject(ASOT_IOREQUEST,ioTags);

      if (ioRequest == 0) throw Exception("Unable to create an IO Request.");

    }


    IOBase::~IOBase() {

//    printf("IOBase::~IOBase() ioRequest = %p\n",ioRequest);

      if (ioRequest != 0) IExec->FreeSysObject(ASOT_IOREQUEST,ioRequest);

      if (ioPort != 0 && owner) delete ioPort;

//    printf("IOBase::~IOBase() - Done\n");

    }


  }
}

