#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <complex>
#include <string>

using namespace std;

const int		DEFAULT_POLY_LEN 	= 10;
const double	EPSILON 			= 1e-9;

class Polynomial
{
	public:
		Polynomial	();
		Polynomial	(double coeff);
		Polynomial	(vector<double> coefficients);
		~Polynomial	();

		double 			getCoeff		(int i);
		void 			setLength		(int numOfCoefficients);
		void 			adjustDegree	();
		int 			degree			();
		int 			numTerms		();
		Polynomial		upOneDegree		();
		complex<double>	evaluate		(complex<double> val);
		Polynomial 		add				(Polynomial polynomial);
		Polynomial 		add				(double constant);
		//Polynomial multByConst(double constant);

		Polynomial 		operator +=		(const Polynomial& polynomial);
		Polynomial 		operator +=		(double constant);
		Polynomial 		operator -=		(const Polynomial& polynomial);
		Polynomial 		operator -=		(double constant);
		Polynomial 		operator *=		(double constant);
		string 			toString		();
	private:
		vector<double>	m_Coefficients;
		int 			m_Degree;
		int 			m_NumTerms;
};

Polynomial operator +	(const Polynomial& polynomial_0, const Polynomial& polynomial_1);
Polynomial operator +	(const Polynomial& polynomial, double constant);
Polynomial operator +	(double constant, const Polynomial& polynomial);
Polynomial operator -	(const Polynomial& minuend_polynomial, const Polynomial& subtrahend_polynomial);
Polynomial operator -	(const Polynomial& minuend_polynomial, double constant);
Polynomial operator -	(double constant, const Polynomial& polynomial);
Polynomial operator *	(const Polynomial& polynomial, double constant);
Polynomial operator *	(double constant, const Polynomial& polynomial);

#endif // POLYNOMIAL_H
