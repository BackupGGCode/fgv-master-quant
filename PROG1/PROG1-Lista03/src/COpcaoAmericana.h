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
	int numero_passos;

public:
	COpcaoAmericana();
	virtual ~COpcaoAmericana();
};

#endif /* COPCAOAMERICANA_H_ */
