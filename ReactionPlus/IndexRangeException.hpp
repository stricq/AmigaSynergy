#ifndef INDEXRANGEEXCEPTION_HPP
#define INDEXRANGEEXCEPTION_HPP

#include <stdio.h>

#include "Exception.hpp"


namespace RAPlus {

  class IndexRangeException : public Exception {

    public:

      IndexRangeException(const char *msg, int rangeBoundary, int badIndex);
     ~IndexRangeException() { }

      int getBoundary() { return(bounds); }
      int getIndex()    { return(index); }

    private:

      int bounds;
      int index;

  };

}

#endif // INDEXRANGEEXCEPTION_HPP

