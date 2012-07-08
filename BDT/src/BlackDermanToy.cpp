#include "BlackDermanToy.h"
#include <iostream>		// cin, cout

BlackDermanToy::BlackDermanToy() {
}

double** BlackDermanToy::buildBDT(double* yield_curve,double* volatility_curve, int N, double T){

	int TAM = N+1;

	double** r = new double*[TAM];		// short rate at node i, j
	double** d = new double*[TAM];		// discount rate at node i, j

	double* U = new double[TAM];		// median of the (lognormal)
										// distribution for r at time t
	double dt = 0.0;					// time step
	double* volR = new double[TAM];		// short rate volatiliy
	double* vol = new double[TAM];		// stores calibrated volatility
										// parameter
	double* P = new double[TAM];		// discount bond prices
	double* Pu = new double[TAM];		// price of bond in up movement
	double* Pd = new double[TAM];		// price of bond in down movement


	double** Qu = new double*[TAM];		// state securities (Arrow-Debreu)
										// prices for an up movement
	double** Qd = new double*[TAM];		// state securities (Arrow-Debreu)
										// prices for a down movement
	double* R = new double[TAM];		// discount curve rates
	const double epsilon = 0.001;		// error tolerance level
	double error, error1, error2 = 0.0;	// errors computed in numerical search
	double error3, error4 = 0.0;		// errors computed in numerical search
	double sum1, sum2 = 0.0;			// sums of first derivatives
	double sum3, sum4 = 0.0;			// sums of second derivatives
	double volSum1, volSum2 = 0.0;		// sum of volatilities
	double sigVal1 = 0.0;				// calibrated volatility parameter
	double sigVal2, sigVal3 = 0.0;		// computed volatilities in numerical
										// search
	double alpha1 = 0.05;				// calibrated U(i) parameter
	double alpha2 = 0.0;				// updated alpha1 (U(i)) parameter
	double alpha3 = 0.10;				// computed U(i) parameter in numerical
										// search
	int i,j;

	// memory allocation
	for(i=0;i<TAM;i++){
		r[i] = new double[TAM];
		d[i] = new double[TAM];
		Qu[i] = new double[TAM];
		Qd[i] = new double[TAM];
	}

	// precompute constants – assume one year time step
	dt = 1;

	// initialize yield and volatility curves
	for (i = 1; i <= N; i++){
		R[i] = yield_curve[i-1];
		P[i] = 1/(pow((1 + R[i]*dt),i*dt));
		volR[i] = volatility_curve[i-1];
	}

	// initialize nodes
	U[0] = R[1];
	r[0][0] = R[1];
	d[0][0] = 1/(1 + r[0][0]*dt);
	vol[0] = volR[1];
	Qu[1][1] = 1;
	Qd[1][-1] = 1;

	// compute Pu[.] and Pd[.]
	for (i = 2; i <= N; i++){
		// solve the following for Pu[i]
		sum1 = 0;
		sum2 = 0;
		error = 0;
		alpha1 = 0.92;
		do{
			sum1 = (alpha1 + pow(alpha1,exp(-2*volR[i]*sqrt(dt))))/(2*(1 + r[0][0]*dt));
			sum2 = (1/(2*(1 + r[0][0]*dt)))*(1 + exp(-2*volR[i]*sqrt(dt))*(pow(alpha1,exp(-2*volR[i]*sqrt(dt)) - 1)));
			alpha2 = alpha1 - (sum1 - P[i])/(sum2);
			error = fabs(alpha2 - alpha1);
			alpha1 = alpha2;
		}while (error > epsilon);
		Pu[i] = alpha1;
		Pd[i] = pow(Pu[i],exp(-2*volR[i]*sqrt(dt)));
	}

	// evolve tree for the short rate
	for (i = 1; i < N; i++){
		// update pure security prices at time step i
		if (i > 1){
			for (j = -i+2; j <= i; j += 2){
				Qu[i][j]= 0.5*Qu[i-1][j-1]*d[i-1][j-1] + 0.5*Qu[i-1][j+1]*d[i-1][j+1];
			}
			for (j = i-2; j >= -i; j -= 2){
				Qd[i][j] =0.5*Qd[i-1][j-1]*d[i-1][j-1] + 0.5*Qd[i-1][j+1]*d[i-1][j+1];
			}
		}
		// solve simultaneously for U[i] and sig[i]
		// using 2 dimensional Newton-Raphson
		// initial guess
		alpha1 = 0.05;
		sigVal1 = 0.092;
		do{
			sum1 = 0;
			sum2 = 0;
			sum3 = 0;
			sum4 = 0;
			volSum1 = 0;
			volSum2 = 0;
			for (j = -i; j <= i; j += 2){
				sum1 += Qu[i][j]*(1/(1 + alpha1*exp(sigVal1*j*sqrt(dt))*dt));
				sum2 += Qu[i][j]*(pow((1+alpha1*exp(sigVal1*j*sqrt(dt))*dt),-2)*(exp(sigVal1*j*sqrt(dt))*dt));
				volSum1 += Qu[i][j]*(pow((1+ alpha1*exp(sigVal1*j*sqrt(dt))*dt),-2)*(alpha1*(j*sqrt(dt))*dt*exp(sigVal1*j*sqrt(dt))));
				sum3 += Qd[i][j]*(1/(1 + alpha1*exp(sigVal1*j*sqrt(dt))*dt));
				sum4 += Qd[i][j]*(pow((1+ alpha1*exp(sigVal1*j*sqrt(dt))*dt),-2)*(exp(sigVal1*j*sqrt(dt))*dt));
				volSum2 += Qd[i][j]*(pow((1+ alpha1*exp(sigVal1*j*sqrt(dt))*dt),-2)*(alpha1*(j*sqrt(dt))*dt*exp(sigVal1*j*sqrt(dt))));
			}
			alpha2 = alpha1 - (sum1 - Pu[i+1])/(-sum2);
			error = fabs(alpha2 - alpha1);
			alpha1 = alpha2;
			sigVal2 = sigVal1 - (sum1 - Pu[i+1])/(-volSum1);
			error1 = fabs(sigVal2 - sigVal1);
			sigVal1 = sigVal2;
			alpha3 = alpha1 - (sum3 - Pd[i+1])/(-sum4);
			error3 = fabs(alpha3 - alpha1);
			sigVal3 = sigVal1 - (sum3 - Pd[i+1])/(-volSum2);
			error4 = fabs(sigVal3 - sigVal1);
			sigVal1 = sigVal3;
		}while ((error > epsilon) || (error1 > epsilon) || (error3 > epsilon) ||(error4 > epsilon));

		U[i] = alpha1;
		vol[i] = sigVal1;
		// set r[.] and d[.]
		for (j = -i; j <= i; j += 2){
			r[i][j] = U[i]*exp(vol[i]*j*sqrt(dt));
			d[i][j] = 1/(1 + r[i][j]*dt);
		}
	}
	// Export
	return r;

}

BlackDermanToy::~BlackDermanToy() {
}

