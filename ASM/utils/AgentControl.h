/*
 * AgentControl.h
 *
 *  Created on: Feb 11, 2013
 *      Author: msaito
 */






#ifndef AGENTCONTROL_H_
#define AGENTCONTROL_H_


// Standard C++ includes
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <fstream>

#include "boost/algorithm/string.hpp"
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>


#include "cppconn/exception.h"
#include "cppconn/driver.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"

#include "mysql_connection.h"
#include "mysql_driver.h"


// Connection properties
#define DB   "quickfix"
#define HOST "tcp://localhost:3306"
#define USER "quickfix"
#define PASS "quickfix"




class AgentControl {
public:
	std::string agentID;
	AgentControl();
	AgentControl(std::string agentID);
	std::string getFixConfiguration();
	std::string getSessionConfiguration();
	std::string getStrategyConfiguration();

	void setupPrices(std::string time);
	void updateExogenousTimes(std::string start_time);
	void updatePrices(std::string start_time, float price, float quantity);
	void setPortfolio(	float cash, float  number_stock, float  number_exogenous);
	float getRate(std::string time);
	float getLastPrice(void);
	float* getLastNPrices(int N, int& tam);
	float* getPrices(std::string time1, std::string time2, int& tam);
	float* getExogenousValues(std::string time1, std::string time2, int& tam);


	int run();


	virtual ~AgentControl();
};

#endif /* AGENTCONTROL_H_ */
