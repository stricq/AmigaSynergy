#ifndef REACTIONPLUS_EXEC_TIMERREQUEST_HPP
#define REACTIONPLUS_EXEC_TIMERREQUEST_HPP

#include <devices/timer.h>

#include <exec/io.h>

#include "IOBase.hpp"


namespace RAPlus {
  namespace Exec {

    class TimerRequest : public IOBase {

      public:

        enum TimerCommand { AddRequest = TR_ADDREQUEST };

                 TimerRequest() : IOBase(sizeof(struct ::TimeRequest)) { }
                 TimerRequest(TimerRequest *timer);
                 TimerRequest(TimerRequest &timer);
        virtual ~TimerRequest() { }

        struct ::TimeRequest *getTimerReq() { return(reinterpret_cast<struct ::TimeRequest *>(ioRequest)); }

        MessagePort *getMessagePort() { return(IOBase::getMessagePort()); }

        void setCommand(TimerCommand cmd) { getTimerReq()->Request.io_Command = cmd; }

        void setSeconds(uint32 seconds) { getTimerReq()->Time.Seconds      = seconds; }
        void setMicros(uint32 micros)   { getTimerReq()->Time.Microseconds = micros; }

      private:

    };

  }
}


#endif // REACTIONPLUS_EXEC_TIMERREQUEST_HPP

