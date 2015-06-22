#include <iostream>
#include <vector>
#include "Polynomial.h"
#include "Netlist.h"
#include "Circuit.h"

using namespace std;

int main()
{
    // Vetores de coeficientes
    vector<double> coeffs_1;
    vector<double> coeffs_2;

    // Valor p/ teste nos polimômios
    complex<double> val(1, 1);

    // Atribuição dos coeficientes
    coeffs_1.push_back(4);
    coeffs_1.push_back(1);
    coeffs_1.push_back(2);

    coeffs_2.push_back(0);
    coeffs_2.push_back(3);
    coeffs_2.push_back(1);

    // Inicialização dos polinômios
    Polynomial poly_1(coeffs_1);
    Polynomial poly_2(coeffs_2);

    // Polinômio 1
    // Valor esperado: 2s^2 + s + 4
    cout << "[Polynomial 1]" << endl;
    cout << "Polynomial: " << poly_1.toString() << endl;
    cout << "Degree: " << poly_1.degree() << endl;
    cout << "Number of terms: " << poly_1.numTerms() << endl;
    cout << "P(" << val << ") = " << poly_1.evaluate(val) << endl << endl;

    // Polinômio 2
    // Valor esperado: s^2 + 3s
    cout << "[Polynomial 2]" << endl;
    cout << "Polynomial: " << poly_2.toString() << endl;
    cout << "Degree: " << poly_2.degree() << endl;
    cout << "Number of terms: " << poly_2.numTerms() << endl;
    cout << "P(" << val << ") = " << poly_2.evaluate(val) << endl << endl;

    // Polinômio 3
    // Valor esperado: 3s^2 + 4s + 4
    Polynomial poly_3 = poly_1.add(poly_2);
    cout << "[Polynomial 3]" << endl;
    cout << "Polynomial: " << poly_3.toString() << endl;
    cout << "Degree: " << poly_3.degree() << endl;
    cout << "Number of terms: " << poly_3.numTerms() << endl;
    cout << "P(" << val << ") = " << poly_3.evaluate(val) << endl << endl;

//    Polynomial poly_4 = poly_3.upOneDegree();
//
//
//    cout << ">> Polynomial 4 <<" << endl;
//    cout << "Polynomial: " << poly_4.toString() << endl;
//    cout << "Degree: " << poly_4.degree() << endl;
//    cout << "Number of terms: " << poly_4.numTerms() << endl;
//
//    cout << "P(" << val << ") = " << poly_4.evaluate(val) << endl << endl;

    // Polinômio 5
    // Valor esperado: 2s^2 + s + 4
    Polynomial poly_5 = poly_3 - poly_2;
    cout << "[Polynomial 5]" << endl;
    cout << "Polynomial: " << poly_5.toString() << endl;
    cout << "Degree: " << poly_5.degree() << endl;
    cout << "Number of terms: " << poly_5.numTerms() << endl;
    cout << "P(" << val << ") = " << poly_5.evaluate(val) << endl << endl;

    // Teste p/ leitura do netlist
    //Netlist netlist(".\\data\\simples.net");
    //Netlist netlist(".\\data\\but3_ini.net");
    Netlist netlist(".\\data\\EL8.NET");
    cout << "Initial number of variables: " << netlist.getNumOfVariables() << endl;
    netlist.showVariables();

    // Teste p/ inicialização do circuito
    Circuit circuit(netlist);
    cout << "Circuit variables:" << endl;
    circuit.showVariables();

    return 0;
}
