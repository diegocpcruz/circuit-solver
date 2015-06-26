#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <vector>
#include <complex>
#include <string>

using namespace std;

class Interpolator
{
    public:
        Interpolator(string mode, double radius, int order) {
        	m_Mode = mode;
        	m_Radius = radius;
        	m_Order = order;
        }
        ~Interpolator();

        vector< complex<double> > getSValues(string mode, double radius, int order); // Usar std::polar

    private:
        string m_Mode;
        int m_Order;
        double m_Radius;

};

#endif // INTERPOLATOR_H
