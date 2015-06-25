#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include <complex>
#include "Polynomial.h"

#define MAX_VARIABLES 200

using namespace std;

class Element
{
    public:
        int m_A, m_B, m_C, m_D;
        int m_X, m_Y;

        Element(string netlistLine, vector<Element> elementsList);
        void applyStamp(double Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables);
        void applyStamp(Polynomial Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables);
        void applyStamp(complex<double> Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables,
                        vector<Element> elementsList, complex<double> sValue);
        void addCurrentVariables(int& numVariables, vector<Element>& elementsList);
        string getName();
        char getType();
        void showMembers();
        bool isValid();
    private:
        string m_Name;
        char m_Type;
        double m_Value;
        double m_InitialValue;
        string m_Mode;
};

#endif // ELEMENT_H
