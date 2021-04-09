#include "ReactionClass.hpp"

#include "Window.hpp"

#include "InvalidStateException.hpp"
#include "Exec/OutOfMemoryException.hpp"

#include <stdarg.h>


namespace RAPlus {
  namespace Reaction {


    Object *ReactionClass::newObject(ClassType type, ReactionClass *gadget, ...) {

      struct TagItem *varargs;

      Object *object;

      va_list va;

      va_startlinear(va,gadget);

      varargs = va_getlinearva(va,struct TagItem *);

      if (gadget == 0) {
        ReactionClass *temp = ReactionClass::classFactory(type);
        if (temp) {
          object = temp->newObject(varargs);
          delete temp;
        }
        else throw OutOfMemoryException("Could not create the temp Class class.");
      }
      else object = gadget->newObject(varargs);

      return(object);

    }



    void ReactionClass::dispose() {

      if (!classObject) return;

      IIntuition->DisposeObject(classObject);

      classObject = 0;

    }


    ReactionClass *ReactionClass::classFactory(ClassType type) {

      switch(type) {
        case WindowType: return(new Window());
      }

      throw InvalidStateException("Unknown Gadget Type in Gadget Factory.\n");

    }


  }
}

