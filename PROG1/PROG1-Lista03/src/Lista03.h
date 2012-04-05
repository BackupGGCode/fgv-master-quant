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
void EX06(void);
#define EX6_TAM 10
void EX07(void);
#define EX7_TAM 32
void EX08(void);
#define EX8_TAM 32
void inverte_string(char* pstring);
void EX09(void);
#define EX9_TAM 5
void imprime(int* array, int tam);
int* adiciona_entrada(int* v, int& tamanho, int novo);
int* apaga_entrada(int* v, int& tamanho, int apagar);
void EX10(void);
#define EX10_ERROR 0.00001
#define ANOS 11
#define ITER_MAX 1000
int bisseccao(double fluxo[2][ANOS], double x1, double x2, double& res, int& iter);
double valor_presente(double fluxo[2][ANOS], double taxa);
double derivada_valor_presente(double fluxo[2][ANOS], double taxa);
int newton_raphson(double fluxo[2][ANOS], double inicial, double& res, int& iter);
bool validParam(double param1);
bool validParam(double param1, double param2);

#endif /* LISTA03_H_ */
