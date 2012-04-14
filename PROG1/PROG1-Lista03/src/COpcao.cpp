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


COpcao::~COpcao() {
	this->m_numero_obj--;
}



