#include <iostream>
#include <fstream>
#include "IO.h"


using namespace std;

const char fileNameExportShortRate[]="/storage/data/R/bdt_short_rate.in";

const char fileNameImportMarketData[]="/storage/data/R/bdt_MD_input.csv";

const char fileNameBondData[]="/storage/data/R/bdt_bond_price.csv";

IO::IO() {
}

void IO::exportShortRate2RStudio(double short_rate[TAM_MAX][TAM_MAX], int N){
	double** tmp = new double*[N];
	double** tree = new double*[N];

	for(int i=0;i<N;i++){
		tmp[i] = new double[N];
		tree[i] = new double[N];
		for(int j=0;j<N;j++)
			tree[i][j] = tmp[i][j] = 0;
	}

	// organizing the data
	for (int i=0;i<N;i++){
		int k =0;
		for (int j = -i; j <= i; j += 2){
			tmp[i][k++] = short_rate[i][j];
		}
	}

	//transpose
	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			tree[i][j]= tmp[j][i];
		}
	}


	ofstream file;
	file.open (fileNameExportShortRate);

	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			file << tree[i][j]<<(j==N-1?"":"\t");
		}
		file << endl;
	}
	file.close();
}

void IO::exportBondPrice2RStudio(double bond[TAM_MAX][TAM_MAX], int N){
	double** tmp = new double*[N];
	double** tree = new double*[N];

	for(int i=0;i<N;i++){
		tmp[i] = new double[N];
		tree[i] = new double[N];
		for(int j=0;j<N;j++)
			tree[i][j] = tmp[i][j] = 0;
	}

	// organizing the data
	for (int i=0;i<N;i++){
		int k =0;
		for (int j = -i; j <= i; j += 2){
			tmp[i][k++] = bond[i][j];
		}
	}

	//transpose
	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			tree[i][j]= tmp[j][i];
		}
	}


	ofstream file;
	file.open (fileNameBondData);

	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			file << tree[i][j]<<(j==N-1?"":"\t");
		}
		file << endl;
	}
	file.close();
}


IO::~IO() {
}

