#ifndef SYNERGYC_HPP
#define SYNERGYC_HPP

#include "Exec/TimerDevice.hpp"

#include "Commodities/Commodity.hpp"

#include "Exec/ClipboardDevice.hpp"
#include "Exec/Exec.hpp"
#include "Exec/Task.hpp"

#include "IFFParse/IFFClipboard.hpp"

#include "Sockets/Socket.hpp"
#include "Sockets/SocketEvents.hpp"
#include "Sockets/Packet.hpp"

#include "Command.hpp"
#include "InputInjector.hpp"

#include <string>

using namespace RAPlus;


class synergyc : public Sockets::ISocketEvent, public Commodities::ICommodityEvent, public Exec::ITimerEvent {

  public:

    synergyc();
   ~synergyc();

    void run(char *host, char *os);

    void shutdown();

  private:

    bool fatal;
    bool enabled;

    InputInjector *injector;

    Commodities::Commodity *commodity;

    Exec::TimerDevice *timer;
    Exec::ClipboardDevice *clip;

    Intuition::Rectangle lastDim;

    Sockets::Socket *socket;

    bool socket_OnRead(Sockets::Socket *socket);

    bool commodity_OnEnable();
    bool commodity_OnDisable();
    bool commodity_OnKill();

    bool timer_OnEvent(Exec::TimerEvent event);

    bool clip_OnClipboardChange(uint32 signals);

};


#endif // SYNERGYC_HPP

