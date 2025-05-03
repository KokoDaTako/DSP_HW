#include <iostream>
#include "Polynomial.h"

using namespace std;


int main()
{
	double i[4] = { 2,3,4,5 };
	Polynomial poly(3, i);


	cout << poly[2];
	poly[2] = 10.0;
	cout << endl << poly[2];

	cin >> poly;
	cout << poly;

}