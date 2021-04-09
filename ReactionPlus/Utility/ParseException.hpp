#ifndef PARSEEXCEPTION_HPP
#define PARSEEXCEPTION_HPP

#include "Exception.hpp"

#include <stdio.h>

#include <string>


namespace RAPlus {

  class ParseException : public Exception {

    public:

      ParseException(const char *msg, std::string badLine, int badIndex);
     ~ParseException() { }

      std::string &getLine() { return(line); }
      int getIndex()         { return(index); }

    private:

      int index;

      std::string line;

  };

}

#endif // PARSEEXCEPTION_HPP

