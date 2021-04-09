#include "Datatypes.hpp"


namespace RAPlus {
  namespace Datatypes {


    Datatypes::~Datatypes() {

      closeDatatype();

    }


    Datatype &Datatypes::getDatatype() {

      if (dty) return(*dty);

      struct DataType *dataType;

      if (IDataTypes->GetDTAttrs(dto,DTA_DataType,&dataType,TAG_DONE) < 1) throw Exception("Could not get DataType struct.");

      dty = new Datatype(dataType);

      return(*dty);

    }


    void Datatypes::closeDatatype() {

      if (dty) delete dty;

      if (dto) IDataTypes->DisposeDTObject(dto);

      dty = 0;
      dto = 0;

    }


  }
}

