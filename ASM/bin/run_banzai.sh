#!/bin/sh
rm -rf store/FIX.4.2*
JAR=./jar

RUN_CLASSPATH=$JAR/mina-core-1.1.7.jar:$JAR/slf4j-api-1.6.3.jar:$JAR/slf4j-jdk14-1.6.3.jar:$JAR/quickfixj-all-1.0.jar:$JAR/quickfixj-core-1.0.jar:$JAR/quickfixj-msg-fix44-1.0.jar:$JAR/quickfixj-examples-1.0.jar

java -classpath "$RUN_CLASSPATH" quickfix.examples.banzai.Banzai cfg/banzai.cfg
