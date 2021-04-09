#ifndef RAPLUS_REACTION_BUTTON_HPP
#define RAPLUS_REACTION_BUTTON_HPP

#include "ReactionGadget.hpp"

#include <gadgets/button.h>

#include <proto/button.h>

#ifdef Button
#undef Button
#endif

#define ButtonClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Button::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class Button : public ReactionGadget {

      public:

                 Button() { }
        virtual ~Button() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::ButtonType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_BUTTON_HPP

