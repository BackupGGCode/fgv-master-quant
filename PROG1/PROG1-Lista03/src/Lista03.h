//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Lista03.h
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 05/04/2012
// Description : Lista de exercícios 3
//=======================================================================

#ifndef LISTA03_H_
#define LISTA03_H_

#include <iostream>
#include <locale.h>
using namespace std;
#include <iomanip>
#include <math.h>
#include <cctype>
#include <cstring>
#include <cstdlib>

#define IGNORE_TAM 32
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
bool validParam(double param1);
bool validParam(double param1, double param2);

#endif /* LISTA03_H_ */
