# !/bin/bash
#$1: file to receive readings from teensy
# May register as a different device on your system. Use dmesg when you plug in teensy to find out which one it is

 
while [ true ]
do

cat /dev/ttyACM0 > $1

done
