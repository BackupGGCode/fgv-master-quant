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

#include "cppconn/exception.h"
#include "cppconn/driver.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"

#include "mysql_connection.h"
#include "mysql_driver.h"
///#include <driver/mysql_public_iface.h>



// Connection properties
#define DB   "quickfix"
#define HOST "tcp://localhost:3306"
#define USER "quickfix"
#define PASS "quickfix"




class AgentControl {
public:
	AgentControl();

	std::string getFixConfiguration(std::string agentID);
	std::string getStrategyConfiguration(std::string agentID);

	int run();


	virtual ~AgentControl();
};

#endif /* AGENTCONTROL_H_ */
