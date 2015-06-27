#include <string>
#include <iostream>
#include <complex>
#include "Netlist.h"
#include "Circuit.h"
#include "Element.h"

using namespace std;

Circuit::Circuit(string netlistPath)
{
    m_Netlist = Netlist(netlistPath);

    m_NumVariables = m_Netlist.getNumOfVariables();
    m_NumNodes = m_Netlist.countNodes();
}

Circuit::Circuit(Netlist netlist)
{
    m_Netlist = netlist;

    m_NumVariables = m_Netlist.getNumOfVariables();
    m_NumNodes = m_Netlist.countNodes();
    m_NumElements = m_Netlist.getNumElements();
}

void Circuit::showVariables()
{
    m_Netlist.showVariables();
}

void Circuit::applyStamps(complex<double> Yn[MAX_VARIABLES][MAX_VARIABLES + 1], complex<double> sValue)
{
    for (int i = 0; i < m_NumElements; i++)
    {
        m_Netlist.m_Elements[i].applyStamp(Yn, m_NumVariables, m_Netlist.m_Elements, sValue);
    }
}

void Circuit::solve(double Yn[3][4], int numVariables)
{
    int i, j, l, a;
    double t, p;

    for( i = 1; i <= numVariables; i++ )
    {
        t = 0.0;
        a = i;
        for( l = i; l <= numVariables; l++ )
        {
            if( fabs( Yn[l][i] ) > fabs( t ) )
            {
                a = l;
                t = Yn[l][i];
            }
        }
        if( i != a)
{
            for( l = 1; l <= numVariables + 1; l++ )
            {
                p = Yn[i][l];
                Yn[i][l] = Yn[a][l];
                Yn[a][l] = p;
            }
        }
        if( fabs( t ) < EPSILON )
        {
            //printf("Sistema singular\n");
            return;
        }
        for( j = numVariables + 1; j > 0; j-- ) /* Basta j > i em vez de j > 0 */
        {
            Yn[i][j] /= t;
            p = Yn[i][j];
            for( l = 1; l <= numVariables; l++ )
            {
                if( l != i )
                    Yn[l][j] -= Yn[l][i] * p;
            }
        }
    }
}

void Circuit::show(double Yn[3][4], int numVariables)
{
    for (int i = 0; i < numVariables; i++)
    {
        for (int j = 0; j < numVariables + 1; j++)
            cout << Yn[i][j] << " ";

        cout << endl;
    }
}
