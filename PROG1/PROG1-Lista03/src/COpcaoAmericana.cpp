//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : COpcaoAmericana.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 14/04/2012
// Description : Lista de exercícios 3
//=======================================================================

#include "COpcaoAmericana.h"
#include <cmath>

double max(double a, double b);
COpcaoAmericana::COpcaoAmericana() {
	this->N = 0;
}
COpcaoAmericana::COpcaoAmericana(COpcaoAmericana& opcao){
	this->m_Spot=opcao.m_Spot;
	this->m_Strike=opcao.m_Strike;
	this->m_Vol=opcao.m_Vol;
	this->m_TxLivreRisco=opcao.m_TxLivreRisco;
	this->m_Prazo=opcao.m_Prazo;
	this->m_TipoOpcao=opcao.m_TipoOpcao;
	this->N = opcao.N;
}

COpcaoAmericana::COpcaoAmericana(double Spot, double Strike, double Vol,
					double TxLivreRisco, double Prazo, TipoOpcao TipoOpcao, int n) {
	this->m_Spot=Spot;
	this->m_Strike=Strike;
	this->m_Vol=Vol;
	this->m_TxLivreRisco=TxLivreRisco;
	this->m_Prazo=Prazo;
	this->m_TipoOpcao=TipoOpcao;
	this->SetN(n);
}

int COpcaoAmericana::GetN() const{
	return this->N;
}
void COpcaoAmericana::SetN(int n){
	if(n > 0){ // Número de passos válidos
		if(this->N == 0){ // inicializando a arvore
			this->N = n;
			this->InicializaArvores();
		}
		else // já existe uma árvore, resta saber se ocorrerá mudanças
			if(n != this->N){ // Se o número de passos for diferente ...
				this->FinalizaArvores();
				this->N = n;
				this->InicializaArvores();
			}
	}
}
void COpcaoAmericana::InicializaArvores(){
	int TAM = this->N+1;
	this->pp_arvore_ativo = new double*[TAM];
	this->pp_arvore_derivativo = new double*[TAM];

	for(int i=0;i<TAM;i++){
		this->pp_arvore_ativo[i] = new double[2*i+1];
		this->pp_arvore_derivativo[i] = new double[2*i+1];
	}
}
void COpcaoAmericana::FinalizaArvores(){
	for(int i=0;i<this->N+1;i++){
		delete[] this->pp_arvore_ativo[i];
		delete[] this->pp_arvore_derivativo[i];
	}
	delete[] this->pp_arvore_ativo;
	delete[] this->pp_arvore_derivativo;
}
double COpcaoAmericana::CalculaPreco(){

	double dt = this->m_Prazo/this->N;		// tamanho de cada passo
	double u = exp(this->m_Vol*sqrt(3.0*dt/2.0));	// fator de subida
	double d = 1.0/u;							// fator de descida
	double pu = 1.0/3.0+((this->m_TxLivreRisco-0.5*this->m_Vol*this->m_Vol)/this->m_Vol)*sqrt(dt/6.0);	// probabilidade de o ativo subir
	double pm = 1.0/3.0;							// probabilidade de o ativo permanecer constante
	double pd = 1.0-(pu+pm);						// probabilidade de o ativo descer

	int k = 0;

	// inicializando os valores da árvore do ativo
	for(int i=0;i<this->N+1;i++){
		for(int j=0;j<2*i+1;j++){
			k = i-j;
			this->pp_arvore_ativo[i][j] = this->m_Spot * (k>0?(pow(u,k)*pow(d,0)):(pow(u,0)*pow(d,-k)));
		}
	}

	// parametro multiplicativo de call / put
	double multCallPut = 1.0;
	if(this->m_TipoOpcao==PUT)
		multCallPut=-1.0;

	for(int i=N;i>=0;i--){
		for(int j=0;j<2*i+1;j++){
			if(i==N){
				this->pp_arvore_derivativo[i][j] = max(multCallPut*(pp_arvore_ativo[i][j]-this->m_Strike),0);

			}
			else{
				double valorIntrinseco =
						max(multCallPut*(this->pp_arvore_ativo[i][j]-this->m_Strike),0);

				this->pp_arvore_derivativo[i][j] =
						max(exp(-this->m_TxLivreRisco*dt)*(pu*this->pp_arvore_derivativo[i+1][j] +
								pm*this->pp_arvore_derivativo[i+1][j+1] +
								pd*this->pp_arvore_derivativo[i+1][j+2]), valorIntrinseco);
			}
		}
	}
	// obtenho o preco no primeiro no da arvore
	double preco = this->pp_arvore_derivativo[0][0];
	return preco;
}

COpcaoAmericana::~COpcaoAmericana() {
	this->FinalizaArvores();
}

//Calcula o maximo entre dois numeros
double max(double a, double b){
	return (a>b?a:b);
}
