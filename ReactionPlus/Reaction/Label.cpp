#include "Label.hpp"

#include "Exec/OutOfMemoryException.hpp"


namespace RAPlus {
  namespace Reaction {


    Object *Label::newObject(struct TagItem *tagItem) {

      imageObject = (Object *)IIntuition->NewObjectA(ILabel->LABEL_GetClass(),NULL,tagItem);

      if (!imageObject) throw OutOfMemoryException("Could not create the Label Object.");

      return(imageObject);

    }


  }
}


