#!/bin/sh


export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-
export TOPDIR=`pwd`

#// 1. copy  .config
#make   distclean
#make   xilinx_zynqmp_zcu102_rev1_0_defconfig

make menuconfig

make

#// 4. 复制备份
mkdir -p        ../out
cp u-boot.elf  ../out/u-boot-build`date +%F`.elf
cp .config      ../out/config`date +%F`


