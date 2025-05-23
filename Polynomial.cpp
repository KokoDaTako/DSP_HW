#include "Polynomial.h"
#include "iostream"
#include <string>
#include <cassert>

Polynomial::Polynomial()
{
	polynomialDegree = 0;
	polynomialCoefficients = new double[MAX_DEGREE + 1];
	for (int i = 0; i < MAX_DEGREE + 1; i++) polynomialCoefficients[i] = 0;
}

Polynomial::Polynomial(unsigned int degree, double coefficients[]) : polynomialDegree(degree) 
{
	assert(("ERROR: Degree attempted during creation is higher than Max degree allowed", degree <= MAX_DEGREE));
	polynomialCoefficients = new double[MAX_DEGREE + 1];

	for (unsigned int i = 0; i <= degree; i++) {
		polynomialCoefficients[i] = coefficients[i];
	}
	for (unsigned int i = degree + 1; i < MAX_DEGREE + 1; i++)
	{
		polynomialCoefficients[i] = 0;
	}
}

Polynomial::Polynomial(const Polynomial& poly) 
{
	polynomialDegree = poly.GetDegree();
	polynomialCoefficients = new double[MAX_DEGREE + 1];
	SetCoefficients(poly.GetCoefficients());
}

Polynomial::~Polynomial()
{
	delete[] polynomialCoefficients;
}

unsigned int Polynomial::GetDegree() const
{
	return polynomialDegree;
}

double* Polynomial::GetCoefficients() const
{
	return polynomialCoefficients;
}

void Polynomial::SetDegree(unsigned int newDeg)
{
	unsigned int oldDeg = polynomialDegree;
	polynomialDegree = newDeg;

	if (oldDeg < newDeg)
	{
		for (unsigned int i = oldDeg + 1; i <= polynomialDegree; i++) polynomialCoefficients[i] = 0;
	}
	else if (oldDeg > newDeg)
	{
		for (unsigned int i = oldDeg; i > polynomialDegree; i--) polynomialCoefficients[i] = 0;
	}
	
}

void Polynomial::SetCoefficients(double newCoeff[])
{
	for (unsigned int i = 0; i <= polynomialDegree; i++) {
		polynomialCoefficients[i] = newCoeff[i];
	}
	for (unsigned int i = polynomialDegree + 1; i < MAX_DEGREE + 1; i++)
	{
		polynomialCoefficients[i] = 0;
	}
}

void Polynomial::SetPolynomial(unsigned int newDeg, double newCoeff[])
{
	SetDegree(newDeg);
	SetCoefficients(newCoeff);
}

double& Polynomial::operator[](unsigned int index) const
{
	assert(("ERROR: index attempted is higher than degree", index <= polynomialDegree));
	return polynomialCoefficients[index];
}

void Polynomial::operator=(Polynomial poly)
{
	polynomialDegree = poly.GetDegree();
	polynomialCoefficients = new double[MAX_DEGREE + 1];
	/*for (unsigned int i = 0; i <= polynomialDegree; i++)
	{
		polynomialCoefficients[i] = poly.GetCoefficients()[i];
	}
	for (unsigned int i = polynomialDegree + 1; i < MAX_DEGREE + 1; i++)
	{
		polynomialCoefficients[i] = 0;
	}*/
	SetCoefficients(poly.GetCoefficients());
}

bool Polynomial::operator==(Polynomial poly) const
{
	if (poly.GetDegree() != polynomialDegree) return false;
	else
	{
		for (unsigned int i = 0; i <= polynomialDegree; i++)
		{
			if (polynomialCoefficients[i] != poly.GetCoefficients()[i]) return false;
		}
	}
	
	return true;
}

bool Polynomial::operator!=(Polynomial poly) const
{
	if (poly.GetDegree() != polynomialDegree) return true;
	else
	{
		for (unsigned int i = 0; i <= polynomialDegree; i++)
		{
			if (polynomialCoefficients[i] != poly.GetCoefficients()[i]) return true;
		}
	}

	return false;
}

void Polynomial::operator+=(Polynomial poly)
{
	if (polynomialDegree < poly.GetDegree()) polynomialDegree = poly.GetDegree();

	for (unsigned int i = 0; i <= polynomialDegree; i++)
	{
		polynomialCoefficients[i] += poly.GetCoefficients()[i];
	}

	while (polynomialCoefficients[polynomialDegree] == 0)
	{
		polynomialDegree--;
	}
}

