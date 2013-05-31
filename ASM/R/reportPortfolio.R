#testnumber <- commandArgs(TRUE);
#imgDir <-"../trials/";

#HOSTAME<-"localhost";
HOSTAME<-"musashi.servebeer.com:33306";

library(RMySQL);


# connecting to DB ...
con <- dbConnect(MySQL(),user="quickfix", password="quickfix",dbname="quickfix", host=HOSTAME);
on.exit(dbDisconnect(con));

PORTFOLIO.ROWDATA <- dbGetQuery(con, paste("SELECT id_agent, time, number_stock, cash FROM quickfix.portfolio"));