#!/bin/sh
echo "stopping agents..."
kill `ps -A | grep lt-randomtrader`
