#ifndef RAPLUS_REACTION_LAYOUT_HPP
#define RAPLUS_REACTION_LAYOUT_HPP

#include "ReactionGadget.hpp"

#include <gadgets/layout.h>

#include <proto/layout.h>


#define  LayoutClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Layout::getGadgetType()),(this),(cl)
#define HLayoutClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Layout::getGadgetType()),(this),(cl)
#define VLayoutClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Layout::getGadgetType()),(this),(cl),LAYOUT_Orientation,LAYOUT_ORIENT_VERT


namespace RAPlus {
  namespace Reaction {

    class Layout : public ReactionGadget {

      public:

                 Layout() { }
        virtual ~Layout() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::LayoutType); }

        virtual bool gadgetUpEvent();

        void setAlignLabels(ReactionGadget &gadget);

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_LAYOUT_HPP

