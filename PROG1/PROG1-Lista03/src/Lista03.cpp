//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Lista03.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 05/04/2012
// Description : Lista de exercícios 3
//=======================================================================

#include "Lista03.h"

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
		}
		cout << endl << "Digite o número do exercício [1-10 ou 0-sair]: ";
		cin >> menu;
		cout << endl;
	}while(menu!=0);

	return 0;
}
/**************************** EX01 ****************************/
void EX01(void)
{
	double arg01 = 0, arg02 = 0, arg03 = 0;

	cout << "[EX01 in] Digite um número N: ";
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
		cout << "[EX02 in] Digite o número i: ";
		cin >> i;
		cout << "[EX02 in] Digite o número j: ";
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
		cout << "[EX03 in] Digite um número: ";
		cin >> N;
	}while(!validParam(N));

	cout << "[EX03 out] O número "<< N << (EX03_func(N)==false?" NÃO":"")<< " é perfeito."<< endl;


	cout << "[EX03 out] Deseja imprimir os números perfeitos entre 1 e 1000?(y/n):";
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
		cout << "[EX04 in] Digite o número n1: ";
		cin >> n1;
		cout << "[EX04 in] Digite o número n2: ";
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
	cin.ignore(IGNORE_TAM,'\n');
	char string[EX5_TAM]="";
	cout << "[EX05 in] Digite uma string: ";

	cin.getline(string,EX5_TAM,'\n');
	cout << "[EX05 out] A string digitada: " << string << endl;

	strinv(string);
}

void strinv(char s[])
{
	int i = 0;
	while (s[i++]!='\0'){} // acha o índice do último caracter
	cout << "[EX05 out] A string invertida: ";
	for(int j=i-2; j>=0;j--)
		cout <<s[j];
}

/**************************** validação ****************************/
bool validParam(double param1, double param2){
	if (param1 >= 0 && param2 >= 0)
		return true;
	else{
		cout << "Você digitou parâmetro(s) inválido(s)! .. tente novamente." <<endl;
		return false;
	}
}
bool validParam(double param1){
	if (param1 >= 0)
		return true;
	else{
		cout << "Você digitou um parâmetro inválido! .. tente novamente." <<endl;
		return false;
	}
}
/*********************************************************************************/
