#include "SignalSemaphore.hpp"

#include "Exception.hpp"
#include "OutOfMemoryException.hpp"

#include <proto/exec.h>

#include <stdio.h>


namespace RAPlus {


  SignalSemaphore::SignalSemaphore(const std::string &semaphoreName, uint32 priority) :
    owner(true),
    referenceCount(1),
    internalCount(0),
    task(0),
    name(semaphoreName) {

    printf("SignalSemaphore::SignalSemaphore(%s)\n",semaphoreName.c_str());

    struct TagItem semaphoreTags[] = {
      { ASOSEM_Name,     (uint32)name.c_str() },
      { ASOSEM_Size,     sizeof(struct ::SignalSemaphore) },
      { ASOSEM_Pri,      priority },
      { ASOSEM_CopyName, TRUE },
      { ASOSEM_Public,   TRUE },
      { ASO_NoTrack,     FALSE },
      { TAG_DONE,        0 }
    };

    semaphore = (struct ::SignalSemaphore *)IExec->AllocSysObject(ASOT_SEMAPHORE,semaphoreTags);

    if (semaphore == 0) throw Exception("Unable to create an Exec SignalSemaphore.");

    printf("SignalSemaphore::SignalSemaphore - Done\n");

  }


  SignalSemaphore::SignalSemaphore(struct ::SignalSemaphore *semaphore, const std::string &semaphoreName) :
    owner(false),
    referenceCount(1),
    semaphore(semaphore),
    name(semaphoreName) { }


  SignalSemaphore::~SignalSemaphore() {

    printf("SignalSemaphore::~SignalSemaphore() - semaphore = %p, owner = %d\n",semaphore,owner);

    if (semaphore != 0 && owner) {
      IExec->RemSemaphore(semaphore);
      IExec->ObtainSemaphore(semaphore);
      IExec->ReleaseSemaphore(semaphore);
      IExec->FreeSysObject(ASOT_SEMAPHORE,semaphore);
    }

    printf("SignalSemaphore::~SignalSemaphore() - Done\n");

  }


  SignalSemaphore *SignalSemaphore::getSignalSemaphore(const std::string &semaphoreName) {

    printf("SignalSemaphore::getSignalSemaphore(%s)\n",semaphoreName.c_str());

    struct ::SignalSemaphore *semaphore;

    IExec->Forbid();
    semaphore = IExec->FindSemaphore((char *)semaphoreName.c_str());
    IExec->Permit();

    if (semaphore != 0) return(new SignalSemaphore(semaphore,semaphoreName));

    return(0);

  }


  bool SignalSemaphore::findSignalSemaphore(const std::string &semaphoreName) {

    struct ::SignalSemaphore *semaphore;

//  printf("SignalSemaphore::findSignalSemaphore(%s)\n",semaphoreName.c_str());

    IExec->Forbid();
    semaphore = IExec->FindSemaphore((char *)semaphoreName.c_str());
    IExec->Permit();

    if (semaphore != 0) return(true);

    return(false);

  }


  void SignalSemaphore::obtain(void) {

    if (task == IExec->FindTask(0)) {
      internalCount++;
//    printf("SignalSemaphore::obtain() [%s] Task %p owns me, count = %d\n",name.c_str(),task,internalCount);
      return;
    }
//  else if (task != 0) printf("SignalSemaphore::obtain() [%s] Task %p is waiting for me\n",name.c_str(),IExec->FindTask(0));

    if (semaphore) IExec->ObtainSemaphore(semaphore);

    internalCount = 1;

    task = IExec->FindTask(0);

//  printf("SignalSemaphore::obtain() [%s] Task %p now owns me\n",name.c_str(),task);

  }


  void SignalSemaphore::release(void) {

    if (task == IExec->FindTask(0)) {
      internalCount--;
//    printf("SignalSemaphore::release() [%s] Task %p still owns me, count = %d\n",name.c_str(),task,internalCount);
      if (internalCount > 0) return;
    }

    if (semaphore) IExec->ReleaseSemaphore(semaphore);

    task = 0;

//  printf("SignalSemaphore::release() [%s] No one owns me\n",name.c_str());

  }


}


