#include "include/polynoms/Polynom.h"

Polynom::Polynom(const Polynom& other) : Data(other.Data)
{}
Polynom::Polynom(const list<Monom>& other)
{
	if (other.empty());

	else Data = other;
}
Polynom::Polynom(const Monom& monom)
{
    Data.push_back(monom);
}


//=================================//
// Polynom -> Monom binary methods //
//=================================//
Polynom Polynom::operator *(const Monom& right) const
{
    Polynom res;
    for (auto node : Data)
        res.Data.push_back(node * right);

    return res;
}
Polynom Polynom::operator +(const Monom& right) const
{
    // Ассимптотика та же :)
    Polynom res(*this);
    res += right;
    return res;
}
Polynom& Polynom::operator +=(const Monom& right)
{
    for (auto it = Data.begin(); it != Data.end(); it++) {
        if (it->EqDegree(right)) {
            *it += right;
            break;
        }
        if (right < (*it)) {
            Data.insert(it, right);
            break;
        }
    }

    return *this;
}
Polynom& Polynom::operator *=(const Monom& right)
{
    for (auto& node : Data)
        node *= right;

    return *this;
}


//===================================//
// Polynom -> Polynom binary methods //
//===================================//
Polynom Polynom::operator +(const Polynom& right) const
{
    Polynom res;
    auto l_it = Data.begin();
    auto r_it = right.Data.begin();

    while (l_it != Data.end() && r_it != right.Data.end()) {
        if (l_it->EqDegree(*r_it)){
            res.Data.push_back(*l_it + *r_it);
            l_it++;
            r_it++;
        }
        else if(*l_it < *r_it) {
            res.Data.push_back(*l_it);
            l_it++;
        }
        else {
            res.Data.push_back(*r_it);
            r_it++;
        }
    }

    while (l_it != Data.end())
        res.Data.push_back(*(l_it++));

    while (r_it != right.Data.end())
        res.Data.push_back(*(r_it++));

    return res;
}
Polynom Polynom::operator *(double k) const
{
    Polynom res;
    for (auto node : this->Data)
        res.Data.push_back(node * k);

    return res;
}
Polynom Polynom::operator -(const Polynom& right) const
{
    Polynom res;
    auto l_it = Data.begin();
    auto r_it = right.Data.begin();

    while (l_it != Data.end() && r_it != right.Data.end()) {
        if (l_it->EqDegree(*r_it)){
            res.Data.push_back(*l_it - *r_it);
            l_it++;
            r_it++;
        }
        else if(*l_it < *r_it) {
            res.Data.push_back(*l_it);
            l_it++;
        }
        else {
            res.Data.push_back((*r_it) * -1.0);
            r_it++;
        }
    }

    while (l_it != Data.end())
        res.Data.push_back(*(l_it++));

    while (r_it != right.Data.end())
        res.Data.push_back(*(r_it++) * -1);

    return res;
}
Polynom Polynom::operator *(const Polynom&) const
{}
Polynom Polynom::operator /(const Polynom&)
{}

Polynom& Polynom::operator =(const Polynom& right)
{
    if (this == &right)
        return *this;

    Data = right.Data;
    return *this;
}
Polynom& Polynom::operator +=(const Polynom&)
{}
Polynom& Polynom::operator -=(const Polynom&)
{}
Polynom& Polynom::operator *=(const Polynom&)
{}
Polynom& Polynom::operator /=(const Polynom&)
{}


//==================================//
// Polynom -> double binary methods //
//==================================//
Polynom& Polynom::operator *=(double) const
{}
Polynom& Polynom::operator /=(double coeff)
{}
Polynom Polynom::operator /(double coeff)
{}

//===============//
// Miscellaneous //
//===============//
Polynom Polynom::Integral(char)
{}
Polynom Polynom::Derivative(char)
{}
double Polynom::PolynomValueInPoint(double x, double y, double z) noexcept
{}
string Polynom::getPolynom()
{}
