#ifndef NETLIST_H
#define NETLIST_H

#include <string>
#include <vector>
#include "Element.h"

using namespace std;

class Netlist
{
    public:
        vector<Element> m_Elements;
        Netlist();
        Netlist(string netlistPath);
        ~Netlist();
        int countNodes();
        void showVariables();
        int getNumOfVariables();
        int getNumElements();
    private:
        int m_NumVariables;
        int m_NumElements;
        vector<string> m_VariablesList;

        void addCurrentVariable(Element& element);
        void increaseNumNodes(string nodeName);
};

#endif // NETLIST_H
