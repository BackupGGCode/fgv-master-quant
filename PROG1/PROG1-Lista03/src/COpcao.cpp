//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : COpcao.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 05/04/2012
// Description : Lista de exercícios 3
//=======================================================================
#include <cmath>
#include "COpcao.h"

int COpcao::m_numero_obj = 0;

// construtor default (valores fixos válidos)
COpcao::COpcao() {
	this->m_numero_obj++;
	this->m_Spot=100.0;
	this->m_Strike=100.0;
	this->m_Vol=0.15;
	this->m_TxLivreRisco=0.1;
	this->m_Prazo=5;
	this->m_TipoOpcao=CALL;
}
// construtor com parâmetros
COpcao::COpcao(double Spot, double Strike, double Vol, double TxLivreRisco, double Prazo, TipoOpcao TipoOpcao){
	this->m_numero_obj++;
	this->m_Spot=Spot;
	this->m_Strike=Strike;
	this->m_Vol=Vol;
	this->m_TxLivreRisco=TxLivreRisco;
	this->m_Prazo=Prazo;
	this->m_TipoOpcao=TipoOpcao;
}
// Construtor de cópia
COpcao::COpcao(const COpcao& opcao){
	this->m_numero_obj++;
	this->m_Spot=opcao.m_Spot;
	this->m_Strike=opcao.m_Strike;
	this->m_Vol=opcao.m_Vol;
	this->m_TxLivreRisco=opcao.m_TxLivreRisco;
	this->m_Prazo=opcao.m_Prazo;
	this->m_TipoOpcao=opcao.m_TipoOpcao;
}
// Getters
double COpcao::GetSpot() const {
	return this->m_Spot;
}
double COpcao::GetStrike() const {
	return this->m_Strike;
}
double COpcao::GetVol() const {
	return this->m_Vol;
}
double COpcao::GetTxLivreRisco() const {
	return this->m_TxLivreRisco;
}
double COpcao::GetPrazo() const {
	return this->m_Prazo;
}
TipoOpcao COpcao::GetTipoOpcao() const {
	return this->m_TipoOpcao;
}
// Setters
bool COpcao::SetSpot(double Spot){
	if(Spot<0.0)return false;
	this->m_Spot=Spot;
	return true;
}
bool COpcao::SetStrike(double Strike){
	if(Strike<0.0)return false;
	this->m_Strike=Strike;
	return true;
}
bool COpcao::SetVol(double Vol){
	if(Vol<0.0)return false;
	this->m_Vol=Vol;
	return true;
}
bool COpcao::SetTxLivreRisco(double TxLivreRisco){
	if(TxLivreRisco<0.0)return false;
	this->m_TxLivreRisco=TxLivreRisco;
	return true;
}
bool COpcao::SetPrazo(double Prazo){
	if(Prazo<0.0)return false;
	this->m_Prazo=Prazo;
	return true;
}
bool COpcao::SetTipoOpcao(TipoOpcao tipoOpcao){
	if(tipoOpcao != CALL && tipoOpcao != PUT)return false;
	this->m_TipoOpcao=tipoOpcao;
	return true;
}

int COpcao::GetNumeroObjetos(){
	return m_numero_obj;
}

double COpcao::CalculaPreco(){

	// valido os parâmetros
	if(m_Spot <= 0.0 || m_Strike <= 0.0 || m_TxLivreRisco < 0.0 || m_Vol <= 0.0 || m_Prazo <= 0.0)
		return -1;

	double d1 = (log(m_Spot / m_Strike) + (m_TxLivreRisco + m_Vol * m_Vol / 2.0) * m_Prazo);
	d1 /= (m_Vol * sqrt(m_Prazo));
	double d2 = d1 - m_Vol * sqrt(m_Prazo);

	// calculo o preco
	if(m_TipoOpcao == CALL)
		return m_Spot * norm_cdf(d1) - m_Strike * exp(-m_TxLivreRisco*m_Prazo) * norm_cdf(d2);
	else
		return m_Strike * exp(-m_TxLivreRisco * m_Prazo) * norm_cdf(-d2) - m_Spot * norm_cdf(-d1);

}
COpcao::~COpcao() {
	this->m_numero_obj--;
}

/*
Calcula a cdf da normal em x, com erro
epsilon < 7.5e-8
*/
double COpcao::norm_cdf(double X)
{
	// constante pi
	static double pi = acos(-1.0);

	// constantes
	const double
		a1 = +0.319381530,
		a2 = -0.356563782,
		a3 = +1.781477937,
		a4 = -1.821255978,
		a5 = +1.330274429;

	// trabalho com X > 0 sempre, pois N(-x) = -N(x)
	double x = fabs(X);

	// calculo t
	double t = 1.0 / (1.0 + 0.2316419 * x);

	// pdf
	double n = (1.0 / sqrt(2.0 * pi)) * exp(-0.5 * x * x);

	// cdf
	double CDF = 1.0 - n * (a1 * t + a2 * t * t + a3 * t * t * t +
		a4 * t * t * t * t + a5 * t * t * t * t * t);

	if(X < 0.0)
		CDF  = 1.0 - CDF;

	return CDF;
}

