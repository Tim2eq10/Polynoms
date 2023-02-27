//============================================================================
// Header : polynom.h
// Authors : Poletaev Timur, Tanin Egor, Khalabuda Elizaveta
// Description : 
//		Многочлены от x,y,z степени меньше 1024
//============================================================================
#pragma once

#include <iostream>
#include <bitset>
//============================================================================
template <typename T>
class polynom
{
public: //private
	class Monom;
public:

private:

};
//============================================================================
template <typename T>
class polynom<T>::Monom {
	constexpr static size_t xpowmask = 1023;
	constexpr static size_t ypowmask = xpowmask << 10;
	constexpr static size_t zpowmask = ypowmask << 10;
public:
	/// <summary>
	/// Мономы равны, когда равны их степени.
	/// </summary>
	/// <param name="coeff">Коэффициент монома</param>
	/// <param name="xpower">Степень при x (меньше 1024)</param>
	/// <param name="ypower">Степень при y (меньше 1024)</param>
	/// <param name="zpower">Степень при z (меньше 1024)</param>
	Monom(
		const T& coeff,
		size_t xpower, size_t ypower, size_t zpower,
		Monom* next_monom = nullptr
	) : c(coeff), 
		next(next_monom)
	{
		power = (zpower << 20) + (ypower << 10) + xpower;
	}
	size_t xpow() {
		return (power & xpowmask);
	}
	size_t ypow() {
		return (power & ypowmask) >> 10;
	}
	size_t zpow() {
		return (power & zpowmask) >> 20;
	}
	bool operator ==(const Monom& other) const {
		return this->power == other.power;
	}
	bool operator !=(const Monom& other) const {
		return !(*this == other);
	}
	bool operator<(const Monom& other) const {
		return this->power < other.power;
	}
public:
	T c;
	Monom* next;
private:
	size_t power;
};
//============================================================================
