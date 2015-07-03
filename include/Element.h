#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include <complex>
#include "Polynomial.h"

#define MAX_VARIABLES 200

using namespace std;

class Element
{
	public:
		Element	(string netlistLine, vector<Element> elementsList);

		int m_A;
		int	m_B;
		int	m_C;
		int	m_D;
		int m_X;
		int	m_Y;
		string m_Mode;
//        void applyStamp(double Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables);
//        void applyStamp(Polynomial Yn[MAX_VARIABLES][MAX_VARIABLES + 1], int numVariables);
		string 	getName				();
		char 	getType				();
		void 	applyStamp			(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2], int numVariables, vector<Element> elementsList, complex<double> sValue, double norm);
		void 	addCurrentVariables	(int& numVariables, vector<Element>& elementsList);
		bool 	isValid				();
		void 	showMembers			();

	private:
		string	m_Name;
		char	m_Type;
		double	m_Value;
		double	m_InitialValue;
};

#endif // ELEMENT_H
