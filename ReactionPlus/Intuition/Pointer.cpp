#include "Pointer.hpp"

#include <proto/graphics.h>
#include <proto/intuition.h>

#include <stdio.h>


namespace RAPlus {
  namespace Intuition {


    void Pointer::blankPointer() {

      static uint16 spriteData[] = {
        0, 0,
        0x0000, 0x0000,
        0, 0
      };

      static struct SimpleSprite sprite = {
        0,
        1,
        0, 0,
        0
      };

      IGraphics->ChangeSprite(0,&sprite,&spriteData);

    }

    void Pointer::restorePointer() {

      IIntuition->ScreenToFront(IntuitionBase::getFirstScreen().getScreen());

    }


  }
}

