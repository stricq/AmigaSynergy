#ifndef RAPLUS_DATATYPES_DATATYPES_HPP
#define RAPLUS_DATATYPES_DATATYPES_HPP

#include "DOS/DOS.hpp"
#include "DOS/File.hpp"

#include "InvalidStateException.hpp"

#include <intuition/classusr.h>

#include <proto/datatypes.h>

#include <string>


namespace RAPlus {
  namespace Datatypes {

    class Datatype {

      public:

        Datatype(struct DataType *dty) : dataType(dty) { if (!dty) throw InvalidStateException("Invalid Datatype."); }
        Datatype() : dataType(0) { }
       ~Datatype() { }

        std::string getName() { return(std::string(dataType->dtn_Header->dth_Name)); }

        void setDatatype(struct DataType *dty) { if (!(dataType = dty)) throw InvalidStateException("Invalid Datatype."); }

      private:

        struct ::DataType *dataType;

    };


    class Datatypes {

      public:

        virtual Datatype &getDatatype();

        virtual void closeDatatype();

      protected:

                 Datatypes(DOS::File &file) : filename(file), dto(0), dty(0) { }
                 Datatypes(std::string &file) : filename(file), dto(0), dty(0) { }
        virtual ~Datatypes();

        virtual void openDatatype() = 0;
        virtual void openDatatype(DOS::File &file) = 0;
        virtual void openDatatype(std::string &file) = 0;

        DOS::File filename;

        Object *dto;

        Datatype *dty;

    };

  }
}

#endif // RAPLUS_DATATYPES_DATATYPES_HPP

