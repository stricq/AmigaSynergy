#ifndef REACTIONPLUS_IFFDOS
#define REACTIONPLUS_IFFDOS

#include "IFF.hpp"

#include "DOS/IOException.hpp"
#include "DOS/FileNotFoundException.hpp"

#include <proto/dos.h>


namespace RAPlus {
  namespace IFFParse {

    class IFFDOS : public IFF {

      public:

                 IFFDOS(const std::string &iffFile);
        virtual ~IFFDOS();

        virtual void openIFF(IFFOpenMode mode);

        virtual void closeIFF();

      private:

        std::string iffFilename;

    };

  }
};

#endif // REACTIONPLUS_IFFDOS

