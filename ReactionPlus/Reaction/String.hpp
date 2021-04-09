#ifndef RAPLUS_REACTION_STRING_HPP
#define RAPLUS_REACTION_STRING_HPP

#include "ReactionGadget.hpp"

#include <gadgets/string.h>

#include <proto/string.h>

#ifdef String
#undef String
#endif

#define  StringClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::String::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class String : public ReactionGadget {

      public:

                 String() { }
        virtual ~String() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::StringType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_STRING_HPP


