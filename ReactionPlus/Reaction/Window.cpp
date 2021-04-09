#include "Window.hpp"

#include "Exec/OutOfMemoryException.hpp"

#include <proto/intuition.h>
#include <proto/window.h>

#include <stdio.h>


namespace RAPlus {
  namespace Reaction {


    const char *Window::getAttrError = "GetAttrs() could not get the attribute.";


    Object *Window::newObject(struct TagItem *tagItem) {

      classObject = (Object *)IIntuition->NewObjectA(IWindow->WINDOW_GetClass(),NULL,tagItem);

      if (!classObject) throw OutOfMemoryException("Could not create the Window Object.");

      return(classObject);

    }


    BOOL Window::isOpen() {

      return(getWindow() ? TRUE : FALSE);

    }


    void Window::doActivate() {

      IIntuition->ActivateWindow(getWindow());

    }


    void Window::doClose() {

      RA_CloseWindow(classObject);

    }


    void Window::doOpen() {

      window = RA_OpenWindow(classObject);

    }


    void Window::doReThink() {

      IIntuition->IDoMethod(classObject,WM_RETHINK);

    }


    ULONG Window::getInnerWidth() {

      ULONG value;

      if (Get(classObject,WA_InnerWidth,&value) != 1) throw Exception(getAttrError);

      return(value);

    }


    ULONG Window::getInnerHeight() {

      ULONG value;

      if (Get(classObject,WA_InnerHeight,&value) != 1) throw Exception(getAttrError);

      return(value);

    }


    struct ::Window *Window::getWindow() {

      return(window);

    }


    struct Exec::MessagePort *Window::getSharedPort() {

      return(sharedPort);

    }


    void Window::setInnerHeight(ULONG value) {

      Set(classObject,WA_InnerHeight,value);

    }


    void Window::setLeft(ULONG value) {

      Set(classObject,WA_Left,value);

    }


    void Window::setTop(ULONG value) {

      Set(classObject,WA_Top,value);

    }


    void Window::setSharedPort(Exec::MessagePort *value) {

      Set(classObject,WINDOW_SharedPort,value->getMsgPort());

      sharedPort = value;

    }


  }
}


