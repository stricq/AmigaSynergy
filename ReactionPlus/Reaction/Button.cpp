#include "Button.hpp"

#include "Exec/OutOfMemoryException.hpp"


namespace RAPlus {
  namespace Reaction {


    Object *Button::newObject(struct TagItem *tagItem) {

      gadgetObject = (Object *)IIntuition->NewObjectA(IButton->BUTTON_GetClass(),NULL,tagItem);

      if (!gadgetObject) throw OutOfMemoryException("Could not create the Button Object.");

      return(gadgetObject);

    }


    bool Button::gadgetUpEvent() {

      if (gadgetUpClass != 0) return((gadgetUpClass->*gadgetUpMethod)(this));

      return(false);

    }


  }
}

