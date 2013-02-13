#!/bin/sh
echo "running $1 agent ..."

BINPATH=/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/bin

$BINPATH/randomtraders $1 &
