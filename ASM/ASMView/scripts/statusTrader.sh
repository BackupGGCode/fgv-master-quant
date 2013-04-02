#!/bin/sh
REPONSE=$(ps -ef | grep "$1" | grep -v $$ | grep -v grep)
#echo $REPONSE

if [ "$REPONSE" == "" ]
then
	echo "STOPPED"
        exit 1
else
	echo "STARTED"
        exit 0
fi
