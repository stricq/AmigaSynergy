#ifndef RAPLUS_REACTION_LISTBROWSER_HPP
#define RAPLUS_REACTION_LISTBROWSER_HPP

#include "ReactionGadget.hpp"

#include <gadgets/ListBrowser.h>

#include <proto/ListBrowser.h>

#define ListBrowserClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::ListBrowser::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class ListBrowser : public ReactionGadget {

      public:

                 ListBrowser() { }
        virtual ~ListBrowser() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::ListBrowserType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_LISTBROWSER_HPP



