#include <iostream>
#include <string>
#include "Element.h"
#include "Netlist.h"


Netlist::~Netlist()
{
    //dtor
}

void Netlist::addCurrentVariable(Element& element)
{
    char type = element.getType();
    string name = element.getName();

    if (type == 'V' || type == 'E' || type == 'F' || type == 'O')
    {
        m_NumVariables++;

        if (m_NumVariables > MAX_VARIABLES)
        {
            cout << "As correntes extras excederam o número de variáveis permitido ("
                 << MAX_VARIABLES << ")" << endl;

            return;
        }

        element.m_X = m_NumVariables;
        m_VariablesList[m_NumVariables] = "j" + name;
    }
    else if (type == 'H')
    {
        m_NumVariables += 2;
        element.m_X = m_NumVariables - 1;
        element.m_Y = m_NumVariables;
        m_VariablesList[m_NumVariables - 1] = "jx" + name;
        m_VariablesList[m_NumVariables] = "jy" + name;
    }
}
