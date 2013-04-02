#!/bin/sh
DESTINATION=/var/www/html

rm $DESTINATION/*.php
cp *.php $DESTINATION
cp -r spec $DESTINATION
rm -rf $DESTINATION/scripts
cp -r scripts $DESTINATION
rm -rf $DESTINATION/img
cp -r img $DESTINATION

