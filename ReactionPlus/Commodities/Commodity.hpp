#ifndef REACTIONPLUS_COMMODITIES_COMMODITY_HPP
#define REACTIONPLUS_COMMODITIES_COMMODITY_HPP

#include "CommodityException.hpp"
#include "CommodityMessage.hpp"

#include "Exec/MessagePort.hpp"
#include "Exec/SignalEvents.hpp"

#include <libraries/commodities.h>

#include <proto/commodities.h>

#include <map>
#include <string>


namespace RAPlus {
  namespace Commodities {

    class ICommodityEvent { };

    typedef bool (ICommodityEvent::*CommodityEventMethod)();


    class Commodity : public Exec::ISignalEvents {

      public:

        static Commodity *instance(const std::string &name, int8 priority = 0);

                 Commodity(const std::string &name, int8 priority);
        virtual ~Commodity();

        uint32 getSignal() { return(msgPort.getSignal()); }

        bool isEnabled() const { return(enabled); }

        void setName(const std::string &name);
        void setTitle(const std::string &title);
        void setDescription(const std::string &description);

        void setPriority(int8 priority) { broker.nb_Pri = priority; }

        void isUnique(bool unique) { broker.nb_Unique = (unique ? NBU_UNIQUE | NBU_NOTIFY : NBU_DUPLICATE); }
        void hasGUI(bool hasGUI)   { broker.nb_Flags  = (hasGUI ? COF_SHOW_HIDE : 0 ); }

        bool doEvents(uint32 signals);

        void enable();
        void disable();

        void     onEnable(ICommodityEvent *cls, CommodityEventMethod func) { addListener(CXEnable,cls,func); }
        void    onDisable(ICommodityEvent *cls, CommodityEventMethod func) { addListener(CXDisable,cls,func); }
        void     onAppear(ICommodityEvent *cls, CommodityEventMethod func) { addListener(CXAppear,cls,func); }
        void  onDisappear(ICommodityEvent *cls, CommodityEventMethod func) { addListener(CXDisappear,cls,func); }
        void onListChange(ICommodityEvent *cls, CommodityEventMethod func) { addListener(CXListChange,cls,func); }
        void     onUnique(ICommodityEvent *cls, CommodityEventMethod func) { addListener(CXUnique,cls,func); }
        void       onKill(ICommodityEvent *cls, CommodityEventMethod func) { addListener(CXKill,cls,func); }

      private:

        enum EventType { CXEnable, CXDisable, CXAppear, CXDisappear, CXListChange, CXUnique, CXKill };

        void closeLibrary();

        void addListener(EventType event, ICommodityEvent *cls, CommodityEventMethod func);

        bool fireEvent(EventType event);

        static Commodity *commodityInstance;

        bool enabled;

        class Listener {

          public:

            CommodityEventMethod eventMethod;
            ICommodityEvent     *eventClass;

        };

        std::map<EventType, Listener *> listenerList;

        std::string brokerName;
        std::string brokerTitle;
        std::string brokerDescription;

        CxObj *brokerObject;

        struct NewBroker broker;

        Exec::MessagePort msgPort;

    };

  }
}

#endif // REACTIONPLUS_COMMODITIES_COMMODITY_HPP

