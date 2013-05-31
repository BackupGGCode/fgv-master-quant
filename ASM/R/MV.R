library(fBasics);
library(quantmod);

test<-"CRESCENTE01";

filename<-paste0("./data/mv/test_MV_",test,"_prices",".csv");
FGV.PRICES.ROWDATA <- read.csv(filename);
  
filename<-paste0("./data/mv/test_MV_",test,"_EXOprices",".csv");
FGV.EXOPRICES.ROWDATA <- read.csv(filename);


FGV.prices <- FGV.PRICES.ROWDATA[, "price", drop = FALSE]
rownames(FGV.prices) = FGV.PRICES.ROWDATA$time
FGV.volumes <- FGV.PRICES.ROWDATA[, "volume", drop = FALSE]
rownames(FGV.volumes) = FGV.PRICES.ROWDATA$time
FGV.ASM <- cbind(FGV.prices, FGV.volumes)
FGV.ASM <- as.xts(FGV.ASM)

FGV.EXO <- FGV.EXOPRICES.ROWDATA[, "value", drop = FALSE]
rownames(FGV.EXO) = FGV.EXOPRICES.ROWDATA$simulation_time
FGV.EXO <- as.xts(FGV.EXO)

plot(FGV.EXO, type='l',xlab="tempo", ylab="preco"
     , main="Precos exogenos");

FGV <-merge(FGV.EXO$value, FGV.ASM$price,  all = TRUE)
plot(FGV, type='l',xlab="tempo", ylab="preco"
     , main="Precos EXO e ASM");
