/*
 * Strategy.cpp
 *
 *  Created on: Jan 12, 2013
 *      Author: msaito
 */

#include "Strategy.h"

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
	   && cfg.lookupValue("PRECO_ACAO_INICIAL", preco_acao_inicial)
	   && cfg.lookupValue("DINHEIRO_INICIAL", dinheiro_inicial)
	   && cfg.lookupValue("PERCENTUAL_MAX_NEG", percentual_max_negs)
	   && cfg.lookupValue("TEMPO_INI", tempo_ini)
	   && cfg.lookupValue("TEMPO_CICLO", tempo_ciclo)){
		  std::cout << "ticker:" << ticker<<std::endl;
		  std::cout << "preco_acao_inicial:" << preco_acao_inicial<<std::endl;
		  std::cout << "dinheiro_inicial:" << dinheiro_inicial <<std::endl;
		  std::cout << "percentual_max_negs:" << percentual_max_negs <<std::endl;
		  std::cout << "tempo_ini:" << tempo_ini <<std::endl;
		  std::cout << "tempo_ciclo:" << tempo_ciclo <<std::endl;
	  }else{
		  std::cout << "configs vars not found" << std::endl;
		  exit(1);
	  }
}

void Strategy::preTrade(FIX42::Quote message){
	std::cout << "Strategy::PreTrade"<<std::endl;
	std::cout << this->QuoteToString(message) << std::endl;
	this->lastQuote = message;

}

SimpleOrder Strategy::trade(){
	std::cout << "Strategy::Trade"<<std::endl;
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
		order.price = (bidPx <= 0.0 ? this->preco_acao_inicial: (float)bidPx);
	}else{
		order.price = (offerPx <= 0.0 ? this->preco_acao_inicial: (float)offerPx);
	}

	order.price = order.price*(1.0+0.7/(rand()%100));
	order.orderQty = percentual_max_negs*this->dinheiro_inicial/order.price;

	std::cout << order.toString() << std::endl;

	return order;
}

void Strategy::postTrade(){

}



std::string Strategy::QuoteToString( const FIX42::Quote message ) {
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

	return  "[QUOTE] symbol:" + symbol.getString()
			+ "\tbidPx:" + bidPx.getString()
			+ "\tbidSize:" + bidSize.getString()
			+ "\tofferPx:" + offerPx.getString()
			+ "\tofferSize:" + offerSize.getString();

}


Strategy::~Strategy() {
}

