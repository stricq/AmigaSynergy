#include "Prefs.hpp"


namespace RAPlus {
  namespace Prefs {


    Prefs::Prefs() {

      header.ph_Version = 0;
      header.ph_Type = 0;
      header.ph_Flags = 0;

    }


    void Prefs::writeIFFHeader(IFFParse::IFF &iff) {

      iff.pushChunk(ID_PREF,ID_FORM,IFFSIZE_UNKNOWN);
      iff.pushChunk(ID_PREF,ID_PRHD,sizeof(header));
      iff.writeChunkBytes(&header,sizeof(header));
      iff.popChunk();

    }


  }
}

