#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <complex>
#include "Netlist.h"
#include "Matrix.h"
#include "Polynomial.h"

class Circuit
{
    public:
        Circuit(string netlistPath);
        Circuit(Netlist netlist);
        void evaluate(complex<double> value, complex<double> Yn[MAX_VARIABLES][MAX_VARIABLES + 1]);
        void showVariables();

    private:
        Netlist m_Netlist;
        //Matrix m_Matrix;
        Polynomial m_Matrix[MAX_VARIABLES][MAX_VARIABLES + 1];
        void applyStamps();
        int m_NumVariables;
        int m_NumNodes;
        int m_NumElements;
};

#endif // CIRCUIT_H
