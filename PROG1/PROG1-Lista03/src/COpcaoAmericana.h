//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : COpcaoAmericana.h
// Discipline  : FGV - MPE -Programa��o e M�todos Num�ricos em Finan�as I
// Date		   : 14/04/2012
// Description : Lista de exerc�cios 3
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
