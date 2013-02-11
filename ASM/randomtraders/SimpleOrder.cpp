/*
 * SimpleOrder.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: msaito
 */

#include "SimpleOrder.h"

SimpleOrder::SimpleOrder() {
	// TODO Auto-generated constructor stub

}

SimpleOrder::~SimpleOrder() {
	// TODO Auto-generated destructor stub
}

void SimpleOrder::print() {

if(orderQty >  0.0 && price >  0.0)
	std::cout << "[ORDER] symbol: " << symbol
			  << "\tside: " << ( side == FIX::Side_SELL ? "SELL" : "BUY" )
			  << "\torderQty: " << orderQty
			  << "\tprice: " <<  std::fixed << std::setprecision(2) << (double)price
			  << std::endl;
else
	std::cout << "[ORDER] none"
	<< std::endl;
}
