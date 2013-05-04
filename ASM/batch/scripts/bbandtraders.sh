#!/bin/sh
BINPATH=/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/bbandtraders
if [ "$1" == "start" ]
then
	$BINPATH/bbandtraders $2 &
fi

if [ "$1" == "stop" ]
then
	pkill -f $2
fi

if [ "$1" == "status" ]
then
	REPONSE=$(pgrep -lf "bbandtraders $2")
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

if [ "$1" == "change" ]
then
	REPONSE=$(pgrep -lf "bbandtraders $2")
	#echo $REPONSE

        if [ "$REPONSE" == "" ]
        then
		#echo "STOPPED"
                $BINPATH/bbandtraders $2 &
        else
		#echo "STARTED"
                pkill -f $2
        fi
fi
