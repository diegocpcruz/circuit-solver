#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <vector>
#include <complex>

using namespace std;

class Interpolator
{
    public:
        Interpolator();
        vector< complex<double> > getSValues(string mode, double radius); // Usar std::polar
    protected:
    private:
};

#endif // INTERPOLATOR_H
