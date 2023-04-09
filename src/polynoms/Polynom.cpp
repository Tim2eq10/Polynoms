#include "include/polynoms/Polynom.h"

Polynom::Polynom()
{}
Polynom::Polynom(const Polynom& other) : Data(other.Data)
{}
Polynom::Polynom(const list<Monom>& other)
{
    if (other.empty());

    else Data = other;

    Sort();
}
Polynom::Polynom(const Monom& monom)
{
    Data.push_back(monom);
}
Polynom::Polynom(string polynom)
{
    string temp = "";
    for (auto c = polynom.begin(); c != polynom.end(); c++) {
        if ((*c == '-' || *c == '+') && !temp.empty()) {
            Data.push_back(Monom(temp));
            temp.clear();
            temp += *c;
        }
        else {
            temp += *c;
        }
    }
    if (!temp.empty()) {
        Data.push_back(temp);
        temp.clear();
    }

    Sort();
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
        if (l_it->EqDegree(*r_it)) {
            res.Data.push_back(*l_it + *r_it);
            l_it++;
            r_it++;
        }
        else if (*l_it < *r_it) {
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
    res.Sort();
    return res;
}
Polynom Polynom::operator *(double k) const
{
    Polynom res;
    if (k == 0.0) return res;
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
        if (l_it->EqDegree(*r_it)) {
            res.Data.push_back(*l_it - *r_it);
            l_it++;
            r_it++;
        }
        else if (*l_it < *r_it) {
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
        res.Data.push_back(*(r_it++) * -1.0);
    res.Sort();

    return res;
}

Polynom Polynom::operator *(const Polynom& right) const
{
    Polynom res;
    Monom tmp;
    for (auto r : right.Data) {
        for (auto l : Data) {
            tmp = l * r;
            res.Data.push_back(tmp);
        }
    }
    res.Sort();
    return res;
}

Polynom& Polynom::operator =(const Polynom& other)
{
    if (this == &other)
        return *this;

    Data = other.Data;
    return *this;
}

Polynom& Polynom::operator +=(const Polynom& right)
{
    *this = *this + right;
    return *this;
}
Polynom& Polynom::operator -=(const Polynom& right)
{
    *this = *this - right;
    return *this;
}
Polynom& Polynom::operator *=(const Polynom& right)
{
    *this = *this * right;
    return *this;
}

//==================================//
// Polynom -> double binary methods //
//==================================//

Polynom& Polynom::operator *=(double coeff) 
{
    *this = *this * coeff;
    return *this;
}
Polynom& Polynom::operator /=(double coeff)
{
    *this = *this * (1 / coeff);
    return *this;
}
Polynom Polynom::operator /(double coeff)
{
    Polynom res(*this);
    res /= coeff;
    return res;
}

//===============//
// Miscellaneous //
//===============//

/*
Polynom Polynom::Integral(char)
{}
Polynom Polynom::Derivative(char)
{ return *this; }
double Polynom::PolynomValueInPoint(double x, double y, double z) noexcept
{ return x; }
string Polynom::getPolynom()
{}
*/

void Polynom::Sort() {
    if (Data.empty());
    else {
        //sort
        for (auto i = Data.end(); i != Data.begin(); i--) {
            if (i == Data.end());
            else {
                for (auto j = Data.begin(); j != i; j++) {
                    auto t = j;
                    t++;
                    if (t->LessDegree(*j)) {
                        std::iter_swap(j, t);
                    }
                }
            }
        }
        //delete 0s
        for (auto i = Data.begin(); i != Data.end();) {
            if (i->coef == 0) {
                Data.erase(i);
            }
            else i++;

        }
        //eq degrees
        for (auto i = Data.begin(); i != Data.end() ;) {
            auto t = i;
            t++;
            if (t != Data.end() && i->EqDegree(*t)) {
                Data.emplace(i, *i + *(++i));
                Data.erase(i);
            }
            else i++;
        }
    }
}
