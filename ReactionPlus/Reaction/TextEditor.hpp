#ifndef RAPLUS_REACTION_TEXTEDITOR_HPP
#define RAPLUS_REACTION_TEXTEDITOR_HPP

#include "ReactionGadget.hpp"

#include <gadgets/texteditor.h>

#include <proto/texteditor.h>

#ifdef TextEditor
#undef TextEditor
#endif

#define TextEditorClass(cl) RAPlus::Reaction::ReactionGadget::newObject((RAPlus::Reaction::TextEditor::getGadgetType()),(this),(cl)


namespace RAPlus {
  namespace Reaction {

    class TextEditor : public ReactionGadget {

      public:

                 TextEditor() { }
        virtual ~TextEditor() { }

        static ReactionGadget::GadgetType getGadgetType() { return(ReactionGadget::TextEditorType); }

        virtual bool gadgetUpEvent();

      private:

        Object *newObject(struct TagItem *tagItem);

    };

  }
}

#endif  // RAPLUS_REACTION_TEXTEDITOR_HPP

