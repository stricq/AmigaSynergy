#ifndef RAPLUS_REACTION_SPACE_HPP
#define RAPLUS_REACTION_SPACE_HPP

#include "ReactionGadget.hpp"

#include <gadgets/Space.h>

#include <proto/Space.h>


#define  SpaceClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Space::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class Space : public ReactionGadget {

      public:

                 Space() { }
        virtual ~Space() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::SpaceType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_SPACE_HPP


