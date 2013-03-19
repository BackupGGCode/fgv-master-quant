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
#include "../utils/SimpleOrder.h"
#include "../utils/AgentControl.h"
#include <math.h>
#include "IDGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Strategy {

public:
	std::string	ticker;

    FIX::TransactTime time1;
    FIX::TransactTime time2;


    bool validMinVarPortWeight;
	float referenceStockPrice;
	float previousStockPrice;

	float referenceExogenous;
	float previousExogenous;

	float expectedReturnStock;
	float expectedReturnExogenous;

	float standardDeviationStock;
	float standardDeviationExogenous;

	float referenceCov;

	float cash;

	float numberStock;
	float numberExogenousAsset;


	float weightStock;
	float weightExogenousAsset;

	float cycleTime;
	float initialTime;

	AgentControl agentControl;

	Strategy();
	Strategy(const std::string strats);
	void setAgentControl(AgentControl agentControl);
	virtual ~Strategy();
	void preTrade();
	SimpleOrder trade();
	void postTrade(FIX42::ExecutionReport ereport);
	void printQuote( const FIX42::Quote message );
	void printExecutionReport( const FIX42::ExecutionReport ereport );

private:
	  IDGenerator m_generator;
};

#endif /* STRATEGY_H_ */
