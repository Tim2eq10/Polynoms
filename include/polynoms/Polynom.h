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
    string Name;
public:
	Polynom();                                       		

    Polynom(string Name, string polynom);                       

    Polynom(string, const list<Monom>&);

	Polynom(string, const Monom&);                           

	Polynom(string, const Polynom&);                      

    Polynom& operator =(const Polynom&);

	Polynom operator +(const Polynom&) const;     

	Polynom operator *(const Monom&) const;          

    Polynom operator +(const Monom&) const;  

    Polynom& operator +=(const Monom&) ;

	Polynom operator *(double) const;                

	Polynom operator -(const Polynom&) const;     

	Polynom operator *(const Polynom&) const;   

    Polynom& operator +=(const Polynom&);

    Polynom& operator *=(const Monom&);

    Polynom& operator *=(double) const;

    Polynom& operator -=(const Polynom&) ;

    Polynom& operator *=(const Polynom&);

    Polynom operator/(const Polynom&);

    Polynom& operator/=(const Polynom&);

    Polynom operator /(double coeff);

    Polynom& operator /=(double coeff);

    Polynom Integral(char);

    Polynom AntiIntegral(char);

    double PolynomValueInPoint(double x, double y, double z) noexcept;



	string getPolynom();                               
};
