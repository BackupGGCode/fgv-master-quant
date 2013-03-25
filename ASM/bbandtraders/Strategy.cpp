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
	   && cfg.lookupValue("CASH", cash)
	   && cfg.lookupValue("NUMBER_STOCK", numberStock)
	   && cfg.lookupValue("PERCENTUAL_MAX_NEG", percentual_max_negs)
	   && cfg.lookupValue("INITIAL_TIME", initialTime)
	   && cfg.lookupValue("CYCLE_TIME", cycleTime)){

    	  std::cout << "ticker:" << ticker<< std::endl;
		  std::cout << "cash:" << cash << std::endl;
		  std::cout << "percentual_max_negs:" << percentual_max_negs << std::endl;
		  std::cout << "numberStock:" << numberStock << std::endl;
		  std::cout << "initialTime:" << initialTime << std::endl;
		  std::cout << "cycleTime:" << cycleTime << std::endl;

	  }else{
		  std::cout <<"[" << this->agentControl.agentID <<"] strategy configs vars not found" << std::endl;
		  exit(1);
	  }

		this->state = NONE;
		this->OVERBOUGHTtimeout = 0;
		this->OVERSOLDtimeout = 0;
	    this->windowsSize = 5;
	    this->bandSize = 1;
	    this->averagePrice = 0;
	    this->lastPrice = 0;
	    this->standardDeviation = 0;

}


void Strategy::setAgentControl(AgentControl _agentControl){
	this->agentControl = _agentControl;
	this->agentControl.setPortfolio(this->cash, this->numberStock, 0);
}



float avg(float* array, int tam){
	float res = 0;
	for(int i=0;i<tam;i++){
		res += array[i];
	}
	return res/tam;
}


float stdDev(float* array, int tam, float mean){
	float sum = 0;
	for(int i = 0; i < tam; i++)
			sum += pow(array[i]-mean, 2);
	return sqrt(sum/tam);
}

void Strategy::preTrade(){

	std::cout << std::endl << "[Strategy::preTrade()]"<< std::endl;

	float lowerBound = 0;
	float upperBound = 0;

    int tam_prices = 0;
    float* prices = agentControl.getLastNPrices(this->windowsSize, tam_prices);

    if(tam_prices >= this->windowsSize ){

    	this->averagePrice =avg(prices, tam_prices-1);
    	this->standardDeviation = stdDev(prices,tam_prices-1, this->averagePrice);

    	lowerBound = this->averagePrice - this->bandSize*this->standardDeviation;
    	upperBound = this->averagePrice + this->bandSize*this->standardDeviation;



    	this->lastPrice = prices[tam_prices-1];

    	if(lowerBound >= upperBound)return;


    	// não está com posição
    	if( this->state == NONE){

			if(this->lastPrice < lowerBound)
				this->state = OVERSOLD_IN;

			if(this->lastPrice > upperBound)
				this->state = OVERBOUGHT_IN;
    	}else{

			 if(this->state == OVERSOLD ){
				 if(this->lastPrice >= this->averagePrice)
					 	 this->state = OVERSOLD_OUT;
				 else
					 this->OVERSOLDtimeout++;

			 }
			 if(this->state == OVERBOUGHT){
				 if(this->lastPrice < this->averagePrice)
					 this->state = OVERBOUGHT_OUT;
				 else
					 this->OVERBOUGHTtimeout++;
			 }

			 if(this->OVERSOLDtimeout > 3 || this->OVERBOUGHTtimeout > 3 ){
				 this->OVERBOUGHTtimeout = this->OVERSOLDtimeout = 0;
				 std::cout << std::endl << "strategy timeout "<< std::endl;
				 this->state = NONE;
			 }

    	}



    }else{
    	std::cout << std::endl << "small windows size: " << tam_prices << std::endl;
    }


}


SimpleOrder Strategy::trade(){
	std::cout << "Strategy::trade()"<<std::endl;

	SimpleOrder order;

	order.symbol = this->ticker;
	order.clOrdID = m_generator.genOrderID();

	order.orderQty = 0;
	order.price = 0;

	if(this->state == OVERSOLD_IN){
		order.side = FIX::Side_BUY;
		order.orderQty = (int) (this->cash*this->percentual_max_negs/this->lastPrice);
		order.price = roundASM(this->lastPrice);
		this->state = OVERSOLD;
	}

	if(this->state == OVERBOUGHT_IN){
		order.side = FIX::Side_SELL;
		order.orderQty = (int) (this->numberStock*this->percentual_max_negs);
		order.price = roundASM(this->lastPrice);
		this->state = OVERBOUGHT;
	}

	if( this->state == OVERBOUGHT_OUT){
		order.side = FIX::Side_BUY;
		order.orderQty = (int) (this->cash*this->percentual_max_negs/this->lastPrice);
		order.price = roundASM(this->lastPrice);
		this->state = NONE;
	}

	if( this->state == OVERSOLD_OUT){
		order.side = FIX::Side_SELL;
		order.orderQty = (int) (this->numberStock*this->percentual_max_negs);
		order.price = roundASM(this->lastPrice);
		this->state = NONE;
	}

	order.print();
	return order;
}


void Strategy::postTrade(FIX42::ExecutionReport ereport){
	//std::cout << "Strategy::PostTrade"<<std::endl;

	FIX::LastShares lastShares;
	FIX::LastPx lastPx;
	FIX::Side side;

	ereport.get(lastShares);
	ereport.get(lastPx);
	ereport.get(side);

	this->numberStock += ( side == FIX::Side_SELL ? -lastShares : +lastShares );
	this->cash += ( side == FIX::Side_SELL ? +lastShares*lastPx : -lastShares*lastPx );

	this->agentControl.setPortfolio(this->cash, this->numberStock, 0);

	if(this->cash <= 0.0 && this->numberStock <= 0.0)
		exit(1);

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

