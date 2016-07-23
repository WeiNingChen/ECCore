#include <iostream>
#include <gmp.h>
#include <gmpxx.h> 
#include "ECC.h"

#define infinity ECpoint(projPoint(1, 1, 0))
using namespace std;

mpz_class ECpoint::_char = 2;
int ECpoint::_order = 1;
mpz_class ECpoint::a = 1;
mpz_class ECpoint::b = 1;


//extern const mpz_t negOne = -1;

ECpoint::ECpoint(projPoint pt)
{
    coord.x = pt.x%_char;
	coord.y = pt.y%_char;
	coord.z = pt.z%_char;
}
ECpoint::ECpoint()
{
}

bool ECpoint::checkOnCurve()
{
	ECpoint temp = *this;
	temp.normalize();


	mpz_class x,y;
	y = (temp.coord.y*temp.coord.y)%_char;
	x = (temp.coord.x*temp.coord.x)%_char;
	x = ((x*temp.coord.x)%_char+a*coord.x+b)%_char;
	y = (y+_char)%_char;
	x = (x+_char)%_char;
	return x == y ;
}

void ECpoint::setChar(mpz_class chr)
{
	_char = chr;
}

void ECpoint::setOrder(int order)
{
	_order = order;
}

void ECpoint::setCurveA(mpz_class i)
{
	a = i;
}

void ECpoint::setCurveB(mpz_class i)
{
	b = i;
}

mpz_class ECpoint::getChar()
{
	return _char;
}
int ECpoint::getOrder()
{
	return _order;
}

void ECpoint::Double()
{
	normalize();

	// lambda = (3Xp^2+a)/2Yp
	//x = lambda^2 - 2 Xp
	//y = lambda(Xp-x)-Yp
	mpz_class lambda = (3*coord.x*coord.x+a)%_char;
	mpz_class Xp,Yp,temp1, base =  2*coord.y;
	mpz_class po(-1);
	mpz_powm(temp1.get_mpz_t(),base.get_mpz_t(), po.get_mpz_t(), _char.get_mpz_t());
	lambda = lambda*temp1;
	Xp = coord.x;
	coord.x = (lambda*lambda-2*coord.x)%_char;
	coord.y = (lambda*(Xp-coord.x)-coord.y)%_char;
	coord.x = (coord.x+_char)%_char;
	coord.y = (coord.y+_char)%_char;
}



void ECpoint::Add(ECpoint pt)
{
	if(*this == pt) {
		Double();
		return;
	}
	if(coord.x == pt.coord.x){
		coord.x = 1;
		coord.y = 1;
		coord.z = 0;
		return;
	}

	normalize();
	pt.normalize();

	if(*this == infinity){
		*this = pt;
		return;
	}
	if(pt == infinity) return;

	//lambda = (y2-y1)/(x2-x1)
	//x3 = s^2-x1-x2
	//y3 = s(x1-x2)-y1
	mpz_class x1 = coord.x, x2 = pt.coord.x, y1 = coord.y, y2 = pt.coord.y;

	mpz_class lambda = x2-x1, temp;
	mpz_class po(-1);
	mpz_powm(temp.get_mpz_t(),lambda.get_mpz_t(),po.get_mpz_t(),_char.get_mpz_t());
	lambda = ((y2-y1)*temp)%_char;
	coord.x = (lambda*lambda - x1 -x2)%_char;
	coord.y = (lambda*(x1-coord.x)-y1)%_char;
	coord.x = (coord.x+_char)%_char;
	coord.y = (coord.y+_char)%_char;
}


void ECpoint::multiply(mpz_class& i)
{
	ECpoint temp = *this;
	*this = infinity;
	while(i!=0)
	{
		if(i%2==0) temp.Double();
		else{
			Add(temp);
			temp.Double();
		}
		i = i/2;
	}
}

ECpoint& ECpoint::operator* (mpz_class& n)
{
    this->multiply(n);
    return *this;
}

ECpoint ECpoint::operator+ (ECpoint& pt)
{
	ECpoint ret(this->coord);
	ret.Add(pt);
	return ret;
}

bool ECpoint::operator== (ECpoint pt)
{
	pt.normalize();
	ECpoint temp = *this;
	temp.normalize();
	return (temp.coord.x==pt.coord.x)&&(temp.coord.y==pt.coord.y);
}

void ECpoint::operator = (const ECpoint& pt)
{
	coord.x = pt.coord.x;
	coord.y = pt.coord.y;
	coord.z = pt.coord.z;
}

void ECpoint::print(ostream& os)
{
	os<<"X : "<<hex<<coord.x<<endl;
	os<<"Y : "<<hex<<coord.y<<endl;
	os<<"Z : "<<hex<<coord.z<<endl;

}

