#include "Commodity.hpp"

#include <proto/commodities.h>
#include <proto/exec.h>

#include <stdio.h>


struct Library *CxBase = 0;
struct CommoditiesIFace *ICommodities = 0;


namespace RAPlus {
  namespace Commodities {


    Commodity *Commodity::commodityInstance = 0;


    Commodity *Commodity::instance(const std::string &name, int8 priority) {

      if (commodityInstance == 0) commodityInstance = new Commodity(name,priority);

      return(commodityInstance);

    }


    Commodity::Commodity(const std::string &name, int8 priority) :
      enabled(true),
      brokerName(name),
      brokerTitle(name),
      brokerDescription(name),
      brokerObject(0),
      msgPort(name,priority) {

      if (CxBase == 0) {
        if ((CxBase = IExec->OpenLibrary("commodities.library",51)) == NULL) throw CommodityException("Could not open commodities.library v51");
        if ((ICommodities = (struct CommoditiesIFace *)IExec->GetInterface(CxBase,"main",1,TAG_DONE)) == NULL) {
          IExec->CloseLibrary(CxBase);
          throw CommodityException("Could not open commodities main interface v1");
        }
      }

      broker.nb_Version = NB_VERSION;
      broker.nb_Name    = const_cast<char *>(brokerName.c_str());
      broker.nb_Title   = const_cast<char *>(brokerTitle.c_str());
      broker.nb_Descr   = const_cast<char *>(brokerDescription.c_str());
      broker.nb_Unique  = NBU_DUPLICATE;
      broker.nb_Flags   = 0;
      broker.nb_Pri     = priority;
      broker.nb_Port    = msgPort.getMsgPort();
      broker.nb_ReservedChannel = 0;

    }


    Commodity::~Commodity() {

      CommodityMessage brokerMessage;

      ICommodities->DeleteCxObj(brokerObject);

      while(msgPort.getMessage(&brokerMessage)) msgPort.replyMessage(&brokerMessage);

      while(!listenerList.empty()) {
        delete listenerList.begin()->second;
        listenerList.begin()->second = 0;
        listenerList.erase(listenerList.begin());
      }

      closeLibrary();

    }


    void Commodity::closeLibrary() {

      IExec->DropInterface((struct Interface *)ICommodities);

      IExec->CloseLibrary(CxBase);

    }


    void Commodity::setName(const std::string &name) {

      brokerName = name;

      broker.nb_Name = const_cast<char *>(brokerName.c_str());

    }


    void Commodity::setTitle(const std::string &title) {

      brokerTitle = title;

      broker.nb_Title = const_cast<char *>(brokerTitle.c_str());

    }


    void Commodity::setDescription(const std::string &description) {

      brokerDescription = description;

      broker.nb_Descr = const_cast<char *>(brokerDescription.c_str());

    }


    bool Commodity::doEvents(uint32) {

      bool done = false;

      uint32 msgID;
      uint32 msgType;

      CommodityMessage brokerMessage;

      while(msgPort.getMessage(&brokerMessage)) {
        msgID   = brokerMessage.getMessageID();
        msgType = brokerMessage.getMessageType();
        msgPort.replyMessage(&brokerMessage);
        switch(msgType) {
          case CXM_IEVENT: {
            break;
          }
          case CXM_COMMAND: {
            switch(msgID) {
              case CXCMD_ENABLE: {
                done |= fireEvent(CXEnable);
                break;
              }
              case CXCMD_DISABLE: {
                done |= fireEvent(CXDisable);
                break;
              }
              case CXCMD_APPEAR: {
                done |= fireEvent(CXAppear);
                break;
              }
              case CXCMD_DISAPPEAR: {
                done |= fireEvent(CXDisappear);
                break;
              }
              case CXCMD_LIST_CHG: {
                done |= fireEvent(CXListChange);
                break;
              }
              case CXCMD_KILL: {
                done |= fireEvent(CXKill);
                break;
              }
              case CXCMD_UNIQUE: {
                done |= fireEvent(CXUnique);
                break;
              }
            }
            break;
          }
        }
      }

      return(done);

    }


    bool Commodity::fireEvent(EventType event) {

      std::map<EventType, Listener *>::iterator it = listenerList.find(event);

      if (it != listenerList.end()) {
        CommodityEventMethod eventMethod = it->second->eventMethod;
        ICommodityEvent     *eventClass  = it->second->eventClass;
        return((eventClass->*eventMethod)());
      }

      return(false);

    }


    void Commodity::addListener(EventType event, ICommodityEvent *cls, CommodityEventMethod func) {

      Listener *listener = new Listener();

      listener->eventMethod = func;
      listener->eventClass  = cls;

      listenerList[event] = listener;

    }


    void Commodity::enable() {

      int32 cxError = CBERR_OK;

      if (brokerObject == 0) {
        brokerObject = ICommodities->CxBroker(&broker,&cxError);
        if (cxError != CBERR_OK) {
          switch(cxError) {
            case CBERR_SYSERR: {
              throw CommodityException("System Error (No memory?), Could not create the Broker object.");
            }
            case CBERR_VERSION: {
              throw CommodityException("Version Error, Could not create the Broker object.");
            }
            case CBERR_DUP: {
              throw UniqueCommodityException();
            }
            default: {
              throw CommodityException("Could not create the Commodities Exchange Broker object.");
            }
          }
        }
      }

      ICommodities->ActivateCxObj(brokerObject,TRUE);

      enabled = true;

    }


    void Commodity::disable() {

      ICommodities->ActivateCxObj(brokerObject,FALSE);

      enabled = false;

    }


  }
}
