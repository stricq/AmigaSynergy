#ifndef REACTIONPLUS_COMMODITIES_COMMODITYMESSAGE_HPP
#define REACTIONPLUS_COMMODITIES_COMMODITYMESSAGE_HPP

#include <libraries/commodities.h>

#include "Exec/MessagePort.hpp"


namespace RAPlus {
  namespace Commodities {

    class CommodityMessage : public Exec::IMessage {

      public:

                 CommodityMessage() { }
        virtual ~CommodityMessage() { }

        Exec::IMessageType getType() { return(type); }

        Exec::IMessage *clone() { return(new CommodityMessage(brokerMessage)); }

        void setMessage(struct Message *message);

        uint32 getMessageID();
        uint32 getMessageType();

      private:

        CommodityMessage(CxMsg *brokerMsg) : brokerMessage(brokerMsg) { }

        static const Exec::IMessageType type = 0;

        CxMsg *brokerMessage;

    };

  }
}

#endif // REACTIONPLUS_COMMODITIES_COMMODITYMESSAGE_HPP

