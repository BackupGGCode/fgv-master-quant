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

Strategy::Strategy(const std::string strats) {

	libconfig::Config cfg;
	cfg.readString(strats);

	  if(cfg.lookupValue("TICKER", ticker)
	   && cfg.lookupValue("REFERENCE_STOCK_PRICE", referenceStockPrice)
	   && cfg.lookupValue("CASH", cash)
	   && cfg.lookupValue("NUMBER_STOCK", numberStock)
	   && cfg.lookupValue("PERCENTUAL_MAX_NEG", percentual_max_negs)
	   && cfg.lookupValue("INITIAL_TIME", initialTime)
	   && cfg.lookupValue("CYCLE_TIME", cycleTime)){
		  std::cout << "ticker:" << ticker<< std::endl;
		  std::cout << "referenceStockPrice:" << referenceStockPrice<< std::endl;
		  std::cout << "cash:" << cash << std::endl;
		  std::cout << "numberStock:" << numberStock << std::endl;
		  std::cout << "percentual_max_negs:" << percentual_max_negs << std::endl;
		  std::cout << "initialTime:" << initialTime << std::endl;
		  std::cout << "cycleTime:" << cycleTime << std::endl;
	  }else{
		  std::cout <<"[" << this->agentControl.agentID <<"] strategy configs vars not found" << std::endl;
		  exit(1);
	  }
}


void Strategy::setAgentControl(AgentControl _agentControl){
	this->agentControl = _agentControl;
	this->agentControl.setPortfolio(this->cash, this->numberStock, 0.0);
}




void Strategy::preTrade(FIX42::Quote message){
	std::cout << "Strategy::PreTrade"<<std::endl;
	this->printQuote(message);
	this->lastQuote = message;

	FIX::BidPx bidPx;
	FIX::OfferPx offerPx;
	this->lastQuote.get(this->symbol);
	this->lastQuote.get(bidPx);
	this->lastQuote.get(offerPx);

	if(offerPx > 0.0 && bidPx > 0.0){
		this->referenceStockPrice = 0.5*(offerPx+bidPx);
		this->quoteDistance = 0.5*(offerPx-bidPx);
	}else{

		this->referenceStockPrice = this->agentControl.getLastPrice();
		this->quoteDistance = 5;
	}

	this->referenceStockPrice = roundASM(this->referenceStockPrice );
	this->quoteDistance = roundASM(this->quoteDistance );

}


SimpleOrder Strategy::tradeASK(){
	std::cout << "Strategy::TradeASK"<<std::endl;
	SimpleOrder order;
	order.symbol = this->symbol;
	order.clOrdID = m_generator.genOrderID();
	order.side = FIX::Side_SELL;

	order.price = this->referenceStockPrice+this->quoteDistance;
	order.orderQty = (int) (0.5*this->cash*this->percentual_max_negs/order.price);

	order.print();
	return order;
}

SimpleOrder Strategy::tradeBID(){
	std::cout << "Strategy::TradeBID"<<std::endl;
	SimpleOrder order;
	order.symbol = this->symbol;
	order.clOrdID = m_generator.genOrderID();
	order.side = FIX::Side_BUY;

	order.price = this->referenceStockPrice-this->quoteDistance;
	order.orderQty = (int) (0.5*this->cash*this->percentual_max_negs/order.price);

	order.print();
	return order;
}

void Strategy::postTrade(FIX42::ExecutionReport ereport){
	std::cout << "Strategy::PostTrade"<<std::endl;
	//this->printExecutionReport(ereport);

	FIX::LastShares lastShares;
	FIX::LastPx lastPx;
	FIX::Side side;

	ereport.get(lastShares);
	ereport.get(lastPx);
	ereport.get(side);

	this->numberStock += ( side == FIX::Side_SELL ? -lastShares : +lastShares );
	this->cash += ( side == FIX::Side_SELL ? +lastShares*lastPx : -lastShares*lastPx );

	this->agentControl.setPortfolio(this->cash, this->numberStock, 0.0);

	//if(this->cash <= 0.0 && this->numberStock <= 0.0)
	//	exit(1);

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
			<< "\tSide:" << ( side == FIX::Side_SELL ? "SELL" : "BUY" )
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

