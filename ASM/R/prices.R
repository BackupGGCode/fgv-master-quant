fgvPrice <- read.table("/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/R/prices.csv");
fgvPrice <- data.matrix(fgvPrice);

fgvReturn <- diff(log(fgvPrice));
hist(fgvReturn)




library(quantmod)
library(RMySQL)
con <- dbConnect(MySQL(), user="quickfix", password="quickfix", dbname="quickfix", host="localhost")
# EXOGENOUS
exo_data <- dbGetQuery(con, paste("SELECT simulation_time as time, value as 'EXO.Close' FROM quickfix.exogenous"))
exo_data$time <-as.Date(exo_data$time, format="%Y-%m-%d %h:%m:%s")
EXO <- as.xts(exo_data[,-1], order.by=exo_data$time)
barChart(EXO)
