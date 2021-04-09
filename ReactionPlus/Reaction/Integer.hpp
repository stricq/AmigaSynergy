#ifndef RAPLUS_REACTION_INTEGER_HPP
#define RAPLUS_REACTION_INTEGER_HPP

#include "ReactionGadget.hpp"

#include <gadgets/integer.h>

#include <proto/integer.h>

#define  IntegerClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Integer::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

   class Integer : public ReactionGadget {

     public:

                Integer() { }
       virtual ~Integer() { }

       static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::IntegerType); }

       virtual bool gadgetUpEvent();

     private:

       Object *newObject(struct TagItem *tagItem);

   };

  }
}

#endif  // RAPLUS_REACTION_INTEGER_HPP


