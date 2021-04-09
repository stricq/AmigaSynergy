#include "MessagePort.hpp"

#include "Exception.hpp"
#include "OutOfMemoryException.hpp"

#include <proto/exec.h>

#include <stdio.h>


namespace RAPlus {
  namespace Exec {


    MessagePort::MessagePort() :
      portOwner(true),
      referenceCount(1),
      replyPort(0) {

      struct TagItem portTags[] = {
        { ASOPORT_Pri,    0 },
        { ASOPORT_Public, TRUE },
        { ASO_NoTrack,    FALSE },
        { TAG_DONE,       0 }
      };

      port = (struct MsgPort *)IExec->AllocSysObject(ASOT_PORT,portTags);

      if (port == 0) throw Exception("Unable to create a Message Port.");

      printf("MessagePort::MessagePort() - port = 0x%08x\n",port);

    }


    MessagePort::MessagePort(const std::string &portName, int8 priority) :
      portOwner(true),
      referenceCount(1),
      replyPort(0),
      name(portName) {

      struct TagItem portTags[] = {
        { ASOPORT_Name,     (uint32)name.c_str() },
        { ASOPORT_Pri,      priority },
        { ASOPORT_CopyName, TRUE },
        { ASOPORT_Public,   TRUE },
        { ASO_NoTrack,      FALSE },
        { TAG_DONE,         0 }
      };

      port = (struct MsgPort *)IExec->AllocSysObject(ASOT_PORT,portTags);

      if (port == 0) throw Exception("Unable to create a Message Port.");

      printf("MessagePort::MessagePort(%s) - port = 0x%08x\n",portName.c_str(),port);

    }


    MessagePort::MessagePort(struct MsgPort *msgPort, const std::string &portName) :
      portOwner(false),
      referenceCount(1),
      replyPort(0) {

      name = portName;

      port = msgPort;

    }


    MessagePort::~MessagePort() {

      printf("MessagePort::~MessagePort(%s) port = %p, portOwner = %d\n",name.c_str(),port,portOwner);

      if (port != 0 && portOwner) IExec->FreeSysObject(ASOT_PORT,port);

      printf("MessagePort::~MessagePort() - Done\n");

    }


    MessagePort *MessagePort::getMessagePort(const std::string &portName) {

      struct MsgPort *msgPort;

//    printf("MessagePort::getMessagePort(%s)\n",portName.c_str());

      IExec->Forbid();
      msgPort = IExec->FindPort((char *)portName.c_str());
      IExec->Permit();

//    printf("  Message port %s\n",(msgPort == 0 ? "is unique" : "exists"));

      if (msgPort != 0) return(new MessagePort(msgPort,portName));

      return(0);

    }


    bool MessagePort::findMessagePort(const std::string &portName) {

      struct MsgPort *msgPort;

//    printf("MessagePort::getMessagePort(%s)\n",portName.c_str());

      IExec->Forbid();
      msgPort = IExec->FindPort((char *)portName.c_str());
      IExec->Permit();

//    printf("  Message port %s\n",(msgPort == 0 ? "is unique" : "exists"));

      if (msgPort != 0) return(true);

      return(false);

    }


    MessagePort *MessagePort::getReplyPort() {

      if (replyPort == 0) return(0);

//    printf("MessagePort::getReplyPort() port = %p, name = %s\n",replyPort,replyPort->mp_Node.ln_Name);

      return(new MessagePort(replyPort,replyPort->mp_Node.ln_Name));

    }


    bool MessagePort::sendMessage(MessagePort *toPort,IMessage *message) {

      IPCMessage *ipcMessage;

      if (!(ipcMessage = (struct IPCMessage *)IExec->AllocVec(sizeof(struct IPCMessage),MEMF_PUBLIC | MEMF_CLEAR))) {
        throw OutOfMemoryException("Could not allocate memory for an IPCMessage.");
      }

      ipcMessage->msg.mn_Node.ln_Type = NT_MESSAGE;
      ipcMessage->msg.mn_Length = sizeof(struct IPCMessage);
      ipcMessage->msg.mn_ReplyPort = port;

//    printf("MessagePort::sendMessage(%s [%u] -> %s)\n",name.c_str(),static_cast<uint>(message->getType()),toPort->getPortName().c_str());

      ipcMessage->message = message;

      IExec->PutMsg(toPort->getMsgPort(),(struct Message *)ipcMessage);

      IExec->WaitPort(port);

      IExec->GetMsg(port);

      IExec->FreeVec(ipcMessage);

      return(true);

    }


    IMessage *MessagePort::recvMessage() {

      IMessage *message;

      IPCMessage *ipcMessage;

      if (!(ipcMessage = (struct IPCMessage *)IExec->GetMsg(port))) return(0);

      replyPort = ipcMessage->msg.mn_ReplyPort;

      message = ipcMessage->message->clone();

      IExec->ReplyMsg((struct Message *)ipcMessage);

      return(message);

    }


    bool MessagePort::getMessage(IMessage *message) {

      struct Message *msg = (struct Message *)IExec->GetMsg(port);

      message->setMessage(msg);

      return(msg != 0);

    }


    void MessagePort::replyMessage(IMessage *message) {

      if (message->getMessage() != 0) {
        IExec->ReplyMsg(message->getMessage());
        message->setMessage(0);
      }

    }


  }
}

