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

void Circuit::solve(double Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables)
{
    int i, j, l, a;
    double t, p, counter = 0;

    cout << "[INICIO]: " << endl; show(Yn, 2); cout << endl;
    for( i = 1; i <= numVariables; i++ )
    {
        t = 0.0;
        a = i;
        for( l = i; l <= numVariables; l++ )
        {
            if( fabs( Yn[l][i] ) > fabs( t ) )
//            if( fabs( Yn[l][i] ) != 0)
            {
                a = l;
                t = Yn[l][i];
                counter++;

                cout << "counter: " << counter << endl;
                cout << "l: " << l << endl;
                cout << "i: " << i<< endl;
                cout << "Yn: " << Yn[l][i] << endl << endl;
            }
        }
        if( i != a)
        {
            cout << "[2]: "; cout << endl; show(Yn, 2); cout << endl;
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
            cout << "[3]: "; cout << endl; show(Yn, 2); cout << endl;
            //Yn[i][j] /= t;
            //p = Yn[i][j];
            p = Yn[i][j]/t;
            cout << "[4]: "; cout << endl; show(Yn, 2); cout << endl;
            for( l = 1; l <= numVariables; l++ )
            {
                if( l != i )
                    //Yn[l][j] -= Yn[l][i] * p;
                    Yn[l][j] -= Yn[l][i] * Yn[i][j]/t;
            }
        }
        cout << "ITERACAO [" << i << "] :" << endl; show(Yn, 2);  cout << endl;
    }

    cout << "final counter: " << counter << endl;
}

double Circuit::determinant(double Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables)
{
    int i, j, l, a;
    double t, p, counter = 0;
    double det = 1;

    cout << "[INICIO]: " << endl; show(Yn, 2); cout << endl;
    for( i = 1; i <= numVariables; i++ )
    {
        t = 0.0;
        a = i;
        for( l = i; l <= numVariables; l++ )
        {
            if( fabs( Yn[l][i] ) > fabs( t ) )
//            if( fabs( Yn[l][i] ) != 0)
            {
                a = l;
                t = Yn[l][i];
                counter++;

                cout << "counter: " << counter << endl;
                cout << "l: " << l << endl;
                cout << "i: " << i<< endl;
                cout << "Yn: " << Yn[l][i] << endl << endl;
            }
        }
        if( i != a)
        {
            cout << "[2]: "; cout << endl; show(Yn, 2); cout << endl;
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
            return 0;
        }
        for( j = numVariables + 1; j > 0; j-- ) /* Basta j > i em vez de j > 0 */
        {
            cout << "[3]: "; cout << endl; show(Yn, 2); cout << endl;
            //Yn[i][j] /= t;
            //p = Yn[i][j];
            p = Yn[i][j]/t;
            cout << "[4]: "; cout << endl; show(Yn, 2); cout << endl;
            for( l = 1; l <= numVariables; l++ )
            {
                if( l != i )
                    //Yn[l][j] -= Yn[l][i] * p;
                    Yn[l][j] -= Yn[l][i] * Yn[i][j]/t;
            }
        }
        cout << "ITERACAO [" << i << "] :" << endl; show(Yn, 2);  cout << endl;
    }

    for (int i = 1; i <= numVariables; i++)
        det *= Yn[i][i];

    cout << "det antes: " << det << endl;
    det *= pow(-1, counter);

    cout << "final counter: " << counter << endl;

    return det;
}

void Circuit::show(double Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables)
{
    for (int i = 1; i <= numVariables; i++)
    {
        for (int j = 1; j <= numVariables + 1; j++)
            cout << Yn[i][j] << " ";

        cout << endl;
    }
}
