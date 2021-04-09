#ifndef REACTIONPLUS_EXEC_IOREQUEST_HPP
#define REACTIONPLUS_EXEC_IOREQUEST_HPP

#include <exec/io.h>

#include "IOBase.hpp"


namespace RAPlus {
  namespace Exec {

    class IORequest : public IOBase {

      public:

                 IORequest() : IOBase(sizeof(::IORequest)) { }
        virtual ~IORequest() { }

      private:

    };

  }
}


#endif // REACTIONPLUS_EXEC_IOREQUEST_HPP

