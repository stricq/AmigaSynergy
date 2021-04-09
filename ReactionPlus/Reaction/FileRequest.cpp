#include "FileRequest.hpp"

#include "Exec/OutOfMemoryException.hpp"


namespace RAPlus {
  namespace Reaction {


    Object *FileRequest::newObject(struct TagItem *tagItem) {

      gadgetObject = (Object *)IIntuition->NewObjectA(IGetFile->GETFILE_GetClass(),NULL,tagItem);

      if (!gadgetObject) throw OutOfMemoryException("Could not create the FileRequest Object.");

      return(gadgetObject);

    }


    bool FileRequest::gadgetUpEvent() {

      if (gadgetUpClass != 0) return((gadgetUpClass->*gadgetUpMethod)(this));

      return(false);

    }


  }
}

