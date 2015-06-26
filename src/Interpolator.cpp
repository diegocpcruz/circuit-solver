#include <vector>
#include <complex>
#include "Interpolator.h"

using namespace std;

 vector< complex<double> > Interpolator::getSValues(string mode, double radius)
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
	 		 step = 2*m_Radius/m_Order;
	 		 sValue = (-real , imag);
	 		 while (real(sValue) <= radius)
	 		 {
	 			 if (real(sValue) == 0)
	 			 {
	 				 sValue += (step/2 , imag);
	 				 values.push_back(sValue);
	 				 sValue += (step/2 , imag);
	 			 }
				 values.push_back(sValue);
				 sValue += (step , imag);
	 		 }
	 	 }

	 	 if (mode == "CIR")
	 	 {
	 		 step = 360/m_Order;
	 		 sValue = polar(modulus , phase);
	 		 while (arg(sValue) <= 360)
	 		 {
	 			 values.push_back(sValue);
	 			 sValue += polar(modulus , step);
	 		 }
	 	 }

	 	 return values;
     }
