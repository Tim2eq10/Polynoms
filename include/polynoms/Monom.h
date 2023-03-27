#pragma once

#include <iostream>
#include <string>

using namespace std;

class Monom
{
	
    unsigned short degree;
public:
	double coef;
    unsigned char xpower()const { return static_cast<unsigned char>(degree/100);};
    unsigned char ypower()const {return (degree/10)%10;};
    unsigned char zpower()const {return (degree%10);};

	Monom() = default;                                        

    //TODO : unsigned char
    Monom( double, unsigned char,unsigned char,unsigned char)noexcept;

    Monom(double) noexcept;

    Monom& operator =(const Monom&)noexcept;

	const Monom operator +(const Monom&) const;           

    Monom& operator +=(const Monom&);

	const Monom operator -(const Monom&) const;   
	   
    Monom& operator -=(const Monom&);

	const Monom operator *(const Monom&) const;           

    Monom& operator *=(const Monom&);

    Monom& operator *=(double)noexcept ;

    const Monom operator *(double)const noexcept ;

	bool operator <(const Monom&) const noexcept;            

	bool operator <=(const Monom&) const noexcept;           

	bool operator >(const Monom&) const noexcept;            

	bool operator >=(const Monom&) const noexcept;           

	bool operator ==(const Monom&) const noexcept; 

	bool operator !=(const Monom&) const noexcept; 

	bool LessDegree(const Monom&) const noexcept;  

	bool EqDegree(const Monom&) const noexcept;

    string stringMonom();

    double MonomValueInPoint(double x, double y, double z) noexcept;
};