void ECpoint::normalize()
{
	if(this->coord.z==0){
		*this = infinity;
		return;
	}
	mpz_class temp, po = -2;
	// x = X/Z^2, y = Y/Z^3
	mpz_powm(temp.get_mpz_t() , coord.z.get_mpz_t(),po.get_mpz_t(),_char.get_mpz_t());
	coord.x = (coord.x*temp)%_char; 
	coord.x = (coord.x+_char)%_char;
	po = -3;
	mpz_powm(temp.get_mpz_t() , coord.z.get_mpz_t(),po.get_mpz_t(),_char.get_mpz_t());
	coord.y = (coord.y*temp)%_char;
	coord.y = (coord.y+_char)%_char;
	coord.z = 1;
}

void ECpoint::negtive()
{
	coord.y = -coord.y;
}



ECpoint::~ECpoint()
{

}


/*
void ECpoint::Double(debugFlag flag)
{
	mpz_class T1, T2, T3, T4, T5;
	T1 = coord.x;
	T2 = coord.y;
	T3 = coord.z;
	if(T2==0||T3==0){
		coord.x = 1;
		coord.y = 1;
		coord.z = 0;
		return;
	}
	if(a==_char-3){
		T4 = (T3*T3)%_char;
		T5 = T1-T4;
		T4 = T1+T4;
		T5 = (T4*T5)%_char;
		T4 = 3*T5;
	}
	else{
		T4 = a;
		T5 = (T3*T3)%_char;
		T5 = (T5*T5)%_char;
		T5 = (T4*T5)%_char;
		T4 = (T1*T1)%_char;
		T4 = 3*T4;
		T4 = T4 + T5;
	}
	//step6
	T3 = (T2*T3)%_char;
	T3 = 2*T3;
	T2 = (T2*T2)%_char;
	T5 = (T1*T2)%_char;
	T5 = 4*T5;
	T1 = T4*T4;
	T1 = T1 - 2*T5;
	// step 13
	T2 = (T2*T2)%_char;
	T2 = 8*T2;
	T5 = T5-T1;
	T5 = (T4*T5)%_char;
	T2 = T5 - T2;
	coord.x = T1%_char;
	coord.y = T2%_char;
	coord.z = T3%_char;
	coord.x = (coord.x+_char)%_char;
	coord.y = (coord.y+_char)%_char;
	coord.z = (coord.z+_char)%_char;
}

void ECpoint::Add(ECpoint pt, debugFlag flag)
{
	mpz_class T1, T2, T3, T4, T5, T6, T7;
	//Step 1
	T1 = pt.coord.x;
	T2 = pt.coord.y;
	T3 = pt.coord.z;
	//cout<<"T1 : "<<T1<<endl<<"T2 : "<<T2<<endl<<"T3 : "<<T3<<endl;
	T4 = coord.x;
	T5 = coord.y;
	//Step6
	if(coord.z !=1) {
		T6 = coord.z;
		T7 = (T6*T6)%_char;
		T1 = (T1*T7)%_char;
		T7 = (T6*T7)%_char;
		T2 = (T2*T7)%_char;
	}

	T7 = (T3*T3)%_char;
	T4 = (T4*T7)%_char;
	T7 = (T3*T7)%_char;
	T5 = (T5*T7)%_char;
	//Step 11
	T4 = T1 - T4;
	T5 = T2 - T5;
	if(T4 == 0){
		if(T5 == 0) {
			coord.x = 0;
			coord.y = 0;
			coord.z = 0;
			return;
		}
		else {
			//cout<<"lalalalala"<<endl;
			coord.x = 1;
			coord.y = 1;
			coord.z = 0;
			return;
		}
	}
	//Step 14
	T1 = 2*T1 - T4;
	T2 = 2*T2 - T5;
	if(coord.z != 1) T3 = T3*T6;
	T3 = (T3*T4)%_char;
	T7 = (T4*T4)%_char;
	T4 = (T4*T7)%_char;
	T7 = (T1*T7)%_char;
	T1 = (T5*T5)%_char;
	//Step 22
	T1 = T1 - T7;
	T7 = T7 - 2*T1;
	T5 = (T5*T7)%_char;
	T4 = (T2*T4)%_char;
	T2 = T5 - T4;

	//Step 27
	mpz_class temp1 = 2, po = -1 , temp2 ;
	mpz_powm(temp2.get_mpz_t(),temp1.get_mpz_t(), po.get_mpz_t() , _char.get_mpz_t());
	T2 = T2*temp2;

	coord.x = T1%_char;
	coord.y = T2%_char;
	coord.z = T3%_char;

	coord.x = (coord.x+_char)%_char;
	coord.y = (coord.y+_char)%_char;
	coord.z = (coord.z+_char)%_char;
}
*/
