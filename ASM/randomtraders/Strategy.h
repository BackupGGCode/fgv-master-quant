/*
 * Strategy.h
 *
 *  Created on: Jan 12, 2013
 *      Author: msaito
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <libconfig.h++>
#include "Application.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

class Strategy {


public:
	float preco_acao_inicial;
	float dinheiro_inicial;
	float min_tempo_neg;
	Application application;


	Strategy();
	Strategy(std::string file, Application application);
	void run();
	virtual ~Strategy();

private:
	Application fix;
};

#endif /* STRATEGY_H_ */
