#include <string>
#include "Element.h"

Element::Element()
{
    //ctor
}

// Está sendo considerado que os nós somente podem ser números
// * Implementar elementos reativos!
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

Element::~Element()
{
    //dtor
}

string Element::getName()
{
    return m_Name;
}

char Element::getType()
{
    return m_Name[0];
}
