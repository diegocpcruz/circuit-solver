#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <complex>
#include <string>

using namespace std;

const int DEFAULT_POLY_LEN = 10;
const double EPSILON = 1e-9;

class Polynomial
{
    public:
        Polynomial();
        Polynomial(vector<double> coefficients);
        ~Polynomial();
        void setLength(int numOfCoefficients);
        void adjustDegree();
        int degree();
        int numOfTerms();
        Polynomial upOneDegree();
        complex<double> evaluate(complex<double> val);
        double getCoeff(int i);
        string toString();
        Polynomial add(Polynomial polynomial);
        Polynomial add(double constant);
        Polynomial multByConst(double constant);

    private:
        vector<double> m_Coefficients;
        int m_Degree;
        int m_NumOfTerms;
};

#endif // POLYNOMIAL_H
