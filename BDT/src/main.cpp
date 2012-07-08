//============================================================================
// Name        : main.cpp
// Author      : Milton Yukio Godoy Saito
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <clocale>		// setlocale
#include "BlackDermanToy.h"


using namespace std;

int main() {

	// configura o locale da aplicação
	// para Português - Brasil
	setlocale(LC_ALL, "ptb");

	double yield_curve[4] = {0.05,0.05,0.05,0.05};
	double volatility_curve[4] = {0.1,0.09,0.08,0.07};
	int N = 4;
	double T = 1;

	BlackDermanToy BDT;

	double** tree;		// short rate tree

	tree=BDT.buildBDT(yield_curve,volatility_curve,N,T);

	for (int i=0;i<N+1;i++){
		for (int j=0;j<N+1;j++){
			cout << tree[i][j] <<"\t\t";
		}
		cout << endl;
	}
	return 0;
}
