#pragma once

#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include "Monom.h"

using namespace std;

class Polynom
{
private:
    list<Monom> Data;
public:
	Polynom();                                       		
    Polynom(string polynom);
    Polynom(const list<Monom>&);
    Polynom(const Monom&);
    Polynom(const Polynom&);

    Polynom operator *(const Monom&) const;
    Polynom operator +(const Monom&) const;
    Polynom& operator +=(const Monom&);
    Polynom& operator *=(const Monom&);

	Polynom operator +(const Polynom&) const;     
	Polynom operator *(double) const;                
	Polynom operator -(const Polynom&) const;     
	Polynom operator *(const Polynom&) const;   
    Polynom operator /(const Polynom&);

    Polynom& operator =(const Polynom&);
    Polynom& operator +=(const Polynom&);
    Polynom& operator -=(const Polynom&) ;
    Polynom& operator *=(const Polynom&);
    Polynom& operator /=(const Polynom&);

    Polynom& operator *=(double) const;
    Polynom& operator /=(double coeff);
    Polynom operator /(double coeff);

    Polynom Integral(char);
    Polynom Derivative(char);
    double PolynomValueInPoint(double x, double y, double z) noexcept;
	string getPolynom();                               
};
