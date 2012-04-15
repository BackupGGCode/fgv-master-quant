//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : COpcaoAmericana.h
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 14/04/2012
// Description : Lista de exercícios 3
//=======================================================================

#ifndef COPCAOAMERICANA_H_
#define COPCAOAMERICANA_H_

#include "COpcao.h"

class COpcaoAmericana: public COpcao {
protected:
	int N; //número de passos
	double** pp_arvore_ativo;
	double** pp_arvore_derivativo;


protected:
	void InicializaArvores();
	void FinalizaArvores();

public:
	COpcaoAmericana();
	COpcaoAmericana(COpcaoAmericana& opcao);
	COpcaoAmericana(double Spot, double Strike, double Vol,
			double TxLivreRisco, double Prazo, TipoOpcao TipoOpcao, int n);

	int GetN() const;
	void SetN(int n);

	// calcula o preco da opcao
	double CalculaPreco();

	virtual ~COpcaoAmericana();
};

#endif /* COPCAOAMERICANA_H_ */
