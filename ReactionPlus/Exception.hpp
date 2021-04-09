#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <proto/exec.h>

#include <string.h>

#include <string>


namespace RAPlus {

  class Exception {

    public:

               Exception(const Exception &e);
               Exception(const char *msg);
               Exception(const std::string &msg);
      virtual ~Exception();

      virtual std::string toString();
      virtual std::string getMessage();


    protected:

      char *errorMessage;

  };

}

#endif // EXCEPTION_HPP

