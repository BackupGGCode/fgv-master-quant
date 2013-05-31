
testnumber<-1;
ltestnumber <-c(); lsumvolume<-c(); lsdprice<-c(); lsdret<-c();
while (testnumber < 600){
  filename<-paste0("./data/budget/test",testnumber,"_prices",".csv");
  FGV.PRICES.ROWDATA <- read.csv(filename);
  
  FGV.prices <- FGV.PRICES.ROWDATA[, "price", drop = FALSE]
  rownames(FGV.prices) = FGV.PRICES.ROWDATA$time
  FGV.volumes <- FGV.PRICES.ROWDATA[, "volume", drop = FALSE]
  rownames(FGV.volumes) = FGV.PRICES.ROWDATA$time
  FGV.PRICESVOLUMES <- cbind(FGV.prices, FGV.volumes)
  FGV.PRICESVOLUMES <- as.xts(FGV.PRICESVOLUMES)
  
  FGV.prices.rows = nrow(FGV.prices)
  # retorno simples ...
  FGV.rt = (FGV.prices[2:FGV.prices.rows, 1] - 
              FGV.prices[1:(FGV.prices.rows - 1), 1])/FGV.prices[1:(FGV.prices.rows - 1), 1]
  names(FGV.rt) = rownames(FGV.prices)[2:FGV.prices.rows]
  # retorno composto continuo
  FGV.ccret = log(1 + FGV.rt);
  
  sd_price <- sd(FGV.PRICESVOLUMES[,1]);
  sd_return <- sd(FGV.ccret);
  s<-sum(FGV.PRICESVOLUMES[,2]);
  
  
  ltestnumber <- c(ltestnumber,testnumber);
  lsumvolume <- c(lsumvolume, s);
  lsdprice <- c(lsdprice, sd_price);
  lsdret <- c(lsdret, sd_return);
  testnumber<-testnumber*2;
}
sdprice <- data.frame(ltestnumber,lsdprice);
plot(sdprice, type='o',xlab="orçamento", ylab="desvio-padrão dos preços"
     , main="Desvio-padrão dos preços x Orçamento");
mod1 <- lm(lsdprice ~ ltestnumber)
abline(mod1, lwd=2, col="blue", lty=3)


sdret <- data.frame(ltestnumber,lsdret);
plot(sdret, type='o',xlab="orçamento", ylab="desvio-padrão dos log-retornos"
     , main="Desvio-padrão dos log-retornos x Orçamento");



volume <- data.frame(ltestnumber,lsumvolume);
plot(volume, type='o',xlab="orçamento (log)", ylab="número de negociações (log)"
     , main="Volume de negociação x Orçamento", log="xy");