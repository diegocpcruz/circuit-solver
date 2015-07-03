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
        int getSystemMaxOrder();
        double getNorm();
        string m_Mode;
        double m_Radius;
        double m_Norm;
        vector<string> m_VariablesList;
    private:
        int m_NumVariables;
        int m_NumElements;

        void addCurrentVariables(Element& element);
        void addAllCurrentVariables();
        void increaseNumNodes(string nodeName);
};

#endif // NETLIST_H
