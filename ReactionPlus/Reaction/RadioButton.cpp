#include "RadioButton.hpp"

#include "Exec/OutOfMemoryException.hpp"


namespace RAPlus {
  namespace Reaction {


    std::string RadioButton::getAttrError = "RadioButton GetAttrs() could not get the attribute.";


    Object *RadioButton::newObject(struct TagItem *tagItem) {

      gadgetObject = (Object *)IIntuition->NewObjectA(IRadioButton->RADIOBUTTON_GetClass(),NULL,tagItem);

      if (!gadgetObject) throw OutOfMemoryException("Could not create the RadioButton Object.");

      return(gadgetObject);

    }


    bool RadioButton::gadgetUpEvent() {

      if (gadgetUpClass != 0) return((gadgetUpClass->*gadgetUpMethod)(this));

      return(false);

    }


    uint16 RadioButton::getSelected() {

      uint32 value = 0;

      if (Get(gadgetObject,RADIOBUTTON_Selected,&value) != 1) throw Exception(getAttrError);

      return(value);

    }


    void RadioButton::setSelected(uint16 value) {

      Set(gadgetObject,RADIOBUTTON_Selected,value);

    }


  }
}

