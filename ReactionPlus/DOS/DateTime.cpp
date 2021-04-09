#include "DateTime.hpp"

#include "InvalidStateException.hpp"


namespace RAPlus {

  void DateTime::copyDateStamp(const struct DateStamp *ds) {

    dateStamp.ds_Days   = ds->ds_Days;
    dateStamp.ds_Minute = ds->ds_Minute;
    dateStamp.ds_Tick   = ds->ds_Tick;

  }


  std::string DateTime::toString(UBYTE format, UBYTE flags) {

    struct ::DateTime dt;

    dt.dat_Stamp.ds_Days   = dateStamp.ds_Days;
    dt.dat_Stamp.ds_Minute = dateStamp.ds_Minute;
    dt.dat_Stamp.ds_Tick   = dateStamp.ds_Tick;

    dt.dat_Format = format;
    dt.dat_Flags  = flags;

    dt.dat_StrDay  = day;
    dt.dat_StrDate = date;
    dt.dat_StrTime = time;

    if (IDOS->DateToStr(&dt) == DOSFALSE) throw InvalidStateException("Invalid DateStamp in DateToStr() call.");

    return(std::string(day).append(", ").append(date).append(" ").append(time));

  }


  std::string DateTime::toDayString(UBYTE flags) {

    toString(FORMAT_DEF,flags);

    return(std::string(day));

  }


  std::string DateTime::toDateString(UBYTE format) {

    toString(format);

    return(std::string(date));

  }


  std::string DateTime::toTimeString() {

    toString();

    return(std::string(time));

  }


}

