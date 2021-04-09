#include "IFF.hpp"


namespace RAPlus {
  namespace IFFParse {


    IFF::IFF() :
      iff(0),
      ci(0),
      cn(0) {

      if ((iff = IIFFParse->AllocIFF()) == 0) throw InvalidStateException("Could not initialize IFF Handle.");

    }


    IFF::~IFF() {

      if (ci) delete ci;

      if (iff) IIFFParse->FreeIFF(iff);

    }


    void IFF::collectionChunk(long type, long id) {

      long iffError = IIFFParse->CollectionChunk(iff,type,id);

      if (iffError != 0) throw Exception(iffErrorString(iffError).c_str());

    }


    void IFF::stopOnExit(long type, long id) {

      long iffError = IIFFParse->StopOnExit(iff,type,id);

      if (iffError != 0) throw Exception(iffErrorString(iffError).c_str());

    }


    void IFF::stopChunk(long type, long id) {

      long iffError = IIFFParse->StopChunk(iff,type,id);

      if (iffError != 0) throw Exception(iffErrorString(iffError));

    }


    long IFF::parseIFF(long mode) {

      return(IIFFParse->ParseIFF(iff,mode));

    }


    CollectionItem &IFF::findCollection(long type, long id) {

      if (ci) delete ci;

      ci = new CollectionItem(IIFFParse->FindCollection(iff,type,id));

      return(*ci);

    }


    ContextNode &IFF::currentChunk() {

      if (cn) delete cn;

      cn = new ContextNode(IIFFParse->CurrentChunk(iff));

      return(*cn);

    }


    void IFF::pushChunk(long type, long id, long size) {

      long iffError = IIFFParse->PushChunk(iff,type,id,size);

      if (iffError != 0) throw Exception(iffErrorString(iffError));

    }


    long IFF::writeChunkBytes(const APTR buf, long size) {

      long iffError = IIFFParse->WriteChunkBytes(iff,buf,size);

      if (iffError < 0) throw Exception(iffErrorString(iffError));

      return(iffError);

    }


    long IFF::readChunkBytes(APTR buf, long size) {

      long iffError = IIFFParse->ReadChunkBytes(iff,buf,size);

      if (iffError < 0) throw Exception(iffErrorString(iffError));

      return(iffError);

    }


    void IFF::popChunk() {

      long iffError = IIFFParse->PopChunk(iff);

      if (iffError != 0) throw Exception(iffErrorString(iffError));

    }


    const std::string IFF::iffErrorString(long error) {

      switch(error) {
        case IFFERR_EOF:        return("End of File.");
        case IFFERR_EOC:        return("End of Chunk.");
        case IFFERR_NOSCOPE:    return("No Scope.");
        case IFFERR_NOMEM:      return("No Memory.");
        case IFFERR_READ:       return("Read Error.");
        case IFFERR_WRITE:      return("Write Error.");
        case IFFERR_SEEK:       return("Seek Error.");
        case IFFERR_MANGLED:    return("Mangled IFF.");
        case IFFERR_SYNTAX:     return("Syntax Error.");
        case IFFERR_NOTIFF:     return("Not an IFF.");
        case IFFERR_NOHOOK:     return("No Hook Provided.");
        case IFF_RETURN2CLIENT: return("Normal Return to Client.");
      }

      return("Unknown Error Code.");

    }


  }
}

