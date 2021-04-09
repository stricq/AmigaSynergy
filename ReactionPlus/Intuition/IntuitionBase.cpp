#include "IntuitionBase.hpp"

#include <proto/intuition.h>


namespace RAPlus {
  namespace Intuition {


    Screen IntuitionBase::getActiveScreen() {

      uint32 lock = IIntuition->LockIBase(0);

      Screen screen(::IntuitionBase->ActiveScreen);

      IIntuition->UnlockIBase(lock);

      return(screen);

    }


    Screen IntuitionBase::getFirstScreen() {

      uint32 lock = IIntuition->LockIBase(0);

      Screen screen(::IntuitionBase->FirstScreen);

      IIntuition->UnlockIBase(lock);

      return(screen);

    }


    Point IntuitionBase::getMousePoint() {

      uint32 lock = IIntuition->LockIBase(0);

      Point point(::IntuitionBase->MouseX,::IntuitionBase->MouseY);

      IIntuition->UnlockIBase(lock);

      return(point);

    }


  }
}

