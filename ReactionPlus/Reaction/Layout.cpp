#include "Layout.hpp"

#include "Exec/OutOfMemoryException.hpp"


namespace RAPlus {
  namespace Reaction {


    Object *Layout::newObject(struct TagItem *tagItem) {

      gadgetObject = (Object *)IIntuition->NewObjectA(ILayout->LAYOUT_GetClass(),NULL,tagItem);

      if (!gadgetObject) throw OutOfMemoryException("Could not create the Layout Object.");

      return(gadgetObject);

    }


    bool Layout::gadgetUpEvent() {

      if (gadgetUpClass != 0) return((gadgetUpClass->*gadgetUpMethod)(this));

      return(false);

    }


    void Layout::setAlignLabels(ReactionGadget &gadget) {

      Set(gadgetObject,LAYOUT_AlignLabels,gadget.getObject());

    }


  }
}

