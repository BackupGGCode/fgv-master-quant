/*
 * Strategy.cpp
 *
 *  Created on: Jan 12, 2013
 *      Author: msaito
 */

#include "Strategy.h"

float roundASM(float x) { return floorf(x * 100 + 0.5) / 100; }

Strategy::Strategy() {
}

Strategy::Strategy(std::string file) {
	libconfig::Config cfg;

	try{
		cfg.readFile(file.c_str());
	  }catch(const libconfig::FileIOException &fioex){
	    std::cerr << "I/O error while reading file." << std::endl;
	    exit(1);
	  }catch(const libconfig::ParseException &pex){
	    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
	              << " - " << pex.getError() << std::endl;
	    exit(1);
	  }

	  if(cfg.lookupValue("TICKER", ticker)
	   && cfg.lookupValue("INITIAL_STOCK_PRICE", initialStockPrice)
	   && cfg.lookupValue("CASH", cash)
	   && cfg.lookupValue("NUMBER_STOCK", numberStock)
	   && cfg.lookupValue("PERCENTUAL_MAX_NEG", percentual_max_negs)
	   && cfg.lookupValue("INITIAL_TIME", initialTime)
	   && cfg.lookupValue("CYCLE_TIME", cycleTime)){
		  std::cout << "ticker:" << ticker<< std::endl;
		  std::cout << "initialStockPrice:" << initialStockPrice<< std::endl;
		  std::cout << "cash:" << cash << std::endl;
		  std::cout << "numberStock:" << numberStock << std::endl;
		  std::cout << "percentual_max_negs:" << percentual_max_negs << std::endl;
		  std::cout << "initialTime:" << initialTime << std::endl;
		  std::cout << "cycleTime:" << cycleTime << std::endl;
	  }else{
		  std::cout << "configs vars not found" << std::endl;
		  exit(1);
	  }
}



void Strategy::preTrade(FIX42::Quote message){
	std::cout << "Strategy::PreTrade"<<std::endl;
	this->printQuote(message);
	this->lastQuote = message;

}

SimpleOrder Strategy::trade(){
	std::cout << "Strategy::Trade"<<std::endl;
	float price = 0.0;
	SimpleOrder order;

	FIX::Symbol symbol;
	FIX::BidPx bidPx;
	FIX::OfferPx offerPx;
	this->lastQuote.get(symbol);
	this->lastQuote.get(bidPx);
	this->lastQuote.get(offerPx);

	order.symbol = symbol;

	if(rand()%100 > 50){
		order.side = FIX::Side_SELL;
	}else{
		order.side = FIX::Side_BUY;
	}

	if(order.side == FIX::Side_SELL){
		price = (bidPx <= 0.0 ? this->initialStockPrice: (float)bidPx);
	}else{
		price = (offerPx <= 0.0 ? this->initialStockPrice: (float)offerPx);
	}

	price += price*(0.7/(rand()%100));

	order.price = roundASM(price);
	order.orderQty = (int) (percentual_max_negs*this->cash/order.price);

	order.print();

	return order;
}

void Strategy::postTrade(FIX42::ExecutionReport ereport){
	std::cout << "Strategy::PostTrade"<<std::endl;
	this->printExecutionReport(ereport);

	FIX::CumQty cumQty;
	FIX::AvgPx avgPx;
	FIX::Side side;

	ereport.get(cumQty);
	ereport.get(avgPx);
	ereport.get(side);


	this->numberStock += ( side == FIX::Side_SELL ? -cumQty : +cumQty );
	this->cash += ( side == FIX::Side_SELL ? +cumQty*avgPx : -cumQty*avgPx );

}

void Strategy::printExecutionReport( const FIX42::ExecutionReport ereport ) {

	FIX::OrderID orderID;
	FIX::ExecID execID;
	FIX::ExecTransType execTransType;
	FIX::ExecType execType;
	FIX::OrdStatus ordStatus;
	FIX::Symbol symbol;
	FIX::Side side;
	FIX::LeavesQty leavesQty;
	FIX::CumQty cumQty;
	FIX::AvgPx avgPx;

	ereport.get(orderID);
	ereport.get(execID);
	ereport.get(execTransType);
	ereport.get(execType);
	ereport.get(ordStatus);
	ereport.get(symbol);
	ereport.get(side);
	ereport.get(leavesQty);
	ereport.get(cumQty);
	ereport.get(avgPx);

	std::cout<<  "[EXECUTION REPORT] symbol:" << symbol
			<< "\tLeavesQty:" << leavesQty
			<< "\tCumQty:" << cumQty
			<< "\tAvgPx:"<< std::fixed << std::setprecision(2) << (double)avgPx
			<< std::endl;
}


void Strategy::printQuote( const FIX42::Quote message ) {
	FIX::Symbol symbol;
	FIX::BidPx bidPx;
	FIX::OfferPx offerPx;
	FIX::BidSize bidSize;
	FIX::OfferSize offerSize;

	message.get(symbol);
	message.get(bidPx);
	message.get(offerPx);
	message.get(bidSize);
	message.get(offerSize);
	std::cout<<  "[QUOTE] symbol:" << symbol
			<< "\tbidPx:" << std::fixed << std::setprecision(2) << (double)bidPx
			<< "\tbidSize:" << bidSize
			<< "\tofferPx:" << std::fixed << std::setprecision(2) << (double)offerPx
			<< "\tofferSize:" << offerSize
			<< std::endl;
}


Strategy::~Strategy() {
}

