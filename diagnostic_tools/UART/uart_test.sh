#!/bin/sh

echo "resetting permissions to USB port"
sudo chmod o+rw /dev/ttyUSB1

echo "setting speed and flow control"
stty 9600 -cread cs8 < /dev/ttyUSB1

echo "sending message to FPGA"
echo "t" > /dev/ttyUSB1

#sleep 1

echo "waiting to hear back from FPGA"
cat -v < /dev/ttyUSB1