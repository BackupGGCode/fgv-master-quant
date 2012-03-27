//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Lista02.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 27/03/2012
// Description : Lista de exercícios 2
//=======================================================================

#ifndef LISTA02_H_
#define LISTA02_H_

#include <iostream>
using namespace std;
#include <iomanip>
#include <math.h>
#include <cctype>


void EX01(void);
void EX01_func(double _arg01,double& _arg02,double& _arg03);
void EX02(void);
int potencia(int i, int j);
void EX03(void);
bool EX03_func(int n);
void EX04(void);
int EX04_func(int n1, int n2);
void EX05(void);
void strinv(char s[]);
#define EX5_TAM 32
void EX06(void);
void EX07(void);
#define EX7_TAM 32
void EX08(void);
void EX09(void);
void EX10(void);
bool validParam(double param1);
bool validParam(double param1, double param2);
bool validParam(double param1, double param2, double param3);


#endif /* LISTA02_H_ */
