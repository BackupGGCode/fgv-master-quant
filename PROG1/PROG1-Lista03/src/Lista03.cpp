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
		case  6: COMPARACAO(); break;
		}
		cout << endl << "Digite o número do exercício [1-5 ou 0-sair]: ";
		cin >> menu;
		cout << endl;
	}while(menu!=0);

	return 0;
}
/**************************** EX01 ****************************/
void EX01(void){

	Racional racional1(5,12);
	cout << "[EX01 in] r1 = "; racional1.Imprime();
	Racional racional2(2,12);
	cout << "[EX01 in] r2 = "; racional2.Imprime();

	racional1.Add(racional2);
	cout << "[EX01 out] r1 = Add(r1,r2) = "; racional1.Imprime();

	Racional racional3(1,12);
	cout << "[EX01 in] r3 = "; racional3.Imprime();

	racional1.Sub(racional3);
	cout << "[EX01 out] r1 = Sub(r1,r3) = "; racional1.Imprime();

	Racional racional4(3,7);
	cout << "[EX01 in] r4 = "; racional4.Imprime();

	racional1.Mult(racional4);
	cout << "[EX01 out] r1 = Mult(r1,r4) = "; racional1.Imprime();

	Racional racional5(3,21);
	cout << "r5 = "; racional5.Imprime();

	racional1.Div(racional5);
	cout << "[EX01 in] r1 = Div(r1,r5) = "; racional1.Imprime();

	Racional racional6(4,2);
	cout << "[EX01 in] r6 = "; racional6.Imprime();
	cout << "[EX01 out] r6 "<<(racional1.Less(racional6)?"<":">")<<" r1"<<endl;


	Racional racional7(1,2);
	cout << "[EX01 in] r7 = "; racional7.Imprime();
	cout << "[EX01 out] r7 "<<(racional1.Less(racional7)?"<":">")<<" r1"<<endl;

	cout << "[EX01 out] r1 em ponto flutuante = "; racional1.ImprimePtoFlutuante();

}

/**************************** EX02 ****************************/
void EX02(void){
	Relogio relogio;
	relogio.SolicitaHoraUsuario();
	cout << "[EX02 out]";
	relogio.Imprime();
	//avancando 15 segundos
	for(int i=0; i < 15; i++)
		relogio.AvancaProxSegundo();
	cout << "[EX02 out] ";
	relogio.Imprime();
}

/**************************** EX03 ****************************/
void EX03(void){



}
/**************************** EX04 ****************************/
void EX04(void){

	double T = 2.0;			// prazo (em anos) para o vencimento
	double vol = 0.20;		// volatilidade do ativo base
	double K = 100.0;		// preco strike
	double S = 100.0;		// preco spot
	double r = 0.12;		// taxa de juros livre de risco
	TipoOpcao tipo = PUT;	// tipo da opcao

	cout << "[EX04 in] Spot: "<< S << endl;
	cout << "[EX04 in] Strike: "<< K << endl;
	cout << "[EX04 in] Volatilidade: "<< vol << endl;
	cout << "[EX04 in] Taxa Risk Free: "<< r << endl;
	cout << "[EX04 in] Prazo: "<< T << endl;
	cout << "[EX04 in] Tipo: "<< (tipo==CALL?"CALL":"PUT")<< endl<< endl;

	COpcaoEuropeia opcao(S,K,vol,r,T, tipo);
	cout << "[EX04 out] preço da opção européia:"<< opcao.CalculaPreco() << endl;

}
/**************************** EX05 ****************************/
void EX05(void){

	double T = 2.0;			// prazo (em anos) para o vencimento
	double vol = 0.20;		// volatilidade do ativo base
	double K = 100.0;		// preco strike
	double S = 100.0;		// preco spot
	double r = 0.12;		// taxa de juros livre de risco
	int N = 100;			// numero de passos da arvore
	TipoOpcao tipo = PUT;	// tipo da opcao

	cout << "[EX05 in] Spot: "<< S << endl;
	cout << "[EX05 in] Strike: "<< K << endl;
	cout << "[EX05 in] Volatilidade: "<< vol << endl;
	cout << "[EX05 in] Taxa Risk Free: "<< r << endl;
	cout << "[EX05 in] Prazo: "<< T << endl;
	cout << "[EX05 in] N: "<< N << endl;
	cout << "[EX05 in] Tipo: "<< (tipo==CALL?"CALL":"PUT")<< endl<< endl;

	COpcaoAmericana opcao(S,K,vol,r,T,tipo,N);
	cout << "[EX05 out] preço da opção americana:"<< opcao.CalculaPreco() << endl;
}

void COMPARACAO(void){

	double T = 7;			// prazo (em anos) para o vencimento
	double vol = 0.20;		// volatilidade do ativo base
	double K = 35;		// preco strike
	double S = 30;		// preco spot
	double r = 0.308;		// taxa de juros livre de risco
	int N = 7;			// numero de passos da arvore
	TipoOpcao tipo = PUT;	// tipo da opcao

	cout << "Spot: "<< S << endl;
	cout << "Strike: "<< K << endl;
	cout << "Volatilidade: "<< vol << endl;
	cout << "Taxa Risk Free: "<< r << endl;
	cout << "Prazo: "<< T << endl;
	cout << "N: "<< N << endl;
	cout << "Tipo: "<< (tipo==CALL?"CALL":"PUT")<< endl<< endl;

	COpcaoEuropeia opcaoEUR(S,K,vol,r,T, tipo);
	cout << "preço da opção européia:"<< opcaoEUR.CalculaPreco() << endl;

	COpcaoAmericana opcaoAME(S,K,vol,r,T,tipo,N);
	cout << "preço da opção americana:"<< opcaoAME.CalculaPreco() << endl;
}

