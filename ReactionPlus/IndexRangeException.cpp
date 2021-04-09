#include "IndexRangeException.hpp"


namespace RAPlus {


  IndexRangeException::IndexRangeException(const char *msg, int rangeBoundary, int badIndex) :
    Exception(NULL),
    bounds(rangeBoundary),
    index(badIndex) {

    if (msg) errorMessage = (char *)IExec->AllocVec(512,MEMF_CLEAR);
    else errorMessage = NULL;

    if (errorMessage) sprintf(errorMessage,"%s (Boundary = %d, Index = %d)",msg,bounds,index);

  }


}

