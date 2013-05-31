testnumber<-8192

filename<-paste0("./data/budget/test",testnumber,"_prices",".csv")

library(quantmod)
library(fBasics)

# reading CSV file ...
FGV.PRICES.ROWDATA <- read.csv(filename)

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
FGV.ccret = log(1 + FGV.rt)


# grafico de preços e volumes de negociaçao
chartSeries(FGV.PRICESVOLUMES,theme='white')

# grafico de log-retornos
#plot(FGV.ccret,type='l',col="darkblue", main='Retornos', xlab="tempo",ylab="log-retorno");

# grafico histograma de log-retornos
hist(FGV.ccret, 
     col="lightblue",
     xlab="retornos",
     probability = TRUE,
     ylab="densidade",
     main="Histograma dos log-retornos")
curve(dnorm(x, mean=mean(FGV.ccret), sd=sd(FGV.ccret)), add=TRUE, col="darkblue", lwd=2)

acf(FGV.ccret,type="correlation",lag=10)


library(urca)
ur <- ur.df(y = FGV.PRICESVOLUMES[,1], type = "none",lags = 10,  selectlags = "BIC")
ur@testreg
summary(ur)



mean_volume <- mean(FGV.PRICESVOLUMES[,2]);
sd_volume <- sd(FGV.PRICESVOLUMES[,2]);
skewness_volume <- skewness(FGV.PRICESVOLUMES[,2]);
kurtosis_volume <- kurtosis(FGV.PRICESVOLUMES[,2]);



mean_return <- mean(FGV.ccret)
sd_return <- sd(FGV.ccret)
skewness_return <- skewness(FGV.ccret)
kurtosis_return <- kurtosis(FGV.ccret)
