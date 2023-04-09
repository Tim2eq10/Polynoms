#include "include/polynoms/Monom.h"

#include <cmath>

Monom::Monom(double coef_val, unsigned char x, unsigned char y, unsigned char z) noexcept : coef(coef_val)
{
	degree = static_cast<unsigned short>(x) * 100 + y * 10 + z;
}
Monom::Monom(double coef_val) noexcept : degree(0), coef(coef_val)
{}

Monom::Monom(string input_monom)
{
	unsigned short xpow = 0;
	unsigned short ypow = 0;
	unsigned short zpow = 0;
	int coeff = 1;
	bool dot_count = false;
	int count_after_dot = 0;
	for (auto c = input_monom.begin(); c != input_monom.end(); c++) {
		if (*c == '-' && c == input_monom.begin()) {
			coeff = -1;
		}
		else if (*c == '-' && c != input_monom.begin()) {
			throw std::invalid_argument("Monomial entered incorrectly1");
		}
		else if (*c == '.' && !dot_count) {
			dot_count = true;
		}
		else if (*c == '.' && dot_count) {
			throw std::invalid_argument("Monomial entered incorrectly2");
		}
		else if (*c <= '9' && *c >= '0') {
			unsigned short t = *c - '0';
			coef += t;
			coef *= 10;
			if (dot_count) {
				count_after_dot++;
			}

		}
		else if (*c == 'x') {
			xpow = 1;
			auto it = c;
			it++;
			if (it != input_monom.end() && *it == '^') {
				it++;
				xpow = *it - '0';
				c += 2;
			}
		}
		else if (*c == 'y') {
			ypow = 1;
			auto it = c;
			it++;
			if (it != input_monom.end() && *it == '^') {
				it++;
				ypow = *it - '0';
				c += 2;
			}
		}
		else if (*c == 'z') {
			zpow = 1;
			auto it = c;
			it++;
			if (it != input_monom.end() && *it == '^') {
				it++;
				zpow = *it - '0';
				c += 2;
			}
		}

	}
	if (coef == 0 && (xpow || ypow || zpow)) coef = 1;
	else coef = coef / pow(10, count_after_dot + 1);
	coef *= coeff;
	degree = static_cast<unsigned short>(xpow) * 100 + ypow * 10 + zpow;
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

