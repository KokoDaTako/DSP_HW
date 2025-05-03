#pragma once
#include <iostream>
#define MAX_DEGREE 15

using namespace std;

class Polynomial
{
public:
	Polynomial();
	Polynomial(unsigned int degree, double coefficients[]);
	Polynomial(Polynomial& poly);
	~Polynomial();

	//Getters
	unsigned int GetDegree();
	double* GetCoefficients();

	//Setters
	void SetDegree(unsigned int newDeg);
	void SetCoefficients(double newCoeff[]);

	//Operators
	double& operator[](unsigned int index);
	
	/*double operator[](Polynomial& poly);
	double operator[](Polynomial& poly);
	double operator[](Polynomial& poly);*/

private:
	unsigned int polynomialDegree = 0;
	double* polynomialCoefficients;

};

ostream& operator<<(ostream& os, Polynomial& poly);
istream& operator>>(istream& os, Polynomial& poly);