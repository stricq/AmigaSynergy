#ifndef REACTIONPLUS_EXEC_SIGNALEVENTS_HPP
#define REACTIONPLUS_EXEC_SIGNALEVENTS_HPP

#include <exec/types.h>

#include <map>
#include <list>


namespace RAPlus {
  namespace Exec {


    class IEvent { };

    typedef bool (IEvent::*EventMethod)(uint32 signals);


    class ISignalEvents {

      public:
                 ISignalEvents() { }
        virtual ~ISignalEvents() { }

        virtual uint32 getSignal() = 0;

        virtual bool doEvents(uint32 signals) = 0;

    };


    class SignalEvents : public ISignalEvents {

      public:

                 SignalEvents() : done(false) { }
        virtual ~SignalEvents();

        void    addListener(uint32 signal, IEvent *cls, EventMethod func);
        void    addListener(ISignalEvents *eventsClass);
        void removeListener(uint32 signal);
        void removeListener(ISignalEvents *eventsClass);

        bool isDone() { return(done); }

        virtual uint32 getSignal();
        virtual uint32 waitSignals(bool onePass = false);

        virtual bool doEvents(uint32 signals);

      protected:

        bool done;

      private:

        class Listener {

          public:

            EventMethod eventMethod;
            IEvent     *eventClass;

        };

        std::map<uint32, Listener *> listenerList;

        std::list<ISignalEvents *> classList;

    };

  }
}

#endif // REACTIONPLUS_EXEC_SIGNALEVENTS_HPP

