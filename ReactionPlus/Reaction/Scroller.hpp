#ifndef REACTIONPLUS_SCROLLER_HPP
#define REACTIONPLUS_SCROLLER_HPP

#include "ReactionGadget.hpp"

#include <gadgets/scroller.h>

#include <string>


#define ScrollerClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::Scroller::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class Scroller : public ReactionGadget {

      public:

                 Scroller() { }
        virtual ~Scroller() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::ScrollerType); }

        bool   getArrows();
        int32  getTop();
        int32  getTotal();
        int32  getVisible();
        uint32 getOrientation();
        int16  getArrowDelta();

        void setTop(int32 value);
        void setTop(int32 value, struct ::Window *win);
        void setTotal(int32 value);
        void setTotal(int32 value, struct ::Window *win);
        void setVisible(int32 value);
        void setVisible(int32 value, struct ::Window *win);
        void setArrowDelta(int32 value);
        void setSignalTask(struct Task *value);
        void setSignalTaskBit(uint32 value);

        virtual bool gadgetUpEvent();

      private:

        static std::string getAttrError;

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // REACTIONPLUS_SCROLLER_HPP

