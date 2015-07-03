#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <complex>
#include "Netlist.h"
#include "Matrix.h"
#include "Polynomial.h"

class Circuit
{
    public:
        bool haveStep();

        Circuit();
        Circuit(string netlistPath);
        Circuit(Netlist netlist);
        //void evaluate(complex<double> value, complex<double> Yn[MAX_VARIABLsulaES][MAX_VARIABLES + 1]);
        void showVariables();
        int getNumVariables();
        int getNumNodes();
        int getSystemMaxOrder();
        void applyStamps();
        void solve(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables);

        void show(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables);

        complex<double> determinant(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables);

        void init(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2]);

        void applyStamps(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], complex<double> sValue);

        string getMode();
        double getNorm();
        double getRadius();
        Netlist m_Netlist; // MUDAR!!!
    private:
        //Matrix m_Matrix;
        //Polynomial m_Matrix[MAX_VARIABLES][MAX_VARIABLES + 1];
        int m_NumVariables;
        int m_NumNodes;
        int m_NumElements;
};
#endif // CIRCUIT_H
