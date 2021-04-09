#ifndef RAPLUS_REACTION_CHOOSER_HPP
#define RAPLUS_REACTION_CHOOSER_HPP

#include "ReactionGadget.hpp"

#include <gadgets/Chooser.h>

#include <proto/Chooser.h>

#ifdef Chooser
#undef Chooser
#endif

#define ChooserClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Chooser::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class Chooser : public ReactionGadget {

      public:

                 Chooser() { }
        virtual ~Chooser() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::ChooserType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_CHOOSER_HPP

