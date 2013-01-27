/*
 * Strategy.h
 *
 *  Created on: Jan 12, 2013
 *      Author: msaito
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <libconfig.h++>
#include "quickfix/fix42/Quote.h"
#include "SimpleOrder.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

class Strategy {


public:
	std::string	ticker;
	float preco_acao_inicial;
	float dinheiro_inicial;
	float percentual_max_negs;
	float tempo_ciclo;
	float tempo_ini;
	FIX42::Quote lastQuote;


	Strategy();
	Strategy(std::string file);
	virtual ~Strategy();
	void preTrade(FIX42::Quote message);
	SimpleOrder trade();
	void postTrade();
	std::string QuoteToString( const FIX42::Quote message );

};

#endif /* STRATEGY_H_ */
