//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : COpcaoEuropeia.h
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 05/04/2012
// Description : Lista de exercícios 3
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
