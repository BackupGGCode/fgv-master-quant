//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Lista02.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 27/03/2012
// Description : Lista de exercícios 2
//=======================================================================

#include "Lista02.h"

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
/**************************** EX06 ****************************/
void EX06(void)
{
	/*
	 * criar-se-á uma array 2D, sendo uma das dimensões números de 2 até n
	 * a outra dimensão assumirá valores 1 (primo) e -1 (não é primo)
	 */
	int array[EX6_TAM][2];
	int p, index=0,i=0;

	//a. Crie uma lista de inteiros consecutivos de 2 até n
	//b. Marque todos os elementos da lista inicialmente como primos
	for(i=0; i<EX6_TAM;i++){
		array[i][0] = i+ 2; // preenche com número de 2 até EX6_TAM+2
		array[i][1] = 1; // é primo
	}
	//c. Inicialmente, faça p=2, o primeiro número primo
	p=2;
	index=1;

	do{
		//d. Marque como não primo(-1) todos os números superiores a p que são múltiplos de p
		for(i=index; i<EX6_TAM;i++){
			if(array[i][0]%p==0)array[i][1] =-1;
		}
		//e. Encontre o próximo número primo(1) da lista e faça p igual a esse número
		i=index;
		while(i < EX6_TAM){
			if(array[i][1] == 1)break;
			else
				i++;
		}
		p=array[i][1];
		index=i;
		//f. Repita os passos d e e até que p^2 seja maior que n
	}while(pow(p,2) < EX6_TAM+2);

	for(i=0; i<EX6_TAM;i++){
		if(array[i][1]==1)
			cout <<array[i][0] <<",";
	}

}
/**************************** EX07 ****************************/
void EX07(void)
{
	char string[EX7_TAM]="";
	cout << "[EX07 in] Digite uma string: ";
	cin.getline(string,EX7_TAM,'\t');
	cout << "[EX07 out] Input: " << string << endl;
	for(int i=0; i<EX7_TAM || string[i]!='\0';i++)
		if(isdigit(string[i]))string[i]='x';
	cout << "[EX07 out] Output: " << string << endl;
}
/**************************** EX08 ****************************/
void EX08(void)
{
	cin.ignore(IGNORE_TAM,'\n');
	char string[EX8_TAM]="";
	cout << "[EX08 in] Digite uma string: ";

	cin.getline(string,EX8_TAM,'\n');
	cout << "[EX08 out] A string digitada: " << string << endl;
	inverte_string(string);
	cout << "[EX08 out] A string invertida: " << string << endl;
}
void inverte_string(char* pstring){
	int tam = strlen(pstring);
	int iter = tam/2;

	for(int i=0; i < iter;i++){
		swap(pstring[i],pstring[tam-1-i]);
	}
}

/**************************** EX09 ****************************/
void EX09(void)
{

	int tamanho = EX9_TAM;
	int tmp = 2;
	int* array1 = new int[tamanho];

	cout << "[EX09 in]:"<< endl;
	for(int i=0;i<tamanho;i++)array1[i] = i+1; // inicializando
	imprime(array1,tamanho);

	cout << "[EX09 out] adiciona o inteiro "<< tmp << endl;
	int* array2 = adiciona_entrada(array1, tamanho, tmp);
	imprime(array2,tamanho);

	cout << "[EX09 out] remove o inteiro "<< tmp << endl;
	int* array3 = apaga_entrada(array2, tamanho, tmp);
	imprime(array3,tamanho);

}

