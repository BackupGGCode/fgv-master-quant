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
#include "quickfix/fix42/ExecutionReport.h"
#include "SimpleOrder.h"
#include <math.h>
#include "IDGenerator.h"

class Strategy {

public:
	std::string	ticker;
	float referenceStockPrice;
	float cash;
	float numberStock;
	float percentual_max_negs;
	float cycleTime;
	float initialTime;
	FIX42::Quote lastQuote;

	Strategy();
	Strategy(std::string file);
	virtual ~Strategy();
	void preTrade(FIX42::Quote message);
	SimpleOrder trade();
	void postTrade(FIX42::ExecutionReport ereport);
	void printQuote( const FIX42::Quote message );
	void printExecutionReport( const FIX42::ExecutionReport ereport );

private:
	  IDGenerator m_generator;
};

#endif /* STRATEGY_H_ */
