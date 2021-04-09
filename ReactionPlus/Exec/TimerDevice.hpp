#ifndef TIMERDEVICE_HPP
#define TIMERDEVICE_HPP

#include <dos/dos.h>

#include <exec/exec.h>

#include "TimerRequest.hpp"

#include "SignalEvents.hpp"

#include <map>


namespace RAPlus {

  class TimerDeviceException { };

  namespace Exec {

    class ITimerEvent { };

    typedef uint32 TimerEvent;

    typedef bool (ITimerEvent::*TimerEventMethod)(TimerEvent);


    class TimerMessage : public IMessage {

      public:

                 TimerMessage() { }
        virtual ~TimerMessage() { }

        virtual IMessageType getType() { return(type); }

        virtual TimerMessage *clone() { return(new TimerMessage(msg)); }

      private:

        TimerMessage(struct Message *msg) { setMessage(msg); }

        static const IMessageType type = 0;

    };


    class TimerDevice : public Exec::ISignalEvents {

      public:

        enum TimerUnit { MicroHertz = UNIT_MICROHZ, VBlank = UNIT_VBLANK };

                 TimerDevice(TimerUnit unit);
        virtual ~TimerDevice();

        uint32 getSignal() { return(timerBit); }

        TimerEvent addTimer(uint32 seconds, uint32 micros, bool repeat, ITimerEvent *cls, TimerEventMethod func);
        void removeTimer(TimerEvent event);

        bool doEvents(uint32 signals);

        void disableTimer(TimerEvent event);
        void enableTimer(TimerEvent event);

        bool wait(uint32 seconds, uint32 micros);

      private:

        void abortIO(TimerRequest *request);
        void sendIO(TimerRequest *request, uint32 seconds, uint32 micros);

        bool used;

      	uint32 timerBit;
      	uint32 timerStat;

        TimerEvent event;

        TimerUnit unit;

        TimerRequest *masterRequest;
        TimerRequest *timerRequest;

        class Listener {

          public:

            Listener(TimerRequest *request) { timerRequest = new TimerRequest(request);  }
           ~Listener() { delete timerRequest; }

            bool repeat;
            bool enabled;

            uint32 seconds;
            uint32 micros;

            TimerRequest *timerRequest;

            TimerEventMethod eventMethod;
            ITimerEvent     *eventClass;

        };

        std::map<TimerEvent, Listener *> timersList;

        bool handleEvent(TimerMessage &timerMessage);

    };

  }
}


#endif // TIMERDEVICE_HPP

