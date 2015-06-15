#include "Polynomial.h"

#include <vector>
#include <complex>
#include <string>

using namespace std;

Polynomial::Polynomial(vector<double> coefficients)
{
    m_Coefficients = coefficients;
};

Polynomial::~Polynomial()
{
    m_Coefficients.clear();
};

int Polynomial::degree()
{
    int degree = (int)m_Coefficients.size() - 1;

    while (m_Coefficients[degree] == 0)
        degree--;

    return degree;
}

int Polynomial::numOfTerms()
{
    int numTerms = 0;

    for (int i = 0; i < (int)m_Coefficients.size(); i++)
        if (m_Coefficients[i] != 0)
            numTerms++;

    return numTerms;
};

double Polynomial::getCoeff(int i)
{
    if (i >= (int)m_Coefficients.size())
        return 0; // Modificar este tratamento de erro...

    return m_Coefficients[i];
};

string Polynomial::toString()
{
    stringstream strTemp;
    string out = "";
    bool first = true;

    for (int i = (int)m_Coefficients.size() - 1; i >= 0; i--)
    {
        if (m_Coefficients[i] > 0)
        {
            if (!first)
            {
                if (i == 0)
                    strTemp << "+ " << m_Coefficients[i] << " ";
                else
                    strTemp << "+ " << m_Coefficients[i] << "s^" << i << " ";
            }
            else
            {
                if (i == 0)
                    strTemp << m_Coefficients[i] << " ";
                else
                    strTemp << m_Coefficients[i] << "s^" << i << " ";
            }

            first = false;
        }
        else if (m_Coefficients[i] < 0)
        {
            if (!first)
            {
                if (i == 0)
                    strTemp << "- " << m_Coefficients[i] << " ";
                else
                    strTemp << "- " << m_Coefficients[i] << "s^" << i << " ";
            }
            else
            {
                if (i == 0)
                    strTemp << m_Coefficients[i] << " ";
                else
                    strTemp << m_Coefficients[i] << "s^" << i << " ";
            }

            first = false;
        }

        out += strTemp.str();

        strTemp.str("");
        strTemp.clear();
    }

    return out;
}
