#include "SignalEvents.hpp"

#include <dos/dos.h>

#include <proto/exec.h>

#include <stdio.h>


namespace RAPlus {
  namespace Exec {


    SignalEvents::~SignalEvents() {

      while(!listenerList.empty()) {
        delete listenerList.begin()->second;
        listenerList.begin()->second = 0;
        listenerList.erase(listenerList.begin());
      }

      while(!classList.empty()) {
        classList.erase(classList.begin());
      }

    }


    void SignalEvents::addListener(uint32 signal, IEvent *cls, EventMethod func) {

      Listener *listener = new Listener();

      listener->eventMethod = func;
      listener->eventClass  = cls;

      listenerList[signal] = listener;

    }


    void SignalEvents::addListener(ISignalEvents *eventsClass) {

      classList.push_back(eventsClass);

    }


    void SignalEvents::removeListener(uint32 signal) {

      std::map<uint32, Listener *>::iterator it = listenerList.find(signal);

      if (it != listenerList.end()) {
        delete it->second;
        it->second = 0;
        listenerList.erase(it);
      }

    }


    void SignalEvents::removeListener(ISignalEvents *eventsClass) {

      classList.remove(eventsClass);

    }


    uint32 SignalEvents::getSignal() {

      uint32 signals = 0;

      for(std::map<uint32, Listener *>::iterator it = listenerList.begin(); it != listenerList.end(); ++it) {
        signals |= it->first;
      }

      for(std::list<ISignalEvents *>::iterator it = classList.begin(); it != classList.end(); ++it) {
        signals |= (*it)->getSignal();
      }

      return(signals);

    }


    uint32 SignalEvents::waitSignals(bool onePass) {

      done = false;

      uint32 signals = 0;

      do {
        signals = IExec->Wait(getSignal() | SIGBREAKF_CTRL_C);
        if (signals & SIGBREAKF_CTRL_C) done = true;
        done |= doEvents(signals);
      } while(!done && !onePass);

      return(signals);

    }


    bool SignalEvents::doEvents(uint32 signals) {

      bool done = false;

      EventMethod eventMethod;

      IEvent *eventClass;

      for(std::map<uint32, Listener *>::iterator it = listenerList.begin(); it != listenerList.end(); ++it) {
        if (it->first & signals) {
          eventMethod = it->second->eventMethod;
          eventClass  = it->second->eventClass;
          done |= (eventClass->*eventMethod)(signals);
        }
      }
      for(std::list<ISignalEvents *>::iterator it = classList.begin(); it != classList.end(); ++it) {
        if ((*it)->getSignal() & signals) {
          done |= (*it)->doEvents(signals);
        }
      }

      return(done);

    }

  }
}

