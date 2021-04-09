#include "Writer.hpp"


namespace RAPlus {
  namespace DOS {


    Writer::Writer() : buffer(0) { }


    Writer::~Writer() {

      delete buffer;

    }


    void Writer::write(char c) {

      if (buffer == 0) buffer = new char[bufferSize];

      buffer[0] = c;

      write(buffer,bufferSize,0,1);

    }


    void Writer::write(const char *buffer, long bufLen) {

      write(buffer,bufLen,0,bufLen);

    }


    void Writer::write(const std::string &str) {

      write(str.c_str(),str.length(),0,str.length());

    }


    void Writer::write(const std::string &str, long offset, long size) {

      write(std::string(str,offset,size));

    }


  }
}

