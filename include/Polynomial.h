#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>

class Polynomial
{
    public:
        Polynomial();
        ~Polynomial();

        int degree();
        int numOfTerms();

    private:
        vector<double> m_Coefficients;
};

#endif // POLYNOMIAL_H