int* adiciona_entrada(int* v, int& tamanho, int novo){
	int novo_tam = tamanho+1;
	int* novo_array = new int[novo_tam];

	for(int i=0;i<tamanho;i++)novo_array[i] =v[i];

	novo_array[tamanho] = novo; // adicionando novo elemento no array
	tamanho++;

	delete[] v;

	return novo_array;
}
int* apaga_entrada(int* v, int& tamanho, int apagar){
	int cont = 0;
	for(int i=0;i<tamanho;i++)
		if(v[i]==apagar)
			cont++;

	if(cont == 0) return v; //ignorar caso não encontrar nada.

	int novo_tam = tamanho-cont;
	int* novo_array = new int[novo_tam];

	cont = 0;
	for(int i=0;i<tamanho;i++)
		if(v[i]!=apagar)
			novo_array[cont++] =v[i];

	tamanho=novo_tam;

	delete[] v;

	return novo_array;
}
void imprime(int* array, int tam){
	cout << "array: ";
	for(int i=0;i<tam;i++)
		cout << array[i] <<(i<tam-1?",":"");
	cout << endl;
}
/**************************** EX10 ****************************/
void EX10(void)
{
	double fluxo[2][ANOS] = {{0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0},
						{-1000.0, 100.0, 200.0, 100.0, 200.0, 100.0, 200.0, 100.0, 200.0, 100.0, 200.0}};


	double r = 0.0;
	int iter = 0;

	if (bisseccao(fluxo, 0.0, 1.0, r, iter)==0){
		cout << "[EX10 out] Bissecção: TIR = " << r * 100.0 << "%" << endl;
		cout << "[EX10 out] Bissecção: Número de iterações = " << iter << endl;
	}

	if (newton_raphson(fluxo, 0.0, r, iter)==0){
		cout << "[EX10 out] Newton-Raphson: TIR = " << r * 100.0 << "%" << endl;
		cout << "[EX10 out] Newton-Raphson: Número de iterações = " << iter << endl;
	}

}

int bisseccao(double fluxo[2][ANOS], double x1, double x2, double& res, int& iter){

	// obtenho o minimo e o maximo do intervalo inicial
	double min = (x2<x1?x2:x1);
	double max = (x2>x1?x2:x1);

	// calculo a função objetivo em min e max
	double f_min = valor_presente(fluxo, min);
	double f_max = valor_presente(fluxo, max);

	// verifico se a função nos pontos possui sinais opostos
	if ((f_min > 0 && f_max > 0) || (f_min < 0 && f_max < 0)){
		cout << "[EX10 out] Bissecção: Os pontos iniciais devem ser tais que a função neles tenha sinais opostos" << endl;
		return 1;
	}

	double xmid = 0.5 * (min + max);// ponto intermediário

	// loop principal
	for (iter=1;iter<=ITER_MAX;iter++){

		// valor da função objetivo no ponto intermediário
		double fmid = valor_presente(fluxo, xmid);

		if(fmid == 0.0){// a raiz foi encontrada: improvavel
			res = xmid;
			return 0;
		}

		// obtenho o novo subintervalo (min, max) que contem a raiz
		if((fmid > 0 && f_min > 0) || (fmid < 0 && f_min < 0))
			min = xmid;
		else
			max = xmid;

		xmid = 0.5 * (min+max);// novo ponto intermediário


		if (max-min < EX10_ERROR){ // verifico convergência
			res = (min + max) / 2.0;
			return 0;
		}
	}

	cout << "[EX10 out] Bissecção: Número de iterações máximo (" << ITER_MAX << ") atingido.";
	return 2;
}
double valor_presente(double fluxo[2][ANOS], double taxa){
	double soma = 0.0;
	for(int i=0; i<ANOS; i++)
		soma += fluxo[1][i] / pow((1+taxa), fluxo[0][i]);
	return soma;
}

int newton_raphson(double fluxo[2][ANOS], double inicial, double& res, int& iter){

	// chute inicial.
	double raiz = inicial;

	// loop principal
	for (iter=1;iter<=ITER_MAX;iter++){
		// calcula preco
		double f = valor_presente(fluxo, raiz);

		// calcula derivada com relacao a vol
		double df = derivada_valor_presente(fluxo, raiz);

		if(df == 0.0){
			cout << "[EX10 out] Newton-Raphson: A derivada da funcao em "  << raiz << " é zero" << endl;
			return 2;
		}

		// tamanho do passo
		double dx = f/df;

		// atualizo a raiz
		raiz -= dx;

		// verifico convergência
		if(fabs(dx) < EX10_ERROR){
			res = raiz;
			return 0;
		}
	}

	cout << "[EX10 out] Newton-Raphson: Número de iterações máximo (" << ITER_MAX << ") atingido.";
	return 1;
}

double derivada_valor_presente(double fluxo[2][ANOS], double taxa){
	double derivada = 0.0;
	for(int i=1;i<ANOS; i++){
		derivada -= fluxo[1][i]*fluxo[0][i]/pow(1+taxa,fluxo[0][i]-1);
	}
	return derivada;
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
