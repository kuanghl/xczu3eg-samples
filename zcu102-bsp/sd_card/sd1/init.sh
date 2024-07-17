#!/bin/sh

echo " `pwd`/init.sh "

modprobe  jimu_mem.ko

ifconfig eth0 192.168.1.240
