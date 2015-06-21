#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Element.h"

using namespace std;

// Est� sendo considerado que os n�s somente podem ser n�meros
//
// [TODO: Implementar elementos reativos!]
Element::Element(string netlistLine)
{
    stringstream sstream(netlistLine);

    sstream >> m_Name;
    m_Type = getType();

    m_A = m_B = m_C = m_D = m_X = m_Y = -1;
    m_Mode = "";

    sstream.str(string(netlistLine, m_Name.size(), string::npos));

    if (m_Type == 'R')
    {
        sstream >> m_A >> m_B >> m_Value;
        cout << m_Name << " " << m_A << " " << m_B << " " << m_Value << endl;
    }
    if (m_Type == 'I' || m_Type == 'V')
    {
        sstream >> m_A >> m_B >> m_Value >> m_Mode;
        cout << m_Name << " " << m_A << " " << m_B << " " << m_Value
             << " " << m_Mode << endl;
    }
    else if (m_Type == 'G' || m_Type == 'E' || m_Type == 'F' || m_Type == 'H')
    {
        sstream >> m_A >> m_B >> m_C >> m_D >> m_Value;
        cout << m_Name << " " << m_A << " " << m_B << " " << m_C << " "
             << m_D << " " << m_Value << endl;
    }
    else if (m_Type == 'O')
    {
        sstream >> m_A >> m_B >> m_C >> m_D;
        cout << m_Name << " " << m_A << " " << m_B << " " << m_C << " "
             << m_D << " " << endl;
    }
}

void Element::showMembers()
{
    cout << "[ELEMENT DESCRIPTION]" << endl;
    cout << "Name: " << m_Name << endl;
    cout << "Type: " << m_Type << endl;
    cout << "Value: " << m_Value << endl;
    cout << "A: " << m_A << endl;
    cout << "B: " << m_B << endl;
    cout << "C: " << m_C << endl;
    cout << "D: " << m_D << endl;
    cout << "X: " << m_X << endl;
    cout << "Y: " << m_Y << endl << endl;
}

void Element::applyStamp(double Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables)
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

bool Element::isValid()
{
    string validTypes("RIVGEFHO");

    return validTypes.find(m_Type) != string::npos;
}
