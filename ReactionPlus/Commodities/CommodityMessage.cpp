#include "CommodityMessage.hpp"

#include <proto/commodities.h>


namespace RAPlus {
  namespace Commodities {


    void CommodityMessage::setMessage(struct Message *message) {

      IMessage::setMessage(message);

      brokerMessage = reinterpret_cast<CxMsg *>(message);

    }


    uint32 CommodityMessage::getMessageID() {

      return(ICommodities->CxMsgID(brokerMessage));

    }


    uint32 CommodityMessage::getMessageType() {

      return(ICommodities->CxMsgType(brokerMessage));

    }


  }
}

