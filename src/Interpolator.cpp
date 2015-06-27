#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include "Interpolator.h"

using namespace std;

Interpolator::Interpolator(int i)
{
    cout << "FODASE" << endl;
}

 vector< complex<double> > Interpolator::getSValues(string mode, double radius, double order)
 	 {
	 	 double step = 0;
	 	 complex<double> sValue;
	 	 vector< complex<double> > values;
//	 	 Linear:
	 	 double real = radius;
	 	 double imag = 0;
//	 	 Circular:
	 	 double modulus = radius;
	 	 double phase = 0;

	 	 if (mode == "LIN")
	 	 {
	 		 step = 2 * radius/order;
	 		 sValue = complex<double>(-real , imag);
	 		 for (int i = 0; i < order + 1; i++)
	 		 {
	 			 if (std::real(sValue) == 0)
	 			 {
	 				 sValue += complex<double>(step/2 , imag);
	 				 values.push_back(sValue);
	 				 sValue += complex<double>(step/2 , imag);

	 				 continue;
	 			 }

				 values.push_back(sValue);
				 sValue += complex<double>(step , imag);
	 		 }
	 	 }

	 	 if (mode == "CIR")
	 	 {
	 		 step = 2 * M_PI/(order + 1);
	 		 sValue = polar(modulus, phase);
	 		 for (int i = 0; i < order + 1; i++)
	 		 {
	 			 values.push_back(sValue);
	 			 phase += step;
	 			 sValue = polar(modulus, phase);
	 		 }
	 	 }

	 	 return values;
     }
