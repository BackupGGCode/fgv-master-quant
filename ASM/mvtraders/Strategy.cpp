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
	  // && cfg.lookupValue("REFERENCE_STOCK_PRICE", referenceStockPrice)
	  // && cfg.lookupValue("REFERENCE_EXOGENOUS", referenceExogenous)
	   && cfg.lookupValue("REFERENCE_COV", referenceCov)
	   && cfg.lookupValue("CASH", cash)
	   && cfg.lookupValue("NUMBER_STOCK", numberStock)
	   && cfg.lookupValue("NUMBER_EXOGENOUS", numberExogenous)
	   && cfg.lookupValue("INITIAL_TIME", initialTime)
	   && cfg.lookupValue("CYCLE_TIME", cycleTime)){
		  if(false){
				 // this->previousStockPrice = this->referenceStockPrice;
				 // this->previousExogenous = this->referenceExogenous;
			  std::cout << "ticker:" << ticker<< std::endl;
			  std::cout << "referenceCov:" << referenceCov << std::endl;
			  std::cout << "cash:" << cash << std::endl;
			  std::cout << "numberStock:" << numberStock << std::endl;
			  std::cout << "numberExogenous:" << numberExogenous << std::endl;
			  std::cout << "initialTime:" << initialTime << std::endl;
			  std::cout << "cycleTime:" << cycleTime << std::endl;
		  }

	  }else{
		  std::cout <<"[" << this->agentControl.agentID <<"] strategy configs vars not found" << std::endl;
		  exit(1);
	  }

	    //FIX::TransactTime now;
	    //this->time1 = now;
	    //this->time2 = now;
}


void Strategy::setAgentControl(AgentControl _agentControl){
	this->agentControl = _agentControl;
    FIX::TransactTime now;

	this->agentControl.setPortfolio(now.getString(),this->cash, this->numberStock, this->numberExogenous);
}

float* returnPrice(float* array, int& tam){
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

	this->validMinVarPortWeight = false;

	this->time1 = this->time2;
    FIX::TransactTime now;
    this->time2 = now;

	this->weightStock=0;
	this->weightExogenous=0;

	this->diffNumberStock=0;
	this->diffNumberExogenous=0;

    int tam_exo = 0;
    float* exogenous_prices = agentControl.getExogenousValues(this->time1.getString(), this->time2.getString(), tam_exo);

    int tam_prices = 0;
    float* prices = agentControl.getPrices(this->time1.getString(), this->time2.getString(), tam_prices);

	this->lastPriceStock =roundASM(prices[tam_prices-1]) ;
	this->lastPriceExogenous = roundASM(exogenous_prices[tam_exo-1]);

    float* returnExoPrices = returnPrice(exogenous_prices,tam_exo);
    float* returnPrices = returnPrice(prices,tam_prices);

	this->expectedReturnStock= avg(returnPrices, tam_prices);
	this->expectedReturnExogenous = avg(returnExoPrices, tam_exo);

//	for(int i=0;i<tam_exo;i++)
//		std::cout << "Ep[" << i <<"]=" <<returnExoPrices[i] << std::endl;
//
//	for(int i=0;i<tam_prices;i++)
//		std::cout<< "Sp[" << i <<"]=" <<prices[i] << "\treturnPrices[" << i <<"]=" <<returnPrices[i] << std::endl;


	this->standardDeviationExogenous = stdDev(returnExoPrices,tam_exo, this->expectedReturnExogenous);
	this->standardDeviationStock = stdDev(returnPrices,tam_prices, this->expectedReturnStock);

	float r_stock= this->expectedReturnStock;
	float r_exo = this->expectedReturnExogenous;

	float exo_var = pow(this->standardDeviationExogenous, 2);
	float stock_var = pow(this->standardDeviationStock, 2);
	float cov_stk_exo = this->referenceCov*this->standardDeviationStock*this->standardDeviationExogenous;

	this->weightStock = (exo_var*r_stock - cov_stk_exo*r_exo )/(exo_var*r_stock + stock_var*r_exo - cov_stk_exo*(r_stock+r_exo));
	this->weightExogenous = 1 - this->weightStock;


	///Minimum Variance Portfolio Weight

	if(this->weightStock >= 0 && this->weightStock <= 1
			&& this->weightExogenous >= 0 && this->weightExogenous <= 1 ){
		this->validMinVarPortWeight = true;

		float wealthOfExogenous = this->lastPriceExogenous*this->numberExogenous;
		float wealthOfStock = this->lastPriceStock*this->numberStock;

		float totalWealth=wealthOfExogenous+wealthOfStock+(this->cash < 0 ? 0:this->cash);

		float wealth4Exogenous = this->weightExogenous*totalWealth;
		float wealth4Stock = this->weightStock*totalWealth;

		this->diffNumberExogenous =(int) ((wealth4Exogenous/this->lastPriceExogenous) - this->numberExogenous);
		this->diffNumberStock =(int) ((wealth4Stock/this->lastPriceStock) - this->numberStock);

		std::cout << "[Strategy::PreTrade]" <<std::endl
			<< "\t\tSTOCK\t\tEXOGENOUS"<< std::endl
			<< "\t   E[.]\t"<< this->expectedReturnStock<<"\t"<< this->expectedReturnExogenous << std::endl
			<< "\t  SD[.]\t" << this->standardDeviationStock <<"\t" << this->standardDeviationExogenous  << std::endl
			<< "\t   W[.]\t" << this->weightStock <<"\t" << this->weightExogenous  << std::endl
			<< "\t   P[.]\t" << this->lastPriceStock <<"\t\t" << this->lastPriceExogenous  << std::endl
			<< "\tdiff[.]\t" << this->diffNumberStock <<"\t\t" << this->diffNumberExogenous  << std::endl
			<< std::endl <<"\tPortfolio\tcash:" << this->cash <<"\t#stock:" << this->numberStock <<"\t#Exogenous:" << this->numberExogenous << std::endl;

	}else{
		this->validMinVarPortWeight = false;
		std::cout << "[Strategy::PreTrade] **** NOT VALID! *****" <<std::endl;
	}

}

