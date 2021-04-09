#include "InputEvent.hpp"


namespace RAPlus {
  namespace Exec {


    InputEvent::InputEvent() :
      owner(true) {

      event = new struct ::InputEvent;

      event->ie_NextEvent = 0;

    }


    InputEvent::InputEvent(struct ::InputEvent *event) :
      owner(false),
      event(event) {

      if (event == 0) throw InvalidArgumentException("InputEvent is NULL.");

    }


    InputEvent::~InputEvent() {

      if (owner) delete event;

    }


  }
}

