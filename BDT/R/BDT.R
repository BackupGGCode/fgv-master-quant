# ------------------------------------------------------------------------------

BinomialTreePlot = 
  function(BinomialTreeValues, dx = -0.025, dy = 0.4, cex = 1, digits = 4, ...){         
    
    # Tree:
    Tree = round(BinomialTreeValues, digits = digits)
    depth = ncol(Tree)
    plot(x = c(1,depth), y = c(-depth+1, depth-1), type = "n", col = 0, ...)
    points(x = 1, y = 0)
    text(1+dx, 0+dy, deparse(Tree[1, 1]), cex = cex)
    for (i in 1:(depth-1) ) {
      y = seq(from = -i, by = 2, length = i+1)
      x = rep(i, times = length(y))+1
      points(x, y, col = 1) 
      for (j in 1:length(x))
        text(x[j]+dx, y[j]+dy, deparse(Tree[length(x)+1-j,i+1]), cex = cex)   
      y = (-i):i
      x = rep(c(i+1,i), times = 2*i)[1:length(y)]
      lines(x, y, col = 2)
    }
    invisible()
  }

# ------------------------------------------------------------------------------
input <- read.delim("/storage/data/R/bdt_short_rate.in", header=F)
BinomialTreePlot(input,dy = 0.4,cex = 0.9,ylim = c(-4, 4),xlab = "n",ylab = "rate")
title(main = "Short Rate Tree")
# ------------------------------------------------------------------------------
