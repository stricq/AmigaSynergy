#include "IFFDOS.hpp"


namespace RAPlus {
  namespace IFFParse {


    IFFDOS::IFFDOS(const std::string &iffFile) :
      iffFilename(iffFile) {
    }


    IFFDOS::~IFFDOS() {

      closeIFF();

    }


    void IFFDOS::openIFF(IFFOpenMode mode) {

      if (iffFilename.empty()) throw InvalidStateException("No filename specified to open.");

      long dosMode = (mode == MODE_Read ? MODE_OLDFILE : MODE_NEWFILE);
      long iffMode = (mode == MODE_Read ? IFFF_READ : IFFF_WRITE);

      long iffError;

      iff->iff_Stream = IDOS->Open((char *)iffFilename.c_str(),dosMode);

      if (iff->iff_Stream == 0) {
        if (mode == MODE_Read) throw FileNotFoundException("IFF File not found in open.");
        else throw IOException("Could not create a new IFF File.");
      }

      IIFFParse->InitIFFasDOS(iff);

      if ((iffError = IIFFParse->OpenIFF(iff,iffMode)) != 0) {
        IDOS->Close(iff->iff_Stream);
        throw Exception(iffErrorString(iffError).c_str());
      }

    }


    void IFFDOS::closeIFF() {

      if (iff == 0) return;

      IIFFParse->CloseIFF(iff);

      IDOS->Close(iff->iff_Stream);

      iff = 0;

    }


  }
}

