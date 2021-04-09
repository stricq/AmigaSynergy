#ifndef RAPLUS_REACTION_RADIOBUTTON_HPP
#define RAPLUS_REACTION_RADIOBUTTON_HPP

#include "ReactionGadget.hpp"

#include <gadgets/radiobutton.h>

#include <libraries/gadtools.h>

#include <proto/radiobutton.h>

#ifdef RadioButton
#undef RadioButton
#endif

#define RadioButtonClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::RadioButton::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class RadioButton : public ReactionGadget {

      public:

                 RadioButton() { }
        virtual ~RadioButton() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::RadioButtonType); }

        uint16 getSelected();

        void setSelected(uint16 value);

        virtual bool gadgetUpEvent();

      private:

        static std::string getAttrError;

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_RADIOBUTTON_HPP

