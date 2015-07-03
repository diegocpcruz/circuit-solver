#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <complex>
#include "Element.h"

using namespace std;

// Está sendo considerado que os nós somente podem ser números
//
// [TODO: Implementar elementos reativos!]
Element::Element(string netlistLine, vector<Element> elementsList)
{
    stringstream sstream(netlistLine);

    sstream >> m_Name;
    m_Type = getType();

    m_A = m_B = m_C = m_D = m_X = m_Y = -1;
    m_InitialValue = 0;
    m_Mode = "";

    sstream.str(string(netlistLine, m_Name.size(), string::npos));

    if (m_Type == 'R')
    {
        sstream >> m_A >> m_B >> m_Value;
//        cout << m_Name << " " << m_A << " " << m_B << " " << m_Value << endl;
    }
    if (m_Type == 'C' || m_Type == 'L')
    {
        string str_InitialValue;

        sstream >> m_A >> m_B >> m_Value >> str_InitialValue;
        if (str_InitialValue.length() != 0)
            m_InitialValue = atoi((str_InitialValue.substr(3, string::npos)).c_str());

//        cout << m_Name << " " << m_A << " " << m_B << " " << m_Value << " " << m_InitialValue << endl;
    }
    if (m_Type == 'K')
    {
        string L_A, L_B;

        sstream >> L_A >> L_B >> m_Value;

        for (int i = 0; i < (int)elementsList.size(); i++)
        {
            if (!(elementsList[i].getName()).compare(L_A))
            {
                m_A = elementsList[i].m_A;
                m_B = elementsList[i].m_B;
            }
        }

        for (int i = 0; i < (int)elementsList.size(); i++)
        {
            if (!(elementsList[i].getName()).compare(L_B))
            {
                m_C = elementsList[i].m_A;
                m_D = elementsList[i].m_B;
            }
        }

//        cout << m_Name << " " << m_A << " " << m_B << " " << m_C << " "
//             << m_D << " " << m_Value << endl;
    }
    if (m_Type == 'I' || m_Type == 'V')
    {
        sstream >> m_A >> m_B >> m_Value >> m_Mode;
//        cout << m_Name << " " << m_A << " " << m_B << " " << m_Value
//             << " " << m_Mode << endl;
    }
    else if (m_Type == 'G' || m_Type == 'E' || m_Type == 'F' || m_Type == 'H')
    {
        sstream >> m_A >> m_B >> m_C >> m_D >> m_Value;
//        cout << m_Name << " " << m_A << " " << m_B << " " << m_C << " "
//             << m_D << " " << m_Value << endl;
    }
    else if (m_Type == 'O')
    {
        sstream >> m_A >> m_B >> m_C >> m_D;
//        cout << m_Name << " " << m_A << " " << m_B << " " << m_C << " "
//             << m_D << " " << endl;
    }
}

void Element::showMembers()
{
    cout << "Name: " << m_Name << endl;
    cout << "Type: " << m_Type << endl;
    cout << "Value: " << m_Value << endl;
    cout << "Initial value: " << m_InitialValue << endl;
    cout << "A: " << m_A << endl;
    cout << "B: " << m_B << endl;
    cout << "C: " << m_C << endl;
    cout << "D: " << m_D << endl;
    cout << "X: " << m_X << endl;
    cout << "Y: " << m_Y << endl << endl;
}

