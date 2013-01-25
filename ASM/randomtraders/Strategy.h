/*
 * Strategy.h
 *
 *  Created on: Jan 12, 2013
 *      Author: msaito
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <libconfig.h++>
#include <iostream>
#include <iomanip>
#include <cstdlib>

class Strategy {


public:
	float preco_acao_inicial;
	float dinheiro_inicial;
	float tempo_ciclo;
	float tempo_ini;


	Strategy();
	Strategy(std::string file);
	void run();
	virtual ~Strategy();

};

#endif /* STRATEGY_H_ */
