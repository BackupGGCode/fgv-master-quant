fgvPrice <- read.table("/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/R/prices.csv");
fgvPrice <- data.matrix(fgvPrice);
fgvReturn <- diff(log(fgvPrice));
hist(fgvReturn)


