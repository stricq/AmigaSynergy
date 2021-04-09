#include "AppWindow.hpp"

#include "ReactionGadget.hpp"

#include <reaction/reaction_macros.h>

#include <proto/intuition.h>


namespace RAPlus {
  namespace Reaction {


    AppWindow::~AppWindow() {

      while(!gadgetList.empty()) gadgetList.erase(gadgetList.begin());

      window.doClose();
      window.dispose();

    }


    void AppWindow::activateWindow() {

      window.doActivate();

    }


    bool AppWindow::openWindow() {

      window.doOpen();

      return(window.isOpen());

    }


    bool AppWindow::closeWindow() {

      window.doClose();

      return(true);

    }


    void AppWindow::addGadget(ReactionGadget *gadget) {

      uint32 gadgetID = 0;

      Get(gadget->getObject(),GA_ID,&gadgetID);

      if (gadgetID > 0) gadgetList[gadgetID] = gadget;

    }


    void AppWindow::removeGadget(ReactionGadget *gadget) {

      uint32 gadgetID = 0;

      Get(gadget->getObject(),GA_ID,&gadgetID);

      if (gadgetID == 0) return;

      std::map<uint32, ReactionGadget *>::iterator it = gadgetList.find(gadgetID);

      if (it != gadgetList.end()) gadgetList.erase(it);

    }


    bool AppWindow::handleEvent(uint32 result) {

      bool done = false;

      uint32 gadgetID = result & WMHI_GADGETMASK;

      if (gadgetID == 0) return(done);

      switch(result & WMHI_CLASSMASK) {
        case WMHI_GADGETUP: {
          std::map<uint32, ReactionGadget *>::iterator it = gadgetList.find(gadgetID);
          if (it != gadgetList.end()) done |= it->second->gadgetUpEvent();
          break;
        }
      }

      return(done);

    }


  }
}

