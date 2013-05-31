library(quantmod)
png(filename = "./figure/bb.png", width = 700, height = 600, units = "px");
getSymbols('ITUB4.SA', from="2013-01-01", to="2013-03-30", src='yahoo');
barChart(ITUB4.SA,,theme='white');
addBBands();
dev.off();

