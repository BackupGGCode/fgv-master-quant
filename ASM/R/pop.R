library(fBasics);
library(quantmod);

TESTE<-"HORIZONTAL";
nTESTE<-1;
lcoef <-c();


while (nTESTE <= 50){
 
    filename<-paste0("./data/MV150/test_MV_",TESTE,"",nTESTE,"_prices",".csv");
    FGV.PRICES.ROWDATA <- read.csv(filename);
  
    #############################################################
    FGV.prices <- FGV.PRICES.ROWDATA[, "price", drop = FALSE];
    rownames(FGV.prices) = FGV.PRICES.ROWDATA$time;
    #############################################################
    rows<-1:nrow(FGV.prices);
    tendencia <- lm( FGV.prices[,1] ~ rows);
    coef<-tendencia$coefficients[2]; #inclinacao
    #plot(FGV.prices[,1], type="l",xlab="tempo", ylab="preços",main="Preços");
    #abline(tendencia, lwd=2, col="blue", lty=3);  
  
    lcoef <- c(lcoef, coef);
    nTESTE<-nTESTE+1;

}
mydata <- data.frame(lcoef);