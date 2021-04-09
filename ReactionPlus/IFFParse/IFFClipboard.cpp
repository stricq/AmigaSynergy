#include "IFFClipboard.hpp"


namespace RAPlus {
  namespace IFFParse {


    IFFClipboard::IFFClipboard(uint32 clipUnit) :
      open(false),
      clipUnit(clipUnit) {
    }


    IFFClipboard::~IFFClipboard() {

      closeIFF();

    }


    void IFFClipboard::openIFF(IFFOpenMode mode) {

      long iffMode = (mode == MODE_Read ? IFFF_READ : IFFF_WRITE);

      long iffError;

      openMode = mode;

      IIFFParse->InitIFFasClip(iff);

      iff->iff_Stream = (uint32)IIFFParse->OpenClipboard(clipUnit);

      if (iff->iff_Stream == 0) {
        throw IOException("Could not open Clipboard.");
      }

      if ((iffError = IIFFParse->OpenIFF(iff,iffMode)) != 0) {
        IIFFParse->CloseClipboard((struct ClipboardHandle *)iff->iff_Stream);
        throw Exception(iffErrorString(iffError).c_str());
      }

      open = true;

    }


    void IFFClipboard::closeIFF() {

      if (!open) return;

      IIFFParse->CloseIFF(iff);

      IIFFParse->CloseClipboard((struct ClipboardHandle *)iff->iff_Stream);

      open = false;

    }


    void IFFClipboard::setText(const std::string &clip) {

      if (open) throw InvalidStateException("The Clipboard is already open.");

      openIFF(MODE_Write);

      pushChunk(ID_FTXT,ID_FORM,IFFSIZE_UNKNOWN);
      pushChunk(0,ID_CHRS,IFFSIZE_UNKNOWN);

      writeChunkBytes((char *)clip.c_str(),clip.length());

      popChunk();
      popChunk();

      closeIFF();

    }


    void IFFClipboard::getText(std::string &clip) {

      char *buffer = 0;

      uint32 textLen = 0;

      if (open) throw InvalidStateException("The Clipboard is already open.");

      openIFF(MODE_Read);

      stopChunk(ID_FTXT,ID_CHRS);

      while(true) {
        long error = parseIFF(IFFPARSE_SCAN);
        if (error == IFFERR_EOC) continue;
        if (error == 0) {
          ContextNode context = currentChunk();
          if (context.getType() == ID_FTXT && context.getID() == ID_CHRS) {
            textLen = context.getSize();
            buffer = new char[textLen];
            readChunkBytes(buffer,textLen);
          }
        }
        else break;
      }

      closeIFF();

      if (textLen > 0 && buffer != 0) clip.assign(buffer,textLen);
      else clip.resize(0);

      delete buffer;

    }


  }
}

