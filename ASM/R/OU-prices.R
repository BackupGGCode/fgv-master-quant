library("chron");
library("RMySQL");

# parametros a taxa com reversao a media
TEMPO_INICIO<-chron(times="00:00:00");
TEMPO_FIM<-chron(times="00:10:00");
DELTA_TEMPO <- seq(TEMPO_INICIO , TEMPO_FIM , by = times("00:00:01"));
TEMPO_TOTAL <- length(DELTA_TEMPO);
NUM_PONTOS <-length(DELTA_TEMPO);

MEDIA_GLOBAL=100.0;
LAMBDA=0.005;# teste 1
#LAMBDA=0.005;# teste 2
SIGMA=0.0005;# teste 1
#SIGMA=1;# teste 2
MEDIA_INICIAL=100.0;


# connecting to DB ...
con <- dbConnect(MySQL(),user="quickfix", password="quickfix",dbname="quickfix", host="localhost");
on.exit(dbDisconnect(con));
#The code of Euler Maruyama simulation method
ornstein_uhlenbeck <- function(T,n,nu,lambda,sigma,x0){
  dw  <- rnorm(n, 0, sqrt(T/n))
  dt  <- T/n
  x <- c(x0)
  for (i in 2:(n+1)) {
    x[i]  <-  x[i-1] + lambda*(nu-x[i-1])*dt + sigma*dw[i-1];
    #if(x[i] < 0)x[i] <-0;
  }
  return(x);
}


reta <- function(n,const,coef){
  y <- c(const);
  for (i in 2:(n+1)) {
    y[i]  <-  y[i-1] + coef;
    if(y[i] < 0)y[i] <-0;
  }
  return(y);
}

#x<- ornstein_uhlenbeck(TEMPO_TOTAL,NUM_PONTOS,MEDIA_GLOBAL,LAMBDA,SIGMA,MEDIA_INICIAL);
#plot(x,type="l", xlab="tempo", ylab="preço",col="red");

#x<- reta(NUM_PONTOS,MEDIA_INICIAL,+0.25);
x<- reta(NUM_PONTOS,MEDIA_INICIAL,+0.25);
#x<- reta(NUM_PONTOS,MEDIA_INICIAL,+0.5);
#x<- reta(NUM_PONTOS,MEDIA_INICIAL,0.0);
plot(x,type="l", xlab="tempo", ylab="preço");



res<-dbSendQuery(con, "DELETE FROM exogenous WHERE time >= '00:00:00'");

for(i in 1:length(x)){
  sql <- sprintf("INSERT INTO exogenous (time, value) VALUES ('%s', %f)",DELTA_TEMPO[i], x[i]);
  rs <- dbSendQuery(con, sql);
}

dbClearResult(rs);
dbDisconnect(con);