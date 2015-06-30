#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include "Interpolator.h"
#include "Circuit.h"

using namespace std;

Interpolator::Interpolator(Circuit circuit)
{
    m_Circuit = circuit;
}

 vector< complex<double> > Interpolator::generateSValues(string mode, double radius, double order)
 {
     double step = 0;
     complex<double> sValue;
     vector< complex<double> > values;
//	 	 Linear:
     double real = radius;
     double imag = 0;

//	 	 Circular:
     double modulus = radius;
     double phase = 0;

     if (mode == "LIN")
     {
         step = 2 * radius/order;
         sValue = complex<double>(-real , imag);
         for (int i = 0; i < order + 1; i++)
         {
             if (std::real(sValue) == 0)
             {
                 sValue += complex<double>(step/2 , imag);
                 values.push_back(sValue);
                 sValue += complex<double>(step/2 , imag);

                 continue;
             }

             values.push_back(sValue);
             sValue += complex<double>(step , imag);
         }
     }

     if (mode == "CIR")
     {
         step = 2 * M_PI/(order + 1);
         sValue = polar(modulus, phase);
         for (int i = 0; i < order + 1; i++)
         {
             values.push_back(sValue);
             phase += step;
             sValue = polar(modulus, phase);
         }
     }

     return values;
 }

vector< complex<double> > Interpolator::getEValues(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2],
                                                   complex<double> sValue)
{
    vector< complex<double> > eValues;
    int numVariables = m_Circuit.getNumVariables();

    m_Circuit.solve(Yn, numVariables);

    for (int i = 1; i <= numVariables; i++)
        eValues.push_back(Yn[i][numVariables + 1]);

    return eValues;
}

complex<double> Interpolator::getDValue(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2],
                                        complex<double> sValue)
{
    complex<double> dValue = m_Circuit.determinant(Yn, m_Circuit.getNumVariables());

    return dValue;
}

void Interpolator::calculateAllDValues()
{
    complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2];

    for (int i = 0; i < (int)m_SValues.size(); i++)
    {
        complex<double> dValue;
        complex<double> sValue = m_SValues[i];

        m_Circuit.init(Yn);
        m_Circuit.applyStamps(Yn, sValue);

        dValue = getDValue(Yn, sValue);

        m_DValues.push_back(dValue);
    }
}

void Interpolator::calculateAllEValues()
{
    complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2];

    for (int i = 0; i < (int)m_SValues.size(); i++)
    {
        vector< complex<double> > eValues;
        complex<double> sValue = m_SValues[i];

        m_Circuit.init(Yn);
        m_Circuit.applyStamps(Yn, sValue);

        eValues = getEValues(Yn, sValue);

        m_EValues[i] = eValues;
    }
}

void Interpolator::buildDMatrix(complex<double> A[MAX_VARIABLES + 1])
{
    complex<double> V[MAX_VARIABLES + 1][MAX_VARIABLES + 2];
    int order = m_Circuit.getSystemMaxOrder();

    for (int i = 1; i <= order + 1; i++)
    {
        complex<double> sValue = m_SValues[i - 1];

        for (int j = 1; j <= order + 1; j++)
            V[i][j] = pow(sValue, order - j + 1);
    }

    for (int i = 1; i <= order + 1; i++)
    {
        complex<double> sValue = m_SValues[i - 1];
        complex<double> dValue = m_DValues[i - 1];

        V[i][order + 1] = dValue * sValue;
    }

    m_Circuit.solve(V, order + 1);
    m_Circuit.show(V, order + 1);
}
