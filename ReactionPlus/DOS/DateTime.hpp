#ifndef REACTIONPLUS_DATETIME_HPP
#define REACTIONPLUS_DATETIME_HPP

#include <dos/dos.h>

#include <proto/dos.h>

#include <string>


namespace RAPlus {

  class DateTime {

    public:

      DateTime(struct DateStamp *ds) { copyDateStamp(ds); }
      DateTime(const DateTime &dt) { copyDateStamp(&dt.dateStamp); }
      DateTime(ULONG seconds) { IDOS->SecondsToDateStamp(seconds,&dateStamp); }
      DateTime() { IDOS->DateStamp(&dateStamp); }
     ~DateTime() { }

      void setDateStamp(struct DateStamp *ds) { copyDateStamp(ds); }
      void setSeconds(ULONG seconds) { IDOS->SecondsToDateStamp(seconds,&dateStamp); }

      std::string toString(UBYTE format = FORMAT_DEF, UBYTE flags = 0);
      std::string toDayString(UBYTE flags = 0);
      std::string toDateString(UBYTE format = FORMAT_DEF);
      std::string toTimeString();

      ULONG toSeconds() { return(IDOS->DateStampToSeconds(&dateStamp)); }

    private:

      void copyDateStamp(const DateStamp *ds);

      struct DateStamp dateStamp;

      char  day[LEN_DATSTRING];
      char date[LEN_DATSTRING];
      char time[LEN_DATSTRING];

  };

}

#endif // REACTIONPLUS_DATETIME_HPP

