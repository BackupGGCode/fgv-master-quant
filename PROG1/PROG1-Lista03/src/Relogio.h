//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Relogio.h
// Discipline  : FGV - MPE -Programa��o e M�todos Num�ricos em Finan�as I
// Date		   : 13/04/2012
// Description : Lista de exerc�cios 3
//=======================================================================


#ifndef RELOGIO_H_
#define RELOGIO_H_

class Relogio {
private:
	int hora;
	int minuto;
	int segundo;
public:
	// Construtores
	Relogio();
	Relogio(int hr, int min, int seg);
	Relogio(Relogio& relogio);

	void SolicitaHoraUsuario(void);
	void SetHora(int hr, int min, int seg);
	void GetHora(int *hr, int *min, int *seg) const;
	void AvancaProxSegundo(void);

	//Imprimir no formato hh:mm:ss
	void Imprime() const;


	virtual ~Relogio();
};

#endif /* RELOGIO_H_ */
