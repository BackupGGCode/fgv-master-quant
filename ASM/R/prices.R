fgvPrice <- read.table("/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/R/prices.csv");
fgvPrice <- data.matrix(fgvPrice);

fgvReturn <- diff(log(fgvPrice));
hist(fgvReturn)

fgvPrice <- read.table("/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/R/prices_with_MM.csv");

clipboard_prices <- readClipboard()