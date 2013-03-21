#!/bin/sh
if [ "$1" == "start" ]
then
	./randomtraders RANDTRADER01 &
fi

if [ "$1" == "stop" ]
then
	kill `ps -A | grep lt-randomtrader`
fi
