//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Lista02.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 06/03/2012
// Description : Lista de exercícios 2
//=======================================================================

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

void EX01(void);
void EX02(void);
void EX03(void);
void EX04(void);
void EX05(void);
void EX06(void);
void EX07(void);
void EX08(void);
void EX09(void);
void EX10(void);
void EX11(void);
void EX12(void);
bool validParam(double param1);
bool validParam(double param1, double param2);
bool validParam(double param1, double param2, double param3);

int main(void)
{
	setlocale(LC_ALL, "ptb");
	int menu=-1;
	do{
		switch(menu){
		case 0:  return 0;
		case  1: EX01(); menu=-1; break;
		case  2: EX02(); menu=-1; break;
		case  3: EX03(); menu=-1; break;
		case  4: EX04(); menu=-1; break;
		case  5: EX05(); menu=-1; break;
		case  6: EX06(); menu=-1; break;
		case  7: EX07(); menu=-1; break;
		case  8: EX08(); menu=-1; break;
		case  9: EX09(); menu=-1; break;
		case 10: EX10(); menu=-1; break;
		case 11: EX11(); menu=-1; break;
		case 12: EX12(); menu=-1; break;
		default:
			cout << endl << "Digite o número do exercício [1-12 ou 0-sair]: ";
			cin >> menu;
			cout << endl;
			break;
		}
	}while(menu!=0);

	return 0;
}
/*********************************************************************************/
void EX01(void)
{
	double n = 0;
	double soma = 0;
	do{
		cout << "[EX01 in] Digite o número N: ";
		cin >> n;
	}while(!validParam(n));

	n = 2*n+1;
	for(int i=0;i<n;i++){
		soma+=(i%2>0?i:0);
	}
	cout << "[EX01 out] O quadrado de N é "<< soma << endl;
}
/*********************************************************************************/
void EX02(void)
{
	int ano = 0;
	do{
		cout << "[EX02 in] Digite um ano: ";
		cin >> ano;
	}while(!validParam(ano));

	if(((ano%4==0) && (ano%100!=0)) || (ano%400==0))
		cout << "[EX02 out] Ano Bissexto" << endl;
	else
		cout << "[EX02 out] Ano não é bissexto" << endl;
}
/*********************************************************************************/
void EX03(void)
{
	double cabeca=0, pe=0, pato=0,coelho=0;
	do{
		cout << "[EX03 in] Número de cabeças: ";
		cin >> cabeca;

		cout << "[EX03 in] Número de pés: ";
		cin >> pe;
	}while(!validParam(cabeca,pe));

	coelho = pe/2 - cabeca;
	pato = 2*cabeca - pe/2;

	if(coelho<0 || pato <0)
		cout << "[EX03 out] Números de pés e cabeças Inválidos" << endl;
	else
		cout << "[EX03 out] São "<<pato<<" patos e "<<coelho<< " coelhos."<< endl;
}
/*********************************************************************************/
void EX04(void)
{
	char c;

	cout << "[EX04 in] Digite um caractere: ";
	cin >> c;

	if((c>='a')&&(c<='z'))c-=32;

	cout << "[EX04 out] " << c << endl;
}
/*********************************************************************************/
void EX05(void)
{
	double n=0, n1=1, n2=0, fib=0;
	do{
		cout << "[EX05 in] Digite o termo da série de Fibonacci: ";
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

	cout << "[EX05 out] O n-ésimo número da série Fibonacci é " << fib << endl;
}
/*********************************************************************************/
void EX06(void)
{
	int n=0, tmp=0, inv=0;

	cout << "[EX06 in] Digite um número inteiro: ";
	cin >> n;
	tmp=n;

	 while(tmp != 0){
		int digit = tmp%10;
		inv = inv*10 + digit;
		tmp = tmp/10;
	 }
	 cout << "[EX06 out] Seu número invertido é: " << inv << endl;
	 cout << "[EX06 out] O número " << n << (inv!=n?" não ":" ")<< "é palíndromo"<< endl;
}
/*********************************************************************************/
void EX07(void)
{
	double n=0,fat=1;
	do{
		cout << "[EX07 in] Digite um número inteiro: ";
		cin >> n;
	}while(!validParam(n));

	while(n>0)
		fat*=n--;

	cout << "[EX07 out] O fatorial do número é: " << fat << endl;
}
/*********************************************************************************/
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
/*********************************************************************************/
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
/*********************************************************************************/
void EX10(void)
{
	int n=0, codificado=0;
	int digito[4] ={0,0,0,0};

	cout << "[EX10 in] Digite um número inteiro: ";
	cin >> n;
	for(int i=3;i>=0;i--){
		digito[i] = ((n%10)+7)%10;
		n = n/10;
	}
	codificado=1000*digito[2]+100*digito[3]+10*digito[0]+digito[1];

	cout << "[EX10 out] O número codificado é "<< setfill('0') << setw(4) << codificado << endl;

}
/*********************************************************************************/
void EX11(void)
{
	int n=0, decodificado=0;
	int digito[4] ={0,0,0,0};

	cout << "[EX11 in] Digite um número codificado: ";
	cin >> n;
	for(int i=3;i>=0;i--){
		digito[i] = (((n%10)+10)-7)%10;
		n = n/10;
	}
	decodificado=1000*digito[2]+100*digito[3]+10*digito[0]+digito[1];

	cout << "[EX11 out] O número decodificado é "<< setfill('0') << setw(4) << decodificado << endl;
}
/*********************************************************************************/
void EX12(void)
{
	double emprestimo=0,parcela=0,txjuro=0,pmt=0, juros=0;

	do{
		cout << "[EX12 in] Valor do empréstimo (R$): ";
		cin >> emprestimo;
		cout << "[EX12 in] Número de parcelas: ";
		cin >> parcela;
		cout << "[EX12 in] Taxa de juros: ";
		cin >> txjuro;
		txjuro = txjuro/100.0;
	}while(!validParam(emprestimo,parcela,txjuro));

	cout << "[EX12 out]\t#Parcela\tSaldo Devedor\tAmortização\tJuros" <<endl;
	pmt = (emprestimo*txjuro)/(1-1/pow((1+txjuro),parcela));

	for(int i=1; i<=parcela;i++){
		juros = emprestimo*txjuro;
		double amortizacao = pmt - juros;
		emprestimo-=amortizacao;
		cout << "[EX12 out]\t" <<i<<"\t\t"<<emprestimo<<"\t\t"<<amortizacao<<"\t\t"<<juros<<endl;
	}
}
/*********************************************************************************/
bool validParam(double param1, double param2, double param3){
	if (param1 >= 0 && param2 >= 0 && param3 >= 0)
		return true;
	else{
		cout << "Você digitou parâmetro(s) inválido(s)! .. tente novamente." <<endl;
		return false;
	}
}
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
