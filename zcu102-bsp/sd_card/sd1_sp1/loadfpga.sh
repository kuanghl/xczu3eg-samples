#!/bin/sh

mkdir -p /lib/firmware
cp -f  fpga.bit.bin  /lib/firmware

echo   "load fpga.bin..."
echo   0 > /sys/class/fpga_manager/fpga0/flags
echo  fpga.bit.bin > /sys/class/fpga_manager/fpga0/firmware
echo   "load fpga.bin... ok"


