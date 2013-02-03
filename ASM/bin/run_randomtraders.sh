#!/bin/sh
if [ "$1" == "start" ]
then
	./randomtraders cfg/randomtraders01.fixcfg cfg/randomtraders01.stycfg &
	./randomtraders cfg/randomtraders02.fixcfg cfg/randomtraders02.stycfg &
	./randomtraders cfg/randomtraders03.fixcfg cfg/randomtraders03.stycfg &
	./randomtraders cfg/randomtraders04.fixcfg cfg/randomtraders04.stycfg &
	./randomtraders cfg/randomtraders05.fixcfg cfg/randomtraders05.stycfg &
fi

if [ "$1" == "stop" ]
then
	kill `ps -A | grep lt-randomtrader`
fi
