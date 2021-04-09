#ifndef REACTIONPLUS_LOCALE
#define REACTIONPLUS_LOCALE

#include <libraries/locale.h>

#include <utility/hooks.h>

#include <string>

#include "Utility/Hook.hpp"


namespace RAPlus {
  namespace Locale {

    class Locale {

      public:

        Locale();
        Locale(std::string &name);
       ~Locale();

        std::string &format(const std::string &spec, const LONG data);

        std::string buffer;

      private:

        struct ::Locale *locale;

    };

  }
}

#endif // REACTIONPLUS_LOCALE

