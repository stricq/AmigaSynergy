#include "Interrupt.hpp"

#include <proto/exec.h>


namespace RAPlus {
  namespace Exec {


    Interrupt::Interrupt() :
      interrupt(0) {

      struct TagItem intTags[] = {
        { ASOINTR_Size, sizeof(interrupt) },
        { ASO_NoTrack,  FALSE },
        { TAG_DONE,     0 }
      };

      interrupt = (struct ::Interrupt *)IExec->AllocSysObject(ASOT_INTERRUPT,intTags);

      if (interrupt == 0) throw Exception("Unable to create an Interrupt object.");

    }


    Interrupt::~Interrupt() {

      if (interrupt != 0) IExec->FreeSysObject(ASOT_INTERRUPT,interrupt);

    }


  }
}

