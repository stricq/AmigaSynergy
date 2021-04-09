#include "Locale.hpp"

#include "InvalidArgumentException.hpp"

#include <proto/locale.h>

ULONG _formatBufferFill(struct Hook *hook, struct ::Locale *locale, UBYTE c);


namespace RAPlus {
  namespace Locale {


    Locale::Locale() {

      locale = ILocale->OpenLocale(NULL);

    }


    Locale::Locale(std::string &name) {

      locale = ILocale->OpenLocale(name.c_str());

      if (locale == NULL) throw InvalidArgumentException("The supplied Locale name was not found in the system.");

    }


    Locale::~Locale() {

      ILocale->CloseLocale(locale);

    }


    std::string &Locale::format(const std::string &spec, const LONG data) {

      Utility::Hook formatHook;

      formatHook.setEntry((HOOKFUNC)_formatBufferFill);
      formatHook.setData(this);

      buffer.erase();

      ILocale->FormatString(locale,spec.c_str(),(APTR)&data,formatHook.getHook());

      return(buffer);

    }


  }
}


ULONG _formatBufferFill(struct Hook *hook, struct ::Locale *, UBYTE c) {

  RAPlus::Locale::Locale *me = (RAPlus::Locale::Locale *)hook->h_Data;

  me->buffer += c;

  return(0);

}


