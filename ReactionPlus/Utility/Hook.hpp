#ifndef RAPLUS_UTILITY_HOOK_HPP
#define RAPLUS_UTILITY_HOOK_HPP

#include <utility/hooks.h>


namespace RAPlus {
  namespace Utility {

    class Hook {

      public:

        Hook() { }
       ~Hook() { }

        void setEntry(HOOKFUNC function) { hook.h_Entry = function; }
        void setData(APTR data)          { hook.h_Data  = data; }

        struct ::Hook *getHook() { return(&hook); }

      private:

        struct ::Hook hook;

    };

  }
}

#endif // RAPLUS_UTILITY_HOOK_HPP

