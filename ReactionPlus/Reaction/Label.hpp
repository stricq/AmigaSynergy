#ifndef RAPLUS_REACTION_LABEL_HPP
#define RAPLUS_REACTION_LABEL_HPP

#include "ReactionImage.hpp"

#include <images/label.h>

#include <proto/label.h>

#ifdef Label
#undef Label
#endif

#define  LabelClass(cl) RAPlus::Reaction::ReactionImage::newObject((RAPlus::Reaction::Label::getImageType()),(cl)


namespace RAPlus {
  namespace Reaction {

    class Label : public ReactionImage {

      public:

                 Label() { }
        virtual ~Label() { }

        static ReactionImage::ImageType getImageType() { return(ReactionImage::LabelType); }

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_LABEL_HPP


