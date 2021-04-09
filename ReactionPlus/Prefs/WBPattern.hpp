#ifndef RAPLUS_PREFS_WBPATTERN
#define RAPLUS_PREFS_WBPATTERN

#include <prefs/wbpattern.h>

#include "Prefs.hpp"

#include "InvalidStateException.hpp"

#include "DOS/File.hpp"

#include <string>


namespace RAPlus {
  namespace Prefs {

    class WBPattern : public Prefs {

      public:

                 WBPattern();
                 WBPattern(IFFParse::CollectionItem &ci);
        virtual ~WBPattern() { }

        virtual void setWhich(UWORD which) { pattern.wbp_Which = which; }
        virtual void setFlags(UWORD flags) { pattern.wbp_Flags = flags; }
        virtual void setRevision(BYTE rev) { pattern.wbp_Revision = rev; }

        virtual UWORD getWhich()    { return(pattern.wbp_Which); }
        virtual UWORD getFlags()    { return(pattern.wbp_Flags); }
        virtual BYTE  getRevision() { return(pattern.wbp_Revision); }

        virtual void readFromIFFCollection(IFFParse::CollectionItem &ci);
        virtual void writeToIFF(IFFParse::IFF &iff);
        virtual void prepareIFFCollection(IFFParse::IFF &iff);

        virtual IFFParse::CollectionItem &findIFFCollection(IFFParse::IFF &iff);

        virtual DOS::File &getImageName() { return(imageName); }

        virtual void  setImageName(DOS::File &image)   { imageName = image; }
        virtual void  setImageName(std::string &image) { imageName = image; }

      private:

        DOS::File imageName;

        struct ::WBPatternPrefs pattern;

    };

  }
}

#endif // RAPLUS_PREFS_WBPATTERN

