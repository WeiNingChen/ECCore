#ifndef ECC_H
#define ECC_H

#include <iostream>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

struct projPoint
{
    projPoint(mpz_class _x, mpz_class _y, mpz_class _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    projPoint(){}
	mpz_class x;
	mpz_class y;
	mpz_class z;
};

class ECpoint
{
public:
	ECpoint(projPoint);
	ECpoint();
	~ECpoint();
	
	bool checkOnCurve();

	void Double(); //Double the point in common way
	//void Double(debugFlag); //Double the point by IEEE 1363
	void Add(ECpoint); // Add the point in common way
	//void Add(ECpoint,debugFlag);// Add the point by IEEE 1363
	void multiply(mpz_class&);
	void normalize(); //set Z = 1;
	void negtive();
    mpz_class getCoordX(){return coord.x;}
    mpz_class getCoordY(){return coord.y;}

	void print(ostream&);
	//void printNormal(ostream&);
	
	static void setChar(mpz_class );
	static void setOrder(int );
	static void setCurveA(mpz_class);
	static void setCurveB(mpz_class);
	static mpz_class getChar();
	static int getOrder();
	
	ECpoint& operator *(mpz_class&);
	ECpoint operator +(ECpoint&);
	bool operator == (ECpoint);
	void operator = (const ECpoint&);
private:
	projPoint coord;
	static mpz_class _char;
	static int _order;
	//y^2 = x^3 + ax + b
	static mpz_class a,b;

};



#endif
