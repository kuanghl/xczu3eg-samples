# xilinx_mpsoc_zcu102

#### 介绍
xilinx MPSoC  ZCU102开发板BSP (包括kernel、rootfs、devicetree、boot.bin制作、petalinux等）



#### 开发环境
1.  petalinux 2018.3
2.  xilinx SDK2018.3


#### 目录说明
backup/			备份目录
fpga2bin/       将fpga.bit文件转为*.bit.bin文件
bootgen/        制作boot.bin

kernel/         linux内核
deviceTree/		设备树
rootfs/			根文件系统
kenerlgen/      合并（kernel，devicetree，rootfs）成一个image.ub文件

uboot/			u-boot
gdb/            调试工具gdb

sd_card/        SD卡运行环境


