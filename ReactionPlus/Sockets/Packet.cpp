#include "Packet.hpp"


namespace RAPlus {
  namespace Sockets {


    Packet::~Packet() {

      delete buffer;

    }


    void Packet::readPacket(Sockets::Socket *socket) {

      Sockets::SocketReader reader(socket,false);

      index = 0;

      delete buffer;

      reader.readFull((char *)&length,sizeof(int32),0,sizeof(int32));

//    printf("packet length = %ld\n",length);

      buffer = new char[length];

      reader.readFull(buffer,length,0,length);

//    printHex(std::string("Incoming packet:"));

    }


    void Packet::writePacket(Sockets::Socket *socket) {

      Sockets::SocketWriter writer(socket,false);

      int32 len = length;

      writer.writeFull((char *)&len,sizeof(int32),0,sizeof(int32));
      writer.writeFull(buffer,length,0,length);

//    printHex(std::string("Outgoing packet:"));

    }


    int8 Packet::getInt8() {

      int8 value;

      if ((index + (int)sizeof(int8)) > length) return(0);

      memcpy(&value,buffer + index,sizeof(int8));

      index += sizeof(int8);

      return(value);

    }


    int16 Packet::getInt16() {

      int16 value;

      if ((index + (int)sizeof(int16)) > length) return(0);

      memcpy(&value,buffer + index,sizeof(int16));

      index += sizeof(int16);

      return(value);

    }


    int32 Packet::getInt32() {

      int32 value;

      if ((index + (int)sizeof(int32)) > length) return(0);

      memcpy(&value,buffer + index,sizeof(int32));

      index += sizeof(int32);

      return(value);

    }


    void Packet::getData(char *buf, long bufLen) {

      if ((index + bufLen) > length || buf == 0) return;

      memcpy(buf,buffer + index,bufLen);

      index += bufLen;

    }


    std::string Packet::getString(long bufLen) {

      if ((index + bufLen) > length) return(std::string(""));

      std::string val(buffer + index,bufLen);

      index += bufLen;

      return(val);

    }


    void Packet::setBuffer(long bufLen) {

      if (buffer != 0) delete buffer;

      buffer = new char[bufLen];

      length = bufLen;

      index = 0;

    }


    void Packet::setInt8(int8 value) {

      if ((index + (int)sizeof(int8)) > length) return;

      memcpy(buffer + index,&value,sizeof(int8));

      index += sizeof(int8);

    }


    void Packet::setInt16(int16 value) {

      if ((index + (int)sizeof(int16)) > length) return;

      memcpy(buffer + index,&value,sizeof(int16));

      index += sizeof(int16);

    }


    void Packet::setInt32(int32 value) {

      if ((index + (int)sizeof(int32)) > length) return;

      memcpy(buffer + index,&value,sizeof(int32));

      index += sizeof(int32);

    }


    void Packet::setData(const char *buf, long bufLen) {

      if ((index + bufLen) > length || buf == 0) return;

      memcpy(buffer + index,buf,bufLen);

      index += bufLen;

    }


    void Packet::setString(const std::string &buf) {

      if ((index + (int)buf.length()) > length) return;

      memcpy(buffer + index,buf.c_str(),buf.length());

      index += buf.length();

    }


    void Packet::printHex(const std::string &desc, int bytesPerLine, int cutoff) const {

      bool skip = false;

      char tmp[bytesPerLine];

      int i, j;

      uint8 c;

      std::string line;

      if (!desc.empty()) {
        printf("%s\n",desc.c_str());
      }

      if (cutoff == -1) cutoff = length;

      for(i = 0; i < length; i += bytesPerLine) {
        if (i > cutoff && i < (length - cutoff)) {
          if (!skip) printf("...\n");
          skip = true;
          continue;
        }
        line.erase();
        sprintf(tmp,"%08x: ",i);
        line.append(tmp);
        for(j = 0; j < bytesPerLine; j++) {
          if (i + j >= length) line.append("   ");
          else {
            c = buffer[i + j];
            sprintf(tmp,"%02x ",c);
            line.append(tmp);
          }
        }
        for(j = 0; j < bytesPerLine; j++) {
          if (i + j >= length) break;
          c = buffer[i + j];
          if (c >= 32 && c <= 127) sprintf(tmp,"%c",c);
          else sprintf(tmp,".");
          line.append(tmp);
        }
        printf("%s\n",line.c_str());
        if (j < bytesPerLine) break;
      }

    }


  }
}

