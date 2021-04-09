#ifndef OUTOFMEMORYEXCEPTION_HPP
#define OUTOFMEMORYEXCEPTION_HPP

#include "Exception.hpp"

#include <string>


namespace RAPlus {

  class OutOfMemoryException : public Exception {

    public:

      OutOfMemoryException(const std::string &msg) : Exception(msg) { }
     ~OutOfMemoryException() { }

  };

}

#endif // OUTOFMEMORYEXCEPTION_HPP

