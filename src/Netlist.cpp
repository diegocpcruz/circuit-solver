#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Element.h"
#include "Netlist.h"

using namespace std;

Netlist::Netlist(string path)
{
    ifstream netlistFile;
    string line;

    cout << "Netlist path: " << path << endl;

    netlistFile.open(path.c_str(), ifstream::in);

    if (!netlistFile.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    while(getline(netlistFile, line))
    {
        //cout << line << endl;

        if (line[0] == '*' || isdigit(line[0]))
            continue;

        Element currElement(line);

        if (currElement.isValid())
        {
            m_Elements.push_back(currElement);
            currElement.showMembers();
        }
    }

    netlistFile.close();

    countNodes();
}

Netlist::~Netlist()
{
    m_VariablesList.clear();
    m_Elements.clear();
}

void Netlist::countNodes()
{
    char buffer[255];

    for (int i = 0; i < (int)m_Elements.size(); i++)
    {
        Element currElement = m_Elements[i];
        char type = currElement.getType();

        if (type == 'R' || type == 'I' || type == 'V')
        {
            increaseNumNodes(string(itoa(currElement.m_A, buffer, 10)));
            increaseNumNodes(string(itoa(currElement.m_B, buffer, 10)));
        }
        else if (type == 'G' || type == 'E' || type == 'F' || type == 'H' || type == 'O')
        {
            increaseNumNodes(string(itoa(currElement.m_A, buffer, 10)));
            increaseNumNodes(string(itoa(currElement.m_B, buffer, 10)));
            increaseNumNodes(string(itoa(currElement.m_C, buffer, 10)));
            increaseNumNodes(string(itoa(currElement.m_D, buffer, 10)));
        }
    }

    m_NumVariables = m_VariablesList.size();
}

void Netlist::showVariables()
{
    for (int i = 0; i < (int)m_VariablesList.size(); i++)
        cout << "Variable [" << i << "] : " << m_VariablesList[i] << endl;

}

void Netlist::increaseNumNodes(string nodeName)
{
    for (int i = 0; i < (int)m_VariablesList.size(); i++)
    {
        if (!m_VariablesList[i].compare(nodeName)) // N� j� existente
            return;
    }

    m_VariablesList.push_back(nodeName); // Novo n�
}

int Netlist::getNumOfVariables()
{
    return m_NumVariables;
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
            cout << "As correntes extras excederam o n�mero de vari�veis permitido ("
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
