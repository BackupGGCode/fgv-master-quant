library(fBasics);
library(quantmod);

TESTE<-c("CRESCENTE","DECRESCENTE");
#TESTE<-c("CRESCENTE","CONSTANTE","DECRESCENTE");
#TESTE<-c("CRESCENTE");

nTIPO<-1;
EXO.TIPOS <-data.frame(teste=c(1:50));

while (nTIPO <= 2){
    lcoef <-c();
    nTESTE<-1;
    while (nTESTE <= 50){
      filename<-paste0("./data/MV6/test_MV6_",TESTE[nTIPO],"",nTESTE,"_prices",".csv");
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
    COEFICIENTES <- data.frame(lcoef);
    colnames(COEFICIENTES) <- TESTE[nTIPO];
    EXO.TIPOS <-data.frame(EXO.TIPOS, COEFICIENTES);
    nTIPO<-nTIPO+1;
}

write.csv(EXO.TIPOS, file = "./data/MV6/test_MV6_summary.csv", sep = " ",
          eol = "\n", na = "NA", dec = ",", row.names = TRUE,
          col.names = TRUE, qmethod = c("escape", "double"),fileEncoding = "")