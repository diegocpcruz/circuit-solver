#include <iostream>
#include <vector>
#include "Polynomial.h"

using namespace std;

int main()
{
    vector<double> coeffs;

    // Polinômio para teste
    coeffs.push_back(4);
    coeffs.push_back(1);
    coeffs.push_back(2);
    coeffs.push_back(7);
    coeffs.push_back(0);
    coeffs.push_back(0);
    coeffs.push_back(3);
    coeffs.push_back(0);
    coeffs.push_back(0);

    Polynomial poly(coeffs);

    cout << "Degree: " << poly.degree() << endl;
    cout << "Number of terms: " << poly.numOfTerms() << endl;
    cout << "Polynomial: " << poly.toString() << endl;

    return 0;
}
