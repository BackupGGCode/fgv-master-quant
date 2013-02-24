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
	   && cfg.lookupValue("REFERENCE_RATE", referenceRate)
	   && cfg.lookupValue("REFERENCE_COV", referenceCov)
	   && cfg.lookupValue("CASH", cash)
	   && cfg.lookupValue("NUMBER_STOCK", numberStock)
	   && cfg.lookupValue("INITIAL_TIME", initialTime)
	   && cfg.lookupValue("CYCLE_TIME", cycleTime)){
		  this->previousStockPrice = this->referenceStockPrice;
		  this->previousRate = this->referenceRate;

		  std::cout << "ticker:" << ticker<< std::endl;
		  std::cout << "referenceStockPrice:" << referenceStockPrice<< std::endl;
		  std::cout << "referenceRate:" << referenceRate << std::endl;
		  std::cout << "referenceCov:" << referenceCov << std::endl;
		  std::cout << "cash:" << cash << std::endl;
		  std::cout << "numberStock:" << numberStock << std::endl;
		  std::cout << "initialTime:" << initialTime << std::endl;
		  std::cout << "cycleTime:" << cycleTime << std::endl;

	  }else{
		  std::cout <<"[" << this->agentControl.agentID <<"] strategy configs vars not found" << std::endl;
		  exit(1);
	  }

	   // FIX::TransactTime now;
	  //  this->time1 = now;
	  //  this->time2 = now;
}


void Strategy::setAgentControl(AgentControl _agentControl){
	this->agentControl = _agentControl;
	this->agentControl.setPortfolio(this->cash, this->numberStock);
}

float* returnStock(float* array, int& tam){
	float* res;
	if (tam <= 1){
		res = new float[1];
		res[0] = 0.0;
	}
	else{
		tam = tam - 1;
		res = new float[tam];
		for(int i=0;i<tam;i++){
			float diff = array[i+1]- array[i];
			float denominador =  array[i];
			res[i] = diff/denominador;
		}
	}
	return res;
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

	this->time1 = this->time2;
	//sleep(this->initialTime);
    FIX::TransactTime now;
    this->time2 = now;

    int tam_rates = 0;
    float* rates = agentControl.getRates(this->time1.getString(), this->time2.getString(), tam_rates);

    int tam_prices = 0;
    float* prices = agentControl.getPrices(this->time1.getString(), this->time2.getString(), tam_prices);

    float* returnPrices = returnStock(prices,tam_prices);

	this->expectedReturnStock= avg(returnPrices, tam_prices);
	this->expectedReturnBank = avg(rates, tam_rates);

	//for(int i=0;i<tam_rates;i++)
	//	std::cout << "rates[" << i <<"]=" <<rates[i] << std::endl;
	//std::cout << "avg: " << this->expectedReturnBank << std::endl;

	//for(int i=0;i<tam_prices;i++)
	//	std::cout<< "Prices[" << i <<"]=" <<prices[i] << "\treturnPrices[" << i <<"]=" <<returnPrices[i] << std::endl;
	//std::cout << "avg: " << this->expectedReturnStock << std::endl;

	this->standardDeviationBank = stdDev(rates,tam_rates, this->expectedReturnBank);
	this->standardDeviationStock = stdDev(returnPrices,tam_prices, this->expectedReturnStock);




	float r_stock= this->expectedReturnStock-0.01;
	float r_bank = this->expectedReturnBank -0.01;

	float bank_var = pow(this->standardDeviationBank, 2);
	float stock_var = pow(this->standardDeviationStock, 2);
	float cov_stk_bnk = this->referenceCov*this->standardDeviationStock*this->standardDeviationBank;

	float w_stock = (bank_var*r_stock - cov_stk_bnk*r_bank )/(bank_var*r_stock + stock_var*r_bank - cov_stk_bnk*(r_stock+r_bank));
	float w_bank = 1 - w_stock;

	///Minimum Variance Portfolio Weight

	if(w_stock > 0 && w_stock < 1 && w_bank > 0 && w_bank < 1 )
		std::cout << "[Strategy::PreTrade]" <<std::endl
			<< "\tE[Stock]:"<< this->expectedReturnStock<<"\t sd[Stock]:"<< this->standardDeviationStock << std::endl
	        << "\tE[Bank]:" << this->expectedReturnBank <<"\t sd[Bank]:" << this->standardDeviationBank  << std::endl
			<< "\tW[Bank]:" << w_bank <<"\t W[Stock]:" << w_stock  << std::endl;







}

SimpleOrder Strategy::trade(){

	//	http://xa.yimg.com/kq/groups/18315139/411279682/name/Aula+14.pdf
	//std::cout << "Strategy::Trade"<<std::endl;
	SimpleOrder order;

	FIX::Symbol symbol;



	//order.print();
	return order;
}

void Strategy::postTrade(FIX42::ExecutionReport ereport){
	//std::cout << "Strategy::PostTrade"<<std::endl;
	//this->printExecutionReport(ereport);


	FIX::LastShares lastShares;
	FIX::LastPx lastPx;
	FIX::Side side;

	ereport.get(lastShares);
	ereport.get(lastPx);
	ereport.get(side);

	this->numberStock += ( side == FIX::Side_SELL ? -lastShares : +lastShares );
	this->cash += ( side == FIX::Side_SELL ? +lastShares*lastPx : -lastShares*lastPx );

	this->agentControl.setPortfolio(this->cash, this->numberStock);

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

