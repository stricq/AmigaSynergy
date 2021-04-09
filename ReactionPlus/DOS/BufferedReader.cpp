#include "BufferedReader.hpp"

#include <proto/exec.h>


namespace RAPlus {
  namespace DOS {


    BufferedReader::BufferedReader(Reader *reader, long bufferSize) :
      skipLF(false),
      buffer(0),
      bufferSize(bufferSize),
      reader(reader) {

      if (bufferSize <= 0) throw IndexRangeException("Buffer size below 0.",0,bufferSize);

      buffer = new char[bufferSize];

      nextChar = nChars = 0;

    }


    BufferedReader::BufferedReader(Reader &reader, long bufferSize) :
      skipLF(false),
      buffer(0),
      bufferSize(bufferSize),
      reader(&reader) {

      if (bufferSize <= 0) throw IndexRangeException("Buffer size below 0.",0,bufferSize);

      buffer = new char[bufferSize];

      nextChar = nChars = 0;

    }


    BufferedReader::~BufferedReader() {

      close();

    }


    void BufferedReader::ensureOpen() {

      if (reader == 0) throw IOException("Stream closed.");

    }


    void BufferedReader::fill() {

      long n;

      do {
        n = reader->read(buffer,bufferSize,0,bufferSize);
      } while(n == 0);

      if (n > 0) {
        nChars = n;
        nextChar = 0;
      }

    }


    char BufferedReader::read() {

      ensureOpen();

      for(;;) {
        if (nextChar >= nChars) {
          fill();
          if (nextChar >= nChars) return((char)-1);
        }
        if (skipLF) {
          skipLF = false;
          if (buffer[nextChar] == '\n') {
            ++nextChar;
            continue;
          }
        }
        return(buffer[nextChar++]);
      }

    }


    long BufferedReader::read1(char *buf, long bufLen, long offset, long size) {

      if (nextChar >= nChars) {
        if (size >= bufferSize && !skipLF) return(reader->read(buf,bufLen,offset,size));
        fill();
      }

      if (nextChar >= nChars) return(-1);

      if (skipLF) {
        skipLF = false;
        if (buffer[nextChar] == '\n') {
          ++nextChar;
          if (nextChar >= nChars) fill();
          if (nextChar >= nChars) return(-1);
        }
      }

      long n = (size < (nChars - nextChar) ? size : (nChars - nextChar));

      memcpy(buf + offset,buffer + nextChar,n);

      nextChar += n;

      return(n);

    }


    long BufferedReader::read(char *buf, long bufLen, long offset, long size) {

      ensureOpen();

      if ((offset < 0) || (offset > bufLen) || (size < 0) || ((offset + size) > bufLen) || ((offset + size) < 0)) {
        throw IndexRangeException("Values out of range.",0,0);
      }
      else if (size == 0) return(0);

      long n = read1(buf,bufLen,offset,size);

      if (n <= 0) return(n);

      while((n < size) && reader->ready()) {
        long n1 = read1(buf,bufLen,offset + n,size - n);
        if (n1 <= 0) break;
        n += n1;
      }

      return(n);

    }


    bool BufferedReader::readLine(std::string &str, bool ignoreLF) {

      bool omitLF = ignoreLF || skipLF;

      long startChar;

      std::string *line = 0;

      ensureOpen();

      for(;;) {
        if (nextChar >= nChars) fill();
        if (nextChar >= nChars) {
          if (line != 0 && line->length() > 0) {
            str.assign(*line);
            delete line;
            return(true);
          }
          else {
            delete line;
            return(false);
          }
        }
        bool eol = false;
        char c = 0;
        int i;
        if (omitLF && (buffer[nextChar] == '\n')) ++nextChar;
        skipLF = omitLF = false;
        for(i = nextChar; i < nChars; ++i) {
          c = buffer[i];
          if (c == '\n' || c == '\r') {
            eol = true;
            break;
          }
        }
        startChar = nextChar;
        nextChar = i;
        if (eol) {
          if (line == 0) str.assign(std::string(buffer,startChar,i - startChar));
          else {
            line->append(std::string(buffer,startChar,i - startChar));
            str.assign(std::string(*line));
          }
          ++nextChar;
          if (c == '\r') skipLF = true;
          delete line;
          return(true);
        }
        if (line == 0) line = new std::string();
        line->append(std::string(buffer,startChar,i - startChar));
      }

    }


    bool BufferedReader::readLine(std::string &str) {

      return(readLine(str,false));

    }


    bool BufferedReader::ready() {

      ensureOpen();

      if (skipLF) {
        if (nextChar >= nChars && reader->ready()) fill();
        if (nextChar < nChars) {
          if (buffer[nextChar] == '\n') ++nextChar;
          skipLF = false;
        }
      }

      return((nextChar < nChars) || reader->ready());

    }


    void BufferedReader::close() {

      if (reader == 0) return;

      reader->close();

      delete buffer;

      reader = 0;

      buffer = 0;

    }


  }
}

