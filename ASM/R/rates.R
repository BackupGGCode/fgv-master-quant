library("chron");
library("RMySQL");

# parametros a taxa com reversao a media
TEMPO_INICIO<-chron(times="00:00:00");
TEMPO_FIM<-chron(times="01:00:00");
DELTA_TEMPO <- seq(TEMPO_INICIO , TEMPO_FIM , by = times("00:00:01"));
TEMPO_TOTAL <- length(DELTA_TEMPO);
NUM_PONTOS <-length(DELTA_TEMPO);

MEDIA_GLOBAL=8;
LAMBDA=0.001;
SIGMA=0.001;
MEDIA_INICIAL=8;


# connecting to DB ...
con <- dbConnect(MySQL(),user="quickfix", password="quickfix",dbname="quickfix", host="localhost");
on.exit(dbDisconnect(con));
#The code of Euler Maruyama simulation method
ornstein_uhlenbeck <- function(T,n,nu,lambda,sigma,x0){
  dw  <- rnorm(n, 0, sqrt(T/n))
  dt  <- T/n
  x <- c(x0)
  for (i in 2:(n+1)) {
    x[i]  <-  x[i-1] + lambda*(nu-x[i-1])*dt + sigma*dw[i-1]
  }
  return(x);
}

x<- ornstein_uhlenbeck(TEMPO_TOTAL,NUM_PONTOS,MEDIA_GLOBAL,LAMBDA,SIGMA,MEDIA_INICIAL);
plot(x,type="l");



res<-dbSendQuery(con, "DELETE FROM rates WHERE time >= '00:00:00'");

for(i in 1:length(x)){
  sql <- sprintf("INSERT INTO rates (time, rate) VALUES ('%s', %f)",DELTA_TEMPO[i], x[i]);
  rs <- dbSendQuery(con, sql);
}

dbClearResult(rs);
dbDisconnect(con);