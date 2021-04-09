#include "ListBrowser.hpp"

#include "Exec/OutOfMemoryException.hpp"


namespace RAPlus {
  namespace Reaction {


    Object *ListBrowser::newObject(struct TagItem *tagItem) {

      gadgetObject = (Object *)IIntuition->NewObjectA(IListBrowser->LISTBROWSER_GetClass(),NULL,tagItem);

      if (!gadgetObject) throw OutOfMemoryException("Could not create the ListBrowser Object.");

      return(gadgetObject);

    }


    bool ListBrowser::gadgetUpEvent() {

      if (gadgetUpClass != 0) return((gadgetUpClass->*gadgetUpMethod)(this));

      return(false);

    }


  }
}



