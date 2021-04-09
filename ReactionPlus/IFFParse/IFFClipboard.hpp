#ifndef RAPLUS_IFFPARSE_IFFCLIPBOARD_HPP
#define RAPLUS_IFFPARSE_IFFCLIPBOARD_HPP

#include "IFF.hpp"

#include "InvalidStateException.hpp"

#include "DOS/IOException.hpp"

#include <string>

#include <exec/types.h>

#define ID_FTXT MAKE_ID('F','T','X','T')
#define ID_CHRS MAKE_ID('C','H','R','S')


namespace RAPlus {

  class ClipboardException { };

  namespace IFFParse {

    class IFFClipboard : public IFF {

      public:

                 IFFClipboard(uint32 clipUnit);
        virtual ~IFFClipboard();

        virtual void openIFF(IFFOpenMode mode);

        virtual void closeIFF();

        void setText(const std::string &clip);

        void getText(std::string &clip);

        long getTextLength();

      private:

        bool open;

        uint32 clipUnit;

        IFFOpenMode openMode;

    };

  }
}

#endif // RAPLUS_IFFPARSE_IFFCLIPBOARD_HPP

