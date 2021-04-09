#include "ReactionImage.hpp"

#include "Label.hpp"

#include "InvalidStateException.hpp"
#include "Exec/OutOfMemoryException.hpp"

#include <stdarg.h>


namespace RAPlus {
  namespace Reaction {


    Object *ReactionImage::newObject(ImageType type, ReactionImage *gadget, ...) {

      struct TagItem *varargs;

      Object *object;

      va_list va;

      va_startlinear(va,gadget);

      varargs = va_getlinearva(va,struct TagItem *);

      if (gadget == 0) {
        ReactionImage *temp = ReactionImage::classFactory(type);
        if (temp) {
          object = temp->newObject(varargs);
          delete temp;
        }
        else throw OutOfMemoryException("Could not create the temp Class class.");
      }
      else object = gadget->newObject(varargs);

      return(object);

    }



    void ReactionImage::dispose() {

      if (!imageObject) return;

      IIntuition->DisposeObject(imageObject);

      imageObject = 0;

    }


    ReactionImage *ReactionImage::classFactory(ImageType type) {

      switch(type) {
        case LabelType: return(new Label());
      }

      throw InvalidStateException("Unknown Gadget Type in Gadget Factory.\n");

    }


  }
}

