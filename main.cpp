#include <iostream>
#include <vector>
#include <cstdlib>
#include "Polynomial.h"
#include "Netlist.h"
#include "Circuit.h"
#include "Interpolator.h"

using namespace std;

int main()
{
//    Netlist netlist(".\\data\\simples.net");
//    Netlist netlist(".\\data\\tesla.net");
//    Netlist netlist(".\\data\\leapfrog5.net");
//    Netlist netlist(".\\data\\but3.net");
//    Netlist netlist(".\\data\\but3ic.net");
//    Netlist netlist(".\\data\\but3id.net");
//    Netlist netlist(".\\data\\el7g.net");
//    Netlist netlist(".\\data\\el4.net");
//    Netlist netlist(".\\data\\but3_ini.net");
//    Netlist netlist(".\\data\\EL8.NET");
//    Netlist netlist(".\\data\\el51Hz.net");
//    cout << "Initial number of variables: " << netlist.getNumOfVariables() << endl;
//    netlist.showVariables();
    string netlistPath;

    cout << "Caminho para o netlist: ";
    cin >> netlistPath;
    cout << endl;
//
    Netlist netlist(netlistPath);
    // Teste p/ inicialização do circuito

    Circuit circuit(netlist);
    cout << "Number of variables: " << circuit.getNumVariables() << endl;
    cout << "Max order: " << circuit.getSystemMaxOrder() << endl << endl;
    circuit.m_Netlist.showVariables();
    //cout << "Number of variables: " << circuit.getNumVariables << endl;
//    cout << "Circuit variables:" << endl;
//    circuit.showVariables();

    Interpolator interpolator(circuit);
//    circuit.m_Netlist.showVariables();

//    vector< complex<double> > values;

//    values = interpolator.generateSValues("CIR", 1, 3);
//
//    for (int i = 0; i < (int)values.size(); i++)
//        cout << "value[" << i << "] - " << values[i] << endl;

//    circuit.init(Yn);
//    circuit.applyStamps(Yn, 2);
//    circuit.show(Yn, 3);

    complex<double> A[MAX_VARIABLES + 1];
    complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1];

    interpolator.getAVector(A);
    interpolator.getBMatrix(B);

    interpolator.writeResultsToFile(A, B, "xxx");

//    for (int i = 0; i < circuit.getSystemMaxOrder() + 1; i++)
//        cout <<

    system("pause");
    return 0;
}