//void Element::applyStamp(double Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables)
//{
//    if (m_Type == 'R')
//    {
//        double G = 1/m_Value;
//
//        Yn[m_A][m_A] += G;
//        Yn[m_B][m_B] += G;
//        Yn[m_A][m_B] -= G;
//        Yn[m_B][m_A] -= G;
//    }
//    else if (m_Type == 'G')
//    {
//        Yn[m_A][m_C] += m_Value;
//        Yn[m_B][m_D] += m_Value;
//        Yn[m_A][m_D] -= m_Value;
//        Yn[m_B][m_C] -= m_Value;
//    }
//    else if (m_Type == 'I')
//    {
//        Yn[m_A][numVariables + 1] -= m_Value;
//        Yn[m_B][numVariables + 1] += m_Value;
//    }
//    else if (m_Type == 'V')
//    {
//        Yn[m_A][m_X] += 1;
//        Yn[m_B][m_X] -= 1;
//        Yn[m_X][m_A] -= 1;
//        Yn[m_X][m_B] += 1;
//        Yn[m_X][numVariables + 1] -= m_Value;
//    }
//    else if (m_Type == 'E')
//    {
//        Yn[m_A][m_X] += 1;
//        Yn[m_B][m_X] -= 1;
//        Yn[m_X][m_A] -= 1;
//        Yn[m_X][m_B] += 1;
//        Yn[m_X][m_C] += m_Value;
//        Yn[m_X][m_D] -= m_Value;
//    }
//    else if (m_Type == 'F')
//    {
//        Yn[m_A][m_X] += m_Value;
//        Yn[m_B][m_X] -= m_Value;
//        Yn[m_C][m_X] += 1;
//        Yn[m_D][m_X] -= 1;
//        Yn[m_X][m_C] -= 1;
//        Yn[m_X][m_D] += 1;
//    }
//    else if (m_Type == 'H')
//    {
//        Yn[m_A][m_Y] += 1;
//        Yn[m_B][m_Y] -= 1;
//        Yn[m_C][m_X] += 1;
//        Yn[m_D][m_X] -= 1;
//        Yn[m_Y][m_A] -= 1;
//        Yn[m_Y][m_B] += 1;
//        Yn[m_X][m_C] -= 1;
//        Yn[m_X][m_D] += 1;
//        Yn[m_Y][m_X] += m_Value;
//    }
//    else if (m_Type == 'O')
//    {
//        Yn[m_A][m_X] += 1;
//        Yn[m_B][m_X] -= 1;
//        Yn[m_X][m_C] += 1;
//        Yn[m_X][m_D] -= 1;
//    }
//}

