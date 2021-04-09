#include "File.hpp"

#include <proto/dos.h>
#include <proto/exec.h>

#include <stdio.h>


namespace RAPlus {
  namespace DOS {


    File::File(const std::string &file) :
      isfile(false),
      isdir(false),
      islink(false),
      exist(false),
      filesize(0),
      original(file) {

      examineFile();

    }


    File::File(const File &file) :
      isfile(false),
      isdir(false),
      islink(false),
      exist(false),
      filesize(0),
      original(file.getOriginal()) {

      examineFile();

    }


    File::File(const File *file) :
      isfile(false),
      isdir(false),
      islink(false),
      exist(false),
      filesize(0),
      original(file->getOriginal()) {

      examineFile();

    }


    long File::getFilesize() const {

      return(filesize);

    }


    std::string &File::getFilepath() const {

      return(filepath);

    }


    std::string &File::getFilename() const {

      return(filename);

    }


    std::string &File::getPathName() const {

      return(pathname);

    }


    std::string &File::getComment() const {

      return(comment);

    }


    std::string &File::getOriginal() const {

      return(original);

    }


    DateTime &File::getDateTime() const {

      return(dateTime);

    }


    void File::examineFile() {

      char *path;
      char *part;

      BPTR lock;

      LONG resultNameFromLock;
      LONG resultExamine;

      struct FileInfoBlock *fib;

      if (!(path = (char *)IExec->AllocVec(2048,MEMF_CLEAR))) throw OutOfMemoryException("Cannot allocate file path buffer.");

      if (!(fib = (struct FileInfoBlock *)IDOS->AllocDosObject(DOS_FIB,TAG_DONE))) {
        IExec->FreeVec(path);
        throw IOException("Unable to allocate FileInfoBlock for file.");
      }

      if (!(lock = IDOS->Lock(original.c_str(),ACCESS_READ))) {
        IDOS->FreeDosObject(DOS_FIB,fib);
        IExec->FreeVec(path);
        return;
      }

      exist = true;

      resultNameFromLock = IDOS->NameFromLock(lock,path,2048);

      resultExamine = IDOS->Examine(lock,fib);

      pathname = path;

      if (resultExamine != DOSFALSE) {
        filesize = fib->fib_Size;
        filename = fib->fib_FileName;
        comment  = fib->fib_Comment;
        dateTime = &fib->fib_Date;
        isfile = FIB_IS_FILE(fib);
        isdir  = FIB_IS_DRAWER(fib);
        islink = FIB_IS_LINK(fib);
      }

      if (resultNameFromLock != DOSFALSE) {
        part = (char *)IDOS->PathPart(path);
        if (*part == '/') *(part + 1) = '\0';
        else if (part == path) { }
        else *(part) = '\0';
        filepath = path;
      }

      if (path) IExec->FreeVec(path);

      IDOS->UnLock(lock);

      IDOS->FreeDosObject(DOS_FIB,fib);

      if (resultExamine == DOSFALSE) throw IOException("Cannot examine file.");

      if (resultNameFromLock == DOSFALSE) throw IOException("Cannot determine full path for file.");

    }


    void File::deleteFile() {

      if (original.empty()) throw InvalidStateException("No filename has been set.");

      IDOS->DeleteFile(pathname.c_str());

    }


    File &File::operator=(const File &rhs) {

      original = rhs.original;

      examineFile();

      return(*this);

    }


    File &File::operator=(const std::string &rhs) {

      original = rhs;

      examineFile();

      return(*this);

    }


  }
}

