#ifndef RAPLUS_SOCKETS_SOCKET_HPP
#define RAPLUS_SOCKETS_SOCKET_HPP

#include <exec/types.h>

#include <libraries/bsdsocket.h>

#include <sys/ioctl.h>

#include "Exception.hpp"
#include "IndexRangeException.hpp"
#include "SocketException.hpp"
#include "DOS/IOException.hpp"

#include <string>


namespace RAPlus {

  class HostNotFoundException { };

  namespace Sockets {

    class Socket {

      public:

        enum AddressFamily { InterNetwork = AF_INET };

        enum SocketType { Stream = SOCK_STREAM, DataGram = SOCK_DGRAM };

        Socket(AddressFamily addressFamily, SocketType socketType);
       ~Socket();

        bool isConnected() { return(connected); }
        bool isBlocking()  { return(blocking); }

        static std::string getErrorStr();
        static std::string getHostName();
        static uint32      getErrorNum();

        SocketType getSocketType() { return(type); }

        long getSocket() { return(socket); }

        long getAvailable();

        void setBlocking(bool block);

        void connect(const std::string &host, uint16 port);
        void disconnect();

        void bind(uint16 port = 0);
        void bind(const std::string &host, uint16 port = 0);

        long receive(char *buffer, long bufLen, long offset, long size);
        long send(const char *buffer, long bufLen, long offset, long size);

      private:

        bool connected;
        bool blocking;

        long socket;

        AddressFamily family;
        SocketType    type;

        struct sockaddr_in remoteAddress;
        struct sockaddr_in  localAddress;

        void openSocket();
        void bindAddress();

        void resolve(const std::string &host, struct sockaddr_in &address);

    };

  }
}


#endif // RAPLUS_SOCKETS_SOCKET_HPP

