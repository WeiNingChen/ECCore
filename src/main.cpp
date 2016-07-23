#include <iostream>
#include "EC_Core.h"
#include "thread.h"

using namespace std;

int main()
{
    ecc_core core;
    
    /* Start ECC_CORE on another thread */
    ThreadExc _th(&core);
    _th.StartInternalThread();
    string str;
    int ctr;
    
    /* First round, set the curve parameters */

    core.setCtrl(0);
    str = "ffffffff ffffffff ffffffff fffffffe ffffffff fffffffc";
    core.setCoreR1(str);
    str = "64210519 e59c80e7 0fa7e9ab 72243049 feb8deec c146b9b1";
    core.setCoreR2(str);
    str = "ffffffff ffffffff ffffffff fffffffe ffffffff ffffffff";
    core.setCoreR3(str);
    
    /* Send start signal */
    core.setStart(true);
    

    /* Enter the event loop, and keep checking the ready signal */
    while(1){
        if(core.readReady()){
            /* Print the result of last round */
            cout<<"R5 = ";
            cout<<core.readCoreR5()<<endl;
            cout<<"R6 = ";
            cout<<core.readCoreR6()<<endl;
            
            /* Set parameters */
            cout<<"Set ctrl:"<<endl;
            cin>>ctr;
            core.setCtrl(ctr);
            cout<<"Set R1:"<<endl;
            cin>>str;
            core.setCoreR1(str);
            cout<<"Set R2:"<<endl;
            cin>>str;
            core.setCoreR2(str);
            cout<<"Set R3:"<<endl;
            cin>>str;
            core.setCoreR3(str);
            cout<<"Set R4:"<<endl;
            cin>>str;
            core.setCoreR4(str);

            /* Send start signal */
            core.setStart(true);
        }
    }
}
