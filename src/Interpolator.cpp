#include <vector>
#include <complex>
#include "Interpolator.h"

using namespace std;

 vector< complex<double> > Interpolator::getSValues(string mode, double radius, int order)
 	 {
	 	 double step, beggin, point = 0;
	 	 vector< complex<double> > values;

	 	 step = 2*m_Radius/m_Order;

	 	 if (mode == "LIN")
	 	 {
	 		 point = beggin = -radius;
	 	 }

	 	 if (mode == "CIR")
	 	 {

	 	 }

	 	 for (int i = 0; i < N; i++)
	 	 {
	 		 complex<double> currValue;

	 		 values.push_back(currValue);
	 	 }

	 	 return values;
     }
