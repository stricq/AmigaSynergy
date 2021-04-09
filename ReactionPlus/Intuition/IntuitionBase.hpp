#ifndef RAPLUS_INTUITION_INTUITIONBASE_HPP
#define RAPLUS_INTUITION_INTUITIONBASE_HPP

#define __USE_BASETYPE__

#include <intuition/intuitionbase.h>

#include "Screen.hpp"
#include "Point.hpp"


namespace RAPlus {
  namespace Intuition {

    class IntuitionBase {

      public:

        IntuitionBase() { }
       ~IntuitionBase() { }

        static Screen getActiveScreen();
        static Screen getFirstScreen();

        static Point getMousePoint();

      private:

    };

  }
}

#endif // RAPLUS_INTUITION_INTUITIONBASE_HPP

