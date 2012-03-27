//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Lista02.cpp
// Discipline  : FGV - MPE -Programa��o e M�todos Num�ricos em Finan�as I
// Date		   : 06/03/2012
// Description : Lista de exerc�cios 2
//=======================================================================

#include <iostream>
#include <iomanip>
#include <math.h>
#include "Lista02.h"
using namespace std;



int main(void)
{
	setlocale(LC_ALL, "ptb");
	int menu=-1;
	do{
		switch(menu){
		case 0:  return 0;
		case  1: EX01(); break;
		case  2: EX02(); break;
		case  3: EX03(); break;
		case  4: EX04(); break;
		case  5: EX05(); break;
		case  6: EX06(); break;
		case  7: EX07(); break;
		case  8: EX08(); break;
		case  9: EX09(); break;
		case 10: EX10(); break;
		}
		cout << endl << "Digite o n�mero do exerc�cio [1-10 ou 0-sair]: ";
		cin >> menu;
		cout << endl;
	}while(menu!=0);

	return 0;
}
/**************************** EX01 ****************************/
void EX01(void)
{
	double arg01 = 0, arg02 = 0, arg03 = 0;

	cout << "[EX01 in] Digite um n�mero N: ";
	cin >> arg01;
	EX01_func(arg01,arg02,arg03);

	cout << "[EX01 out] A parte inteira de N:  "<< arg02 << endl;
	cout << "[EX01 out] A parte decimal de N:  "<< arg03 << endl;
}
void EX01_func(double _arg01,double& _arg02,double& _arg03)
{
	_arg02 = (int)_arg01;
	_arg03 = _arg01 - _arg02;
}

/**************************** EX02 ****************************/
void EX02(void)
{
	int i = 0, j = 0;
	do{
		cout << "[EX02 in] Digite o n�mero i: ";
		cin >> i;
		cout << "[EX02 in] Digite o n�mero j: ";
		cin >> j;
	}while(!validParam(i,j));

	cout << "[EX02 out] i^j=" << potencia(i,j) << endl;
}
int potencia(int i, int j)
{
	if (j>0)
		return i*potencia(i, --j);
	else
		return 1;
}
/**************************** EX03 ****************************/
void EX03(void)
{
	int N = 0;
	const int N_MAX = 1000;
	char resp = 'n';
	do{
		cout << "[EX03 in] Digite um n�mero: ";
		cin >> N;
	}while(!validParam(N));

	cout << "[EX03 out] O n�mero "<< N << (EX03_func(N)==false?" N�O":"")<< " � perfeito."<< endl;


	cout << "[EX03 out] Deseja imprimir os n�meros perfeitos entre 1 e 1000?(y/n):";
	cin >> resp;
	if (resp == 'y')
		for (int i=1; i <=N_MAX; i++)
			if(EX03_func(i)==true)
				cout << i << ", ";
}
bool EX03_func(int n){
	int soma = 0;
	for (int i=1; i <=n/2; i++)
		if(n%i==0)
			soma +=i;

	if (soma == n)
		return true;
	else
		return false;
}
/**************************** EX04 ****************************/
void EX04(void)
{
	int n1 = 0, n2 = 0;

	do{
		cout << "[EX04 in] Digite o n�mero n1: ";
		cin >> n1;
		cout << "[EX04 in] Digite o n�mero n2: ";
		cin >> n2;
	}while(!validParam(n1,n2));

	cout << "[EX04 out] o mdc(n1,n2)=" << EX04_func(n1,n2) << endl;
}
int EX04_func(int n1, int n2){
	int resto;
	while(n2 != 0){
		resto = n1 % n2;
		n1 = n2;
		n2 = resto;
	}
	return n1;
}
/**************************** EX05 ****************************/
void EX05(void)
{
	double n=0, n1=1, n2=0, fib=0;
	do{
		cout << "[EX05 in] Digite o termo da s�rie de Fibonacci: ";
		cin >> n;
	}while(!validParam(n));

	if (n <= 1){
		fib = n;
	}
	else
		for(double i=2;i<=n;i++){
			fib = n1 + n2;
			n2=n1;
			n1=fib;
		}

	cout << "[EX05 out] O n-�simo n�mero da s�rie Fibonacci � " << fib << endl;
}
/**************************** EX06 ****************************/
void EX06(void)
{
	int n=0, tmp=0, inv=0;

	cout << "[EX06 in] Digite um n�mero inteiro: ";
	cin >> n;
	tmp=n;

	 while(tmp != 0){
		int digit = tmp%10;
		inv = inv*10 + digit;
		tmp = tmp/10;
	 }
	 cout << "[EX06 out] Seu n�mero invertido �: " << inv << endl;
	 cout << "[EX06 out] O n�mero " << n << (inv!=n?" n�o ":" ")<< "� pal�ndromo"<< endl;
}
/**************************** EX07 ****************************/
void EX07(void)
{
	double n=0,fat=1;
	do{
		cout << "[EX07 in] Digite um n�mero inteiro: ";
		cin >> n;
	}while(!validParam(n));

	while(n>0)
		fat*=n--;

	cout << "[EX07 out] O fatorial do n�mero �: " << fat << endl;
}
/**************************** EX08 ****************************/
void EX08(void)
{
	double x=1,e=1;
	double i=1;
	//cout << "[EX08 in] Digite o valor x : ";
	//cin >> x;

	while(x>0.000001){
		e+=x;
		x*=1/(i++);
	}
	cout << "[EX08 out] A constante e vale: " << e << endl;
}
/**************************** EX09 ****************************/
void EX09(void)
{
	double pi=0.0;
	double termo=4.0;
	double denominador=3.0;
	bool sinal = true;

	do{
		pi+=termo;
		termo=4.0/(denominador);
		termo=(sinal?-termo:termo);
		sinal = !sinal;
		denominador+=2;
	}while(termo>0.000001 ||termo<-0.000001);

	cout << "[EX09 out] A constante PI vale: " << pi << endl;
}
/**************************** EX10 ****************************/
void EX10(void)
{
	int n=0, codificado=0;
	int digito[4] ={0,0,0,0};

	cout << "[EX10 in] Digite um n�mero inteiro: ";
	cin >> n;
	for(int i=3;i>=0;i--){
		digito[i] = ((n%10)+7)%10;
		n = n/10;
	}
	codificado=1000*digito[2]+100*digito[3]+10*digito[0]+digito[1];

	cout << "[EX10 out] O n�mero codificado � "<< setfill('0') << setw(4) << codificado << endl;

}
/**************************** valida��o ****************************/
bool validParam(double param1, double param2, double param3){
	if (param1 >= 0 && param2 >= 0 && param3 >= 0)
		return true;
	else{
		cout << "Voc� digitou par�metro(s) inv�lido(s)! .. tente novamente." <<endl;
		return false;
	}
}
bool validParam(double param1, double param2){
	if (param1 >= 0 && param2 >= 0)
		return true;
	else{
		cout << "Voc� digitou par�metro(s) inv�lido(s)! .. tente novamente." <<endl;
		return false;
	}
}
bool validParam(double param1){
	if (param1 >= 0)
		return true;
	else{
		cout << "Voc� digitou um par�metro inv�lido! .. tente novamente." <<endl;
		return false;
	}
}
/*********************************************************************************/
