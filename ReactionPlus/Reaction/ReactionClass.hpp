#ifndef RAPLUS_REACTION_REACTIONCLASS_HPP
#define RAPLUS_REACTION_REACTIONCLASS_HPP

#include <intuition/classusr.h>

#include <proto/intuition.h>

#include <reaction/reaction_macros.h>

#define BOOLP(b) (b ? TRUE : FALSE)

#define Get(obj,attr,store) IIntuition->GetAttr((attr),(obj),(uint32 *)(store))
#define Set(obj,attr,value) IIntuition->SetAttrs((obj),(attr),(value),TAG_DONE)

#define SetRefresh(win,obj,attr,value) IIntuition->RefreshSetGadgetAttrs((Gadget *)(obj),(win),0,(attr),(value),TAG_DONE)


namespace RAPlus {
  namespace Reaction {

    class ReactionClass {

      public:

        enum ClassType { WindowType };

        virtual ~ReactionClass() { }

        static VARARGS68K Object *newObject(ClassType type, ReactionClass *gadget, ...);

        virtual Object *getObject() const { return(classObject); }

        virtual void dispose();

        static ReactionClass *classFactory(ClassType type);

      protected:

        ReactionClass() : classObject(0) { }

        virtual Object *newObject(struct TagItem *tagItem) = 0;

        Object *classObject;

    };

  }
}

#endif // RALUS_REACTION_REACTIONCLASS_HPP

