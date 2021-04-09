#include "DOS.hpp"


namespace RAPlus {
  namespace DOS {


    void DOS::delay(uint32 ticks) {

      IDOS->Delay(ticks);

    }


    void DOS::deleteFile(File &file) {

      deleteFile(file.getPathName());

    }


    void DOS::deleteFile(std::string &file) {

      IDOS->DeleteFile((char *)file.c_str());

    }


    LONG DOS::ioError() {

      return(IDOS->IoErr());

    }


    void DOS::renameFile(File &from, File &to) {

      renameFile(from.getPathName(),to.getPathName());

    }


    void DOS::renameFile(std::string &from, std::string &to) {

      IDOS->Rename((char *)from.c_str(),(char *)to.c_str());

    }


  }
}

