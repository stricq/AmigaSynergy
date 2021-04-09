#ifndef RAPLUS_REACTION_CLICKTAB_HPP
#define RAPLUS_REACTION_CLICKTAB_HPP

#include "ReactionGadget.hpp"

#include <gadgets/ClickTab.h>

#include <proto/ClickTab.h>

#define ClickTabClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::ClickTab::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class ClickTab : public ReactionGadget {

      public:

                 ClickTab() { }
        virtual ~ClickTab() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::ClickTabType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_CLICKTAB_HPP


