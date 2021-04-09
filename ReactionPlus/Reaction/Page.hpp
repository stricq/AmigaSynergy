#ifndef RAPLUS_REACTION_PAGE_HPP
#define RAPLUS_REACTION_PAGE_HPP

#include "ReactionGadget.hpp"

#include <gadgets/Layout.h>

#include <proto/Layout.h>


#define PageClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Page::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class Page : public ReactionGadget {

      public:

                 Page() { }
        virtual ~Page() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::PageType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_PAGE_HPP


