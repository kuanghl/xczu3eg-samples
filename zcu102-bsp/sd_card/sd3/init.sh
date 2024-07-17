#!/bin/sh

echo "++ $0 "

insmod  ./ko/jimu_mem.ko

#// load fpga
if [ -f fpga.bit.bin ]; then
	mkdir  -p /lib/firmware
	cp -f  fpga.bit.bin  /lib/firmware
	echo   "load fpga.bin..."
	echo   0 > /sys/class/fpga_manager/fpga0/flags
	echo   fpga.bit.bin > /sys/class/fpga_manager/fpga0/firmware
	echo   "load fpga.bin... OK"
else
	echo   "not Find fpga.bit.bin"
fi


ifconfig eth0 192.168.0.119


