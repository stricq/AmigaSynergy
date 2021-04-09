#include "ReactionGadget.hpp"

#include "AppWindow.hpp"

#include "Button.hpp"
#include "CheckBox.hpp"
#include "Chooser.hpp"
#include "ClickTab.hpp"
#include "FileRequest.hpp"
#include "Integer.hpp"
#include "Layout.hpp"
#include "ListBrowser.hpp"
#include "Page.hpp"
#include "RadioButton.hpp"
#include "Scroller.hpp"
#include "Space.hpp"
#include "String.hpp"
#include "TextEditor.hpp"

#include <stdarg.h>


namespace RAPlus {
  namespace Reaction {


    uint32 ReactionGadget::gadgetID = 0;


    Object *ReactionGadget::newObject(GadgetType type, AppWindow *appWin, ReactionGadget *gadget, ...) {

      struct TagItem *varargs;

      Object *object;

      va_list va;

      va_startlinear(va,gadget);

      varargs = va_getlinearva(va,struct TagItem *);

      if (gadget == 0) {
        ReactionGadget *temp = ReactionGadget::gadgetFactory(type);
        if (temp) {
          object = temp->newObject(varargs);
          delete temp;
        }
        else throw OutOfMemoryException("Could not create the temp Gadget class.");
      }
      else {
        object = gadget->newObject(varargs);
        Set(object,GA_ID,++gadgetID);
        appWin->addGadget(gadget);
        gadget->parentWindow = appWin;
      }

      return(object);

    }



    void ReactionGadget::dispose() {

      if (!gadgetObject) return;

      IIntuition->DisposeObject(gadgetObject);

      gadgetObject = 0;

    }


    void ReactionGadget::focus() {

      IIntuition->ActivateGadget((Gadget *)gadgetObject,parentWindow->getWindow().getWindow(),0);

    }


    ReactionGadget *ReactionGadget::gadgetFactory(GadgetType type) {

      switch(type) {
        case ButtonType:      return(new Button());
        case CheckBoxType:    return(new CheckBox());
        case ChooserType:     return(new Chooser());
        case ClickTabType:    return(new ClickTab());
        case FileRequestType: return(new FileRequest());
        case IntegerType:     return(new Integer());
        case LayoutType:      return(new Layout());
        case ListBrowserType: return(new ListBrowser());
        case PageType:        return(new Page());
        case RadioButtonType: return(new RadioButton());
        case ScrollerType:    return(new Scroller());
        case SpaceType:       return(new Space());
        case StringType:      return(new String());
        case TextEditorType:  return(new TextEditor());
      }

      throw InvalidStateException("Unknown Gadget Type in Gadget Factory.\n");

    }


    void ReactionGadget::onGadgetUp(AppWindow *cls, GadgetMethod func) {

      gadgetUpClass = cls;
      gadgetUpMethod = func;

    }


    void ReactionGadget::setDisabled(bool value) {

      SetRefresh(parentWindow->getWindow().getWindow(),gadgetObject,GA_Disabled,value);

    }


    void ReactionGadget::setText(const std::string &text) {

      SetRefresh(parentWindow->getWindow().getWindow(),gadgetObject,GA_Text,text.c_str());

    }


  }
}

