#ifndef INVALIDARGUMENTEXCEPTION_HPP
#define INVALIDARGUMENTEXCEPTION_HPP

#include "Exception.hpp"


namespace RAPlus {

  class InvalidArgumentException : public Exception {

    public:

      InvalidArgumentException(const char *msg) : Exception(msg) { }
     ~InvalidArgumentException() { }

  };

}

#endif // INVALIDARGUMENTEXCEPTION_HPP

