#include "FileWriter.hpp"
#include "File.hpp"

#include "FileNotFoundException.hpp"

#include "Exec/OutOfMemoryException.hpp"

#include <proto/dos.h>
#include <proto/exec.h>


namespace RAPlus {
  namespace DOS {


    FileWriter::FileWriter(const File &file, long bufSize) :
      bufferSize(bufSize),
      filename(new File(file)),
      handle(0) {

      open();

    }


    FileWriter::FileWriter(const File *file, long bufSize) :
      bufferSize(bufSize),
      filename(new File(file)),
      handle(0) {

      open();

    }


    FileWriter::FileWriter(const std::string &file, long bufSize) :
      bufferSize(bufSize),
      filename(new File(file)),
      handle(0) {

      open();

    }


    FileWriter::~FileWriter() {

      close();

      delete filename;

    }


    void FileWriter::open() {

      handle = IDOS->FOpen(filename->getPathName().c_str(),MODE_NEWFILE,bufferSize);

      if (handle == 0) throw FileNotFoundException("Could not open the file.");

    }


    void FileWriter::close() {

      if (handle != 0) IDOS->FClose(handle);

      handle = 0;

    }


    void FileWriter::flush() {

      if (handle == 0) throw IOException("File is not writable.");

      IDOS->FFlush(handle);

    }


    void FileWriter::write(char *buffer, long bufLen, long offset, long size) {

      if (handle == 0)            throw IOException("File is not writable.");
      if (buffer == 0)            throw Exception("Buffer is NULL");
      if (offset < 0)             throw IndexRangeException("Offset is below 0",bufLen,offset);
      if (size < 0)               throw IndexRangeException("Size is below 0",bufLen,size);
      if (offset > bufLen)        throw IndexRangeException("Offset exceeds Buffer Length",bufLen,offset);
      if (offset + size > bufLen) throw IndexRangeException("Offset + Size exceeds Buffer Length",bufLen,offset + size);

      long actual = IDOS->FWrite(handle,buffer + offset,1,size);

      if (actual == -1 && IDOS->IoErr() != 0) throw IOException("IO Exception during write.");

    }


  }
}

