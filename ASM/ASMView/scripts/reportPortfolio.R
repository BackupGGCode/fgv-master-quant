library(RMySQL);
library(quantmod);
#library(fBasics);

# connecting to DB ...
con <- dbConnect(MySQL(),user="quickfix", password="quickfix",dbname="quickfix", host="localhost");
on.exit(dbDisconnect(con));

PORTFOLIO.ROWDATA <- dbGetQuery(con, paste("SELECT id_agent, time, number_stock, cash FROM quickfix.portfolio where id_agent='MARKETMAKER'"));


PORTFOLIO.NSTOCK <- PORTFOLIO.ROWDATA[, "number_stock", drop = FALSE];
rownames(PORTFOLIO.NSTOCK) = PORTFOLIO.ROWDATA$time;

PORTFOLIO.CASH <- PORTFOLIO.ROWDATA[, "cash", drop = FALSE];
rownames(PORTFOLIO.CASH) = PORTFOLIO.CASH$time;


PORTFOLIO<- cbind(PORTFOLIO.NSTOCK, PORTFOLIO.CASH);
PORTFOLIO.CASH <- as.xts(PORTFOLIO.CASH);

plot(PORTFOLIO.CASH)