#ifndef FILENOTFOUNDEXCEPTION_HPP
#define FILENOTFOUNDEXCEPTION_HPP

#include "IOException.hpp"


namespace RAPlus {

  class FileNotFoundException : public IOException {

    public:

      FileNotFoundException(const char *msg) : IOException(msg) { }
     ~FileNotFoundException() { }

  };

}

#endif // FILENOTFOUNDEXCEPTION_HPP

