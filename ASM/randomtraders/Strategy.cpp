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
	  // && cfg.lookupValue("PERCENTUAL_MAX_NEG", percentual_max_negs)
	   && cfg.lookupValue("INITIAL_TIME", initialTime)
	   && cfg.lookupValue("CYCLE_TIME", cycleTime)){
		 // std::cout << "ticker:" << ticker<< std::endl;
		 // std::cout << "referenceStockPrice:" << referenceStockPrice<< std::endl;
		 // std::cout << "cash:" << cash << std::endl;
		 // std::cout << "numberStock:" << numberStock << std::endl;
		 // std::cout << "percentual_max_negs:" << percentual_max_negs << std::endl;
		 // std::cout << "initialTime:" << initialTime << std::endl;
		 // std::cout << "cycleTime:" << cycleTime << std::endl;
	  }else{
		  //std::cout <<"[" << this->agentControl.agentID <<"] strategy configs vars not found" << std::endl;
		  exit(1);
	  }
}


void Strategy::setAgentControl(AgentControl _agentControl){
	this->agentControl = _agentControl;
	this->agentControl.setPortfolio(this->cash, this->numberStock);
}




void Strategy::preTrade(FIX42::Quote message){
	//std::cout << "Strategy::PreTrade"<<std::endl;
	//this->printQuote(message);
	this->lastQuote = message;

}

SimpleOrder Strategy::trade(){
	//std::cout << "Strategy::Trade"<<std::endl;
	SimpleOrder order;

	FIX::Symbol symbol;
	FIX::BidPx bidPx;
	FIX::OfferPx offerPx;
	this->lastQuote.get(symbol);
	this->lastQuote.get(bidPx);
	this->lastQuote.get(offerPx);


	order.symbol = symbol;
	order.clOrdID = m_generator.genOrderID();

	//float volatility = 1.0+(rand()%20 - 10)/100.0;
	float volatility = 1.0+(rand()%11 - 5)/100.0;

	// Implementacao do Fluxo de decisao do agente aleatorio ...

	if(offerPx > 0.0 && bidPx > 0.0){
		this->referenceStockPrice = 0.5*(offerPx+bidPx);
	}else{
		if(offerPx > 0.0){
			this->referenceStockPrice = offerPx;
		}else{
			if(bidPx > 0.0){
				this->referenceStockPrice = bidPx;
			}else{
				// nothing => keep previous
			}
		}
	}

	this->referenceStockPrice *= volatility;
	this->referenceStockPrice = roundASM(this->referenceStockPrice );

	//std::cout<<  "referenceStockPrice:" << this->referenceStockPrice << std::endl;
	//std::cout<<  "cash:" << this->cash << std::endl;
	//std::cout<<  "numberStock:" << this->numberStock << std::endl;

	srand(time(0));
	int rand_decision = rand()%100;
	float rand_amount =(rand()%100)/100.0;



	// [DECISAO-01] Possui acao no inventario?
	if(this->numberStock > 0.0){
		//std::cout<<  "[DECISAO-01] Possui acao no inventario" << std::endl;

		// [DECISAO-01] SIM
		int qty = (int)(this->cash/this->referenceStockPrice );
		order.price = this->referenceStockPrice;

		// [DECISAO-02] Possui saldo em dinheiro superior ao preco de pelo menos uma acao (ASK)?
		if(qty >= 1 ){
			//std::cout<<  "[DECISAO-02] Possui saldo em dinheiro superior ao preco de pelo menos uma acao (ASK)" << std::endl;
			// [DECISAO-02] SIM => [ACAO 01] Não Operar, Comprar ou Vender acoes
			if(rand_decision < 33 ){
				//std::cout<<  "[DECISAO-02] SIM => [ACAO 01] Comprar acoes" << std::endl;
				order.side = FIX::Side_BUY;

				qty=(int)qty*rand_amount;
				qty=(qty > 1 ? qty: 1);

				order.orderQty = qty ;

			}else{
				if(rand_decision >= 67 ){
					//std::cout<<  "[DECISAO-02] SIM => [ACAO 01] Vender acoes" << std::endl;
					order.side = FIX::Side_SELL;
					qty=(int)this->numberStock*rand_amount;
					qty=(qty > 1 ? qty: 1);
					order.orderQty =qty;
				}else{
					// Não Operar
					//std::cout<<  "[DECISAO-02] SIM => [ACAO 01]  Não Operar" << std::endl;
					order.side ='0';
					order.orderQty = 0;
					order.price = 0;
				}
			}

		}else{
			// [DECISAO-02] NAO => [ACAO 02] Não Operar ou Vender acoes
			if(rand_decision > 50 ){
			//std::cout<<  "[DECISAO-02] NAO => [ACAO 02] Vender acoes" << std::endl;
			order.side = FIX::Side_SELL;
			qty=(int)this->numberStock*rand_amount;
			qty=(qty > 1 ? qty: 1);
			order.orderQty = qty;

			}else{
				// Não Operar
				//std::cout<<  "[DECISAO-02] NAO => [ACAO 02] Não Operar" << std::endl;
				order.side ='0';
				order.orderQty = 0;
				order.price = 0;
			}
		}
	}else{
		// [DECISAO-01] NAO
		//std::cout<<  "[DECISAO-01] NAO possui acao no inventario" << std::endl;

		int qty = (this->cash/this->referenceStockPrice );
		order.price = this->referenceStockPrice;

		if(qty >= 1 ){
			// [DECISAO-04] SIM => [ACAO 04] Não Operar ou Comprar acoes
			if(rand_decision < 50 ){
				//std::cout<<  "[DECISAO-04] SIM => [ACAO 04] Comprar acoes" << std::endl;
				order.side = FIX::Side_BUY;
				qty=(int)qty*rand_amount;
				qty=(qty > 1 ? qty: 1);

				order.orderQty = qty;
			}else{
				// Não Operar
				//std::cout<<  "[DECISAO-04] SIM => [ACAO 04] Não Operar" << std::endl;
				order.side ='0';
				order.orderQty = 0;
				order.price = 0;
			}

		}else{
			// [DECISAO-03] NAO => [ACAO 03] VALIDO!

			// Não Operar
			//std::cout<<  "[DECISAO-03] NAO => [ACAO 03] VALIDO!" << std::endl;
			exit(1);
			order.side ='0';
			order.orderQty = 0;
			order.price = 0;
		}
	}

	//order.print();
	return order;
}

void Strategy::postTrade(FIX42::ExecutionReport ereport){
	//std::cout << "Strategy::PostTrade"<<std::endl;
	//this->printExecutionReport(ereport);

	//FIX::CumQty cumQty;
	FIX::LastShares lastShares;
	//FIX::AvgPx avgPx;
	FIX::LastPx lastPx;
	FIX::Side side;

	//ereport.get(cumQty);
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

