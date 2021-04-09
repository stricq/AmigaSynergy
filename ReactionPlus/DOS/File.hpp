#ifndef REACTIONPLUS_DOS_FILE_HPP
#define REACTIONPLUS_DOS_FILE_HPP

#include <dos/dos.h>

#include <string>

#include "DateTime.hpp"

#include "IOException.hpp"
#include "FileNotFoundException.hpp"
#include "InvalidStateException.hpp"
#include "Exec/OutOfMemoryException.hpp"



namespace RAPlus {
  namespace DOS {

    class File {

      public:

        File(const std::string &file);
        File(const File &file);
        File(const File *file);
       ~File() { }

        bool isFile() { return(isfile); }
        bool isDir()  { return(isdir); }
        bool isLink() { return(islink); }
        bool exists() { return(exist); }

        std::string &getOriginal() const;  // Returns whatever was passed in, could be a full or partial path or just a filename
        std::string &getFilename() const;  // Returns just the filename
        std::string &getFilepath() const;  // Returns the full path of the file, ending in either ':' or '/'
        std::string &getPathName() const;  // Returns the full path and filename
        std::string &getComment() const;

        DateTime &getDateTime() const;

        long getFilesize() const;

        void deleteFile();

        File &operator=(const File &rhs);
        File &operator=(const std::string &rhs);

      private:

        void examineFile();

        bool isfile;
        bool isdir;
        bool islink;
        bool exist;

        long filesize;

        mutable std::string original;

        mutable std::string filepath;
        mutable std::string filename;
        mutable std::string pathname;
        mutable std::string comment;

        mutable DateTime dateTime;

    };

  }
}

#endif // REACTIONPLUS_DOS_FILE_HPP

