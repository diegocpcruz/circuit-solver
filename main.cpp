#include <iostream>
#include <vector>
#include "Polynomial.h"

using namespace std;

int main()
{
    vector<double> coeffs_1;
    vector<double> coeffs_2;
    complex<double> val(1, 1);

    // Polinômio para teste
    coeffs_1.push_back(4);
    coeffs_1.push_back(1);
    coeffs_1.push_back(2);

    coeffs_2.push_back(0);
    coeffs_2.push_back(3);
    coeffs_2.push_back(1);

    Polynomial poly_1(coeffs_1);
    Polynomial poly_2(coeffs_2);

    cout << ">> Polynomial 1 <<" << endl;
    cout << "Polynomial: " << poly_1.toString() << endl;
    cout << "Degree: " << poly_1.degree() << endl;
    cout << "Number of terms: " << poly_1.numTerms() << endl;

    cout << "P(" << val << ") = " << poly_1.evaluate(val) << endl << endl;

    cout << ">> Polynomial 2 <<" << endl;
    cout << "Polynomial: " << poly_2.toString() << endl;
    cout << "Degree: " << poly_2.degree() << endl;
    cout << "Number of terms: " << poly_2.numTerms() << endl;

    cout << "P(" << val << ") = " << poly_2.evaluate(val) << endl << endl;

    Polynomial poly_3 = poly_1.add(poly_2);

    cout << ">> Polynomial 3 <<" << endl;
    cout << "Polynomial: " << poly_3.toString() << endl;
    cout << "Degree: " << poly_3.degree() << endl;
    cout << "Number of terms: " << poly_3.numTerms() << endl;

    cout << "P(" << val << ") = " << poly_3.evaluate(val) << endl << endl;

    Polynomial poly_4 = poly_3.upOneDegree();


    cout << ">> Polynomial 4 <<" << endl;
    cout << "Polynomial: " << poly_4.toString() << endl;
    cout << "Degree: " << poly_4.degree() << endl;
    cout << "Number of terms: " << poly_4.numTerms() << endl;

    cout << "P(" << val << ") = " << poly_4.evaluate(val) << endl << endl;


    return 0;
}
