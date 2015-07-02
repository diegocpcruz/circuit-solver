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

    m_SValues = generateSValues(m_Circuit.getMode(), m_Circuit.getRadius(), m_Circuit.getSystemMaxOrder());

    calculateAllDValues();
    calculateAllEValues();
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
             if (fabs(std::real(sValue)) < EPSILON)
                sValue = complex<double>(0, std::imag(sValue));

             if (fabs(std::imag(sValue)) < EPSILON)
                sValue = complex<double>(std::real(sValue), 0);

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
//        m_Circuit.show(Yn, m_Circuit.getNumVariables());

        m_Circuit.applyStamps(Yn, sValue);
//        m_Circuit.show(Yn, m_Circuit.getNumVariables());

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

void Interpolator::getAVector(complex<double> A[MAX_VARIABLES + 1])
{
    complex<double> V[MAX_VARIABLES + 1][MAX_VARIABLES + 2];
    int order = m_Circuit.getSystemMaxOrder();

    buildInterpolationMatrix(V);

    for (int i = 1; i <= order + 1; i++)
    {
//        complex<double> sValue = m_SValues[i - 1];
        complex<double> dValue = m_DValues[i - 1];

//        V[i][order + 1] = dValue * sValue;
        V[i][order + 2] = dValue;
    }

    m_Circuit.solve(V, order + 1);
    cout << "After solve D: " << endl;
    m_Circuit.show(V, order + 1);

    for (int i = order + 1; i >= 1; i--)
        A[i - 1] = V[i][order + 2];

    normalizeA(A, order);

    for (int i = order + 1; i >= 1; i--)
        cout << "A[" << order + 1 - i << "] = " << A[i - 1] << endl;

    cout << endl;
}

void Interpolator::getBMatrix(complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1])
{
    complex<double> V[MAX_VARIABLES + 1][MAX_VARIABLES + 2];
    int order = m_Circuit.getSystemMaxOrder();

    for (int coluna = 1; coluna <= order; coluna++)
    {
//        vector< complex<double> > eValues = m_EValues[i - 1];

        m_Circuit.init(V);
        buildInterpolationMatrix(V);

        for (int linha = 1; linha <= order + 1; linha++)
        {
//            V[j][order + 1] = m_EValues[j - 1][i - 1] * m_DValues[j - 1] * m_SValues[j - 1];
            V[linha][order + 2] = m_EValues[linha - 1][coluna - 1] * m_DValues[linha - 1];
        }

        m_Circuit.solve(V, order + 1);
        cout << "After solve E" << coluna << endl;
        m_Circuit.show(V, order + 1);

        normalizeB(B, order);
        for (int linha = order + 1; linha >= 1; linha--)
        {
        	if (abs(V[linha][order + 2]) < EPSILON)
        		B[linha - 1][coluna - 1] = 0;
        	else
        		B[linha - 1][coluna - 1] = V[linha][order + 2] / m_NormVectorB[coluna -1];

//            cout << "B[" << order + 1 - j << "][" << i - 1 << "] = " << B[j - 1][i - 1] << endl;
        }

//        Exibe na tela
        for (int j = order + 1; j >= 1; j--)
            cout << "B[" << order + 1 - j << "][" << coluna - 1 << "] = " << B[j - 1][coluna - 1] << endl;

        cout << endl;
    }
}

void Interpolator::buildInterpolationMatrix(complex<double> V[MAX_VARIABLES + 1][MAX_VARIABLES + 2])
{
    int order = m_Circuit.getSystemMaxOrder();

    for (int i = 1; i <= order + 1; i++)
    {
        complex<double> sValue = m_SValues[i - 1];

        for (int j = 1; j <= order + 1; j++)
            V[i][j] = pow(sValue, order - j + 1);
    }
}

void Interpolator::normalizeA(complex<double> A[MAX_VARIABLES + 1], int maxOrder)
{
    double normFactor;

    // Retirar lixo numérico
    for (int i = 0; i < maxOrder + 1; i++)
        if (abs(A[i]) < EPSILON)
            A[i] = 0;

    // Encontrar coeficiente de maior grau
    for (int i = 0; i < maxOrder + 1; i++)
    {
        if (abs(A[i]) != 0)
        {
            normFactor = abs(A[i]);
            break;
        }
    }

    // Normaliza
    for (int i = 0; i < maxOrder + 1; i++)
        A[i] /= normFactor;

    m_NormA = normFactor;
}

void Interpolator::normalizeB(complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1], int order)
{
	double normFactor = 1;
	m_NormVectorB.resize(order);

    // Retira lixo numérico e seta o maior coeficiente de cada coluna da matriz B.
    for (int coluna = 0; coluna < order + 1; coluna++)
    {
    	for (int linha = 0; linha < order + 1; linha++)
    	{
    		if (abs(B[linha][coluna]) < EPSILON)
    			B[linha][coluna] = 0;
    		if (abs(B[linha][coluna]) > normFactor)
    			normFactor = abs(B[linha][coluna]);
    	}
    	m_NormVectorB[coluna] = normFactor;

    }

	for (unsigned i = 0; i < m_NormVectorB.size(); i++)
		cout << "m_NormVectorB[" << i << "]" << m_NormVectorB[i] << endl;

}
