#ifndef EC_CORE_H
#define EC_CORE_H

#include <iostream>
//#include <ECC.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

class ecc_core
{
public:
    ecc_core(){start = false; ready = false;};
    ~ecc_core(){};
    
    void setCoreR1(string&);
    void setCoreR2(string&);
    void setCoreR3(string&);
    void setCoreR4(string&);
    string readCoreR5();
    string readCoreR6();
    void setStart(bool);
    void setCtrl(int);
    bool readReady();
    void run();

private:
    void setReady(bool);
    void setCoreR5(string&);
    void setCoreR6(string&);

    void setCharExc();
    void addExc();
    void multExc();
    mpz_class R1,R2,R3,R4,R5,R6;
    int ctrl;
    bool start, ready;

};



#endif
