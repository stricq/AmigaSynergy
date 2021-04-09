#ifndef RAPLUS_DOS_WRITER_HPP
#define RAPLUS_DOS_WRITER_HPP

#include <string>


namespace RAPlus {
  namespace DOS {

    class Writer {

      public:

        virtual void close() = 0;
        virtual void flush() = 0;

        virtual void write(const char c);
        virtual void write(const char *buffer, long bufLen);
        virtual void write(const char *buffer, long bufLen, long offset, long size) = 0;

        virtual void write(const std::string &str);
        virtual void write(const std::string &str, long offset, long size);

      protected:

                 Writer();
        virtual ~Writer();

      private:

        char *buffer;

        static const int bufferSize = 1024;

    };

  }
}


#endif // RAPLUS_DOS_WRITER_HPP

