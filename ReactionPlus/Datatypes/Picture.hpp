#ifndef RAPLUS_DATATYPES_PICTURE_HPP
#define RAPLUS_DATATYPES_PICTURE_HPP

#include "Datatypes.hpp"

#include "DOS/DOS.hpp"
#include "DOS/IOException.hpp"

#include "Exec/OutOfMemoryException.hpp"

#include "InvalidArgumentException.hpp"
#include "InvalidStateException.hpp"

#include <datatypes/pictureclass.h>

#include <proto/intuition.h>

#include <string>


namespace RAPlus {
  namespace Datatypes {

    class BitmapHeader {

      public:

        BitmapHeader(struct BitMapHeader *bmh) : bitmapHeader(bmh) { if (!bmh) throw InvalidStateException("Invalid BitMapHeader."); }
        BitmapHeader() : bitmapHeader(0) { }
       ~BitmapHeader() { }

        UWORD getWidth()  { return(bitmapHeader->bmh_Width); }
        UWORD getHeight() { return(bitmapHeader->bmh_Height); }
        UBYTE getDepth()  { return(bitmapHeader->bmh_Depth); }

        void setBitmapHeader(struct BitMapHeader *bmh) { if (!(bitmapHeader = bmh)) throw InvalidStateException("Invalid BitMapHeader."); }

      private:

        struct BitMapHeader *bitmapHeader;

    };


    class Picture : public Datatypes {

      public:

        Picture(DOS::File &file) : Datatypes(file), bmh(0) { }
        Picture(std::string &file) : Datatypes(file), bmh(0) { }
       ~Picture();

        void openDatatype();
        void openDatatype(DOS::File &file);
        void openDatatype(std::string &file);

        void doProcLayout();
        void doScale(ULONG width, ULONG height);
        void doSave(std::string &file);

        BitmapHeader &getBitmapHeader();

        static std::string &getErrorString(LONG error);

      private:

        BitmapHeader *bmh;

    };

  }
}

#endif // RAPLUS_DATATYPES_PICTURE_HPP

