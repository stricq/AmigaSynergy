#ifndef RAPLUS_SOCKETS_SOCKETREADER_HPP
#define RAPLUS_SOCKETS_SOCKETREADER_HPP

#include "Socket.hpp"

#include "DOS/Reader.hpp"


namespace RAPlus {
  namespace Sockets {

    class SocketReader : public RAPlus::DOS::Reader {

      public:

                 SocketReader(Socket *socket, bool autoClose = true);
                 SocketReader(Socket &socket, bool autoClose = true);
        virtual ~SocketReader() { }

        virtual void close();

        virtual long read(char *buffer, long bufLen, long offset, long size);

        virtual long readFull(char *buffer, long bufLen, long offset, long size);

        virtual bool ready();

      private:

        bool autoClose;

        Socket *socket;

    };

  }
}


#endif // RAPLUS_SOCKETS_SOCKETREADER_HPP

