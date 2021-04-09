#include "MessagePortFactory.hpp"

#include <stdio.h>


namespace RAPlus {
  namespace Exec {


    MessagePortFactory *MessagePortFactory::portFactoryInstance = 0;


    MessagePortFactory *MessagePortFactory::instance() {

      if (portFactoryInstance == 0) portFactoryInstance = new MessagePortFactory();

      if (portFactoryInstance == 0) throw OutOfMemoryException("Could not create a MessagePortFactory instance.");

      portFactoryInstance->reference++;

      return(portFactoryInstance);

    }


    void MessagePortFactory::removeMessagePortFactory() {

      if (portFactoryInstance == 0) return;

      portFactoryInstance->reference--;

      if (portFactoryInstance->reference == 0) {
        delete portFactoryInstance;
        portFactoryInstance = 0;
      }

    }


    MessagePortFactory::~MessagePortFactory() {

  //  printf("MessagePortFactory::~MessagePortFactory()\n");

      semaphore.obtain();

      while(!portList.empty()) {
        printf("MessagePortFactory::~MessagePortFactory() - Delete MessagePort %s\n",portList.begin()->first.c_str());
        delete portList.begin()->second;
        portList.begin()->second = 0;
        portList.erase(portList.begin());
      }

      semaphore.release();

  //  printf("MessagePortFactory::~MessagePortFactory() - Done\n");

    }


    MessagePort *MessagePortFactory::getMessagePort(const std::string &portName, int8 priority, bool unique) {

      semaphore.obtain();

      std::map<std::string, MessagePort *>::iterator it = portList.find(portName);

      if (it != portList.end()) {
        if (unique) {
          semaphore.release();
          throw UniqueMessagePortException("Unique MessagePort requested, but it has been used.");
        }
  //    printf("MessagePortFactory::getMessagePort(%s) in the list, returning\n",portName.c_str());
        it->second->addReference();
        semaphore.release();
        return(it->second);
      }

      bool exists = MessagePort::findMessagePort(portName);

  //  printf("MessagePortFactory::getMessagePort(%s,%d,%d) exists = %d\n",portName.c_str(),priority,unique,exists);

      MessagePort *msgPort;

      if (unique && exists) {
        semaphore.release();
        throw UniqueMessagePortException("Unique MessagePort requested, but it already exists.");
      }

      if (exists) msgPort = MessagePort::getMessagePort(portName);
      else msgPort = new MessagePort(portName,priority);

      portList[portName] = msgPort;

      semaphore.release();

      return(msgPort);

    }


    MessagePort *MessagePortFactory::addMessagePort(MessagePort *msgPort) {

      semaphore.obtain();

      std::map<std::string, MessagePort *>::iterator it = portList.find(msgPort->getPortName());

      if (it != portList.end()) {
        delete msgPort;
        it->second->addReference();
        msgPort = it->second;
      }
      else portList[msgPort->getPortName()] = msgPort;

      semaphore.release();

      return(msgPort);

    }


    void MessagePortFactory::deleteMessagePort(const std::string &portName) {

      semaphore.obtain();

      std::map<std::string, MessagePort *>::iterator it = portList.find(portName);

      if (it != portList.end()) {
        it->second->subReference();
        printf("MessagePortFactory::deleteMessagePort(%s) referenceCount = %d\n",portName.c_str(),it->second->getReferenceCount());
        if (it->second->getReferenceCount() == 0) {
          printf("  About to delete it->second\n");
          delete it->second;
          it->second = 0;
          printf("  About to erase from map\n");
          portList.erase(it);
          printf("  Deleted port\n");
        }
      }

      semaphore.release();

    }


  }
}

