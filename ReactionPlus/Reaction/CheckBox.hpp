#ifndef RAPLUS_REACTION_CHECKBOX_HPP
#define RAPLUS_REACTION_CHECKBOX_HPP

#include "ReactionGadget.hpp"

#include <gadgets/checkbox.h>

#include <proto/checkbox.h>

#ifdef CheckBox
#undef CheckBox
#endif

#define CheckBoxClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::CheckBox::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class CheckBox : public ReactionGadget {

      public:

                 CheckBox() { }
        virtual ~CheckBox() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::CheckBoxType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_CHECKBOX_HPP

