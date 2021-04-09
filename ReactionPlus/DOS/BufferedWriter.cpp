#include "BufferedWriter.hpp"


namespace RAPlus {
  namespace DOS {


    BufferedWriter::BufferedWriter(Writer *writer, long bufferSize) :
      buffer(0),
      bufferSize(bufferSize),
      writer(writer) {

      if (bufferSize <= 0) throw IndexRangeException("Buffer size below 0.",0,bufferSize);

      buffer = new char[bufferSize];

      nChars = bufferSize;

      nextChar = 0;

    }


    BufferedWriter::BufferedWriter(Writer &writer, long bufferSize) :
      buffer(0),
      bufferSize(bufferSize),
      writer(&writer) {

      if (bufferSize <= 0) throw IndexRangeException("Buffer size below 0.",0,bufferSize);

      buffer = new char[bufferSize];

      nChars = bufferSize;

      nextChar = 0;

    }


    BufferedWriter::~BufferedWriter() {

      close();

    }


    void BufferedWriter::ensureOpen() {

      if (writer == 0) throw IOException("Stream closed.");

    }


    void BufferedWriter::flushBuffer() {

      ensureOpen();

      if (nextChar == 0) return;

      writer->write(buffer,bufferSize,0,nextChar);

      nextChar = 0;

    }


    void BufferedWriter::write(const char c) {

      ensureOpen();

      if (nextChar >= nChars) flushBuffer();

      buffer[nextChar++] = c;

    }


    void BufferedWriter::write(const char *buf, long bufLen, long offset, long size) {

      ensureOpen();

      if ((offset < 0) || (offset > bufLen) || (size < 0) || ((offset + size) > bufLen) || ((offset + size) < 0)) {
        throw IndexRangeException("Indexes out of range.",bufLen,0);
      }
      else if (size == 0) return;

      if (size >= nChars) {
        flushBuffer();
        writer->write(buf,bufLen,offset,size);
        return;
      }

      long b = offset;
      long t = offset + size;

      while(b < t) {
        long d = ((nChars - nextChar) < (t - b) ? (nChars - nextChar) : (t - b));
        memcpy(buffer + nextChar,buf + b,d);
        b += d;
        nextChar += d;
        if (nextChar >= nChars) flushBuffer();
      }

    }


    void BufferedWriter::writeLine(const std::string &str) {

      write(str);

      newLine();

    }


    void BufferedWriter::newLine() {

      write('\n');

    }


    void BufferedWriter::flush() {

      flushBuffer();

      writer->flush();

    }


    void BufferedWriter::close() {

      if (writer == 0) return;

      flushBuffer();

      writer->close();

      delete buffer;

      writer = 0;

      buffer = 0;

    }


  }
}

