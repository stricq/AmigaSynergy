#ifndef RAPLUS_REACTION_REACTIONIMAGE_HPP
#define RAPLUS_REACTION_REACTIONIMAGE_HPP

#include <intuition/classusr.h>

#include <proto/intuition.h>

#include <reaction/reaction_macros.h>

#define BOOLP(b) (b ? TRUE : FALSE)

#define Get(obj,attr,store) IIntuition->GetAttr((attr),(obj),(uint32 *)(store))
#define Set(obj,attr,value) IIntuition->SetAttrs((obj),(attr),(value),TAG_DONE)

#define SetRefresh(win,obj,attr,value) IIntuition->RefreshSetGadgetAttrs((Gadget *)(obj),(win),0,(attr),(value),TAG_DONE)


namespace RAPlus {
  namespace Reaction {

    class ReactionImage {

      public:

        enum ImageType { LabelType };

        virtual ~ReactionImage() { }

        static VARARGS68K Object *newObject(ImageType type, ReactionImage *gadget, ...);

        virtual Object *getObject() const { return(imageObject); }

        virtual void dispose();

        static ReactionImage *classFactory(ImageType type);

      protected:

        ReactionImage() : imageObject(0) { }

        virtual Object *newObject(struct TagItem *tagItem) = 0;

        Object *imageObject;

    };

  }
}

#endif // RALUS_REACTION_REACTIONIMAGE_HPP

