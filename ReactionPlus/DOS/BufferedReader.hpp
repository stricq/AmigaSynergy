#ifndef RAPLUS_DOS_BUFFEREDREADER_HPP
#define RAPLUS_DOS_BUFFEREDREADER_HPP

#include "Reader.hpp"

#include "IOException.hpp"
#include "IndexRangeException.hpp"

#include <string>


namespace RAPlus {
  namespace DOS {

    class BufferedReader : public Reader {

      public:

                 BufferedReader(Reader *reader, long bufferSize = 8192);
                 BufferedReader(Reader &reader, long bufferSize = 8192);
        virtual ~BufferedReader();

        virtual void close();

        using Reader::read;

        virtual char read();
        virtual long read(char *buffer, long bufLen, long offset, long size);

        virtual bool readLine(std::string &str);

        virtual bool ready();

      private:

        bool skipLF;

        char *buffer;

        long bufferSize;

        long nextChar;
        long nChars;

        Reader *reader;

        void ensureOpen();
        void fill();
        long read1(char *buf, long bufLen, long offset, long size);

        bool readLine(std::string &str, bool ignoreLF);

    };

  }
}

#endif // RAPLUS_DOS_BUFFEREDREADER_HPP

