#!/bin/sh
echo "running $1 agent ...."

BINPATH=/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/randomtraders

$BINPATH/randomtraders $1
