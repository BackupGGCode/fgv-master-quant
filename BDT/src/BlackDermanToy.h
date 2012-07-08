#include <cmath>
class BlackDermanToy {
public:
	BlackDermanToy();
	double** buildBDT(double* yield_curve,double* volatility_curve, int N, double T);
	virtual ~BlackDermanToy();
};
