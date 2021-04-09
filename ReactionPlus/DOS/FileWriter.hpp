#ifndef RAPLUS_DOS_FILEWRITER_HPP
#define RAPLUS_DOS_FILEWRITER_HPP

#include <dos/dos.h>

#include "Writer.hpp"
#include "File.hpp"

#include "FileNotFoundException.hpp"
#include "IndexRangeException.hpp"

#include "Exec/OutOfMemoryException.hpp"

#include <string>


namespace RAPlus {
  namespace DOS {

    class FileWriter : public Writer {

      public:

                 FileWriter(const File &file, long bufSize = 8192);
                 FileWriter(const File *file, long bufSize = 8192);
                 FileWriter(const std::string &file, long bufSize = 8192);
        virtual ~FileWriter();

        virtual void close();
        virtual void flush();

        virtual void write(char *buffer, long bufLen, long offset, long size);

      private:

        long bufferSize;

        File *filename;

        BPTR handle;

        void open();

    };

  }
}

#endif // RAPLUS_DOS_FILEWRITER_HPP

