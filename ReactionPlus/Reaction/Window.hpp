#ifndef REACTIONPLUS_WINDOW_HPP
#define REACTIONPLUS_WINDOW_HPP

#include "ReactionClass.hpp"

#include "Exec/MessagePort.hpp"

#include <classes/window.h>

#include <exec/ports.h>


#define WindowClass(cl) RAPlus::Reaction::ReactionClass::newObject((RAPlus::Reaction::Window::getClassType()),(cl)

namespace RAPlus {
  namespace Reaction {

    class Window : public ReactionClass {

      public:

                 Window() : sharedPort(0) { }
        virtual ~Window() { }

        static ReactionClass::ClassType getClassType() { return(ReactionClass::WindowType); }

        BOOL isOpen();

        void doActivate();
        void doClose();
        void doOpen();
        void doReThink();

        ULONG getInnerWidth();
        ULONG getInnerHeight();

        struct Exec::MessagePort *getSharedPort();
        struct ::Window *getWindow();

        void setInnerHeight(ULONG value);
        void setLeft(ULONG value);
        void setTop(ULONG value);
        void setSharedPort(Exec::MessagePort *value);

      private:

        static const char *getAttrError;

        Object *newObject(struct TagItem *tagItem);

        struct ::Window *window;

        Exec::MessagePort *sharedPort;

    };

  }
}

#endif  // REACTIONPLUS_WINDOW_HPP

