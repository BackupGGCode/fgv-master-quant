//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Racional.h
// Discipline  : FGV - MPE -Programa��o e M�todos Num�ricos em Finan�as I
// Date		   : 05/04/2012
// Description : Lista de exerc�cios 3
//=======================================================================

#ifndef RACIONAL_H_
#define RACIONAL_H_

class Racional {
private:
	int numerador;
	int denominador;

public:
	// Construtores
	Racional();
	Racional(int numerador,int denominador);
	Racional(int inteiro);
	Racional(Racional& racional);

	// M�todos
	Racional Add(Racional n1, Racional n2);
	Racional Sub(Racional n1, Racional n2);
	Racional Mult(Racional n1, Racional n2);
	Racional Div(Racional n1, Racional n2);
	bool Less(Racional n);
	void imprime(Racional n);
	void imprimePtoFlutuante(Racional n);


	~Racional();
};

#endif /* RACIONAL_H_ */
