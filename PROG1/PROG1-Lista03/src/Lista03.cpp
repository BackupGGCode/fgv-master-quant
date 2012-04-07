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
		cout << endl << "Digite o número do exercício [1-5 ou 0-sair]: ";
		cin >> menu;
		cout << endl;
	}while(menu!=0);

	return 0;
}
/**************************** EX01 ****************************/
void EX01(void){
	// crio objeto Racional
	Racional racional1(12,8);
	racional1.Imprime();

	Racional racional2(racional1);
	racional2.Imprime();


	racional1.Mult(racional2);
	racional1.Imprime();

}

/**************************** EX02 ****************************/
void EX02(void){
}

/**************************** EX03 ****************************/
void EX03(void){

}
/**************************** EX04 ****************************/
void EX04(void){
	cout << "[EX04 in] Digite o número n1: ";

	cout << "[EX04 out] o mdc(n1,n2)=" << endl;
}
/**************************** EX05 ****************************/
void EX05(void){
	cout << "[EX05 in] Digite uma string: ";
	cout << "[EX05 out] A string digitada: " << endl;
}

