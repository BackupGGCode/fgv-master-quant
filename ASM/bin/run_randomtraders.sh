#!/bin/sh
if [ "$1" == "start" ]
then
	./randomtraders RANDTRADER01 &
	./randomtraders RANDTRADER02 &
	./randomtraders RANDTRADER03 &
	./randomtraders RANDTRADER04 &
	./randomtraders RANDTRADER05 &
	./randomtraders RANDTRADER06 &
	./randomtraders RANDTRADER07 &
	./randomtraders RANDTRADER08 &
	./randomtraders RANDTRADER09 &
	./randomtraders RANDTRADER10 &
	./randomtraders RANDTRADER11 &
	./randomtraders RANDTRADER12 &
	./randomtraders RANDTRADER13 &
	./randomtraders RANDTRADER14 &
	./randomtraders RANDTRADER15 &

fi

if [ "$1" == "stop" ]
then
	kill `ps -A | grep lt-randomtrader`
fi
