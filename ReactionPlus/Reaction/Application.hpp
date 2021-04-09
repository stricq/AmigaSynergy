#ifndef REACTIONPLUS_APPLICATION_HPP
#define REACTIONPLUS_APPLICATION_HPP

#include "Exec/MessagePort.hpp"
#include "Exec/SignalEvents.hpp"

#include <exec/ports.h>

#include <vector>


namespace RAPlus {
  namespace Reaction {

    class AppWindow;

    class Application : public Exec::ISignalEvents {

      public:

                 Application();
        virtual ~Application();

        static Reaction::Application *instance();
        static void dispose();

        void addWindow(Reaction::AppWindow *appWin);
        void removeWindow(Reaction::AppWindow *appWin);

        void closeAllRemember();
        void openAllRemember();

        bool doEvents(uint32 signals);

        ULONG getSignal() { return(appPort->getSignal()); }

      private:

        std::vector<Reaction::AppWindow *> appList;

        static Reaction::Application *app;

        Exec::MessagePort *appPort;

    };

  }
}

#endif // REACTIONPLUS_APPLICATION_HPP

