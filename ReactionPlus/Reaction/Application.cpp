#include "Application.hpp"
#include "AppWindow.hpp"

#include "InvalidStateException.hpp"
#include "Exec/OutOfMemoryException.hpp"

#include <classes/window.h>

#include <reaction/reaction_macros.h>

#include <proto/exec.h>
#include <proto/intuition.h>

#include <stdio.h>


namespace RAPlus {
  namespace Reaction {


    Application *Application::app = NULL;


    Application *Application::instance() {

      if (app == NULL) app = new Application();

      if (app == NULL) throw OutOfMemoryException("Unable to create the Application class.");

      return(app);

    }


    void Application::dispose() {

      if (app != NULL) delete app;

    }


    Application::Application() {

      appPort = new Exec::MessagePort();

    }


    Application::~Application() {

      appList.clear();

      printf("Application::~Application - Delete appPort\n");

      delete appPort;

      printf("  appPort - done\n");

    }


    void Application::addWindow(AppWindow *appWin) {

      appWin->setSharedPort(appPort);

      appList.push_back(appWin);

    }


    void Application::removeWindow(AppWindow *appWin) {

      std::vector<AppWindow *>::iterator it;

      for(it = appList.begin(); it != appList.end(); it++) {
        if (*it == appWin) {
          appList.erase(it);
          break;
        }
      }

    }


    void Application::closeAllRemember() {

      std::vector<AppWindow *>::iterator it;

      for(it = appList.begin(); it != appList.end(); ++it) {
        (*it)->setRememberOpen();
        (*it)->closeWindow();
      }

    }


    void Application::openAllRemember() {

      std::vector<AppWindow *>::iterator it;

      for(it = appList.begin(); it != appList.end(); ++it) {
        if ((*it)->getRememberOpen()) (*it)->openWindow();
      }

    }


    bool Application::doEvents(uint32) {

      bool done = false;

      uint32 result = 0;
      uint32 code   = 0;

      uint32 size = 0;

      std::vector<AppWindow *>::iterator it;

      for(it = appList.begin(); it != appList.end(); ++it) {
        AppWindow *win = (*it);
        size = appList.size();
        while((result = RA_HandleInput(win->getWindow().getObject(),&code)) != WMHI_LASTMSG) {
          switch(result & WMHI_CLASSMASK) {
            case WMHI_CLOSEWINDOW: {
              done |= win->closeWindow();
              break;
            }
            default: {
              done |= win->handleEvent(result);
            }
          }
        }
        if (size != appList.size()) {
          it = appList.begin();
          size = appList.size();
        }
      }

      return(done);

    }


  }
}

