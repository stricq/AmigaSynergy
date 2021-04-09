#include "Integer.hpp"

#include "Exec/OutOfMemoryException.hpp"


namespace RAPlus {
  namespace Reaction {


    Object *Integer::newObject(struct TagItem *tagItem) {

      gadgetObject = (Object *)IIntuition->NewObjectA(IInteger->INTEGER_GetClass(),NULL,tagItem);

      if (!gadgetObject) throw OutOfMemoryException("Could not create the Integer Object.");

      return(gadgetObject);

    }


    bool Integer::gadgetUpEvent() {

      if (gadgetUpClass != 0) return((gadgetUpClass->*gadgetUpMethod)(this));

      return(false);

    }


  }
}


