#ifndef RAPLUS_PREFS_PREFS
#define RAPLUS_PREFS_PREFS

#include <prefs/prefhdr.h>

#include "IFFParse/IFF.hpp"


namespace RAPlus {
  namespace Prefs {

    class Prefs {

      public:

                 Prefs();
        virtual ~Prefs() { }

        virtual void setHeaderVersion(UBYTE ver) { header.ph_Version = ver; }
        virtual void setHeaderType(UBYTE type)   { header.ph_Type = type; }
        virtual void setHeaderFlags(ULONG flags) { header.ph_Flags = flags; }

        virtual UBYTE getHeaderVersion() { return(header.ph_Version); }
        virtual UBYTE getHeaderType()    { return(header.ph_Type); }
        virtual ULONG getHeaderFlags()   { return(header.ph_Flags); }

        virtual void writeIFFHeader(IFFParse::IFF &iff);

        virtual void readFromIFFCollection(IFFParse::CollectionItem &ci) = 0;
        virtual void writeToIFF(IFFParse::IFF &iff) = 0;
        virtual void prepareIFFCollection(IFFParse::IFF &iff) = 0;

        virtual IFFParse::CollectionItem &findIFFCollection(IFFParse::IFF &iff) = 0;

      private:

        struct ::PrefHeader header;

    };

  }
}

#endif // RAPLUS_PREFS_PREFS

