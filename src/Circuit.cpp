#include <string>
#include <iostream>
#include "Netlist.h"
#include "Circuit.h"
#include "Element.h"

using namespace std;

Circuit::Circuit(string netlistPath)
{
    m_Netlist = Netlist(netlistPath);

    m_NumVariables = m_Netlist.getNumOfVariables();
    m_NumNodes = m_Netlist.countNodes();
}

Circuit::Circuit(Netlist netlist)
{
    m_Netlist = netlist;

    m_NumVariables = m_Netlist.getNumOfVariables();
    m_NumNodes = m_Netlist.countNodes();
    m_NumElements = m_Netlist.getNumElements();
}

void Circuit::showVariables()
{
    m_Netlist.showVariables();
}

//void Circuit::applyStamps()
//{
//    for (int i = 0; i < m_NumElements; i++)
//    {
//        m_Netlist.m_Elements[i].applyStamp()
//    }
//}
