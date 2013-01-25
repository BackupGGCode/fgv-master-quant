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

	  if(cfg.lookupValue("PRECO_ACAO_INICIAL", preco_acao_inicial)
	   && cfg.lookupValue("DINHEIRO_INICIAL", dinheiro_inicial)
	   && cfg.lookupValue("TEMPO_INI", tempo_ini)
	   && cfg.lookupValue("TEMPO_CICLO", tempo_ciclo)){
		  std::cout << "preco_acao_inicial:" << preco_acao_inicial<<std::endl;
		  std::cout << "dinheiro_inicial:" << dinheiro_inicial <<std::endl;
		  std::cout << "tempo_ini:" << tempo_ini <<std::endl;
		  std::cout << "tempo_ciclo:" << tempo_ciclo <<std::endl;
	  }else{
		  std::cout << "configs vars not found" << std::endl;
		  exit(1);
	  }
}

void Strategy::run(){

    try{
//    	application.sendOrder()

    }
    catch ( std::exception & e )
    {
      std::cout << "Problem: " << e.what();
    }

}

Strategy::~Strategy() {
}

