#ifndef RAPLUS_DOS_BUFFEREDWRITER_HPP
#define RAPLUS_DOS_BUFFEREDWRITER_HPP

#include "Writer.hpp"

#include "IOException.hpp"
#include "IndexRangeException.hpp"

#include <string>


namespace RAPlus {
  namespace DOS {

    class BufferedWriter : public Writer {

      public:

                 BufferedWriter(Writer *writer, long bufferSize = 8192);
                 BufferedWriter(Writer &writer, long bufferSize = 8192);
        virtual ~BufferedWriter();

        virtual void close();
        virtual void flush();

        virtual void newLine();

        using Writer::write;

        virtual void write(const char c);
        virtual void write(const char *buffer, long bufLen, long offset, long size);

        virtual void writeLine(const std::string &str);

      private:

        char *buffer;

        long bufferSize;

        long nChars;
        long nextChar;

        Writer *writer;

        void ensureOpen();
        void flushBuffer();

    };

  }
}


#endif // RAPLUS_DOS_BUFFEREDWRITER_HPP

