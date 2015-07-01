#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Element.h"
#include "Netlist.h"

using namespace std;

Netlist::Netlist()
{
    m_NumVariables = m_NumElements = 0;
    m_Norm = 1;
	m_Radius = 0;
}

Netlist::Netlist(string netlistPath)
{
    ifstream netlistFile;
    string line;

    cout << "Netlist path: " << netlistPath << endl;

    netlistFile.open(netlistPath.c_str(), ifstream::in);

    if (!netlistFile.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    while(getline(netlistFile, line))
    {
        //cout << line << endl;

        if (line[0] == '.')
        {
            cout << "line: " << line << endl;

            stringstream sstream;
            string command, mode, strTemp(line);
            double radius, norm;

            sstream.str(strTemp);

            sstream >> command >> mode >> radius >> norm;

            cout << "sstream: " << sstream.str() << endl;
            cout << "params: " << command << " " << mode << " " << radius << " " << norm << endl;

            m_Mode = mode;
            m_Radius = radius;
            m_Norm = norm;
        }

        if (line[0] == '*' || isdigit(line[0]))
            continue;

        Element currElement(line, m_Elements);

        if (currElement.isValid())
        {
            cout << "line: " << line << endl;

            m_Elements.push_back(currElement);
            currElement.showMembers();
        }
    }

    netlistFile.close();

    countNodes();
    addAllCurrentVariables();
    showVariables();

    m_NumElements = m_Elements.size();
}

Netlist::~Netlist()
{
    m_VariablesList.clear();
    m_Elements.clear();
}

void Netlist::addAllCurrentVariables()
{
    for (int i = 0; i < (int)m_Elements.size(); i++)
        addCurrentVariables(m_Elements[i]);
}

int Netlist::countNodes()
{
    char buffer[255];
    m_VariablesList.push_back("0");

    for (int i = 0; i < (int)m_Elements.size(); i++)
    {
        Element currElement = m_Elements[i];
        char type = currElement.getType();

        if (type == 'R' || type == 'I' || type == 'V' || type == 'C' || type == 'L' )
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

    m_NumVariables = m_VariablesList.size() - 1;

    return m_NumVariables;
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
        if (!m_VariablesList[i].compare(nodeName)) // Nó já existente
            return;
    }

    m_VariablesList.push_back(nodeName); // Novo nó
}

int Netlist::getNumOfVariables()
{
    return m_NumVariables;
}

int Netlist::getNumElements()
{
    return m_NumElements;
}

void Netlist::addCurrentVariables(Element& element) // CHECAR !!!
{
    char type = element.getType();
    string name = element.getName();

//    if (type == 'V' || type == 'E' || type == 'F' || type == 'O' || type == 'L' || type == 'C')
    if (type == 'V' || type == 'E' || type == 'F' || type == 'O' || type == 'L')
    {
        m_NumVariables++;

        if (m_NumVariables > MAX_VARIABLES)
        {
            cout << "As correntes extras excederam o número de variáveis permitido ("
                 << MAX_VARIABLES << ")" << endl;

            return;
        }

        element.m_X = m_NumVariables;
//        m_VariablesList[m_NumVariables] = "j" + name;
        m_VariablesList.push_back( "j" + name);
    }
    else if (type == 'H' || type == 'K')
    {
        m_NumVariables += 2;
        element.m_X = m_NumVariables - 1;
        element.m_Y = m_NumVariables;
//        m_VariablesList[m_NumVariables - 1] = "jx" + name;
//        m_VariablesList[m_NumVariables] = "jy" + name;
        m_VariablesList.push_back("jx" + name);
        m_VariablesList.push_back("jy" + name);
    }
}

int Netlist::getSystemMaxOrder()
{
    int counter = 0;

    for (int i = 0; i < (int)m_Elements.size(); i++)
    {
        char type = m_Elements[i].getType();

        if (type == 'C' || type == 'L')
            counter++;
    }

    return counter;
}

double Netlist::getNorm()
{
    return m_Norm;
}
