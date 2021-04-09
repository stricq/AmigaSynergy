#include "FileReader.hpp"

#include <proto/dos.h>
#include <proto/exec.h>


namespace RAPlus {
  namespace DOS {


    FileReader::FileReader(const File &file, long bufSize) :
      bufferSize(bufSize),
      filename(new File(file)),
      handle(0) {

      open();

    }


    FileReader::FileReader(const File *file, long bufSize) :
      bufferSize(bufSize),
      filename(new File(file)),
      handle(0) {

      open();

    }


    FileReader::FileReader(const std::string &file, long bufSize) :
      bufferSize(bufSize),
      filename(new File(file)),
      handle(0) {

      open();

    }


    FileReader::~FileReader() {

      close();

      delete filename;

    }


    void FileReader::open() {

      handle = IDOS->FOpen(filename->getPathName().c_str(),MODE_OLDFILE,bufferSize);

      if (handle == 0) {
        throw FileNotFoundException("Could not open the file.");
      }

    }


    void FileReader::close() {

      if (handle) IDOS->FClose(handle);

      handle = 0;

    }


    long FileReader::read(char *buffer, long bufLen, long offset, long size) {

      if (handle == 0)            throw IOException("File is not readable.");
      if (buffer == 0)            throw Exception("Buffer is NULL");
      if (offset < 0)             throw IndexRangeException("Offset is below 0",bufLen,offset);
      if (size < 0)               throw IndexRangeException("Size is below 0",bufLen,size);
      if (offset > bufLen)        throw IndexRangeException("Offset exceeds Buffer Length",bufLen,offset);
      if (offset + size > bufLen) throw IndexRangeException("Offset + Size exceeds Buffer Length",bufLen,offset + size);

      long actual = IDOS->FRead(handle,(buffer + offset),1,size);

      if (actual == -1 && IDOS->IoErr() != 0) throw IOException("IO Exception during read.");

      return(actual == 0 ? -1 : actual);

    }


    bool FileReader::ready() {

      return(handle != 0);

    }


  }
}

