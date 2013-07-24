library(fBasics);
library(quantmod);
testnumber<-1;
ltestnumber <-c(); lsumvolume<-c(); lsdprice<-c(); lsdret<-c();

while (testnumber <=30){
  filename<-paste0("./data/MMCycleTime/test_mmCycleTime_",testnumber,"_prices",".csv");
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
  
  #  mean_return <- mean(FGV.ccret)
  #  sd_return <- sd(FGV.ccret)
  #  skewness_return <- skewness(FGV.ccret)
  #  kurtosis_return <- kurtosis(FGV.ccret)
  
  ltestnumber <- c(ltestnumber,testnumber);
  lsumvolume <- c(lsumvolume, s);
  lsdprice <- c(lsdprice, sd_price);
  lsdret <- c(lsdret, sd_return);
  testnumber<-testnumber+1;
}

sdprice <- data.frame(ltestnumber,lsdprice);
plot(sdprice, type='o',xlab="periodo", ylab="volatilidade dos preços"
     , main="Volatilidade dos preços x Periodo");
mod2 <- lm(lsdprice ~ ltestnumber)
abline(mod2, lwd=2, col="blue", lty=3)


sdret <- data.frame(ltestnumber,lsdret);
plot(sdret, type='o',xlab="periodo", ylab="volatilidade dos log-retornos"
     , main="Volatilidade dos log-retornos x Periodo");
mod3 <- lm(lsdret ~ ltestnumber)
abline(mod3, lwd=2, col="blue", lty=3)

volume <- data.frame(ltestnumber,lsumvolume);
plot(volume, type='o',xlab="periodo", ylab="número de negociações"
     , main="Volume de negociação x Periodo");
mod4 <- lm(lsumvolume ~ ltestnumber)
abline(mod4, lwd=2, col="blue", lty=3)
