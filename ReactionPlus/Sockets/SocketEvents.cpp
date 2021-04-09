#include "SocketEvents.hpp"

#include <proto/bsdsocket.h>
#include <proto/exec.h>


namespace RAPlus {
  namespace Sockets {


    SocketEvents::~SocketEvents() {

      while(!readerList.empty()) {
        delete readerList.begin()->second;
        readerList.begin()->second = 0;
        readerList.erase(readerList.begin());
      }

    }


    void SocketEvents::addReader(Socket *socket, ISocketEvent *cls, SocketEventMethod func) {

      Listener *listener = new Listener();

      listener->eventMethod = func;
      listener->eventClass  = cls;

      readerList[socket] = listener;

    }


    void SocketEvents::removeReader(Socket *socket) {

      std::map<Socket *, Listener *>::iterator it = readerList.find(socket);

      if (it != readerList.end()) {
        delete it->second;
        it->second = 0;
        readerList.erase(it);
      }

    }


    void SocketEvents::addWriter(Socket *socket, ISocketEvent *cls, SocketEventMethod func) {

      Listener *listener = new Listener();

      listener->eventMethod = func;
      listener->eventClass  = cls;

      writerList[socket] = listener;

    }


    void SocketEvents::removeWriter(Socket *socket) {

      std::map<Socket *, Listener *>::iterator it = writerList.find(socket);

      if (it != writerList.end()) {
        delete it->second;
        it->second = 0;
        writerList.erase(it);
      }

    }


    long SocketEvents::getMaxFD() {

      long maxFD = -1;

      FD_ZERO(&readSet);
      FD_ZERO(&writeSet);

      for(std::map<Socket *, Listener *>::iterator it = readerList.begin(); it != readerList.end(); ++it) {
        int32 socket = it->first->getSocket();
        if (it->first->isConnected()) {
          if (socket > maxFD) maxFD = socket;
          FD_SET(socket,&readSet);
        }
      }

      for(std::map<Socket *, Listener *>::iterator it = writerList.begin(); it != writerList.end(); ++it) {
        int32 socket = it->first->getSocket();
        if (it->first->isConnected()) {
          if (socket > maxFD) maxFD = socket;
          FD_SET(socket,&writeSet);
        }
      }

//    printf("SocketEvents::getMaxFD() = %ld\n",maxFD);

      return(maxFD);

    }


    uint32 SocketEvents::waitSignals(bool onePass) {

      long maxFD;
      long numFDs = 0;

      uint32 signals;

      fd_set rSet;
      fd_set wSet;

      done = false;

      do {
        maxFD = getMaxFD();
        signals = getSignal() | SIGBREAKF_CTRL_C;
        rSet = readSet;
        wSet = writeSet;
//      printf("SocketEvents::waitSignals() - maxFD = %ld\n",maxFD);
        if (maxFD > -1) numFDs = ISocket->WaitSelect(maxFD + 1,&rSet,&wSet,NULL,NULL,&signals);
        else {
          signals = IExec->Wait(signals);
          numFDs = 0;
        }
//      printf("SocketEvents::waitSignals() - numFDs = %ld\n",numFDs);
        if (numFDs == -1) throw SocketException(Socket::getErrorStr(),Socket::getErrorNum());
        else if (numFDs == 0) {
          if (signals & SIGBREAKF_CTRL_C) done = true;
          done |= doEvents(signals);
        }
        else {
          SocketEventMethod eventMethod;
          ISocketEvent     *eventClass;
          for(std::map<Socket *, Listener *>::iterator it = readerList.begin(); it != readerList.end(); ++it) {
            if (FD_ISSET(it->first->getSocket(),&rSet)) {
              eventMethod = it->second->eventMethod;
              eventClass  = it->second->eventClass;
              done |= (eventClass->*eventMethod)(it->first);
            }
          }
          for(std::map<Socket *, Listener *>::iterator it = writerList.begin(); it != writerList.end(); ++it) {
            if (FD_ISSET(it->first->getSocket(),&wSet)) {
              eventMethod = it->second->eventMethod;
              eventClass  = it->second->eventClass;
              done |= (eventClass->*eventMethod)(it->first);
            }
          }
        }
      } while(!done && !onePass);

      return(signals);

    }


  }
}

