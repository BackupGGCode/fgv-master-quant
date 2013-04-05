testnumber <- commandArgs(TRUE);

imgDir <-"../trials/";

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
plot(FGV.ccret,type='l',col="darkblue", main='Retornos', xlab="tempo",ylab="log-retorno");
garbage <- dev.off();

# grafico histograma de log-retornos
graphHistogramRt <- paste0(imgDir,"test",testnumber,"_graphHistogramRt",".png");
png(filename = graphHistogramRt, width = 600, height = 400, units = "px");
hist(FGV.ccret, 
     col="lightblue",
     xlab="retornos",
     probability = TRUE,
     ylab="densidade",
     main="Histograma dos log-retornos");
curve(dnorm(x, mean=mean(FGV.ccret), sd=sd(FGV.ccret)), add=TRUE, col="darkblue", lwd=2);
garbage <- dev.off();

graphAcf <- paste0(imgDir,"test",testnumber,"_acf",".png");
png(filename = graphAcf, width = 600, height = 400, units = "px");
acf(FGV.ccret,type="correlation",lag=10);
garbage <- dev.off();

#estatisticas 
#basicStats(FGV.PRICESVOLUMES)
#retornos<-FGV.ccret;
#basicStats(retornos)

mean_price <- mean(FGV.PRICESVOLUMES[,1]);
sd_price <- sd(FGV.PRICESVOLUMES[,1]);
skewness_price <- skewness(FGV.PRICESVOLUMES[,1]);
kurtosis_price <- kurtosis(FGV.PRICESVOLUMES[,1]);

mean_volume <- mean(FGV.PRICESVOLUMES[,2]);
sd_volume <- sd(FGV.PRICESVOLUMES[,2]);
skewness_volume <- skewness(FGV.PRICESVOLUMES[,2]);
kurtosis_volume <- kurtosis(FGV.PRICESVOLUMES[,2]);

mean_return <- mean(FGV.ccret);
sd_return <- sd(FGV.ccret);
skewness_return <- skewness(FGV.ccret);
kurtosis_return <- kurtosis(FGV.ccret);

output <- paste("<table width='500'>",
                 "<tr><td>",
                  "<b> Preços </b><br>",
                 "Mean: "     ,sprintf("%.3f",mean_price),"<br>",
                 "Std dev: " ,sprintf("%.3f",sd_price),"<br>",
                 "Kurtosis: " ,sprintf("%.3f",kurtosis_price),"<br>",
                 "Skewness: " ,sprintf("%.3f",skewness_price),"<br>",
                  "</td>",
                "<td>",
                "<b> Log-Retorno </b><br>",
                "Mean: "     ,sprintf("%.3f",mean_return),"<br>",
                "Std dev: " ,sprintf("%.3f",sd_return),"<br>",
                "Kurtosis: " ,sprintf("%.3f",kurtosis_return),"<br>",
                "Skewness: " ,sprintf("%.3f",skewness_return),"<br>",
                "</td>",
                "<td>",
                "<b> Volume </b><br>",
                "Mean: "     ,sprintf("%.3f",mean_volume),"<br>",
                "Std dev: " ,sprintf("%.3f",sd_volume),"<br>",
                "Kurtosis: " ,sprintf("%.3f",kurtosis_volume),"<br>",
                "Skewness: " ,sprintf("%.3f",skewness_volume),"<br>",
                "</td>",
                "</tr>",
                 "</table><br>");

cat(output);



