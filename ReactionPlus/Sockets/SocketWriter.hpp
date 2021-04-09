#ifndef RAPLUS_SOCKETS_SOCKETWRITER_HPP
#define RAPLUS_SOCKETS_SOCKETWRITER_HPP

#include "Socket.hpp"

#include "DOS/Writer.hpp"


namespace RAPlus {
  namespace Sockets {

    class SocketWriter : public RAPlus::DOS::Writer {

      public:

                 SocketWriter(Socket *socket, bool autoClose = true);
                 SocketWriter(Socket &socket, bool autoClose = true);
        virtual ~SocketWriter() { }

        virtual void close();
        virtual void flush();

        using Writer::write;

        virtual void write(const char *buffer, long bufLen, long offset, long size);

        virtual void writeFull(const char *buffer, long bufLen, long offset, long size);

      private:

        bool autoClose;

        Socket *socket;

    };

  }
}

#endif // RAPLUS_SOCKETS_SOCKETWRITER_HPP

