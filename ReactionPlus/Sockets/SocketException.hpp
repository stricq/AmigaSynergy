#ifndef RAPLUS_SOCKETS_SOCKETEXCEPTION_HPP
#define RAPLUS_SOCKETS_SOCKETEXCEPTION_HPP

#include "Exception.hpp"


namespace RAPlus {

  class SocketException : public Exception {

    public:

      SocketException(std::string msg, long err) : Exception(msg), error(err) { }
     ~SocketException() { }

      long getError() { return(error); }

    private:

      long error;

  };

}


#endif  //  RAPLUS_SOCKETS_SOCKETEXCEPTION_HPP
