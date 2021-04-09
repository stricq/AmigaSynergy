#ifndef RAPLUS_REACTION_FILEREQUEST_HPP
#define RAPLUS_REACTION_FILEREQUEST_HPP

#include "ReactionGadget.hpp"

#include <gadgets/getfile.h>

#include <proto/getfile.h>

#define FileRequestClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::FileRequest::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class FileRequest : public ReactionGadget {

      public:

                 FileRequest() { }
        virtual ~FileRequest() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::FileRequestType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_FILEREQUEST_HPP

