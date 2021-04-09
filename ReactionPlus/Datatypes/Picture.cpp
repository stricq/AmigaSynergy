#include "Picture.hpp"

#include <stdio.h>


namespace RAPlus {
  namespace Datatypes {


    Picture::~Picture() {

      if (bmh) delete bmh;

    }


    void Picture::openDatatype() {

      openDatatype(filename.getPathName());

    }


    void Picture::openDatatype(DOS::File &file) {

      openDatatype(file.getPathName());

    }


    void Picture::openDatatype(std::string &file) {

      if (bmh) {
        delete bmh;
        bmh = 0;
      }

      if (dty) {
        delete dty;
        dty = 0;
      }

      if (!(dto = IDataTypes->NewDTObject((char *)file.c_str(),DTA_GroupID,GID_PICTURE,PDTA_DestMode,PMODE_V43,PDTA_Remap,FALSE,TAG_DONE))) {
        throw IOException("Could not create DataType Object.",DOS::DOS::ioError());
      }

    }


    void Picture::doProcLayout() {

      IDataTypes->DoDTMethod(dto,0,0,DTM_PROCLAYOUT,NULL,1);

    }


    void Picture::doScale(ULONG width, ULONG height) {

      IDataTypes->SetDTAttrs(dto,0,0,PDTA_ScaleQuality,1,TAG_DONE);

      IIntuition->IDoMethod(dto,PDTM_SCALE,width,height,0);

    }


    void Picture::doSave(std::string &file) {

      BPTR handle;

      ULONG error = 1;

      if ((handle = IDOS->Open((char *)file.c_str(),MODE_NEWFILE)) != 0) {
        error = IDataTypes->DoDTMethod(dto,0,0,DTM_WRITE,0,handle,DTWM_RAW,0);
        IDOS->Close(handle);
      }

      if (error == 0) throw IOException("Could not save the datatype object.",DOS::DOS::ioError());

    }


    BitmapHeader &Picture::getBitmapHeader() {

      if (bmh) {
        delete bmh;
        bmh = 0;
      }

      struct BitMapHeader *bitmapHeader;

      if (IDataTypes->GetDTAttrs(dto,PDTA_BitMapHeader,&bitmapHeader,TAG_DONE) < 1) throw Exception("Could not get BitMapHeader struct.");

      bmh = new BitmapHeader(bitmapHeader);

      return(*bmh);

    }


    std::string &Picture::getErrorString(LONG error) {

      static std::string errStr;

      switch(error) {
        case ERROR_REQUIRED_ARG_MISSING:
          errStr = "Required Argument Missing";
          break;
        case ERROR_BAD_NUMBER:
          errStr = "Invalid Group ID";
          break;
        case ERROR_OBJECT_WRONG_TYPE:
          errStr = "Object Is Wrong Type";
          break;
        case ERROR_NO_FREE_STORE:
          errStr = "Out Of Memory";
          break;
        case DTERROR_UNKNOWN_DATATYPE:
          errStr = "Could Not Open Datatype Class Library";
          break;
        case DTERROR_COULDNT_OPEN:
          errStr = "Could Not Open Object";
          break;
        case ERROR_NOT_IMPLEMENTED:
          errStr = "Unknown Handle Type";
          break;
        default:
          errStr = "Unknown Error";
      }

      return(errStr);

    }


  }
}

