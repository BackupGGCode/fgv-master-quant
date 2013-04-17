testnumber <- commandArgs(TRUE);

imgDir <-"./";

library(RMySQL);
library(quantmod);
library(fBasics);

# connecting to DB ...
con <- dbConnect(MySQL(),user="quickfix", password="quickfix",dbname="quickfix", host="localhost");
on.exit(dbDisconnect(con));

FGV.PRICES.ROWDATA <- dbGetQuery(con, paste("SELECT time, price, volume FROM quickfix.prices"));

FGV.prices <- FGV.PRICES.ROWDATA[, "price", drop = FALSE];
rownames(FGV.prices) = FGV.PRICES.ROWDATA$time;
FGV.volumes <- FGV.PRICES.ROWDATA[, "volume", drop = FALSE];
rownames(FGV.volumes) = FGV.PRICES.ROWDATA$time;
FGV.PRICESVOLUMES <- cbind(FGV.prices, FGV.volumes);
FGV.PRICESVOLUMES <- as.xts(FGV.PRICESVOLUMES);

FGV.prices.rows = nrow(FGV.prices); 
# retorno simples ...
FGV.rt = (FGV.prices[2:FGV.prices.rows, 1] - FGV.prices[1:(FGV.prices.rows - 1), 1])/FGV.prices[1:(FGV.prices.rows - 1), 1];
names(FGV.rt) = rownames(FGV.prices)[2:FGV.prices.rows] ;
#summary(FGV.rt)
# retorno composto continuo
FGV.ccret = log(1 + FGV.rt);


# grafico de preços e volumes de negociaçao
graphPriceVolume <- paste0(imgDir,"test",testnumber,"_graphPriceVolume",".png");
png(filename = graphPriceVolume, width = 1200, height = 500, units = "px");
chartSeries(FGV.PRICESVOLUMES,theme='white');
garbage <- dev.off();

# grafico de log-retornos
graphRt <- paste0(imgDir,"test",testnumber,"_graphRt",".png");
png(filename = graphRt, width = 600, height = 400, units = "px");
plot(FGV.ccret,type='l',col="darkblue", main='Log-retornos', xlab="tempo",ylab="% retorno");
garbage <- dev.off();


# grafico histograma de log-retornos
graphHistogramRt <- paste0(imgDir,"test",testnumber,"_graphHistogramRt",".png");
png(filename = graphHistogramRt, width = 600, height = 400, units = "px");
hist(FGV.ccret, 
     col="lightblue",
     xlab="retornos",
     probability = TRUE,
     ylab="densidade",
     main="Histograma dos Log-retornos");
curve(dnorm(x, mean=mean(FGV.ccret), sd=sd(FGV.ccret)), add=TRUE, col="darkblue", lwd=2);
garbage <- dev.off();

#estatisticas 
#basicStats(FGV.PRICESVOLUMES)
#retornos<-FGV.ccret;
#basicStats(retornos)





