library(fBasics);
library(quantmod);
testnumber<-1;
ltestnumber <-c(); lsumvolume<-c(); lsdprice<-c(); lsdret<-c();

while (testnumber <=100){
  filename<-paste0("./data/vol/test_vol_",testnumber,"_prices",".csv");
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
plot(sdprice, type='o',xlab="fator aleatório (%)", ylab="volatilidade dos preços"
     , main="Volatilidade dos preços x Fator aleatório nos preços");
mod1 <- lm(lsdprice ~ ltestnumber)
abline(mod1, lwd=2, col="blue", lty=3)


sdret <- data.frame(ltestnumber,lsdret);
plot(sdret, type='o',xlab="fator aleatório (%)", ylab="volatilidade dos log-retornos"
     , main="Volatilidade dos log-retornos x Fator aleatório nos preços");
mod2 <- lm(lsdret ~ ltestnumber)
abline(mod2, lwd=2, col="blue", lty=3)

volume <- data.frame(ltestnumber,lsumvolume);
plot(volume, type='o',xlab="fator aleatório (%)", ylab="número de negociações"
     , main="Volume de negociação x Fator aleatório nos preços");
mod3 <- lm(lsumvolume ~ ltestnumber)
abline(mod3, lwd=2, col="blue", lty=3)

