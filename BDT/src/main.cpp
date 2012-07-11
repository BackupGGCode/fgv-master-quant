#include <iostream>
#include "BlackDermanToy.h"
#include "IO.h"


using namespace std;

int main() {
//=====================================================================================================
	// Implementing Derivatives Models (Clewlow) page 244
	double T1 = 1;
	const int N1 = 5;
	double inityield1 = 0.05;
	double yield_curve1[N1] = {0.05,0.05,0.05,0.05};
	double vol_curve1[N1] = {0.1,0.09,0.08,0.07};

	BlackDermanToy bdt1;
	bdt1.buildBDT(yield_curve1,vol_curve1,N1,T1,inityield1);

	IO io;
	io.exportShortRate2RStudio(bdt1.r,N1-1);

	//=====================================================================================================
	// Modeling Derivatives in C++ (London) page 551

	/* 	Consider a two-year payer swaption on a three-year swap. We assume the term
		structure is upward sloping and given by {0.055, 0.0575, 0.0600, 0.0625, 0.0650,0.070}
		and the short-rate volatility is assumed to be 10 percent. The swap rate is
		6.5 percent and we assume annual payments. We assume the notional face value or
		principal is $100. Figure 11.5 shows the BDT tree built.
		The price of the payer swaption is $16.31. */

	double T2 = 1;
	const int N2 = 6;
	double inityield2 = 0.05;
	double yield_curve2[N2] = {0.055, 0.0575, 0.060, 0.0625, 0.0650, 0.070};

	double swap_rate = 0.065;
	double principal = 100.0;
	double volatility1 = 0.1;
	double frequency = 1;

	BlackDermanToy bdt2;
	bdt2.buildBDT(yield_curve2,volatility1,N2,T2,inityield2);

	cout <<"o preço da swaption: " << bdt2.payerSwaptionBDT(5/*three-year swap*/,2/*two-year payer swaption*/,swap_rate,principal,frequency) << endl;

	//=====================================================================================================
	double T3 = 2;
	const int N3 = 3;
	double inityield3 = 0.04;
	double yield_curve3[N3] = {0.0475,0.05,0.0525};
	double volatility3 = 0.18;
	double strike = 0.94;
	double principal = 1.0;

	BlackDermanToy bdt3;
	bdt3.buildBDT(yield_curve3,volatility3,N3,T3,inityield3);

	IO io;
	io.exportShortRate2RStudio(bdt3.r,N3-1);

	cout <<"Call European Bond Option price: " << bdt3.europeanBondBDT(CALL,N3,T3,strike,principal)<< endl;
	cout <<"Put European Bond Option price: " << bdt3.europeanBondBDT(PUT,N3,T3,strike,principal)<< endl;




	return 0;
}
