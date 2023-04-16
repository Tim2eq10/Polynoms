#pragma once

#include <iostream>
#include <string>

using std::string;

class Monom
{
private:
    unsigned short degree;
public:
	double coef;
    unsigned char xpower()const { return static_cast<unsigned char>(degree/100);}
    unsigned char ypower()const {return (degree/10)%10;}
    unsigned char zpower()const {return (degree%10);}

	Monom() = default;                                        
    Monom( double, unsigned char,unsigned char,unsigned char)noexcept;
    Monom(string);
    Monom(double) noexcept;

    Monom& operator =(const Monom&)noexcept;
    const Monom operator *(const Monom&) const;
	const Monom operator +(const Monom&) const;           
    const Monom operator -(const Monom&) const;
    const Monom operator *(double)const noexcept;

    Monom& operator +=(const Monom&);   
    Monom& operator -=(const Monom&);
    Monom& operator *=(const Monom&);
    Monom& operator *=(double) noexcept; // А почему другие не noexcept?    Answer:потому что 

	bool operator <(const Monom&) const noexcept;            
	bool operator <=(const Monom&) const noexcept;           
	bool operator >(const Monom&) const noexcept;            
	bool operator >=(const Monom&) const noexcept;           
	bool operator ==(const Monom&) const noexcept; 
	bool operator !=(const Monom&) const noexcept; 

	bool LessDegree(const Monom&) const noexcept;  
	bool EqDegree(const Monom&) const noexcept;

    Monom Integral(char);
    Monom Derivative(char);
    string toString();
    double ValueInPoint(double x, double y, double z) noexcept;
};
