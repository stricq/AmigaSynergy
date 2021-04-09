#include "SignalSemaphoreFactory.hpp"

#include "OutOfMemoryException.hpp"

#include <stdio.h>


namespace RAPlus {


  SignalSemaphoreFactory *SignalSemaphoreFactory::semaphoreFactoryInstance = 0;


  SignalSemaphoreFactory *SignalSemaphoreFactory::instance() {

    if (semaphoreFactoryInstance == 0) semaphoreFactoryInstance = new SignalSemaphoreFactory();

    if (semaphoreFactoryInstance == 0) throw OutOfMemoryException("Could not create a SignalSemaphoreFactory instance.");

    semaphoreFactoryInstance->reference++;

    return(semaphoreFactoryInstance);

  }


  void SignalSemaphoreFactory::removeSignalSemaphoreFactory() {

    if (semaphoreFactoryInstance == 0) return;

    semaphoreFactoryInstance->reference--;

    if (semaphoreFactoryInstance->reference == 0) {
      delete semaphoreFactoryInstance;
      semaphoreFactoryInstance = 0;
    }

  }


  SignalSemaphoreFactory::~SignalSemaphoreFactory() {

//  printf("SignalSemaphoreFactory::~SignalSemaphoreFactory()\n");

    semaphore.obtain();

    while(!semaphoreList.empty()) {
      printf("SignalSemaphoreFactory::~SignalSemaphoreFactory() - Delete SignalSemaphore %s\n",semaphoreList.begin()->first.c_str());
      delete semaphoreList.begin()->second;
      semaphoreList.begin()->second = 0;
      semaphoreList.erase(semaphoreList.begin());
    }

    semaphore.release();

//  printf("SignalSemaphoreFactory::~SignalSemaphoreFactory() - Done\n");

  }


  SignalSemaphore *SignalSemaphoreFactory::getSignalSemaphore(const std::string &semaphoreName, uint32 priority, bool unique) {

//  printf("SignalSemaphoreFactory::getSignalSemaphore(%s,%u,%d)\n",semaphoreName.c_str(),priority,unique);

    semaphore.obtain();

    std::map<std::string, SignalSemaphore *>::iterator it = semaphoreList.find(semaphoreName);

    if (it != semaphoreList.end()) {
      if (unique) throw UniqueSignalSemaphoreException("Unique SignalSemaphore requested, but it already exists.");
      it->second->addReference();
      semaphore.release();
      return(it->second);
    }

    bool exists = SignalSemaphore::findSignalSemaphore(semaphoreName);

    SignalSemaphore *sema;

    if (unique && exists) {
      semaphore.release();
      throw UniqueSignalSemaphoreException("Unique SignalSemaphore requested, but it already exists.");
    }

    if (exists) sema = SignalSemaphore::getSignalSemaphore(semaphoreName);
    else sema = new SignalSemaphore(semaphoreName,priority);

    semaphoreList[semaphoreName] = sema;

    semaphore.release();

//  printf("SignalSemaphoreFactory::getSignalSemaphore - Done\n");

    return(sema);

  }


  void SignalSemaphoreFactory::deleteSignalSemaphore(const std::string &semaphoreName) {

    semaphore.obtain();

    std::map<std::string, SignalSemaphore *>::iterator it = semaphoreList.find(semaphoreName);

    if (it != semaphoreList.end()) {
      it->second->subReference();
      printf("SignalSemaphoreFactory::deleteSignalSemaphore(%s) referenceCount = %d\n",semaphoreName.c_str(),it->second->getReferenceCount());
      if (it->second->getReferenceCount() == 0) {
        delete it->second;
        it->second = 0;
        semaphoreList.erase(it);
        printf("  Deleted semaphore\n");
      }
    }

    semaphore.release();

  }


}


