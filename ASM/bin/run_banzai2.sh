#!/bin/bash
LIB_DIR="../../lib/jar"
CP="$LIB_DIR/quickfixj-all-1.4.0.jar:$LIB_DIR/junit.jar:$LIB_DIR/log4j.jar:$LIB_DIR/banzai.jar"
APP="Banzai"
CFG_FILE="cfg/banzai.cfg"

java -Djava.library.path=$LIB_DIR -classpath "$CP" "$APP" "$CFG_FILE" 
