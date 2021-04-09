#ifndef RAPLUS_EXEC_INPUTEVENT_HPP
#define RAPLUS_EXEC_INPUTEVENT_HPP

#include <devices/inputevent.h>

#include "InvalidArgumentException.hpp"


namespace RAPlus {
  namespace Exec {

    class InputEvent {

      public:

        InputEvent(struct ::InputEvent *event);
        InputEvent();
       ~InputEvent();

        struct ::InputEvent *getInputEvent() { return(event); }

        uint32 getLength() { return(sizeof(struct ::InputEvent)); }

        bool nextEvent() { return((event = event->ie_NextEvent) != 0); }

        uint8  getClass()     { return(event->ie_Class); }
        uint8  getSubClass()  { return(event->ie_SubClass); }
        uint16 getCode()      { return(event->ie_Code); }
        uint16 getQualifier() { return(event->ie_Qualifier); }

        uint16 getX() { return(event->ie_X); }
        uint16 getY() { return(event->ie_Y); }

        APTR getAddress() { return(event->ie_EventAddress); }

        uint8 getPrev1DownCode() { return(event->ie_Prev1DownCode); }
        uint8 getPrev1DownQual() { return(event->ie_Prev1DownQual); }
        uint8 getPrev2DownCode() { return(event->ie_Prev2DownCode); }
        uint8 getPrev2DownQual() { return(event->ie_Prev2DownQual); }

        uint32 getEventSeconds() { return(event->ie_TimeStamp.Seconds); }
        uint32 getEventMicros()  { return(event->ie_TimeStamp.Microseconds); }

        void setClass(uint8 val)      { event->ie_Class = val; }
        void setSubClass(uint8 val)   { event->ie_SubClass = val; }
        void setCode(uint16 val)      { event->ie_Code = val; }
        void setQualifier(uint16 val) { event->ie_Qualifier = val; }

        void setX(uint16 val) { event->ie_X = val; }
        void setY(uint16 val) { event->ie_Y = val; }

        void setPrev1DownCode(uint8 val) { event->ie_Prev1DownCode = val; }
        void setPrev1DownQual(uint8 val) { event->ie_Prev1DownQual = val; }
        void setPrev2DownCode(uint8 val) { event->ie_Prev2DownCode = val; }
        void setPrev2DownQual(uint8 val) { event->ie_Prev2DownQual = val; }

        void setEventSeconds(uint32 val) { event->ie_TimeStamp.Seconds = val; }
        void setEventMicros(uint32 val)  { event->ie_TimeStamp.Microseconds = val; }

      private:

        bool owner;

        struct ::InputEvent *event;

    };

  }
}

#endif // RAPLUS_EXEC_INPUTEVENT_HPP