void Element::applyStamp(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables,
                         vector<Element> elementsList, complex<double> sValue, double norm)
{
    if (m_Type == 'R')
    {
        double G = 1/m_Value;

        Yn[m_A][m_A] += G;
        Yn[m_B][m_B] += G;
        Yn[m_A][m_B] -= G;
        Yn[m_B][m_A] -= G;
    }
    else if (m_Type == 'G')
    {
        Yn[m_A][m_C] += m_Value;
        Yn[m_B][m_D] += m_Value;
        Yn[m_A][m_D] -= m_Value;
        Yn[m_B][m_C] -= m_Value;
    }
    else if (m_Type == 'C') // CONSERTAR!!!
    {
        Yn[m_A][m_A] += sValue * m_Value * norm;
        Yn[m_B][m_B] += sValue * m_Value * norm;
        Yn[m_A][m_B] -= sValue * m_Value * norm;
        Yn[m_B][m_A] -= sValue * m_Value * norm;
        Yn[m_A][numVariables + 1] += m_Value * m_InitialValue * norm;
        Yn[m_B][numVariables + 1] -= m_Value * m_InitialValue * norm;
    }
//    else if (m_Type == 'L')
//    {
//        Yn[m_A][m_A] += 1.0 / (sValue * m_Value);
//        Yn[m_B][m_B] += 1.0 / (sValue * m_Value);
//        Yn[m_A][m_B] -= 1.0 / (sValue * m_Value);
//        Yn[m_B][m_A] -= 1.0 / (sValue * m_Value);
//        Yn[m_A][numVariables + 1] -= m_InitialValue / sValue;
//        Yn[m_B][numVariables + 1] += m_InitialValue / sValue;
//    }
    else if (m_Type == 'L') // CHECAR !!!
    {
        Yn[m_A][m_X] += 1;
        Yn[m_B][m_X] -= 1;
        Yn[m_X][m_A] -= 1;
        Yn[m_X][m_B] += 1;
        Yn[m_X][m_X] += sValue * m_Value * norm;
        Yn[m_X][numVariables + 1] += m_Value * m_InitialValue * norm;
    }
//    else if (m_Type == 'K') // CONSERTAR!!!
//    {
//        double L1, L2;
//        double initialValueL1, initialValueL2;
//
//        for (int i = 0; i < (int)elementsList.size(); i++)
//        {
//            Element el = elementsList[i];
//
//            if (el.getType() == 'L' && el.m_A == m_A && el.m_B == m_B)
//            {
//                L1 = el.m_Value;
//                initialValueL1 = el.m_InitialValue;
//            }
//        }
//
//        for (int i = 0; i < (int)elementsList.size(); i++)
//        {
//            Element el = elementsList[i];
//
//            if (el.getType() == 'L' && el.m_A == m_C && el.m_B == m_D)
//            {
//                L2 = el.m_Value;
//                initialValueL2 = el.m_InitialValue;
//            }
//        }
//
//        double r11, r22, r12, r21;
//
//        r11 = L2 / (L1 * L2 - m_Value * m_Value);
//        r22 = L1 / (L1 * L2 - m_Value * m_Value);
//        r12 = r21 = - m_Value / (L1 * L2 - m_Value * m_Value);
//
//        Yn[m_A][m_A] += r11 / sValue;
//        Yn[m_B][m_B] += r11 / sValue;
//        Yn[m_C][m_C] += r22 / sValue;
//        Yn[m_D][m_D] += r22 / sValue;
//        Yn[m_A][m_B] -= r11 / sValue;
//        Yn[m_B][m_A] -= r11 / sValue;
//        Yn[m_A][m_C] += r12 / sValue;
//        Yn[m_C][m_A] += r21 / sValue;
//        Yn[m_A][m_D] -= r12 / sValue;
//        Yn[m_D][m_A] -= r21 / sValue;
//        Yn[m_B][m_C] -= r12 / sValue;
//        Yn[m_C][m_B] -= r21 / sValue;
//        Yn[m_B][m_D] += r12 / sValue;
//        Yn[m_D][m_B] += r21 / sValue;
//        Yn[m_C][m_D] -= r22 / sValue;
//        Yn[m_D][m_C] -= r22 / sValue;
//        Yn[m_A][numVariables + 1] -= initialValueL1 / sValue;
//        Yn[m_B][numVariables + 1] += initialValueL1 / sValue;
//        Yn[m_C][numVariables + 1] -= initialValueL2 / sValue;
//        Yn[m_D][numVariables + 1] += initialValueL2 / sValue;
//    }
    else if (m_Type == 'K') // CONSERTAR!!!
    {
        double L1, L2;
        double initialValueL1, initialValueL2;
        int X, Y;

        for (int i = 0; i < (int)elementsList.size(); i++)
        {
            Element el = elementsList[i];

            if (el.getType() == 'L' && el.m_A == m_A && el.m_B == m_B)
            {
                L1 = el.m_Value;
                initialValueL1 = el.m_InitialValue;
            }
        }

        for (int i = 0; i < (int)elementsList.size(); i++)
        {
            Element el = elementsList[i];

            if (el.getType() == 'L' && el.m_A == m_C && el.m_B == m_D)
            {
                L2 = el.m_Value;
                initialValueL2 = el.m_InitialValue;
            }
        }

        double r11, r22, r12, r21;

        r11 = L2 / (L1 * L2 - m_Value * m_Value);
        r22 = L1 / (L1 * L2 - m_Value * m_Value);
        r12 = r21 = - m_Value / (L1 * L2 - m_Value * m_Value);

        Yn[m_A][m_A] += r11 / sValue;
        Yn[m_B][m_B] += r11 / sValue;
        Yn[m_C][m_C] += r22 / sValue;
        Yn[m_D][m_D] += r22 / sValue;
        Yn[m_A][m_B] -= r11 / sValue;
        Yn[m_B][m_A] -= r11 / sValue;
        Yn[m_A][m_C] += r12 / sValue;
        Yn[m_C][m_A] += r21 / sValue;
        Yn[m_A][m_D] -= r12 / sValue;
        Yn[m_D][m_A] -= r21 / sValue;
        Yn[m_B][m_C] -= r12 / sValue;
        Yn[m_C][m_B] -= r21 / sValue;
        Yn[m_B][m_D] += r12 / sValue;
        Yn[m_D][m_B] += r21 / sValue;
        Yn[m_C][m_D] -= r22 / sValue;
        Yn[m_D][m_C] -= r22 / sValue;
        Yn[m_A][numVariables + 1] -= initialValueL1 / sValue;
        Yn[m_B][numVariables + 1] += initialValueL1 / sValue;
        Yn[m_C][numVariables + 1] -= initialValueL2 / sValue;
        Yn[m_D][numVariables + 1] += initialValueL2 / sValue;
    }
    else if (m_Type == 'I')
    {
        Yn[m_A][numVariables + 1] -= m_Value;
        Yn[m_B][numVariables + 1] += m_Value;
    }
    else if (m_Type == 'V')
    {
        Yn[m_A][m_X] += 1;
        Yn[m_B][m_X] -= 1;
        Yn[m_X][m_A] -= 1;
        Yn[m_X][m_B] += 1;
        Yn[m_X][numVariables + 1] -= m_Value;
    }
    else if (m_Type == 'E')
    {
        Yn[m_A][m_X] += 1;
        Yn[m_B][m_X] -= 1;
        Yn[m_X][m_A] -= 1;
        Yn[m_X][m_B] += 1;
        Yn[m_X][m_C] += m_Value;
        Yn[m_X][m_D] -= m_Value;
    }
    else if (m_Type == 'F')
    {
        Yn[m_A][m_X] += m_Value;
        Yn[m_B][m_X] -= m_Value;
        Yn[m_C][m_X] += 1;
        Yn[m_D][m_X] -= 1;
        Yn[m_X][m_C] -= 1;
        Yn[m_X][m_D] += 1;
    }
    else if (m_Type == 'H')
    {
        Yn[m_A][m_Y] += 1;
        Yn[m_B][m_Y] -= 1;
        Yn[m_C][m_X] += 1;
        Yn[m_D][m_X] -= 1;
        Yn[m_Y][m_A] -= 1;
        Yn[m_Y][m_B] += 1;
        Yn[m_X][m_C] -= 1;
        Yn[m_X][m_D] += 1;
        Yn[m_Y][m_X] += m_Value;
    }
    else if (m_Type == 'O')
    {
        Yn[m_A][m_X] += 1;
        Yn[m_B][m_X] -= 1;
        Yn[m_X][m_C] += 1;
        Yn[m_X][m_D] -= 1;
    }
}

