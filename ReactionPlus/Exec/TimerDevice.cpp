#include "TimerDevice.hpp"

#include <proto/exec.h>


namespace RAPlus {
  namespace Exec {


    TimerDevice::TimerDevice(TimerUnit unit) :
      used(false),
      event(0),
      unit(unit) {

      masterRequest = new TimerRequest();

      timerBit = masterRequest->getSignal();

      timerStat = IExec->OpenDevice("timer.device",unit,masterRequest->getIORequest(),0);

      timerRequest  = new TimerRequest(masterRequest);

      if (timerStat != 0) {
        delete timerRequest;
        delete masterRequest;
        throw TimerDeviceException();
      }

    }


    TimerDevice::~TimerDevice() {

      while(!timersList.empty()) {
        if (timersList.begin()->second->enabled) abortIO(timersList.begin()->second->timerRequest);
        delete timersList.begin()->second;
        timersList.begin()->second = 0;
        timersList.erase(timersList.begin());
      }

      if (used) abortIO(timerRequest);

      if (timerStat == 0) IExec->CloseDevice(masterRequest->getIORequest());

      delete timerRequest;
      delete masterRequest;

    }


    void TimerDevice::abortIO(TimerRequest *request) {

      if (IExec->CheckIO(request->getIORequest()) == 0) IExec->AbortIO(request->getIORequest());

      IExec->WaitIO(request->getIORequest());

    }


    void TimerDevice::sendIO(TimerRequest *request, uint32 seconds, uint32 micros) {

      request->setCommand(TimerRequest::AddRequest);

      request->setSeconds(seconds);
      request->setMicros(micros);

      IExec->SendIO(request->getIORequest());

    }


    TimerEvent TimerDevice::addTimer(uint32 seconds, uint32 micros, bool repeat, ITimerEvent *cls, TimerEventMethod func) {

      Listener *listener = new Listener(masterRequest);

      listener->seconds = seconds;
      listener->micros  = micros;

      listener->repeat  = repeat;
      listener->enabled = true;

      listener->eventMethod = func;
      listener->eventClass  = cls;

      timersList[event] = listener;

      sendIO(listener->timerRequest,seconds,micros);

      return(event++);

    }


    void TimerDevice::removeTimer(TimerEvent event) {

      std::map<TimerEvent, Listener *>::iterator it = timersList.find(event);

      if (it != timersList.end()) {
        abortIO(it->second->timerRequest);
        delete it->second;
        it->second = 0;
        timersList.erase(it);
      }

    }


    void TimerDevice::disableTimer(TimerEvent event) {

      std::map<TimerEvent, Listener *>::iterator it = timersList.find(event);

      if (it != timersList.end() && it->second->enabled) {
        abortIO(it->second->timerRequest);
        it->second->enabled = false;
      }

    }


    void TimerDevice::enableTimer(TimerEvent event) {

      std::map<TimerEvent, Listener *>::iterator it = timersList.find(event);

      if (it != timersList.end() && !it->second->enabled) {
        sendIO(it->second->timerRequest,it->second->seconds,it->second->micros);
        it->second->enabled = true;
      }

    }


    bool TimerDevice::doEvents(uint32) {

      bool done = false;

      TimerMessage timerMessage;

      while(masterRequest->getMessagePort()->getMessage(&timerMessage)) {
        done |= handleEvent(timerMessage);
      }

      return(done);

    }


    bool TimerDevice::handleEvent(TimerMessage &timerMessage) {

      bool done = false;

      TimerEventMethod eventMethod;
      ITimerEvent     *eventClass;

      for(std::map<TimerEvent, Listener *>::iterator it = timersList.begin(); it != timersList.end(); ++it) {
        if (it->second->timerRequest->getTimerReq() == reinterpret_cast<struct ::TimeRequest *>(timerMessage.getMessage())) {
          eventMethod = it->second->eventMethod;
          eventClass  = it->second->eventClass;
          done |= (eventClass->*eventMethod)(it->first);
          if (it->second->repeat) sendIO(it->second->timerRequest,it->second->seconds,it->second->micros);
          break;
        }
      }

      return(done);

    }


    bool TimerDevice::wait(uint32 seconds, uint32 micros) {

      bool done = false;

      TimerMessage timerMessage;

      sendIO(timerRequest,seconds,micros);

      used = true;

      while(!done) {
        uint32 sigs = IExec->Wait(timerBit | SIGBREAKF_CTRL_C);
        if (sigs & SIGBREAKF_CTRL_C) {
          abortIO(timerRequest);
          return(false);
        }
        while(masterRequest->getMessagePort()->getMessage(&timerMessage)) {
          if (timerRequest->getTimerReq() == reinterpret_cast<struct ::TimeRequest *>(timerMessage.getMessage())) done = true;
          else done |= handleEvent(timerMessage);
        }
      }

      return(done);

    }


  }
}

