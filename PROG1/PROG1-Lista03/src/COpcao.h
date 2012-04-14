//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : COpcao.h
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 05/04/2012
// Description : Lista de exercícios 3
//=======================================================================

#ifndef COPCAO_H_
#define COPCAO_H_

#define N_OBJ 500

// TipoOpcao: CALL ou PUT
enum TipoOpcao{
	CALL,
	PUT
};

class COpcao {

protected:
	double m_Spot;			// preco spot
	double m_Strike;		// preco strike
	double m_Vol;			// volatilidade do ativo objeto
	double m_TxLivreRisco;	// taxa de juros livre de risco
	double m_Prazo;			// prazo (em anos) para o vencimento
	TipoOpcao m_TipoOpcao;	// call ou put
	static int m_numero_obj; // numero de objetos criados

public:
	// construtor default (sem parâmetros)
	COpcao();

	// Construtor de cópia
	COpcao(const COpcao& opcao);

	// construtor com parâmetros
	COpcao(double Spot, double Strike, double Vol, double TxLivreRisco, double Prazo, TipoOpcao TipoOpcao);

	// destrutor
	virtual ~COpcao();

	double GetSpot() const;		// retorna o Spot
	double GetStrike() const;	// retorna o Strike
	double GetVol() const;		// retorna a volatilidade
	double GetTxLivreRisco() const;	// retorna a taxa de juros
	double GetPrazo() const;	// retorna o prazo
	TipoOpcao GetTipoOpcao() const;	// retorna o tipo da opção: call ou put

	bool SetSpot(double Spot);
	bool SetStrike(double Strike);
	bool SetVol(double Vol);
	bool SetTxLivreRisco(double TxLivreRisco);
	bool SetPrazo(double Prazo);
	bool SetTipoOpcao(TipoOpcao tipoOpcao);

	// retorna o numero de objetos criados
	static int GetNumeroObjetos();

	// calcula o preco da opcao
	virtual double CalculaPreco()=0;

};

#endif /* COPCAO_H_ */
