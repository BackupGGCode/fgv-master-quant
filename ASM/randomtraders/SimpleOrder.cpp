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

std::string SimpleOrder::toString() {

	return "[ORDER] symbol: " + symbol.getString()
			  + "\tside: "+( side == FIX::Side_SELL ? "SELL" : "BUY" )
			  +"\torderQty: "+orderQty.getString()
			  +"\tprice: "+price.getString();
}
