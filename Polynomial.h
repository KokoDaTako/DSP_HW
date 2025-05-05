#pragma once
#include <iostream>
#define MAX_DEGREE 15

using namespace std;

class Polynomial
{
public:
	Polynomial();
	Polynomial(unsigned int degree, double coefficients[]);
	Polynomial(const Polynomial& poly);
	~Polynomial();

	//Getters
	unsigned int GetDegree() const;
	double* GetCoefficients() const;

	//Setters
	void SetDegree(unsigned int newDeg);
	void SetCoefficients(double newCoeff[]);
	void SetPolynomial(unsigned int newDeg, double newCoeff[]);

	//Operators
	double& operator[](unsigned int index) const;
	void operator=(Polynomial poly);
	bool operator==(Polynomial poly) const;
	bool operator!=(Polynomial poly) const;
	void operator+=(Polynomial poly);
	void operator-=(Polynomial poly);
	void operator*=(Polynomial poly);
	Polynomial operator+(Polynomial poly) const;
	Polynomial operator-(Polynomial poly) const;
	Polynomial operator*(Polynomial poly) const;
	void operator++();
	void operator--();
	double operator()(double x) const;

private:
	unsigned int polynomialDegree = 0;
	double* polynomialCoefficients;

};

ostream& operator<<(ostream& os, Polynomial poly);
istream& operator>>(istream& os, Polynomial& poly);