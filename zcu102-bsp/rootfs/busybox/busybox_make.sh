#!/bin/sh

--------------------------------------------------------------------------------
--    zynq7000编译项                                                          --
--------------------------------------------------------------------------------
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-

make   menuconfig

make   busybox  V=1

#// 4. 安装,复制
INSTALL_DIR=../output`date +%F`
mkdir -p          ${INSTALL_DIR}
cp    -f .config  ${INSTALL_DIR}/config`date +%F`
make   install
mv    -f ./_install   ${INSTALL_DIR}




--------------------------------------------------------------------------------
--    MPSoc编译项                                                             --
--------------------------------------------------------------------------------

export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-

make   menuconfig

make   busybox  V=1

#// 4. 安装,复制
INSTALL_DIR=../output`date +%F`
mkdir -p          ${INSTALL_DIR}
cp    -f .config  ${INSTALL_DIR}/config`date +%F`
make   install
mv    -f ./_install   ${INSTALL_DIR}



