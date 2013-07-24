#library(fBasics);

#TESTE<-1;
TESTE<-1;




AGENTS.ROW <- read.csv("./data/bb/test_BB_agents.csv");
AGENTS <- AGENTS.ROW[, "id_agent", drop = FALSE];

while (TESTE <= 100){
  PROFIT <-c();
  #############################################################
    filename<-paste0("./data/bb/test_BB_",TESTE,"_prices",".csv");
    FGV.PRICES.ROWDATA <- read.csv(filename);
    filename<-paste0("./data/bb/test_BB_",TESTE,"_portfolios",".csv");
    FGV.PORTFOLIOS.ROWDATA <- read.csv(filename);

    firstPrice <- FGV.PRICES.ROWDATA[1,"price"];
    lastPrice <- FGV.PRICES.ROWDATA[nrow(FGV.PRICES.ROWDATA),"price"];
  #############################################################
  a<-1;
  while (a <= nrow(AGENTS)){
    fa <- as.matrix(AGENTS[a,"id_agent", drop = FALSE]);
    AGENT.PORTFOLIO <- subset(FGV.PORTFOLIOS.ROWDATA, id_agent==fa[1]);
    AGENT.PROFIT <-0;
    if(nrow(AGENT.PORTFOLIO) > 0){
      CASH.INI <- AGENT.PORTFOLIO[1,"cash"];
      CASH.END <- AGENT.PORTFOLIO[nrow(AGENT.PORTFOLIO),"cash"];
      nSTOCK.INI <- AGENT.PORTFOLIO[1,"number_stock"];
      nSTOCK.END <- AGENT.PORTFOLIO[nrow(AGENT.PORTFOLIO),"number_stock"];  
      AGENT.WEALTH.INI <- CASH.INI + nSTOCK.INI*firstPrice;
      AGENT.WEALTH.END <- CASH.END + nSTOCK.END*lastPrice;
      AGENT.PROFIT <- AGENT.WEALTH.END/AGENT.WEALTH.INI;
    }
    PROFIT<-c(PROFIT,AGENT.PROFIT);
    a<-a+1;
  }
  #############################################################
  PROFIT <-data.frame(PROFIT);
  colnames(PROFIT) <- TESTE;
  AGENTS <-data.frame(AGENTS, PROFIT);
  
  TESTE<-TESTE+1;
}

write.csv(AGENTS, file = "./data/bb/test_BB_summary.csv", sep = " ",
            eol = "\n", na = "NA", dec = ",", row.names = TRUE,
            col.names = TRUE, qmethod = c("escape", "double"),fileEncoding = "")
