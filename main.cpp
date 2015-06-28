#include <iostream>
#include <vector>
#include "Polynomial.h"
#include "Netlist.h"
#include "Circuit.h"
#include "Interpolator.h"

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

    // Polinômio 6
    // Valor esperado: s
    Polynomial poly_6(1);
    cout << "[Polynomial 6]" << endl;
    cout << "Polynomial: " << poly_6.toString() << endl;
    cout << "Degree: " << poly_6.degree() << endl;
    cout << "Number of terms: " << poly_6.numTerms() << endl;
    cout << "P(" << val << ") = " << poly_6.evaluate(val) << endl << endl;


    // Teste p/ leitura do netlist
    //double Yn[3][4] = {{0, 0, 0, 0}, {1, 2, 1, 1}, {3, 4, 2, 3}};
    double Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2];

    Yn[0][0] = Yn[0][1] = Yn[0][2] = Yn[0][3] = Yn[0][4] = Yn[1][0] = Yn[2][0] = Yn[3][0] = 0;
    Yn[1][1] = 5.3; Yn[1][2] = 12.4; Yn[1][3] = 233; Yn[1][4] = 5;
    Yn[2][1] = 1; Yn[2][2] = 3; Yn[2][3] = 4; Yn[2][4] = 9;
    Yn[3][1] = 0; Yn[3][2] = 4; Yn[3][3] = 7; Yn[3][4] = 9;



    Netlist netlist(".\\data\\simples.net");
//    Netlist netlist(".\\data\\but3_ini.net");
    //Netlist netlist(".\\data\\EL8.NET");
//    cout << "Initial number of variables: " << netlist.getNumOfVariables() << endl;
//    netlist.showVariables();

    // Teste p/ inicialização do circuito

    Circuit circuit(netlist);
    circuit.show(Yn, 3);
    circuit.solve(Yn, 3);
    cout << "determinant: " << circuit.determinant(Yn, 3) << endl;
//    circuit.show(Yn, 3);
//    cout << "Circuit variables:" << endl;
//    circuit.showVariables();

    Interpolator interpolator(1);
    vector< complex<double> > values;

    values = interpolator.getSValues("LIN", 1, 3);

    for (int i = 0; i < (int)values.size(); i++)
        cout << "value[" << i << "] - " << values[i] << endl;

    return 0;
}
