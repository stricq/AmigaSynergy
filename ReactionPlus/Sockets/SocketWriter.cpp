#include "SocketWriter.hpp"


namespace RAPlus {
  namespace Sockets {


    SocketWriter::SocketWriter(Socket *socket, bool autoClose) : autoClose(autoClose), socket(socket) { }


    SocketWriter::SocketWriter(Socket &socket, bool autoClose) : autoClose(autoClose), socket(&socket) { }


    void SocketWriter::close() {

      socket->disconnect();

    }


    void SocketWriter::flush() { }


    void SocketWriter::write(const char *buffer, long bufLen, long offset, long size) {

      socket->send(buffer,bufLen,offset,size);

    }


    void SocketWriter::writeFull(const char *buffer, long bufLen, long offset, long size) {

      long bytes = 0;

      long index = offset;

      do {
        bytes = socket->send(buffer,bufLen,index,size - index);
        index += bytes;
      } while(index < size);

    }


  }
}

