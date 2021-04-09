#ifndef RAPLUS_SOCKETS_SOCKETEVENTS_HPP
#define RAPLUS_SOCKETS_SOCKETEVENTS_HPP

#include <map>

#include <exec/types.h>

#include <libraries/bsdsocket.h>

#include "Exec/SignalEvents.hpp"

#include "Socket.hpp"
#include "SocketException.hpp"


namespace RAPlus {
  namespace Sockets {


    class ISocketEvent : public Exec::IEvent { };

    typedef bool (ISocketEvent::*SocketEventMethod)(Socket *socket);


    class SocketEvents : public RAPlus::Exec::SignalEvents {

      public:

                 SocketEvents() { }
        virtual ~SocketEvents();

        virtual void    addReader(Socket *socket, ISocketEvent *cls, SocketEventMethod func);
        virtual void removeReader(Socket *socket);

        virtual void    addWriter(Socket *socket, ISocketEvent *cls, SocketEventMethod func);
        virtual void removeWriter(Socket *socket);

        virtual uint32 waitSignals(bool onePass = false);

      private:

        class Listener {

          public:

            SocketEventMethod eventMethod;
            ISocketEvent     *eventClass;

        };

        fd_set readSet;
        fd_set writeSet;

        std::map<Socket *, Listener *> readerList;
        std::map<Socket *, Listener *> writerList;

        long getMaxFD();

    };


  }
}


#endif // RAPLUS_SOCKETS_SOCKETEVENTS_HPP

