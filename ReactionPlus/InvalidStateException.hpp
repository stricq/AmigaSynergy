#ifndef INVALIDSTATEEXCEPTION_HPP
#define INVALIDSTATEEXCEPTION_HPP

#include "Exception.hpp"


namespace RAPlus {

  class InvalidStateException : public Exception {

    public:

      InvalidStateException(const char *msg) : Exception(msg) { }
     ~InvalidStateException() { }

  };

}

#endif // INVALIDSTATEEXCEPTION_HPP

