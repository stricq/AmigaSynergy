#include "ParseException.hpp"


namespace RAPlus {


  ParseException::ParseException(const char *msg, std::string badLine, int badIndex) :
    Exception(NULL),
    index(badIndex),
    line(badLine) {

    if (msg) errorMessage = (char *)IExec->AllocVec(512,MEMF_CLEAR);
    else errorMessage = NULL;

    if (errorMessage) sprintf(errorMessage,"%s (Line = %s, Index = %d)",msg,line.c_str(),index);

  }


}

