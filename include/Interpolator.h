#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <vector>
#include <complex>

using namespace std;

class Interpolator
{
    public:
        Interpolator(int i);
        vector< complex<double> > getSValues(string mode, double radius, double order);
    private:
};

#endif // INTERPOLATOR_H
