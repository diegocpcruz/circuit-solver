#ifndef NETLIST_H
#define NETLIST_H

#include <string>
#include <vector>
#include "Element.h"

using namespace std;

class Netlist
{
    public:
        Netlist(string path);
        ~Netlist();
        void countNodes();
        void showVariables();
        int getNumOfVariables();

    private:
        int m_NumVariables;
        vector<string> m_VariablesList;
        vector<Element> m_Elements;

        void addCurrentVariable(Element& element);
        void increaseNumNodes(string nodeName);
};

#endif // NETLIST_H
