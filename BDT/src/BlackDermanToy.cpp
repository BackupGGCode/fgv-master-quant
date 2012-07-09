#include "BlackDermanToy.h"
#include <iostream>
#include "IO.h"


BlackDermanToy::BlackDermanToy() {
	alpha1 = 0.05;
	alpha2 = 0.0;
	alpha3 = 0.10;
	dt = 0;
	error=error1=error2=error3=error4=error5=0;
	sum1=sum2=sum3=sum4=0;
	volSum1=volSum2=0;
	sigVal1=sigVal2=sigVal3=0;
}

double BlackDermanToy::max(double a, double b){
	return a > b ? a : b;
}


void BlackDermanToy::buildBDT(double* yield_curve,double volatility, int N, double T, double inityield){
	// precompute constants – assume one year time step
	dt = 1;

	// initialize yield and volatility curves
	for (i = 1; i <= N; i++){
		R[i] = yield_curve[i-1];
		P[i] = 1/(pow((1 + R[i]*dt),i*dt));
	}

	// initialize first node
	Q[0][0] = 1.0;
	P[0] = 1;
	U[0] = yield_curve[0];
	r[0][0] = yield_curve[0];
	d[0][0] = 1/(1 + r[0][0]*dt);
	// evolve the tree for the short rate
	for (i = 1; i <= N; i++){
		// update pure security prices at time i
		Q[i][-i] = 0.5*Q[i-1][-i+1]*d[i-1][-i+1];
		Q[i][i] = 0.5*Q[i-1][i-1]*d[i-1][i-1];
		for (j = -i+2; j <= i-2; j += 2){
			Q[i][j] = 0.5*Q[i-1][j-1]*d[i-1][j-1] + 0.5*Q[i-1][j+1]*d[i-1][j+1];
		}
		// use numerical search to solve for U[i]
		// Newton-Raphson method
		alpha1 = inityield;

		int k=0; // iteration counter
		do{
			k++;
			sum1 = 0;
			sum2 = 0;
			for (j = -i; j <= i; j += 2)
			{
			sum1 += Q[i][j]*(1/(1 + alpha1*exp(volatility*j*sqrt(dt))*dt));
			sum2 += Q[i][j]*(pow((1+ alpha1*exp(volatility*j*sqrt(dt))*dt),-2)*exp(volatility*j*sqrt(dt))*dt);
			}
			alpha2 = alpha1 - (sum1 - P[i+1])/(-sum2);
			error = alpha2 - alpha1;
			alpha1 = alpha2;
		}while ((error > EPSILON) || k > ITER_MAX);

		U[i] = alpha1;
		// set r[.] and d[.]
		for (j = -i; j <= i; j+= 2)	{
			r[i][j] = U[i]*exp(volatility*j*sqrt(dt));
			d[i][j] = 1.0/(1.0 + r[i][j]*dt);
		}
	}
}

void BlackDermanToy::buildBDT(double* yield_curve,double* volatility_curve, int N, double T, double inityield){

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
		int k=0; // iteration counter
		do{
			k++;
			sum1 = (alpha1 + pow(alpha1,exp(-2*volR[i]*sqrt(dt))))/(2*(1 + r[0][0]*dt));
			sum2 = (1/(2*(1 + r[0][0]*dt)))*(1 + exp(-2*volR[i]*sqrt(dt))*(pow(alpha1,exp(-2*volR[i]*sqrt(dt)) - 1)));
			alpha2 = alpha1 - (sum1 - P[i])/(sum2);
			error = fabs(alpha2 - alpha1);
			alpha1 = alpha2;
		}while ((error > EPSILON) || k > ITER_MAX);
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
		// solve simultaneously for U[i] and sig[i] using 2 dimensional Newton-Raphson

		// initial guess
		alpha1 = inityield;
		sigVal1 = 0.092;

		int k=0; // iteration counter
		do{
			k++;
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
		}while (((error > EPSILON) || (error1 > EPSILON) || (error3 > EPSILON) ||(error4 > EPSILON)) || k > ITER_MAX);

		U[i] = alpha1;
		vol[i] = sigVal1;
		// set r[.] and d[.]
		for (j = -i; j <= i; j += 2){
			r[i][j] = U[i]*exp(vol[i]*j*sqrt(dt));
			d[i][j] = 1/(1 + r[i][j]*dt);
		}
	}
}



double BlackDermanToy::payerSwaptionBDT(/*double* yield_curve,double volatility, double inityield,*/
						int Ns, int NT,double swapRate,  double principal, double frequency){


	double B[TAM_MAX][TAM_MAX];			// discount bond prices
	double C[TAM_MAX][TAM_MAX];			// swaption prices

	// initialize B and C
	for (i = 0; i < TAM_MAX; i++){
		for (j = 0; j < TAM_MAX; j++){
			B[i][j]=0.0;
			C[i][j]=0.0;
		}
	}

	// initialize coupon bond maturity condition for fixed side of swap
	for (j = -Ns; j <= Ns; j += 2){
		B[Ns][j] = principal + swapRate/frequency;
	}

	//derive the coupon bond price in the tree via the discounted expectations
	for (i = Ns - 1; i >= NT; i--){
		for (j = -i; j <= i; j += 2){
		if (i % (int)frequency == 0)
			B[i][j] = this->d[i][j]*0.5*(B[i+1][j+1] + B[i+1][j-1] + swapRate/frequency);
		else
			B[i][j] = this->d[i][j]*0.5*(B[i+1][j+1] + B[i+1][j-1]);
		}
	}

	// initialize maturity condition for option
	for (j = -NT; j <= NT; j += 2){
		C[NT][j] = max(0,(principal-B[NT][j]));
	}
	// for European swaption value utilize the pure security prices
	C[0][0] = 0;
	for (j = -NT; j <= NT; j+=2){
		C[0][0] = C[0][0] + max(0,Q[NT][j]*(principal-B[NT][j]));
	}
	for (i = NT-1; i >= 0; i--){
		for (j = -i; j <= i; j += 2){
			C[i][j] = this->d[i][j]*(0.5*(C[i+1][j+1] + C[i+1][j-1]));
		}
	}

	IO io;
	io.exportBondPrice2RStudio(B,Ns);
	return C[0][0];
}


double BlackDermanToy::europeanBondBDT(OptionType type, int N/*steps*/, int T/*maturity*/,double strike,double principal){
	double B[TAM_MAX][TAM_MAX];			// bond prices
	double C[TAM_MAX][TAM_MAX];			// European Bond Option prices:CALL

	// initialize B and C
	for (i = 0; i < TAM_MAX; i++)
		for (j = 0; j < TAM_MAX; j++){
			B[i][j]=0.0;
			C[i][j]=0.0;
		}

	// initialize bond maturity condition
	for (j = -N; j <= N; j += 2)
		B[N][j] = principal;

	//derive the bond price in the tree via the discounted expectations
	for (i = N - 1; i >= T; i--)
		for (j = -i; j <= i; j += 2)
			B[i][j] = this->d[i][j]*0.5*(B[i+1][j+1] + B[i+1][j-1]);

	// initialize maturity condition for option
	for (j = -T; j <= T; j += 2)
		C[T][j] = (type == CALL?max(0,(B[T][j]-strike)):max(0,(strike-B[T][j])));

	//derive the bond price in the tree via
	for (i = T - 1; i >= 0; i--)
		for (j = -i; j <= i; j += 2)
			C[i][j] = this->d[i][j]*0.5*(C[i+1][j+1] + C[i+1][j-1]);

	return C[0][0];
}

BlackDermanToy::~BlackDermanToy() {
}

