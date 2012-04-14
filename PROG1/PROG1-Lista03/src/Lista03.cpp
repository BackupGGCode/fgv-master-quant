//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Lista03.cpp
// Discipline  : FGV - MPE -Programa��o e M�todos Num�ricos em Finan�as I
// Date		   : 05/04/2012
// Description : Lista de exerc�cios 3
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
		cout << endl << "Digite o n�mero do exerc�cio [1-5 ou 0-sair]: ";
		cin >> menu;
		cout << endl;
	}while(menu!=0);

	return 0;
}
/**************************** EX01 ****************************/
void EX01(void){

	Racional racional1(5,12);
	cout << "r1 = "; racional1.Imprime();
	Racional racional2(2,12);
	cout << "r2 = "; racional2.Imprime();

	racional1.Add(racional2);
	cout << "r1 = Add(r1,r2) = "; racional1.Imprime();

	Racional racional3(1,12);
	cout << "r3 = "; racional3.Imprime();

	racional1.Sub(racional3);
	cout << "r1 = Sub(r1,r3) = "; racional1.Imprime();

	Racional racional4(3,7);
	cout << "r4 = "; racional4.Imprime();

	racional1.Mult(racional4);
	cout << "r1 = Mult(r1,r4) = "; racional1.Imprime();

	Racional racional5(3,21);
	cout << "r5 = "; racional5.Imprime();

	racional1.Div(racional5);
	cout << "r1 = Div(r1,r5) = "; racional1.Imprime();

	Racional racional6(4,2);
	cout << "r6 = "; racional6.Imprime();
	cout << "r6 "<<(racional1.Less(racional6)?"<":">")<<" r1"<<endl;


	Racional racional7(1,2);
	cout << "r7 = "; racional7.Imprime();
	cout << "r7 "<<(racional1.Less(racional7)?"<":">")<<" r1"<<endl;

	cout << "[pto flutuante] r1 = "; racional1.ImprimePtoFlutuante();

}

/**************************** EX02 ****************************/
void EX02(void){
	Relogio relogio;
	relogio.SolicitaHoraUsuario();
	relogio.Imprime();
	//avancando 15 segundos
	for(int i=0; i < 15; i++)
		relogio.AvancaProxSegundo();
	relogio.Imprime();
}

/**************************** EX03 ****************************/
void EX03(void){



}
/**************************** EX04 ****************************/
void EX04(void){
	COpcaoEuropeia opcao;
	cout << opcao.CalculaPreco();

}
/**************************** EX05 ****************************/
void EX05(void){

}

