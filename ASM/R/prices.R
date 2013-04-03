#
#
# dicas: http://msenux.redwoods.edu/math/R/hist.php
# http://www.r-bloggers.com/basics-of-histograms/
#
#
setwd("/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/R")

FGV.df <- read.csv("./test002_prices.csv",header = TRUE, stringsAsFactors = FALSE);
class(FGV.df)

str(FGV.df)
head(FGV.df)

fgvPrices.df = FGV.df[, "price", drop = FALSE]
rownames(fgvPrices.df) = FGV.df$time
head(fgvPrices.df)

n = nrow(fgvPrices.df)  # number of rows
# retorno simples ...
FGV.ret = (fgvPrices.df[2:n, 1] - fgvPrices.df[1:(n - 1), 1])/fgvPrices.df[1:(n - 1), 1];
head(FGV.ret)
# retorno composto continuo
FGV.ccret = log(1 + FGV.ret)
names(FGV.ccret) = rownames(fgvPrices.df)[2:n]
tail(FGV.ccret)
summary(FGV.ccret)

#hist(FGV.ccret)
hist(FGV.ret, 
     col="lightblue",
     xlab="retornos",
     freq=FALSE,
     ylab="densidade",
     #ylab="frequencia",
     main="Histograma dos retornos")

curve(dnorm(x, mean=mean(FGV.ret), sd=sd(FGV.ret)), add=TRUE, col="darkblue", lwd=2) 

library("moments")
kurtosis(FGV.ret)