void Polynomial::operator-=(Polynomial poly)
{
	if (polynomialDegree < poly.GetDegree()) polynomialDegree = poly.GetDegree();

	for (unsigned int i = 0; i <= polynomialDegree; i++)
	{
		polynomialCoefficients[i] -= poly.GetCoefficients()[i];
	}

	while (polynomialCoefficients[polynomialDegree] == 0 && polynomialDegree > 0)
	{
		polynomialDegree--;
	}
}

void Polynomial::operator*=(Polynomial poly)
{
	assert(("ERROR: Multiplication causes a polynom to overshoot the max degree limit", (polynomialDegree + poly.GetDegree()) < MAX_DEGREE));
	unsigned int oldDeg = polynomialDegree;
	polynomialDegree += poly.GetDegree();
	double temp[MAX_DEGREE + 1] = { 0 };

	for (unsigned int i = 0; i <= oldDeg; i++)
	{
		for (unsigned int j = 0; j <= poly.GetDegree(); j++)
		{
			temp[i + j] += polynomialCoefficients[i] * poly.GetCoefficients()[j];
		}
	}

	SetCoefficients(temp);
}

Polynomial Polynomial::operator+(Polynomial poly) const
{
	/*unsigned int deg = max(poly.GetDegree(), GetDegree());
	double temp[MAX_DEGREE + 1] = { 0 };
	Polynomial result(deg, temp);

	for (unsigned int i = 0; i <= deg; i++)
	{
		temp[i] = poly.GetCoefficients()[i] + GetCoefficients()[i];
	}

	result.SetCoefficients(temp);
	return result;*/

	Polynomial result = *this;
	result += poly;

	return result;
}

Polynomial Polynomial::operator-(Polynomial poly) const
{
	/*unsigned int deg = max(poly.GetDegree(), GetDegree());
	double temp[MAX_DEGREE + 1] = { 0 };
	Polynomial result(deg, temp);

	for (unsigned int i = 0; i <= deg; i++)
	{
		temp[i] = poly.GetCoefficients()[i] - GetCoefficients()[i];
	}

	result.SetCoefficients(temp);
	return result;*/

	Polynomial result = *this;
	result -= poly;

	return result;
}

Polynomial Polynomial::operator*(Polynomial poly) const
{
	Polynomial result(poly);
	result *= *this;

	return result;
}

void Polynomial::operator++()
{
	double temp[MAX_DEGREE + 1];
	temp[0] = 1;

	SetDegree(GetDegree() + 1);
	for (unsigned int i = 1; i <= GetDegree(); i++)
	{
		temp[i] = GetCoefficients()[i - 1] / i;
	}

	SetCoefficients(temp);
}

void Polynomial::operator--()
{
	double temp[MAX_DEGREE + 1];
	for (unsigned int i = 0; i < GetDegree(); i++)
	{
		temp[i] = GetCoefficients()[i + 1] * (i + 1);
	}

	SetCoefficients(temp);
	SetDegree(GetDegree() - 1);
}

double Polynomial::operator()(double x) const
{
	double res = 0.0;
	for (unsigned int i = 0; i <= GetDegree(); i++)
	{
		res += GetCoefficients()[i] * pow(x, i);
	}
	return res;
}
ostream& operator<<(ostream& os, Polynomial poly)
{
	os << endl << "Degree: " << poly.GetDegree();
	os << endl << "Polynomial: ";
	for (unsigned int i = 0; i <= poly.GetDegree(); i++)
	{
		os << *(poly.GetCoefficients() + i) << "x^" << i;
		if (i != poly.GetDegree()) os << " + ";
	}
	os << endl;
	return os;
}

istream& operator>>(istream& os, Polynomial& poly)
{
	std::cout << endl << "What degree will the polynomial be? ";
	unsigned int deg;
	os >> deg;
	poly.SetDegree(deg);
	for (unsigned int i = 0; i <= deg; i++)
	{
		std::cout << "Give me the coefficient for x^" << i << ": ";
		os >> poly[i];
	}

	return os;
}
