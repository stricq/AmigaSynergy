#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "InputInjector.hpp"

#include "IFFParse/IFFClipboard.hpp"

#include "Intuition/IntuitionBase.hpp"
#include "Intuition/Pointer.hpp"

#include "Sockets/Socket.hpp"
#include "Sockets/Packet.hpp"

#include <string>

using namespace RAPlus;


class UnknownPacketException { };


class ICommand {

  public:

    virtual ~ICommand();

    std::string getType() { return(type); }

  protected:

    ICommand(Sockets::Packet *pkt) : packet(pkt) { }

    Sockets::Packet *packet;

    std::string type;

    static long clipSequence;

};


class IReaderCommand : public ICommand {

  public:

    virtual ~IReaderCommand() { if (response) delete response; }

    static IReaderCommand *readerFactory(Sockets::Packet *pkt);

    virtual void parse() = 0;

    ICommand *getResponse() { return(response); }

    bool isClosed() { return(closed); }
    bool isFatal()  { return(fatal); }

  protected:

    IReaderCommand(Sockets::Packet *pkt, std::string cmd) : ICommand(pkt), response(0), closed(false), fatal(false) { type = cmd; }

    ICommand *response;

    bool closed;
    bool fatal;

};


class RHelloCommand : public IReaderCommand {

  public:

    RHelloCommand(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int major;
    int minor;

};


class RGoodbye : public IReaderCommand {

  public:

    RGoodbye(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RScreenEnter : public IReaderCommand {

  public:

    RScreenEnter(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int mouseX;
    int mouseY;

    uint16 modifiers;

    long sequence;

};


class RScreenLeave : public IReaderCommand {

  public:

    RScreenLeave(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RGrabClipboard : public IReaderCommand {

  public:

    RGrabClipboard(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int8 clipID;

    int32 sequence;

};


class RScreenSaver : public IReaderCommand {

  public:

    RScreenSaver(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RScreenAck : public IReaderCommand {

  public:

    RScreenAck(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RKeyDown : public IReaderCommand {

  public:

    RKeyDown(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int keyID;
    int modifiers;
    int button;

};


class RKeyRepeat : public IReaderCommand {

  public:

    RKeyRepeat(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int keyID;
    int modifiers;
    int repeats;
    int button;

};


class RKeyUp : public IReaderCommand {

  public:

    RKeyUp(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int keyID;
    int modifiers;
    int button;

};


class RMouseDown : public IReaderCommand {

  public:

    RMouseDown(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int button;

};


class RMouseUp : public IReaderCommand {

  public:

    RMouseUp(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int button;

};


class RMouseMove : public IReaderCommand {

  public:

    RMouseMove(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int mouseX;
    int mouseY;

};


class RMouseWheel : public IReaderCommand {

  public:

    RMouseWheel(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int deltaY;
    int deltaX;

};


class RResetOptions : public IReaderCommand {

  public:

    RResetOptions(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RSetOptions : public IReaderCommand {

  public:

    RSetOptions(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RClipboard : public IReaderCommand {

  public:

    RClipboard(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int8 clipID;

    int32 sequence;

};


class RScreenInfo : public IReaderCommand {

  public:

    RScreenInfo(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RKeepAlive : public IReaderCommand {

  public:

    RKeepAlive(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RErrorVersion : public IReaderCommand {

  public:

    RErrorVersion(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

    int major;
    int minor;

};


class RErrorBusy : public IReaderCommand {

  public:

    RErrorBusy(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RErrorUnknown : public IReaderCommand {

  public:

    RErrorUnknown(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


class RErrorProtocol : public IReaderCommand {

  public:

    RErrorProtocol(Sockets::Packet *pkt, std::string cmd) : IReaderCommand(pkt,cmd) { parse(); }

    void parse();

};


// -------------------- Writer Commands


class IWriterCommand : public ICommand {

  public:

    virtual ~IWriterCommand() { }

    static IWriterCommand *writerFactory(std::string cmd);

    virtual  bool prepareResponse() = 0;

    void writePacket(Sockets::Socket *socket) { packet->writePacket(socket); }

  protected:

    IWriterCommand(Sockets::Packet *pkt, std::string &cmd) : ICommand(pkt) { type = cmd; }

};


class WHelloCommand : public IWriterCommand {

  public:

    WHelloCommand(Sockets::Packet *pkt, std::string &cmd) : IWriterCommand(pkt,cmd) { }

    bool prepareResponse();

};


class WKeepAlive : public IWriterCommand {

  public:

    WKeepAlive(Sockets::Packet *pkt, std::string &cmd) : IWriterCommand(pkt,cmd) { }

    bool prepareResponse();

};


class WScreenInfo : public IWriterCommand {

  public:

    WScreenInfo(Sockets::Packet *pkt, std::string &cmd) : IWriterCommand(pkt,cmd) { }

    bool prepareResponse();

};


class WGrabClipboard : public IWriterCommand {

  public:

    WGrabClipboard(Sockets::Packet *pkt, std::string &cmd) : IWriterCommand(pkt,cmd) { }

    bool prepareResponse();

};


class WSendClipboard : public IWriterCommand {

  public:

    WSendClipboard(Sockets::Packet *pkt, std::string &cmd) : IWriterCommand(pkt,cmd) { }

    bool prepareResponse();

};


#endif // COMMAND_HPP

