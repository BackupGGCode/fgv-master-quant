//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : COpcaoEuropeia.h
// Discipline  : FGV - MPE -Programa��o e M�todos Num�ricos em Finan�as I
// Date		   : 05/04/2012
// Description : Lista de exerc�cios 3
//=======================================================================

#ifndef COPCAOEUROPEIA_H_
#define COPCAOEUROPEIA_H_

#include "COpcao.h"

class COpcaoEuropeia: public COpcao {
public:
	COpcaoEuropeia();
	COpcaoEuropeia(COpcaoEuropeia& opcao);
	COpcaoEuropeia(double Spot, double Strike, double Vol, double TxLivreRisco, double Prazo, TipoOpcao TipoOpcao);

	// calcula o preco da opcao
	double CalculaPreco();

	virtual ~COpcaoEuropeia();
};

#endif /* COPCAOEUROPEIA_H_ */
