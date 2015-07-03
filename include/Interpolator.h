#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <vector>
#include <complex>
#include "Circuit.h"

using namespace std;

class Interpolator
{
    public:
        Interpolator(Circuit circuit);

        vector< complex<double> > generateSValues(string mode, double radius, double order);

        void getAVector(complex<double> A[MAX_VARIABLES + 1]);

        void getBMatrix(complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1]);

        void normalizeA(complex<double> A[MAX_VARIABLES + 1], int maxOrder);

        void normalizeB(complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1], int maxOrder);

        void writeResultsToFile(complex<double> A[MAX_VARIABLES + 1], complex<double> B[MAX_VARIABLES + 1][MAX_VARIABLES + 1],
                                string name);
    private:
        Circuit m_Circuit;
        vector< complex<double> > m_SValues;
        vector< complex<double> > m_DValues;
        vector< complex<double> > m_EValues[MAX_VARIABLES + 1];
        vector<double> m_ConstantsB;
        vector<double> m_OrdersB;
        double m_NormA;
        double m_OrderD;

        void calculateAllEValues();

        void calculateAllDValues();

        vector< complex<double> > getEValues(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2],
                                             complex<double> sValue);

        complex<double> getDValue(complex<double> Yn[MAX_VARIABLES + 1][MAX_VARIABLES + 2],
                                  complex<double> sValue);

        void buildInterpolationMatrix(complex<double> VAL[MAX_VARIABLES + 1][MAX_VARIABLES + 2]);
};

#endif // INTERPOLATOR_H
