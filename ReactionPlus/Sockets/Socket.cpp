#include "Socket.hpp"

#include <proto/bsdsocket.h>


namespace RAPlus {
  namespace Sockets {


    Socket::Socket(AddressFamily addressFamily, SocketType socketType) :
      connected(false),
      family(addressFamily),
      type(socketType) {

      openSocket();

    }


    Socket::~Socket() {

      disconnect();

    }


    std::string Socket::getErrorStr() {

      uint32 err = getErrorNum();

      ISocket->SocketBaseTags(SBTM_GETREF(SBTC_ERRNOSTRPTR),&err,TAG_DONE);

      return(std::string((char *)err));

    }


    uint32 Socket::getErrorNum() {

      uint32 val = 0;

      uint32 *err = &val;

      ISocket->SocketBaseTags(SBTM_GETREF(SBTC_ERRNO),err,TAG_DONE);

      return(*err);

    }


    std::string Socket::getHostName() {

      char name[1024];

      if (ISocket->gethostname(name,1024) == -1) {
        throw SocketException(getErrorStr(),getErrorNum());
      }

      return(std::string(name));

    }


    void Socket::openSocket() {

      if ((socket = ISocket->socket((long)family,(long)type,0)) == -1) {
        throw SocketException(getErrorStr(),getErrorNum());
      }

//    printf("socket = %ld\n",socket);

    }


    long Socket::getAvailable() {

      long data;

      ISocket->IoctlSocket(socket,FIONREAD,&data);

      return(data);

    }


    void Socket::setBlocking(bool block) {

      blocking = block;

      long data = (blocking ? 1 : 0);

      if (ISocket->IoctlSocket(socket,FIONBIO,&data) == -1) {
        throw SocketException(getErrorStr(),getErrorNum());
      }

    }


    void Socket::connect(const std::string &host, uint16 port) {

      resolve(host,remoteAddress);

      remoteAddress.sin_port = htons(port);

      if (ISocket->connect(socket,(struct sockaddr *)&remoteAddress,sizeof(remoteAddress)) == -1) {
        throw SocketException(getErrorStr(),getErrorNum());
      }

      connected = true;

//    printf("Connected\n");

    }


    void Socket::disconnect() {

      if (connected) ISocket->CloseSocket(socket);

//    printf("Disconnected.\n");

      openSocket();

      connected = false;

    }


    void Socket::bind(uint16 port) {

      memset((char *)&localAddress,0,sizeof(localAddress));

      localAddress.sin_family      = AF_INET;
      localAddress.sin_addr.s_addr = htonl(INADDR_ANY);
      localAddress.sin_len         = sizeof(struct sockaddr_in);
      localAddress.sin_port        = htons(port);

      bindAddress();

    }


    void Socket::bind(const std::string &host, uint16 port) {

      resolve(host,localAddress);

      localAddress.sin_port = htons(port);

      bindAddress();

    }


    void Socket::bindAddress() {

      if (ISocket->bind(socket,(struct sockaddr *)&localAddress,sizeof(localAddress)) == -1) {
        throw SocketException(getErrorStr(),getErrorNum());
      }

    }


    long Socket::receive(char *buffer, long bufLen, long offset, long size) {

      long bytes = 0;

      if (buffer == 0)            throw Exception("Buffer is NULL");
      if (offset < 0)             throw IndexRangeException("Offset is below 0",bufLen,offset);
      if (size < 0)               throw IndexRangeException("Size is below 0",bufLen,size);
      if (offset > bufLen)        throw IndexRangeException("Offset exceeds Buffer Length",bufLen,offset);
      if (offset + size > bufLen) throw IndexRangeException("Offset + Size exceeds Buffer Length",bufLen,offset + size);

//    printf("Socket::receive(0x%08X,%ld,%ld,%ld)\n",buffer,bufLen,offset,size);

      bytes = ISocket->recv(socket,buffer + offset,size,0);

//    printf("Socket::receive() - read %ld\n",bytes);

      if (bytes == -1) throw SocketException(getErrorStr(),getErrorNum());

      return(bytes);

    }


    long Socket::send(const char *buffer, long bufLen, long offset, long size) {

      long bytes = 0;

      if (buffer == 0)            throw Exception("Buffer is NULL");
      if (offset < 0)             throw IndexRangeException("Offset is below 0",bufLen,offset);
      if (size < 0)               throw IndexRangeException("Size is below 0",bufLen,size);
      if (offset > bufLen)        throw IndexRangeException("Offset exceeds Buffer Length",bufLen,offset);
      if (offset + size > bufLen) throw IndexRangeException("Offset + Size exceeds Buffer Length",bufLen,offset + size);

      bytes = ISocket->send(socket,(char *)(buffer + offset),size,0);

//    printf("Socket::write(%ld) - write %ld\n",bufLen,bytes);

      if (bytes == -1) throw SocketException(getErrorStr(),getErrorNum());

      return(bytes);

    }


    void Socket::resolve(const std::string &host, struct sockaddr_in &address) {

      struct hostent *nameinfo;

      memset((char *)&localAddress,0,sizeof(localAddress));

      if ((nameinfo = ISocket->gethostbyname((char *)host.c_str())) == 0) {
        address.sin_addr.s_addr = ISocket->inet_addr((char *)host.c_str());
        if ((int)address.sin_addr.s_addr == -1) throw HostNotFoundException();
      }
      else memcpy((char *)&address.sin_addr.s_addr,nameinfo->h_addr,nameinfo->h_length);

      address.sin_family = nameinfo->h_addrtype;
      address.sin_len    = sizeof(struct sockaddr_in);

//    printf("Found the host at %s\n",ISocket->Inet_NtoA(address.sin_addr.s_addr));

    }


  }
}

