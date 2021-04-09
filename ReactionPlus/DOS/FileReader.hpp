#ifndef RAPLUS_DOS_FILEREADER_HPP
#define RAPLUS_DOS_FILEREADER_HPP

#include <dos/dos.h>

#include "Reader.hpp"
#include "File.hpp"

#include "FileNotFoundException.hpp"
#include "IndexRangeException.hpp"

#include "Exec/OutOfMemoryException.hpp"

#include <string>


namespace RAPlus {
  namespace DOS {

    class FileReader : public Reader {

      public:

                 FileReader(const File &file, long bufSize = 8192);
                 FileReader(const File *file, long bufSize = 8192);
                 FileReader(const std::string &file, long bufSize = 8192);
        virtual ~FileReader();

        virtual void close();

        virtual long read(char *buffer, long bufLen, long offset, long size);

        virtual bool ready();

      private:

        long bufferSize;

        File *filename;

        BPTR handle;

        void open();

    };

  }
}

#endif // RAPLUS_DOS_FILEREADER_HPP

