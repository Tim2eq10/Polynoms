#include "include/polynoms/Polynom.h"
#include<unordered_map>
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
    res.Sort();
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
    Sort();
    return *this;
}
Polynom& Polynom::operator *=(const Monom& right)
{
    for (auto& node : Data)
        node *= right;
    Sort();
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
    res.Sort();
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

Polynom& Polynom::operator =(const Polynom& right)
{
    if (this == &right)
        return *this;

    Data = right.Data;
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
Polynom Polynom::Integral(char xyz)
{
    list<Monom> tmp;
    for (auto& hu : Data) {
        auto it = tmp.begin();
        it = tmp.insert(it, hu.Integral(xyz));
    }
    Polynom res(tmp);
    res.Sort();
    return res;
}
Polynom Polynom::Derivative(char xyz)
{
    list<Monom> tmp;
    for (auto& hu : Data) {
        auto it = tmp.begin();
        it = tmp.insert(it, hu.Derivative(xyz));
    }
    Polynom res(tmp);
    res.Sort();
    return res;

}
double Polynom::ValueInPoint(double x, double y, double z) noexcept
{
    double ans = 0;
    for (auto& hu : Data) {
        ans += hu.ValueInPoint(x, y, z);
    }
    return ans;
}
string Polynom::toString()
{
    std::string ans = "";
    for (auto& hu : Data) {
        if (hu.coef > 0) {
            ans += " + ";
            ans += hu.toString();
        }
        else {
            ans += hu.toString();
        }
    }
    if (Data.begin()->coef > 0) {
        ans.erase(0, 3);
    }
    return ans;
}

void Polynom::Sort() {
    std::unordered_map<int, double> res = {};
    for (auto& hu : Data) {
        int xyz = static_cast<int>(hu.xpower() * 100 + hu.ypower() * 10 + hu.zpower());
        res[xyz] += hu.coef;
    }
    Monom tmp1;
    list<Monom> tmp;
    for (auto hu : res) {
        if (hu.second!=0.0) {
            tmp1.degree = hu.first;
            tmp1.coef = hu.second;
            auto it = tmp.begin();
            it = tmp.insert(it, tmp1);
        }
    }
    Data = list<Monom>(tmp);
    Data.sort(SortingExpr);
}
bool SortingExpr(const Monom& first, const Monom& second) {
    return (first.Monom::LessDegree(second));
}
