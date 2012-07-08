#include <cmath>
#define	TAM_MAX 100					//tree max dimension
#define EPSILON 0.001				// error tolerance level

class BlackDermanToy {
public:
	double r[TAM_MAX][TAM_MAX];		// short rate
	double d[TAM_MAX][TAM_MAX];		// discount rate
	double Q[TAM_MAX][TAM_MAX];		// state securities (Arrow-Debreu) **** constant volatility ****
	double Qu[TAM_MAX][TAM_MAX];	// state securities (Arrow-Debreu) prices for an up movement
	double Qd[TAM_MAX][TAM_MAX];	// state securities (Arrow-Debreu) prices for a down movement
	double error,error1,error2;		// errors computed in numerical search
	double error3,error4,error5;		// errors computed in numerical search
	double sum1, sum2;				// sums of first derivatives
	double sum3, sum4;				// sums of first derivatives
	double U[TAM_MAX];				// median of the (lognormal)
	double P[TAM_MAX];				// discount bond prices
	double Pu[TAM_MAX];				// price of bond in up movement
	double Pd[TAM_MAX];				// price of bond in down movement
	double R[TAM_MAX];				// discount curve rates

	double volR[TAM_MAX];			// short rate volatiliy
	double vol[TAM_MAX];			// stores calibrated volatility
	double volSum1, volSum2;		// sum of volatilities
	double sigVal1;					// calibrated volatility parameter
	double sigVal2, sigVal3;		// computed volatilities in numerical
									// search
	double alpha1;					// calibrated U(i) parameter
	double alpha2;					// updated alpha1 (U(i)) parameter
	double alpha3;					// computed U(i) parameter in numerical
	double dt;						// time step
	int i,j;						// search index


	BlackDermanToy();
	void buildBDT(double* yield_curve,double* volatility_curve, int N, double T, double inityield);
	void buildBDT(double* yield_curve,double volatility, int N, double T, double inityield);
	double payerSwaptionBDT(/*double* yield_curve,double volatility, double inityield,*/ int Ns, int NT,double swapRate,  double principal, double frequency);
	virtual ~BlackDermanToy();

private:
	double max(double a, double b);
};
