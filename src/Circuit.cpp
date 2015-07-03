#include <string>
#include <iostream>
#include <complex>
#include <cstdio>
#include "Netlist.h"
#include "Circuit.h"
#include "Element.h"

using namespace std;

Circuit::Circuit()
{
    m_Netlist = Netlist();

    m_NumVariables = m_Netlist.getNumOfVariables();
    m_NumNodes = m_Netlist.countNodes();
    m_NumElements = m_Netlist.getNumElements();
}

Circuit::Circuit(string netlistPath)
{
    m_Netlist = Netlist(netlistPath);

    m_NumVariables = m_Netlist.getNumOfVariables();
    m_NumNodes = m_Netlist.countNodes();
    m_NumElements = m_Netlist.getNumElements();
}

Circuit::Circuit(Netlist netlist)
{
    m_Netlist = netlist;

    m_NumVariables = m_Netlist.getNumOfVariables();
    m_NumNodes = m_Netlist.countNodes();
    m_NumElements = m_Netlist.getNumElements();
}

int Circuit::getNumVariables()
{
    return m_NumVariables;
}

void Circuit::showVariables()
{
    m_Netlist.showVariables();
}

bool Circuit::haveStep()
{
    bool haveStep = false;

    for (int i = 0; i < m_NumElements; i++)
    {
        if (m_Netlist.m_Elements[i].m_Mode == "DEGRAU")
            haveStep = true;
    }

    return haveStep;
}

void Circuit::applyStamps(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], complex<double> sValue)
{
    for (int i = 0; i < m_NumElements; i++)
    {
        m_Netlist.m_Elements[i].applyStamp(Yn, m_NumVariables, m_Netlist.m_Elements, sValue, m_Netlist.getNorm());
        cout << "After stamp of (" << m_Netlist.m_Elements[i].getName() << ") | s = " << sValue << endl;
        show(Yn, m_NumVariables);
    }
}

void Circuit::solve(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables)
{
    int i, j, l, a;
    complex<double> t, p = 0;

    //cout << "[INICIO]: " << endl; show(Yn, 2); cout << endl;
    for( i = 1; i <= numVariables; i++ )
    {
        t = 0.0;
        a = i;
        for( l = i; l <= numVariables; l++ )
        {
            if( abs( Yn[l][i] ) > abs( t ) )
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
        if( abs( t ) < EPSILON )
        {
            cout << "Sistema singular" << endl;
            return;
        }
        for( j = numVariables + 1; j > 0; j-- ) /* Basta j>i em vez de j>0 */
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

complex<double> Circuit::determinant(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables)
{
    int i, j, l, a, counter;
    complex<double> t, p = 0;
    complex<double> det = 1;

    //cout << "[INICIO]: " << endl; show(Yn, 2); cout << endl;
    for( i = 1; i <= numVariables; i++ )
    {
        t = 0.0;
        a = i;
        for( l = i; l <= numVariables; l++ )
        {
            if( abs( Yn[l][i] ) > abs( t ) )
//            if( fabs( Yn[l][i] ) != 0)
            {
                a = l;
                t = Yn[l][i];
                counter++;

//                cout << "counter: " << counter << endl;
//                cout << "l: " << l << endl;
//                cout << "i: " << i<< endl;
//                cout << "Yn: " << Yn[l][i] << endl << endl;
            }
        }
        if( i != a)
        {
//            cout << "[2]: "; cout << endl; show(Yn, 2); cout << endl;
            for( l = 1; l <= numVariables + 1; l++ )
            {
                p = Yn[i][l];
                Yn[i][l] = Yn[a][l];
                Yn[a][l] = p;
            }
        }
        if( abs( t ) < EPSILON )
        {
            //printf("Sistema singular\n");
            return 0;
        }
        for( j = numVariables + 1; j > 0; j-- ) /* Basta j > i em vez de j > 0 */
        {
//            cout << "[3]: "; cout << endl; show(Yn, 2); cout << endl;
            //Yn[i][j] /= t;
            //p = Yn[i][j];
            p = Yn[i][j]/t;
//            cout << "[4]: "; cout << endl; show(Yn, 2); cout << endl;
            for( l = 1; l <= numVariables; l++ )
            {
                if( l != i )
                    //Yn[l][j] -= Yn[l][i] * p;
                    Yn[l][j] -= Yn[l][i] * Yn[i][j]/t;
            }
        }
//        cout << "ITERACAO [" << i << "] :" << endl; show(Yn, 2);  cout << endl;
    }

    for (int i = 1; i <= numVariables; i++)
        det *= Yn[i][i];

//    cout << "det antes: " << det << endl;
    det *= pow(-1, counter);

//     cout << "det depois: " << det << endl;
//    cout << "final counter: " << counter << endl;

    return det;
}

void Circuit::init(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2])
{
    for (int i = 0; i <= m_NumVariables; i++)
    {
        for (int j = 0; j <= m_NumVariables + 1; j++)
            Yn[i][j] = 0;
    }
}

string Circuit::getMode()
{
    return m_Netlist.m_Mode;
}

double Circuit::getNorm()
{
    return m_Netlist.m_Norm;
}

double Circuit::getRadius()
{
    return m_Netlist.m_Radius;
}

void Circuit::show(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables)
{
//    cout << " >> " << endl;

    for (int i = 1; i <= numVariables; i++)
    {
        cout << "| ";

        for (int j = 1; j <= numVariables + 1; j++)
        {
            if (abs(Yn[i][j]) < EPSILON && j != numVariables + 1) printf("............. ");
            else printf("%+.2lf %+.2lf j ", std::real(Yn[i][j]), std::imag(Yn[i][j]));
        }

        cout << " |" << endl;
    }

//    cout << " << " << endl << endl;
    cout << endl << endl;
}

int Circuit::getSystemMaxOrder()
{
    return m_Netlist.getSystemMaxOrder();
}

//int Circuit::getNumNodes()
//{
//    return m_Netlist.getnum
//}
