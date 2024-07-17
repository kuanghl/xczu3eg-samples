#!/bin/sh

--------------------------------------------------------------------------------
--    zynq7000编译项                                                          --
--------------------------------------------------------------------------------

export ARCH=arm 
export CROSS_COMPILE=arm-linux-gnueabihf-

#//make distclean
#//make clean
#//make xilinx_zynq_defconfig

make  menuconfig

make -j2 LOADADDR=0x00008000   uImage
make -j2                       modules

mkdir -p `pwd`/../out
make  modules_install  INSTALL_MOD_PATH=`pwd`/../out
make  install          INSTALL_PATH=`pwd`/../out
cp -f  `pwd`/arch/arm/boot/uImage    `pwd`/../out
cp -f  `pwd`/arch/arm/boot/uImage    /tftpboot/



--------------------------------------------------------------------------------
--    MPSoc编译项                                                             --
--------------------------------------------------------------------------------

export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-

#//make distclean
#//make clean
#//make xilinx_zynqmp_defconfig
make  menuconfig

make -j2

mkdir -p `pwd`/../out
make  modules_install  INSTALL_MOD_PATH=`pwd`/../out
make  install          INSTALL_PATH=`pwd`/../out
cp -f  `pwd`/arch/arm64/boot/Image.gz   `pwd`/../out




#mkimage -A arm64 -O linux -T kernel -C gzip -a 0x00080000 -e 0x00080000 -n uImage -d `pwd`/../out/Image.gz `pwd`/../out/uImage
mkimage -f fitimage.its  image.ub