SimpleOrder Strategy::tradeUmountPosition(){
	std::cout << "Strategy::tradeUmountPosition()"<<std::endl;

	SimpleOrder order;

	order.symbol = this->ticker;
	order.clOrdID = m_generator.genOrderID();
	order.side = FIX::Side_SELL;
	order.orderQty = 0;
	order.price = 0;

	if(validMinVarPortWeight){


		if(this->diffNumberExogenous < 0 ){
			//vender Exogenous
			FIX::Symbol symbol("Exogenous");
			order.symbol = symbol;
			order.orderQty = (-1)*this->diffNumberExogenous;
			order.price = this->lastPriceExogenous;
			this->numberExogenous += this->diffNumberExogenous;
			this->cash += (-1/*trocar sinal*/)*this->diffNumberExogenous*this->lastPriceExogenous;
			order.print();
		}

		if(this->diffNumberStock < 0 ){
			//vender Ações
			order.symbol = this->ticker;
			order.orderQty = (-1)*this->diffNumberStock;
			order.price = this->lastPriceStock;
			order.print();
		}

	}
    FIX::TransactTime now;

	this->agentControl.setPortfolio( now.getString(),this->cash, this->numberStock, this->numberExogenous);
	return order;
}


SimpleOrder Strategy::tradeMountPosition(){
	std::cout << "Strategy::tradeMountPosition()"<<std::endl;

	SimpleOrder order;

	order.symbol = this->ticker;
	order.clOrdID = m_generator.genOrderID();
	order.side = FIX::Side_BUY;
	order.orderQty = 0;
	order.price = 0;

	float cashShare4Stock =1.0;
	float cashShare4Exogenous =1.0;

	if(validMinVarPortWeight){

		if(this->diffNumberExogenous > 0 && this->diffNumberStock > 0 ){
			// dividir o cash disponível ...


			float wealth4Stock = this->diffNumberExogenous*this->lastPriceStock;
			float wealth4Exogenous = this->diffNumberExogenous*this->lastPriceExogenous;

			float totalExtraWealth = wealth4Stock+wealth4Exogenous;

			cashShare4Stock = wealth4Stock/totalExtraWealth;
			cashShare4Exogenous = wealth4Exogenous/totalExtraWealth;
		}

		if(this->diffNumberExogenous > 0 ){
			//comprar Exogenous
			FIX::Symbol symbol("Exogenous");
			order.symbol = symbol;

			//float alternativeDiffNumberExogenous =(int) ((this->cash/this->lastPriceExogenous) - this->numberExogenous);

//			order.orderQty = (int)(this->diffNumberExogenous );
			order.orderQty = (int) (this->cash*cashShare4Exogenous/this->lastPriceExogenous);
			order.price = this->lastPriceExogenous;
			this->numberExogenous += order.orderQty;

			this->cash -= order.orderQty*order.price;
			order.print();
		}else if(this->diffNumberStock > 0 ){
				//comprar Ações
				order.symbol = this->ticker;
//				order.orderQty = (int) (this->diffNumberStock);
				order.orderQty = (int) (this->cash*cashShare4Stock/this->lastPriceStock);
				order.price = this->lastPriceStock;
				order.print();
			}

	}
    FIX::TransactTime now;

	this->agentControl.setPortfolio(now.getString(),this->cash, this->numberStock, this->numberExogenous);

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

    FIX::TransactTime now;

	this->agentControl.setPortfolio(now.getString(),this->cash, this->numberStock, this->numberExogenous);

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

