/*
 * SimpleOrder.h
 *
 *  Created on: Jan 25, 2013
 *      Author: msaito
 */

#ifndef SIMPLEORDER_H_
#define SIMPLEORDER_H_

#include "quickfix/Message.h"

class SimpleOrder {
public:
	SimpleOrder();
	virtual ~SimpleOrder();
	FIX::Symbol symbol;
	FIX::Side side;
    FIX::OrderQty orderQty;
    FIX::Price price;

    void print();
};

#endif /* SIMPLEORDER_H_ */
