#ifndef IOEXCEPTION_HPP
#define IOEXCEPTION_HPP

#include "Exception.hpp"


namespace RAPlus {

  class IOException : public Exception {

    public:

      IOException(const char *msg) : Exception(msg), ioError(0) { }
      IOException(const char *msg, LONG error) : Exception(msg), ioError(error) { }
     ~IOException() { }

      LONG getIOError() { return(ioError); }

    private:

      LONG ioError;

  };

}

#endif // IOEXCEPTION_HPP

