#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <complex>
#include <string>

using namespace std;

class Polynomial
{
    public:
        Polynomial(vector<double> coefficients);
        ~Polynomial();
        int degree();
        int numOfTerms();
//        complex<double> evaluate(complex<double> num);
        double getCoeff(int i);
        string toString();
//        Polynomial add(Polynomial polynomial);
//        Polynomial add(double constant);

    private:
        vector<double> m_Coefficients;
//        int m_Degree;
//        int m_NumOfTerms;
};

#endif // POLYNOMIAL_H
