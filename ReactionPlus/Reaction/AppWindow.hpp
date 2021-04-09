#ifndef REACTIONPLUS_APPWINDOW_HPP
#define REACTIONPLUS_APPWINDOW_HPP

#include "Window.hpp"

#include "Exec/MessagePort.hpp"

#include <intuition/gadgetclass.h>

#include <map>


namespace RAPlus {
  namespace Reaction {

    class ReactionGadget;

    class AppWindow {

      public:

                 AppWindow() : rememberOpen(false) { }
        virtual ~AppWindow();

        virtual void activateWindow();
        virtual bool openWindow();
        virtual bool closeWindow();

        Reaction::Window &getWindow() { return(window); }

        virtual bool handleEvent(uint32 result);

        virtual void setRememberOpen() { rememberOpen = window.isOpen(); }
        virtual void setSharedPort(Exec::MessagePort *port) { window.setSharedPort(port); }

        virtual bool getRememberOpen() { return(rememberOpen); }

        virtual void addGadget(Reaction::ReactionGadget *gadget);
        virtual void removeGadget(Reaction::ReactionGadget *gadget);

      protected:

        Reaction::Window window;

      private:

        bool rememberOpen;

        std::map<uint32, Reaction::ReactionGadget *> gadgetList;

    };

  }
}

#endif // REACTIONPLUS_APPWINDOW_HPP

