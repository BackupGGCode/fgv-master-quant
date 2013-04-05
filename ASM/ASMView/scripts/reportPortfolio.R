testnumber <- commandArgs(TRUE);

imgDir <-"../trials/";

library(RMySQL);


# connecting to DB ...
con <- dbConnect(MySQL(),user="quickfix", password="quickfix",dbname="quickfix", host="localhost");
on.exit(dbDisconnect(con));

PORTFOLIO.ROWDATA <- dbGetQuery(con, paste("SELECT id_agent, time, number_stock, cash FROM quickfix.portfolio"));