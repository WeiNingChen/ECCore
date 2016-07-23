#include <EC_Core.h>
#include <iostream>
#include <ECC.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;



void ecc_core::setCoreR1(string& str)
{
    R1 = mpz_class(str,16);
}

void ecc_core::setCoreR2(string& str)
{
    R2 = mpz_class(str,16);
}

void ecc_core::setCoreR3(string& str)
{

    R3 = mpz_class(str,16);
}

void ecc_core::setCoreR4(string& str)
{
    R4 = mpz_class(str,16);
}

void ecc_core::setCoreR5(string& str)
{
    R5 = mpz_class(str,16);
}

void ecc_core::setCoreR6(string& str)
{
    R6 = mpz_class(str,16);
}


string  ecc_core::readCoreR5()
{   
    return R5.get_str(16);
}

string  ecc_core::readCoreR6()
{   
    return R6.get_str(16);
}

void ecc_core::setStart(bool _start )
{
    start = _start;
}

void ecc_core::setCtrl(int _ctrl)
{
    ctrl = _ctrl;
}

bool ecc_core::readReady()
{
    return ready;
}


void ecc_core::setReady(bool _ready)
{
    ready = _ready;
}

void ecc_core::run()
{
    while(1){
        while(start){
            ready = false;
            switch (ctrl){
                case 0:
                    setCharExc();
                    break;
                case 1:
                    addExc();
                    break;
                case 2:
                    multExc();
                    break;
                default :
                    cerr<<"In Switch"<<endl;
                    break;
            }
        }
    }
}

void ecc_core::setCharExc()
{   
    // Set _char in ECPoint to 0xR3
    cout<<"Set Characteristic in EC!"<<endl;
    ECpoint::setCurveA(R1);
    ECpoint::setCurveB(R2); 
    ECpoint::setChar(R3);
    ready = true;
    start = false;
}

void ecc_core::addExc()
{
    ECpoint ans;
    ECpoint temp(projPoint(R3,R4,1));
    ans = ECpoint(projPoint(R1,R2,1))+temp;
    R5 = ans.getCoordX();
    R6 = ans.getCoordY();
    ready = true;
    start = false;
}

void ecc_core::multExc()
{
    ECpoint ans;
    ans = ECpoint(projPoint(R1,R2,1))*R3;
    R5 = ans.getCoordX();
    R6 = ans.getCoordY();
    ready = true;
    start = false;
}



