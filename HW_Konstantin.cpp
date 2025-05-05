#include <iostream>
#include "Polynomial.h"
using namespace std;

int main()
{
	Polynomial poly;

	cin >> poly;

	//Coefficients might be reversed depending on how the array is used
	//In this case coef[0] = coef of x^0, coef[1] = coef of x^1, etc.
	double coef[4] = { -8, 5, 0, 1 };
	Polynomial given(3, coef);

	Polynomial multi = poly * given;

	cout << endl << "Multiplied polynomial: " << multi;

	//derivative:
	--multi;
	cout << endl << "Derivative: " << multi;

	//Integral:
	++multi;
	cout << endl << "Integral: " << multi;

	//Polynomial at x=2
	double evaluation = multi(2);
}