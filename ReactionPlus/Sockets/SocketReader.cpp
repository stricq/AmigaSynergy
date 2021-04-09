#include "SocketReader.hpp"


namespace RAPlus {
  namespace Sockets {


    SocketReader::SocketReader(Socket *socket, bool autoClose) : autoClose(autoClose), socket(socket) { }


    SocketReader::SocketReader(Socket &socket, bool autoClose) : autoClose(autoClose), socket(&socket) { }


    void SocketReader::close() {

      if (autoClose) socket->disconnect();

    }


    long SocketReader::read(char *buffer, long bufLen, long offset, long size) {

      long n = socket->receive(buffer,bufLen,offset,size);

      return(n == 0 ? -1 : n);

    }


    long SocketReader::readFull(char *buffer, long bufLen, long offset, long size) {

      long bytes = 0;

      long index = offset;

      do {
        bytes = socket->receive(buffer,bufLen,index,size - index);
        index += bytes;
      } while(index < size);

//    printf("SocketReader::read(%ld) - read %ld\n",size,index);

      return(index);

    }


    bool SocketReader::ready() {

      return(socket->getAvailable() > 0);

    }

  }
}

