#include "Element.h"
#include "Netlist.h"

Netlist::Netlist()
{
    //ctor
}

Netlist::~Netlist()
{
    //dtor
}

void Netlist::addCurrentVariable(Element& element)
{
    string type = element.getType();

    if (type == 'V' || type == 'E' || type == 'F' || type == 'O')
    {
        numVariables++;

        if (numVariables > MAX_NODES)
        {
            cout << "As correntes extras excederam o número de variáveis permitido ("
                 << MAX_VARIABLES << ")" << endl;

            return;
        }

        x = numVariables;
        variablesList[numVariables] = "j" + m_Name;
    }
    else if (type == 'H')
    {
        numVariables += 2;
        element.m_X = numVariables - 1;
        m_Y = numVariables;
        variablesList[numVariables - 1] = "jx" + m_Name;
        variablesList[numVariables] = "jy" + m_Name;
    }
}
