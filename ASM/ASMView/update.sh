#!/bin/sh
DESTINATION=/var/www/html

rm $DESTINATION/*.php
cp *.php $DESTINATION
rm -rf $DESTINATION/scripts
cp -r scripts $DESTINATION
