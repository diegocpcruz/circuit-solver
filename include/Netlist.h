#ifndef NETLIST_H
#define NETLIST_H

#include <string>
#include "Element.h"

class Netlist
{
    public:
        ~Netlist();
    private:
        int m_NumVariables;
        vector<string> m_VariablesList;

        void addCurrentVariable(Element& element);
};

#endif // NETLIST_H
