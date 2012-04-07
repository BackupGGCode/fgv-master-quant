//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Racional.h
// Discipline  : FGV - MPE -Programa��o e M�todos Num�ricos em Finan�as I
// Date		   : 05/04/2012
// Description : Lista de exerc�cios 3
//=======================================================================

#ifndef RACIONAL_H_
#define RACIONAL_H_
int mdc(int x, int y);
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
	Racional Add(Racional n);
	Racional Sub(Racional n);
	Racional Mult(Racional n);
	Racional Div(Racional n);
	bool Less(Racional n);
	void Imprime();
	void ImprimePtoFlutuante();


	~Racional();
};

#endif /* RACIONAL_H_ */
