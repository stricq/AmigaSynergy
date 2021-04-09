#ifndef RAPLUS_SOCKETS_PACKET_HPP
#define RAPLUS_SOCKETS_PACKET_HPP

#include <exec/types.h>

#include "Socket.hpp"
#include "SocketReader.hpp"
#include "SocketWriter.hpp"

#include <string.h>

#include <string>


namespace RAPlus {
  namespace Sockets {

    class Packet {

      public:

                 Packet() : buffer(0), length(0) { }
        virtual ~Packet();

        virtual void readPacket(Sockets::Socket *socket);
        virtual void writePacket(Sockets::Socket *socket);

        long getLength() const { return(length); }

        int8  getInt8();
        int16 getInt16();
        int32 getInt32();

        void getData(char *buf, long bufLen);

        std::string getString(long bufLen);

        void setBuffer(long bufLen);

        void setInt8(int8 value);
        void setInt16(int16 value);
        void setInt32(int32 value);

        void setData(const char *buf, long bufLen);

        void setString(const std::string &buf);

        void resetIndex(int32 idx = 0) { index = idx; }

        void printHex(const std::string &desc, int bytesPerLine = 16, int cutoff = -1) const;

      private:

        char *buffer;

        int32 length;
        int32 index;

    };

  }
}

#endif // RAPLUS_SOCKETS_PACKET_HPP

