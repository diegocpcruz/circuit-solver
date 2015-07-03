#ifndef NETLIST_H
#define NETLIST_H

#include <string>
#include <vector>
#include "Element.h"

using namespace std;

class Netlist
{
	public:
		Netlist	();
		Netlist	(string netlistPath);
	   ~Netlist	();

		string			m_Mode;
		double			m_Radius;
		double 			m_Norm;
		vector<Element>	m_Elements;
		vector<string>	m_VariablesList;

		int		getNumOfVariables	();
		int		getNumElements		();
		int		getSystemMaxOrder	();
		double	getNorm				();
		int		countNodes			();
		void	showVariables		();

	private:
		int m_NumVariables;
		int m_NumElements;

		void addCurrentVariables	(Element& element);
		void addAllCurrentVariables	();
		void increaseNumNodes		(string nodeName);
};

#endif // NETLIST_H
