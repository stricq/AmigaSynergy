#ifndef RAPLUS_DOS_DOS_HPP
#define RAPLUS_DOS_DOS_HPP

#include <proto/dos.h>

#include "File.hpp"

#include <string>


namespace RAPlus {
  namespace DOS {

    class DOS {

      public:

        static void delay(uint32 ticks);

        static void deleteFile(std::string &file);
        static void deleteFile(File &file);

        static LONG ioError();

        static void renameFile(std::string &from, std::string &to);
        static void renameFile(File &from, File &to);

      private:

        DOS() { }
       ~DOS() { }

    };

  }
}

#endif // RAPLUS_DOS_DOS_HPP

