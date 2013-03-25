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

enum StateBB{
		NONE,
		OVERSOLD_IN,
		OVERSOLD,
		OVERSOLD_OUT,
		OVERBOUGHT_IN,
		OVERBOUGHT,
		OVERBOUGHT_OUT
	};

class Strategy {

public:
	std::string	ticker;

	StateBB state;
	int OVERBOUGHTtimeout;
	int OVERSOLDtimeout;

	int windowsSize;
    float bandSize;
	float averagePrice;
	float lastPrice;
	float standardDeviation;

	float cash;
	float numberStock;
	float percentual_max_negs;

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
