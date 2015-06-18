#include <string>
#include "Element.h"

// Está sendo considerado que os nós somente podem ser números
//
// [TODO: Implementar elementos reativos!]
Element::Element(string netlistLine)
{
    stringstream sstream(netlistLine);

    sstream >> m_Name;
    m_Type = getType();

    sstream.str(string(netlistLine, name.size(), npos));

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

void Element::applyStamp(double Y[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables)
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
