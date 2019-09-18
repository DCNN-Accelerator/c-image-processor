#!/bin/bash

SERIALSOURCE=/dev/ttyUSB0
BAUDRATES=(B9600 B19200 B38400 B57600 B115200)

for i int "${BAUDRATES[@]}"
do
    ./uart_diagnostic($SERIALSOURCE, $i)
done 