#include "Exception.hpp"


namespace RAPlus {


  Exception::Exception(const Exception &e) {

    if (e.errorMessage) errorMessage = (char *)IExec->AllocVec(strlen(e.errorMessage) + 1,MEMF_CLEAR);
    else errorMessage = NULL;

    if (errorMessage) strcpy(errorMessage,e.errorMessage);

  }


  Exception::Exception(const char *msg) {

    if (msg) errorMessage = (char *)IExec->AllocVec(strlen(msg) + 1,MEMF_CLEAR);
    else errorMessage = NULL;

    if (errorMessage) strcpy(errorMessage,msg);

  }


  Exception::Exception(const std::string &msg) {

    errorMessage = (char *)IExec->AllocVec(msg.length() + 1,MEMF_CLEAR);

    if (errorMessage) strcpy(errorMessage,msg.c_str());

  }


  Exception::~Exception() {

    if (errorMessage) IExec->FreeVec(errorMessage);

  }


  std::string Exception::toString() {

    if (errorMessage) return(std::string(errorMessage));

    return(std::string("Out of memory, exception message lost."));

  }


  std::string Exception::getMessage() {

    if (errorMessage) return(std::string(errorMessage));

    return(std::string("Out of memory, exception message lost."));

  }


}

