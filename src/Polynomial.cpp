#include <vector>
#include <complex>
#include <string>
#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial()
{
    m_Coefficients.assign(DEFAULT_POLY_LEN, 0);

    m_Degree = m_NumTerms = 0;
}

Polynomial::Polynomial(double coeff)
{
    m_Coefficients.assign(2, 0);
    m_Coefficients[1] = coeff;

    m_Degree = degree();
    m_NumTerms = numTerms();
}

Polynomial::Polynomial(vector<double> coefficients)
{
    m_Coefficients = coefficients;

    m_Degree = degree();
    m_NumTerms = numTerms();
};

Polynomial::~Polynomial()
{
    m_Coefficients.clear();
};

int Polynomial::degree()
{
    int degree = (int)this->m_Coefficients.size() - 1;

    while (this->m_Coefficients[degree] == 0 && degree > 0)
        degree--;

    return degree;
}

void Polynomial::setLength(int numOfCoefficients)
{
    m_Coefficients.resize(numOfCoefficients);
}

void Polynomial::adjustDegree()
{
    while (m_Degree > 0 && fabs(m_Coefficients[m_Degree]) < EPSILON)
    {
        m_Degree--;
        m_Coefficients.resize(m_Degree);
    }

    return;
}

int Polynomial::numTerms()
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

complex<double> Polynomial::evaluate(complex<double> val)
{
    complex<double> pr = m_Coefficients[m_Degree];

    for (int i = m_Degree - 1; i >= 0; --i)
    {
        pr = pr * val + m_Coefficients[i];
    }

    return pr;
}

Polynomial Polynomial::add(Polynomial polynomial)
{
    if (m_Degree >= polynomial.degree())
    {
        for (int i = 0; i <= polynomial.degree(); i++)
        {
            m_Coefficients[i] += polynomial.getCoeff(i);
        }
    }
    else
    {
        setLength(polynomial.degree() + 1);

        for (int i = 0; i <= m_Degree; i++)
        {
            m_Coefficients[i] += polynomial.getCoeff(i);
        }

        for (int i = m_Degree + 1; i <= polynomial.m_Degree; i++)
        {
            m_Coefficients[i] += polynomial.getCoeff(i);
        }

        m_Degree = polynomial.m_Degree;
    }

    adjustDegree();

    return *this;
}

Polynomial Polynomial::add(double constant)
{
    m_Coefficients[0] += constant;

    return *this;
}

Polynomial Polynomial::upOneDegree()
{
    m_Coefficients.resize(m_Coefficients.size() + 1);

    for (int i = (int)m_Coefficients.size() - 1;  i > 0; i--)
        m_Coefficients[i] = m_Coefficients[i - 1];

    m_Coefficients[0] = 0;

    return *this;
}

//Polynomial Polynomial::multByConst(double constant)
//{
//    for (int i = 0; i <= m_Degree; i++)
//        m_Coefficients[i] *= constant;
//
//    adjustDegree();
//
//    return *this;
//}

Polynomial Polynomial::operator +=(const Polynomial& polynomial)
{
    return this->add(polynomial);
}

Polynomial Polynomial::operator +=(double constant)
{
    return this->add(constant);
}

Polynomial Polynomial::operator -=(const Polynomial& polynomial)
{
    //polynomial.multByConst(-1);

    return this->add((-1)*polynomial);
}

Polynomial Polynomial::operator -=(double constant)
{
    return this->add((-1)*constant);
}

Polynomial Polynomial::operator *=(double constant)
{
    for (int i = 0; i <= m_Degree; i++)
        m_Coefficients[i] *= constant;

    adjustDegree();

    return *this;
}

Polynomial operator +(Polynomial& polynomial_0,
                      Polynomial& polynomial_1)
{
    return Polynomial(polynomial_0) += polynomial_1;
}

Polynomial operator +(const Polynomial& polynomial, double constant)
{
    return Polynomial(polynomial) += constant;
}

Polynomial operator +(double constant, const Polynomial& polynomial)
{
    return Polynomial(polynomial) += constant;
}

Polynomial operator -(const Polynomial& minuend_polynomial, const Polynomial& subtrahend_polynomial)
{
    return Polynomial(minuend_polynomial) -= subtrahend_polynomial;
}

Polynomial operator -(const Polynomial& minuend_polynomial, double constant)
{
    return Polynomial(minuend_polynomial) -= constant;
}

Polynomial operator -(double constant, const Polynomial& polynomial)
{
//    return polynomial.multByConst(-1) + constant;
    return (-1)*polynomial + constant;
}

Polynomial operator *(const Polynomial& polynomial, double constant)
{
    return Polynomial(polynomial) *= constant;
}

Polynomial operator *(double constant, const Polynomial& polynomial)
{
    return Polynomial(polynomial) *= constant;
}


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
