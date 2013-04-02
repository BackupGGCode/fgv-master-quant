#!/bin/sh
BINPATH=/storage/data/projetos/artificial-market/quickfix-1.13.3/ASM/mvtraders
if [ "$1" == "start" ]
then
	$BINPATH/mvtraders $2 &
fi

if [ "$1" == "stop" ]
then
	pkill -f $2
fi

if [ "$1" == "status" ]
then
	REPONSE=$(pgrep -lf "mvtraders $2")
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
	REPONSE=$(pgrep -lf "mvtraders $2")
	#echo $REPONSE

        if [ "$REPONSE" == "" ]
        then
		#echo "STOPPED"
                $BINPATH/mvtraders $2 &
        else
		#echo "STARTED"
                pkill -f $2
        fi
fi
