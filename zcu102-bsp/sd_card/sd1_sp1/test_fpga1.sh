#!/bin/sh

mkdir -p /lib/firmware
echo  0 > /sys/class/fpga_manager/fpga0/flags
cp -f  fpga.bit.bin  /lib/firmware


CNTS=0
while true
do
    echo   "load fpga.bin..."
	echo  fpga.bit.bin > /sys/class/fpga_manager/fpga0/firmware
    echo   "load fpga.bin... ok"

    CNTS=$((++CNTS))
    echo "--total=${CNTS}"

    sleep  1
done

