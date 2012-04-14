//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : COpcaoEuropeia.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 05/04/2012
// Description : Lista de exercícios 3
//=======================================================================

#include "COpcaoEuropeia.h"
#include <cmath>
double norm_cdf(double X);

COpcaoEuropeia::COpcaoEuropeia() {
}

COpcaoEuropeia::~COpcaoEuropeia() {
	// TODO Auto-generated destructor stub
}

double COpcaoEuropeia::CalculaPreco(){

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

/*
Calcula a cdf da normal em x, com erro
epsilon < 7.5e-8
*/
double norm_cdf(double X){
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

