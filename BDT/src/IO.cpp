#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "IO.h"
#include <sstream>

using namespace std;

char exportShortRateTree[]
	= "/storage/data/mestrado/2012/workspace/BDT/data/shortRateTree.out";
char exportBondPrice[]
	= "/storage/data/mestrado/2012/workspace/BDT/data/bondPriceTree.out";

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
	file.open (exportShortRateTree);

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
	file.open (exportBondPrice);

	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			file << tree[i][j]<<(j==N-1?"":"\t");
		}
		file << endl;
	}
	file.close();
}


int IO::importMarketData(double* yield, double* volatility){
    ifstream inFile;
    inFile.open("/storage/data/mestrado/2012/workspace/BDT/data/marketData.csv");

    string line;
    int linenum = 0;
    while (getline (inFile, line)){

        istringstream linestream(line);
        string item;
        int itemnum = 0;
        while (getline (linestream, item, ';')){
        	if(itemnum == 0)
        		yield[linenum] = atof(item.c_str());
        	else
        		volatility[linenum] = atof(item.c_str());
            itemnum++;
        }
        linenum++;
    }
	return linenum;
}


IO::~IO() {
}

