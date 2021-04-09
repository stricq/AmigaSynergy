#include "WBPattern.hpp"


namespace RAPlus {
  namespace Prefs {


    WBPattern::WBPattern() :
      imageName("") {

      memset(&pattern,0,sizeof(struct ::WBPatternPrefs));

    }


    WBPattern::WBPattern(IFFParse::CollectionItem &ci) :
      imageName("") {

      readFromIFFCollection(ci);

    }


    void WBPattern::writeToIFF(IFFParse::IFF &iff) {

      char *str = 0;
      int   len = 0;

      try {
        str = (char *)imageName.getPathName().c_str();
        len = imageName.getPathName().length();
      }
      catch(Exception e) { }

      pattern.wbp_DataLength = len;

      iff.pushChunk(ID_PREF,ID_PTRN,sizeof(struct ::WBPatternPrefs) + len);
      iff.writeChunkBytes(&pattern,sizeof(struct ::WBPatternPrefs));
      iff.writeChunkBytes(str,len);
      iff.popChunk();

    }


    void WBPattern::readFromIFFCollection(IFFParse::CollectionItem &ci) {

      std::string str;

      struct ::WBPatternPrefs *prefs = (struct ::WBPatternPrefs *)ci.getData();

      if (ci.getSize() < (LONG)sizeof(struct ::WBPatternPrefs)) throw InvalidStateException("Data length too small for WBPatternPrefs.");

      memcpy(&pattern,prefs,sizeof(struct ::WBPatternPrefs));

      for(int i = 0; i < prefs->wbp_DataLength; i++) str += *((char *)(prefs + 1) + i);

      imageName = str;

    }


    void WBPattern::prepareIFFCollection(IFFParse::IFF &iff) {

      iff.collectionChunk(ID_PREF,ID_PTRN);
      iff.stopOnExit(ID_PREF,ID_FORM);

    }


    IFFParse::CollectionItem &WBPattern::findIFFCollection(IFFParse::IFF &iff) {

      return(iff.findCollection(ID_PREF,ID_PTRN));

    }


  }
}

