
export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-

#ccflags-y := -std=gnu99 -Wno-declaration-after-statement  -Wno-unused
ccflags-y := -std=gnu99 -Wno-declaration-after-statement  -Wno-unused-function  -Wno-unused-variable 
ccflags-y += -Wno-date-time -Wno-date-time


SRC_PATH := $(shell pwd)

#// linux kernel路径
# KERNEL_PATH := $(SRC_PATH)/../../linux-xlnx-xilinx-v2017.4sp3
KERNEL_PATH := $(SRC_PATH)/../../linux-xlnx-xilinx-v2018.3sp1

#// 模块名称 MODULE_NAME.ko
MODULE_NAME	      =  jimu_mem
obj-m      	     +=  $(MODULE_NAME).o 


#// 添加源文件
$(MODULE_NAME)-objs   :=  xlnk_mem.o 
#$(MODULE_NAME)-objs  +=  xxxx.o 



build:
	make -C $(KERNEL_PATH) M=$(SRC_PATH)  modules



clean:
	#make -C $(KERNEL_PATH)  M=$(SRC_PATH) clean
	rm   -f  *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm   -f  Module.markers Module.symvers modules.order
	rm   -rf .tmp_versions Modules.symvers


all: clean  build


modules_install:
	$(MAKE) -C $(KERNEL_PATH) M=$(SRC_PATH) modules_install  INSTALL_MOD_PATH=$(KERNEL_PATH)/../out


help:
	@echo "usage:"
	@echo " make"
	@echo " make clean"
	@echo " make all"
	@echo " make modules_install"
	
