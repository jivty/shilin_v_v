#include "complex.h"
#include <iostream>

using namespace std;

Complex::Complex(const double real)
	: Complex(real, 0.0) {
}

Complex::Complex(const double real, const double imaginary)
	: re(real)
	, im(imaginary) {
}

Complex& Complex::operator=(const double rhs) {
	re = rhs;
	im = 0;
	return *this;
}

bool Complex::operator==(const Complex& rhs) const {
	return (fabs(re - rhs.re) < numeric_limits<double>::epsilon() && fabs(im - rhs.im) < numeric_limits<double>::epsilon());
}
bool Complex::operator!=(const Complex& rhs) const {
	return !operator==(rhs);
}

Complex conj(const Complex& rhs) {
	Complex conj_(rhs);
	conj_.im *= (-1);
	return conj_;
}

Complex& Complex::operator+=(const Complex& rhs) {
	re += rhs.re;
	im += rhs.im;
	return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
	return Complex(lhs.re + rhs.re, lhs.im + rhs.im);
}

Complex operator+(const Complex& lhs, const double rhs) {
	return Complex(lhs.re + rhs, lhs.im);
}

Complex operator+(const double lhs, const Complex& rhs) {
	return rhs + lhs;
}

Complex& Complex::operator-=(const Complex& rhs) {
	re -= rhs.re;
	im -= rhs.im;
	return *this;
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
	return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}

Complex operator-(const Complex& lhs, const double rhs) {
	return Complex(lhs.re - rhs, -lhs.im);
}

Complex operator-(const double lhs, const Complex& rhs) {
	return Complex(lhs - rhs.re, -rhs.im);
}

Complex& Complex::operator*=(const double rhs) {
	re *= rhs;
	im *= rhs;
	return *this;
}

Complex& Complex::operator*=(const Complex& rhs) {
	double tmpre(re * rhs.re - im * rhs.im);
	im = re * rhs.im + im * rhs.re;
	re = tmpre;
	return *this;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
	Complex comp(lhs);
	comp *= rhs;
	return comp;
}

Complex operator*(const Complex& lhs, const double rhs) {
	return Complex(lhs.re * rhs, lhs.im * rhs);
}

Complex operator*(const double lhs, const Complex& rhs) {
	return rhs * lhs;
}

Complex& Complex::operator/=(const Complex& rhs) {
	double denum(rhs.re * rhs.re + rhs.im * rhs.im);
	if (denum < numeric_limits<double>::epsilon()) throw invalid_argument("Divison by zero");
	else
	{
		double tmpre((re * rhs.re + im * rhs.im) / denum);
		im = (im * rhs.re - re * rhs.im) / denum;
		re = tmpre;
	}
	return *this;
}

Complex& Complex::operator/=(const double rhs) {
	if (rhs < 1e-7) throw invalid_argument("Divison by zero");
	else
	{
		re /= rhs;
		im /= rhs;
	}
	return *this;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
	Complex div(lhs);
	div /= rhs;
	return div; 
}

Complex operator/(const Complex& lhs, const double rhs) {
	Complex div(lhs);
	div /= rhs;
	return div;
}

Complex operator/(const double lhs, const Complex& rhs) {
	Complex div(lhs);
	div /= rhs;
	return div;
}

std::ostream& Complex::writeTo(std::ostream& ostrm) const {
	ostrm << leftBrace << re << separator << im << rightBrace;
	return ostrm;
}

std::istream& Complex::readFrom(std::istream& istrm) {
	char leftBrace = '0';
	double real = 0.0;
	char comma = '0';
	double imaginary = 0.0;
	char rightBrace = 0;
	istrm >> leftBrace >> real >> comma >> imaginary >> rightBrace;
	if (istrm.good()) {
		if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma) &&
			(Complex::rightBrace == rightBrace)) {
			re = real;
			im = imaginary;
		} else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}