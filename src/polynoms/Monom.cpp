#include "include/polynoms/Monom.h"
#include <cmath>
#include <set>

Monom::Monom(double coef_val, unsigned char x, unsigned char y, unsigned char z) noexcept : coef(coef_val)
{
	degree = static_cast<unsigned short>(x) * 100 + y * 10 + z;
}
Monom::Monom(double coef_val) noexcept : degree(0), coef(coef_val)
{}

Monom::Monom(string raw_input)
{
    std::string input = "";
    uint8_t stage = 0;
    uint8_t digits_after_dot = 0;
    bool negative_coef = false;
    std::set<int> good_stages{ 2, 4, 5, 7, 8, 10, 11 ,13, 14, 16, 17, 19,
                              20, 22, 23, 25, 26, 28, 29, 31, 32, 34, 35,
                              37, 38, 40, 41, 43, 44, 46, 47, 49 };
    for (char c : raw_input)
        if (c != ' ')
            input += c;

    degree = 0;
    coef = 0;

    for (char c : input) {
        if (stage == 0) {
            if (c == '-') {
                negative_coef = true;
                stage = 1;
            }
            else if (c == '+') {
                stage = 1;
            }
            else if (c >= '0' && c <= '9') {
                coef = c - '0';
                stage = 2;
            }
            else if (c == 'x') {
                coef = 1;
                stage = 5;
            }
            else if (c == 'y') {
                coef = 1;
                stage = 20;
            }
            else if (c == 'z') {
                coef = 1;
                stage = 35;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 1) {
            if (c == 'x') {
                stage = 5;
                coef = 1;
            }
            else if (c == 'y') {
                stage = 20;
                coef = 1;
            }
            else if (c == 'z') {
                stage = 20;
                coef = 1;
            }
            else if (c >= '0' && c <= '9') {
                coef = 1 * (c - '0');
                stage = 2;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 2) {
            if (c == 'x') {
                degree = 100;
                stage = 5;
            }
            else if (c == 'y') {
                stage = 20;
            }
            else if (c == 'z') {
                stage = 35;
            }
            else if (c >= '0' && c <= '9') {
                coef *= 10;
                coef += (c - '0');
                stage = 2;
            }
            else if (c == '.') {
                stage = 3;
                digits_after_dot = 1;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 3) {
            if (c >= '0' && c <= '9') {
                stage = 4;
                coef += (c - '0') / pow(10, digits_after_dot);
                digits_after_dot++;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 4) {
            if (c >= '0' && c <= '9') {
                coef += (c - '0') / pow(10, digits_after_dot);
                digits_after_dot++;
            }
            else if (c == 'x') {
                degree = 100;
                stage = 5;
            }
            else if (c == 'y') {
                stage = 20;
            }
            else if (c == 'z') {
                stage = 35;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 5) {
            if (c == 'y') {
                degree = 100;
                stage = 8;
            }
            else if (c == 'z') {
                degree = 100;
                stage = 14;
            }
            else if (c == '^') {
                degree = 0;
                stage = 6;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 6) {
            if (c >= '0' && c <= '9') {
                degree = static_cast<unsigned short>((c - '0')) * 100;
                stage = 7;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 7) {
            if (c == 'y') {
                stage = 8;
            }
            else if (c == 'z') {
                stage = 14;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 8) {
            if (c == '^') {
                stage = 9;
            }
            else if (c == 'z') {
                degree += 10;
                stage = 11;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 9) {
            if (c >= '0' && c <= '9') {
                degree += (c - '0') * 10;
                stage = 10;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 10) {
            if (c == 'z') {
                stage = 11;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 11) {
            if (c == '^') {
                stage = 12;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 12) {
            if (c >= '0' && c <= '9') {
                degree += c - '0';
                stage = 13;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 13) {
            throw std::invalid_argument("Incorrect string to transform");
        }
        if (stage == 14) {
            if (c == '^') {
                stage = 15;
            }
            else if (c == 'y') {
                degree += 1;
                stage = 17;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 15) {
            if (c >= '0' && c <= '9') {
                degree += c - '0';
                stage = 16;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 16) {
            if (c == 'y') {
                stage = 17;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 17) {
            if (c == '^') {
                stage = 18;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 18) {
            if (c >= '0' && c <= '9') {
                degree += (c - '0') * 10;
                stage = 19;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 19) {
            throw std::invalid_argument("Incorrect string to transform");
        }
        if (stage == 20) {
            if (c == '^') {
                stage = 21;
            }
            else if (c == 'x') {
                degree = 10;
                stage = 23;
            }
            else if (c == 'z') {
                degree = 10;
                stage = 29;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 21) {
            if (c >= '0' && c <= '9') {
                degree = static_cast<unsigned short>(c - '0') * 10;
                stage = 22;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 22) {
            if (c == 'x') {
                stage = 23;
            }
            else if (c == 'z') {
                stage = 29;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 23) {
            if (c == '^') {
                stage = 24;
            }
            else if (c == 'z') {
                degree += 100;
                stage = 26;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 24) {
            if (c >= '0' && c <= '9') {
                degree += (c - '0') * 100;
                stage = 25;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 25) {
            if (c == 'z') {
                stage = 26;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 26) {
            if (c == '^') {
                stage = 27;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 27) {
            if (c >= '0' && c <= '9') {
                degree += c - '0';
                stage = 28;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 28) {
            throw std::invalid_argument("Incorrect string to transform");
        }
        if (stage == 29) {
            if (c == '^') {
                stage = 30;
            }
            else if (c == 'x') {
                degree += 1;
                stage = 32;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 30) {
            if (c >= '0' && c <= '9') {
                degree += c - '0';
                stage = 31;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 31) {
            if (c == 'x') {
                stage = 32;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 32) {
            if (c == '^') {
                stage = 33;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 33) {
            if (c >= '0' && c <= '9') {
                degree += (c - '0') * 100;
                stage = 34;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 34) {
            throw std::invalid_argument("Incorrect string to transform");
        }
        if (stage == 35) {
            if (c == '^') {
                stage = 36;
            }
            else if (c == 'x') {
                degree = 1;
                stage = 38;
            }
            else if (c == 'y') {
                degree = 1;
                stage = 44;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 36) {
            if (c >= '0' && c <= '9') {
                degree = static_cast<unsigned short>(c - '0');
                stage = 37;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 37) {
            if (c == 'x') {
                stage = 38;
            }
            else if (c == 'y') {
                stage = 44;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 38) {
            if (c == 'y') {
                degree += 100;
                stage = 41;
            }
            else if (c == '^') {
                stage = 39;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 39) {
            if (c >= '0' && c <= '9') {
                degree += (c - '0') * 100;
                stage = 40;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 40) {
            if (c == 'y') {
                stage = 41;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 41) {
            if (c == '^') {
                stage = 42;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 42) {
            if (c >= '0' && c <= '9') {
                degree += (c - '0') * 10;
                stage = 43;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 43) {
            throw std::invalid_argument("Incorrect string to transform");
        }
        if (stage == 44) {
            if (c == '^') {
                stage = 45;
            }
            else if (c == 'x') {
                degree += 10;
                stage = 47;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 45) {
            if (c >= '0' && c <= '9') {
                degree += (c - '0') * 10;
                stage = 46;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 46) {
            if (c == 'x') {
                stage = 47;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 47) {
            if (c == '^') {
                stage = 48;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 48) {
            if (c >= '0' && c <= '9') {
                degree += (c - '0') * 100;
                stage = 49;
            }
            else {
                throw std::invalid_argument("Incorrect string to transform");
            }
            continue;
        }
        if (stage == 49) {
            throw std::invalid_argument("Incorrect string to transform");
        }
    }

    if (good_stages.find(stage) == good_stages.end())
        throw std::invalid_argument("Incorrect string to transform");

    if (negative_coef)
            coef *= -1;

    // last char is x
    if (stage == 5 || stage == 23 || stage == 32 || stage == 38 || stage == 47)
        degree += 100;
    // last char is y
    if (stage == 20 || stage == 8 || stage == 17 || stage == 44 || stage == 41)
        degree += 10;
    // last char is z
    if (stage == 35 || stage == 14 || stage == 11 || stage == 29 || stage == 26)
        degree += 1;
}
Monom& Monom::operator=(const Monom& monom) noexcept
{
	if (this == &monom)
		return *this;
	this->degree = monom.degree;
	this->coef = monom.coef;
	return *this;
}
const Monom Monom::operator+(const Monom& monom) const
{
	if (this->degree != monom.degree)
	{
		throw std::invalid_argument("Not equal degrees of monoms!");
	}
	Monom ans(*this);
	ans.coef += monom.coef;
	return ans;
}
Monom& Monom::operator+=(const Monom& monom)
{
	Monom t(*this);
	*this = t + monom;
	return *this;
}
const Monom Monom::operator -(const Monom& monom) const
{
	if (this->degree != monom.degree)
	{
		throw std::invalid_argument("Not equal degrees of monoms!");
	}
	Monom ans(*this);
	ans.coef -= monom.coef;
	return ans;
}
Monom& Monom::operator-=(const Monom& monom)
{
	*this = *this - monom;
	return *this;
}
const Monom Monom::operator*(const Monom& monom) const
{
	unsigned char x, y, z, xo, yo, zo;

	x = xpower();
	y = ypower();
	z = zpower();
	xo = monom.xpower();
	yo = monom.ypower();
	zo = monom.zpower();
	int px = x + xo, py = y + yo, pz = z + zo;

	if (px > 9 || py > 9 || pz > 9)
	{
		throw std::invalid_argument("Too large degree!");
	}
	Monom third(*this);
	third.degree += monom.degree;
	third.coef *= monom.coef;
	return third;
}
Monom& Monom::operator *=(const Monom& other)
{
	Monom t(*this);
	*this = t * other;
	return *this;
}
Monom& Monom::operator *=(double temp) noexcept
{
	this->coef *= temp;
	return *this;
}
const Monom Monom::operator *(double temp) const noexcept
{
	Monom ans(coef, xpower(), ypower(), zpower());
	ans.coef *= temp;
	return ans;
}

bool Monom::operator <(const Monom& other) const noexcept
{
	if (this->degree == other.degree)
		return this->coef < other.coef;
	return this->degree < other.degree;
}
bool Monom::operator <=(const Monom& other) const noexcept
{
	return !(*this > other);
}
bool Monom::operator >(const Monom& other) const noexcept
{
	return other < *this;
}
bool Monom::operator >=(const Monom& other) const noexcept
{
	return !(*this < other);
}
bool Monom::operator ==(const Monom& other) const noexcept
{
	return !(other<*this || *this>other);
}
bool Monom::operator !=(const Monom& other) const noexcept
{
	return !(*this == other);
}


bool Monom::LessDegree(const Monom& m) const noexcept
{
	return (xpower() + ypower() + zpower() < m.xpower() + m.ypower() + m.zpower());
}
bool Monom::EqDegree(const Monom& m) const noexcept
{
	return (xpower() == m.xpower() && ypower() == m.ypower() && zpower() == m.zpower());
}
string Monom::stringMonom()
{
	int x, y, z;
	string result = "";

	x = xpower();
	y = ypower();
	z = zpower();

	if (this->degree == 0 || this->coef != 1.0)
		result += std::to_string(this->coef);

	if (x)
	{
		result += "x";
		if (x != 1) result += "^" + std::to_string(x);
	}

	if (y)
	{
		result += "y";
		if (y != 1) result += "^" + std::to_string(y);
	}

	if (z)
	{
		result += "z";
		if (z != 1) result += "^" + std::to_string(z);
	}

	return result;
}
double Monom::MonomValueInPoint(double x, double y, double z) noexcept {
	double ans = 0;
	ans = coef * pow(x, xpower()) * pow(y, ypower()) * pow(z, zpower());
	return ans;
}

