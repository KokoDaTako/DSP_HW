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
}

Polynomial::Polynomial(Polynomial& poly) 
{
	polynomialDegree = poly.GetDegree();
	polynomialCoefficients = new double[MAX_DEGREE + 1];
	for (unsigned int i = 0; i <= polynomialDegree; i++) {
		polynomialCoefficients[i] = poly.GetCoefficients()[i];
	}
}

Polynomial::~Polynomial()
{
	delete polynomialCoefficients;
}

unsigned int Polynomial::GetDegree()
{
	return polynomialDegree;
}

double* Polynomial::GetCoefficients()
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
}

double& Polynomial::operator[](unsigned int index)
{
	assert(("ERROR: index attempted is higher than degree", index <= polynomialDegree));
	return polynomialCoefficients[index];
}

void Polynomial::operator=(Polynomial poly)
{
	polynomialDegree = poly.GetDegree();
	polynomialCoefficients = new double[MAX_DEGREE + 1];
	for (unsigned int i = 0; i <= polynomialDegree; i++)
	{
		polynomialCoefficients[i] = poly.GetCoefficients()[i];
	}
}

bool Polynomial::operator==(Polynomial poly)
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

bool Polynomial::operator!=(Polynomial poly)
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
ostream& operator<<(ostream& os, Polynomial& poly)
{
	os << endl << "Degree: " << poly.GetDegree();
	os << endl << "Polynomial: ";
	for (unsigned int i = 0; i <= poly.GetDegree(); i++)
	{
		os << *(poly.GetCoefficients() + i) << "x^" << i;
		if (i != poly.GetDegree()) os << " + ";
	}

	return os;
}

istream& operator>>(istream& os, Polynomial& poly)
{
	std::cout << endl << "What degree will the polynomial be?";
	unsigned int deg;
	os >> deg;
	poly.SetDegree(deg);
	for (unsigned int i = 0; i <= deg; i++)
	{
		std::cout << "Give me the coefficient for x^" << i;
		os >> poly[i];
	}

	return os;
}
