#!/bin/bash
rm -rf store/FIX.4.2-CLIENT*
CFG_FILE="banzai.cfg"
LIB_DIR="./jar"
CP="$LIB_DIR/quickfixj-all-1.4.0.jar:$LIB_DIR/junit.jar:$LIB_DIR/log4j.jar:$LIB_DIR/banzai.jar:$LIB_DIR/slf4j-api-1.5.3.jar:$LIB_DIR/slf4j-jdk14-1.5.3.jar:$LIB_DIR/mina-core-1.0.3.jar:$LIB_DIR/bp-util-concurrent-3.0.jar:."
APP="Banzai"
 
java -Djava.library.path=$LIB_DIR -classpath "$CP" "$APP" "$CFG_FILE"
