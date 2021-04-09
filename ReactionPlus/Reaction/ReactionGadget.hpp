#ifndef RAPLUS_REACTION_REACTIONGADGET_HPP
#define RAPLUS_REACTION_REACTIONGADGET_HPP

#include "InvalidStateException.hpp"

#include "Exec/OutOfMemoryException.hpp"

#include <intuition/classusr.h>

#include <proto/intuition.h>

#define BOOLP(b) (b ? TRUE : FALSE)

#define Get(obj,attr,store) IIntuition->GetAttr((attr),(obj),(uint32 *)(store))
#define Set(obj,attr,value) IIntuition->SetAttrs((obj),(attr),(value),TAG_DONE)

#define SetRefresh(win,obj,attr,value) IIntuition->RefreshSetGadgetAttrs((Gadget *)(obj),(win),0,(attr),(value),TAG_DONE)


namespace RAPlus {
  namespace Reaction {

    class AppWindow;

    class ReactionGadget {

      public:

        enum GadgetType { ButtonType, CheckBoxType, ChooserType, ClickTabType, FileRequestType, IntegerType, LayoutType,
                          ListBrowserType, PageType, RadioButtonType, ScrollerType, SpaceType, StringType, TextEditorType };

        virtual ~ReactionGadget() { }

        static VARARGS68K Object *newObject(GadgetType type, AppWindow *appWin, ReactionGadget *gadget, ...);

        virtual Object *getObject() const { return(gadgetObject); }

        virtual void dispose();
        virtual void focus();

        static ReactionGadget *gadgetFactory(GadgetType type);

        virtual void onGadgetUp(AppWindow *cls, bool (AppWindow::*func)(ReactionGadget *gadget));

        virtual bool gadgetUpEvent() = 0;

        virtual void setDisabled(bool value);
        virtual void setText(const std::string &text);

      protected:

        ReactionGadget() : gadgetObject(0), gadgetUpMethod(0), gadgetUpClass(0) { }

        virtual Object *newObject(struct TagItem *tagItem) = 0;

        Object *gadgetObject;

        bool (AppWindow::*gadgetUpMethod)(ReactionGadget *gadget);

        AppWindow *gadgetUpClass;
        AppWindow *parentWindow;

      private:

        static uint32 gadgetID;

    };

    typedef bool (AppWindow::*GadgetMethod)(ReactionGadget *);

  }
}

#endif // RAPLUS_REACTION_REACTIONGADGET_HPP

