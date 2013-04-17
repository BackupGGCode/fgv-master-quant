
testnumber <- "002";

workdirectory<-"/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/R";
pricesfilename <- paste0("./test",testnumber,"_prices.csv");
portfoliofilename <- paste0("./test",testnumber,"_portfolio.csv");


setwd(workdirectory);
FGV.df <- read.csv(pricesfilename,header = TRUE, stringsAsFactors = FALSE);
#class(FGV.df)
#str(FGV.df)
head(FGV.df);

fgvPrices.df = FGV.df[, "price", drop = FALSE];
summary(fgvPrices.df)
rownames(fgvPrices.df) = FGV.df$time;
fgvVolumes.df = FGV.df[, "volume", drop = FALSE];
summary(fgvVolumes.df)
rownames(fgvVolumes.df) = FGV.df$time;
FGV <- cbind(fgvPrices.df, fgvVolumes.df);

library(quantmod);
FGV <- as.xts(FGV);

png(filename = "testprecos.png",width = 650, height = 450, units = "px");
chartSeries(FGV,theme='white')
dev.off()

n = nrow(fgvPrices.df);  # number of rows
# retorno simples ...
FGV.ret = (fgvPrices.df[2:n, 1] - fgvPrices.df[1:(n - 1), 1])/fgvPrices.df[1:(n - 1), 1];
names(FGV.ret) = rownames(fgvPrices.df)[2:n] ;
summary(FGV.ret)

#head(FGV.ret)
# retorno composto continuo
FGV.ccret = log(1 + FGV.ret)
#names(FGV.ccret) = rownames(fgvPrices.df)[2:n]
#tail(FGV.ccret)
#summary(FGV.ccret)
png(filename = "testretornos.png",width = 650, height = 450, units = "px");
hist(FGV.ccret, 
     col="lightblue",
     xlab="retornos",
     probability = TRUE,
     ylab="densidade",
     main="Histograma dos Log-retornos")
curve(dnorm(x, mean=mean(FGV.ccret), sd=sd(FGV.ccret)), add=TRUE, col="darkblue", lwd=2) 
dev.off()

png(filename = "testretornos.png",width = 650, height = 450, units = "px");
plot(FGV.ccret,type='l',col="darkblue", main='Log-retornos', xlab="tempo",ylab="% retorno");
dev.off()

#library("fBasics")
library("moments")
mean(FGV.ret)
var(FGV.ret)
skewness(FGV.ret)
kurtosis(FGV.ret)

basicStats(FGV.ret)

t.test(FGV.ret)
normalTest(FGV.ret,method='jb')

library(timeSeries)
acf(fgvPrices.df,lag=15)
m1=acf(fgvPrices.df,lag=15)
names(m1)


m2=pacf(fgvPrices.df,lag=10)
names(m2)
m2$acf

Box.test(fgvPrices.df,lag=10)
Box.test(fgvPrices.df,lag=10,type='Ljung')

