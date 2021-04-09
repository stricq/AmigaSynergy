#include "Reader.hpp"


namespace RAPlus {
  namespace DOS {


    char Reader::read() {

      char *cb = new char[1];

      if (read(cb,1,0,1) == -1) return((char)-1);
      else return(cb[0]);

    }


    long Reader::read(char *buffer, long bufLen) {

      return(read(buffer,bufLen,0,bufLen));

    }


    bool Reader::ready() {

      return(false);

    }


  }
}

