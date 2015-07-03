#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
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
        complex<double> sValue = m_SValues[i - 1];
        complex<double> dValue = m_DValues[i - 1];

        if (m_Circuit.haveStep()) V[i][order + 2] = dValue * sValue;
        else V[i][order + 2] = dValue;
    }

    m_Circuit.solve(V, order + 1);
    cout << "After solve D: " << endl;
    m_Circuit.show(V, order + 1);

    for (int i = order + 1; i >= 1; i--)
        A[i - 1] = V[i][order + 2];

    normalizeA(A, order);

    // Exibe na tela
    cout << "Denominador: " << endl;
    for (int i = order + 1; i >= 1; i--)
        //if (order - i + 1 <= m_OrderD)
            printf("a%d = %.4lf\n", order - i + 1, std::real(A[i - 1]));

    cout << endl;
}

void Interpolator::getBMatrix(complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1])
{
    complex<double> V[MAX_VARIABLES + 1][MAX_VARIABLES + 2];
    int order = m_Circuit.getSystemMaxOrder();
    int numVariables = m_Circuit.getNumVariables();

    for (int j = 1; j <= numVariables; j++)
    {
        m_Circuit.init(V);
        buildInterpolationMatrix(V);

        for (int i = 1; i <= order + 1; i++)
        {
            if (m_Circuit.haveStep()) V[i][order + 2] = m_EValues[i - 1][j - 1] * m_DValues[i - 1] * m_SValues[j - 1];
            else V[i][order + 2] = m_EValues[i - 1][j - 1] * m_DValues[i - 1];
        }

        m_Circuit.solve(V, order + 1);
//        cout << "After solve E" << j << endl;
//        m_Circuit.show(V, order + 1);

        for (int i = 1; i <= order + 1; i++)
            B[i - 1][j - 1] = V[i][order + 2];
    }

    normalizeB(B, order);

    // Exibe na tela
    for (int j = 1; j <= numVariables; j++)
    {
//        bool found = false;

        cout << "Numerador " << j << " (" << m_Circuit.m_Netlist.m_VariablesList[j] << "):" << endl;
        for (int i = order + 1; i >= 1; i--)
        {
            if (order - i + 1 <= m_OrdersB[j - 1])
            {
//                printf("b%d = %+.4lf %+.4lf j\n", order - i + 1, std::real(B[i - 1][j - 1]), std::imag( B[i - 1][j - 1]));
                printf("b%d = %.4lf\n", order - i + 1, std::real(B[i - 1][j - 1]));
            }
        }

        printf("cte: %.4lf\n\n", m_ConstantsB[j - 1]);
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

    // Retira lixo numérico
    for (int i = 0; i < maxOrder + 1; i++)
    {
        if (abs(A[i]) < EPSILON)
            A[i] = 0;
    }

    // Encontra coeficiente de maior grau
    for (int i = 0; i < maxOrder + 1; i++)
    {
        if (abs(A[i]) != 0)
        {
            normFactor = std::real(A[i]);
            m_OrderD = maxOrder - i;
            break;
        }
    }

    // Normaliza
    for (int i = 0; i < maxOrder + 1; i++)
        A[i] /= normFactor;

    m_NormA = normFactor;
}

void Interpolator::normalizeB(complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1], int maxOrder)
{
    int numVariables = m_Circuit.getNumVariables();

    m_ConstantsB.clear();

    // Retira lixo numérico e normaliza polinômio numerador
    for (int i = 0; i < maxOrder + 1; i++)
    {
        for (int j = 0; j < numVariables; j++)
        {
            if (abs(B[i][j]) < EPSILON)
                B[i][j] = 0;

            B[i][j] /= m_NormA;
        }
    }

    m_OrdersB.assign(numVariables, 0);
    for (int j = 0; j < numVariables; j++)
    {
        double constant = 1;

        // Encontra coeficiente de maior grau
        for (int i = 0; i < maxOrder + 1; i++)
        {
            if (abs(B[i][j]) != 0)
            {
                constant = std::real(B[i][j]);
                m_OrdersB[j] = maxOrder - i;
                break;
            }
        }

        // Adiciona constante ao vetor
        m_ConstantsB.push_back(constant);

        // Normaliza
        for (int i = 0; i < maxOrder + 1; i++)
            B[i][j] /= constant;

    }
}

void Interpolator::writeResultsToFile(complex<double> A[MAX_VARIABLES + 1],
                                      complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1],
                                      string name)
{
    int maxOrder = m_Circuit.getSystemMaxOrder();

    // Arquivo para coeficientes do DENOMINADOR
    string denFileName(name + ".d");
    ofstream denominatorFile (denFileName.c_str());

    if (denominatorFile.is_open())
    {
        char buffer[255];

        denominatorFile << m_OrderD << endl;

        // Exibe na tela
        for (int i = maxOrder + 1; i >= 1; i--)
        {
            if (maxOrder - i + 1 <= m_OrderD)
            {
                sprintf(buffer, "%.4lf\n", std::real(A[i - 1]));
                denominatorFile << buffer;
            }
        }

        sprintf(buffer, "%.4lf\n", 1.0);
        denominatorFile << buffer;

        sprintf(buffer, "%.4lf\n", m_Circuit.getNorm());
        denominatorFile << buffer;

        denominatorFile.close();
    }


    int numVariables = m_Circuit.getNumVariables();
    for (int j = 1; j <= numVariables; j++)
    {
        // Arquivo para coeficientes do DENOMINADOR
        char bufferName[255];
        string numFileName(name + ".n" + itoa(j, bufferName, 10));
        ofstream numeratorFile (numFileName.c_str());

        if (numeratorFile.is_open())
        {
            char buffer[255];

            numeratorFile << m_OrderD << endl;

            // Exibe na tela
            for (int i = maxOrder + 1; i >= 1; i--)
            {
                if (maxOrder - i + 1 <= m_OrdersB[j - 1])
                {
                    sprintf(buffer, "%.4lf\n", std::real(B[i - 1][j - 1]));
                    numeratorFile << buffer;
                }
            }

            sprintf(buffer, "%.4lf\n", m_ConstantsB[j - 1]);
            numeratorFile << buffer;

            sprintf(buffer, "%.4lf\n", m_Circuit.getNorm());
            numeratorFile << buffer;

            numeratorFile.close();
        }
    }
}