string Element::getName()
{
    return m_Name;
}

char Element::getType()
{
    return m_Name[0];
}

//int Element::getNodeNumber(string nodeName, int& numNodes, vector<string>& variablesList)
//{
//    int i = 0;
//    bool found = false;
//
//    while (!found && i <= numNodes)
//    {
//        if (!(found = !variablesList[i].compare(nodeName)))
//            i++;
//    }
//
//    if (!found) // New node
//    {
//        if (numNodes == MAX_VARIABLES)
//        {
//            cout << "Maximum number of nodes reached: " << MAX_VARIABLES << endl;
//
//            return -1;
//        }
//
//        numNodes++;
//        variablesList[numNodes] = nodeName;
//
//        return numNodes;
//    }
//    else // Known node
//    {
//        return i;
//    }
//}

//void Element::addCurrentVariables(int& numVariables, vector<string>& variablesList)
//{
//    if (m_Type == 'V' || m_Type == 'E' || m_Type == 'F' || m_Type == 'O')
//    {
//        numVariables++;
//
//        if (numVariables> MAX_VARIABLES)
//        {
//            cout << "As correntes extra excederam o numero de variaveis permitido (" << MAX_VARIABLES << ")" << endl;
//            return;
//        }
//
//        x = numVariables;
//        variablesList[numVariables] = "j" + name;
//    }
//    else if (m_Type == 'C')
//    {
//
//    }
//    else if (m_Type=='H')
//    {
//        numVariables += 2;
//        m_X = numVariables - 1;
//        m_Y = numVariables;
//        variablesList[numVariables - 1] = "jx" + m_Name;
//        variablesList[numVariables] = "jy" + m_Name;
//    }
//}

bool Element::isValid()
{
    string validTypes("RIVGEFHOCLK");

    return validTypes.find(m_Type) != string::npos;
}
