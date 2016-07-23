#include<iostream>
#include<pthread.h>
#include "EC_Core.h"

using namespace std;


class Thread
{
public:
   Thread() {}
   virtual ~Thread() {}

   bool StartInternalThread()
   {
      return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
   }

   void WaitForInternalThreadToExit()
   {
      (void) pthread_join(_thread, NULL);
   }

protected:
   virtual void InternalThreadEntry() = 0;

private:
   static void * InternalThreadEntryFunc(void * This) {((Thread*)This)->InternalThreadEntry(); return NULL;}

   pthread_t _thread;
};



class ThreadExc : public Thread
{
public:
    ThreadExc(ecc_core* _core){ core = _core;}
    ecc_core* core;
protected:
    void InternalThreadEntry()
    {
        //cout<<"In Thread!"<<endl;
        core -> run();
    }
};
