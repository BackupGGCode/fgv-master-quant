#!/bin/sh
BINPATH=/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/ordermatch
if [ "$1" == "start" ]
then
	$BINPATH/ordermatch ORDERMATCH &
fi

if [ "$1" == "stop" ]
then
	pkill -f ORDERMATCH
fi

if [ "$1" == "status" ]
then
	REPONSE=$(pgrep -lf ORDERMATCH)
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
