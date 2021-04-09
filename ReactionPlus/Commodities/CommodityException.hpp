#ifndef REACTIONPLUS_COMMODITIES_COMMODITYEXCEPTION_HPP
#define REACTIONPLUS_COMMODITIES_COMMODITYEXCEPTION_HPP

#include "Exception.hpp"

#include <string>


namespace RAPlus {


  class CommodityException : public Exception {

    public:

      CommodityException(const std::string &msg) : Exception(msg) { }
     ~CommodityException() { }

  };


  class UniqueCommodityException { };


}

#endif // REACTIONPLUS_COMMODITIES_COMMODITYEXCEPTION_HPP

