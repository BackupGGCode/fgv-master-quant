#!/bin/sh
BINPATH=/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/marketmaker
if [ "$1" == "start" ]
then
	$BINPATH/marketmaker MARKETMAKER &
fi

if [ "$1" == "stop" ]
then
	pkill -f MARKETMAKER
fi

if [ "$1" == "status" ]
then
	REPONSE=$(pgrep -lf MARKETMAKER)
	#echo $REPONSE

        if [ "$REPONSE" == "" ]
        then
		echo "STOPPED"
                exit 1
        else
		echo "STARTED"
                exit 0
        fi
fi
