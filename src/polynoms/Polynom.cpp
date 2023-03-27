#include "include/polynoms/Polynom.h"
Polynom::Polynom(string s,const Polynom& other) : Data(other.Data), Name(s)
{}

Polynom::Polynom(string s,const list<Monom>& other):Name(s)
{
	if (other.empty());

	else Data = other;
}

Polynom::Polynom(string s, const Monom& monom):Name(s)
{
    Data.push_back(monom);
}
/*string Polynom::getPolynomial()
{
    
}*/
