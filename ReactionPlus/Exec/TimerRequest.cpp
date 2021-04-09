#include "TimerRequest.hpp"


namespace RAPlus {
  namespace Exec {


    TimerRequest::TimerRequest(TimerRequest *timer) :
      IOBase(timer) {

      struct ::TimeRequest *timereq = getTimerReq();

      struct ::TimeRequest *rhs = timer->getTimerReq();

      *timereq = *rhs;

    }


    TimerRequest::TimerRequest(TimerRequest &timer) :
      IOBase(timer) {

      struct ::TimeRequest *timereq = getTimerReq();

      struct ::TimeRequest *rhs = timer.getTimerReq();

      *timereq = *rhs;

    }


  }
}

