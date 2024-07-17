#!/bin/sh
#//============================================================== 
#//制作 initramfs 根文件系统  (cpio)
#//============================================================== 

#//1. 解压 rootfs.cpio.gz 根文件系统
export fs_path=rootfs.cpio
export entry_path=`pwd`
rm     -r ${fs_path}/*
mkdir  -p ${fs_path}/
gunzip -c ${fs_path}.gz | sh -c 'cd ${fs_path}/ && cpio -i'
cd ${fs_path}; sudo chown -hR root:root *; cd ${entry_path}


#//2. 添加、修改、删除rootfs.cpio目录的文件
#  2.1将linux kernel编译生成的modules/* 复制到/lib/modules下
#  2.2  其他脚本等；


#//3. 重新打包生成rootfs.cpio1.gz文件
export fs_path=rootfs.cpio
export entry_path=`pwd`
rm -fr ${fs_path}1.gz 
rm -fr uramdisk.image.gz
sh -c 'cd ${fs_path}/ && find . | cpio -H newc -o' | gzip -9 > ${fs_path}1.gz
#sh -c 'cd ${fs_path}/ && find . | cpio -H newc -o' | lzop -9 > ${fs_path}1.gz


#//4. 添加u-boot头信息，生成uramdisk.image.gz根文件系统
mkimage -A arm -T ramdisk -C gzip -d ${fs_path}1.gz  uramdisk.image.gz



#//5. 复制到/tftpboot目录
cp -f uramdisk.image.gz /tftpboot




#//============================================================== 
#//  uboot文件去掉64字节头信息：
#//============================================================== 
# dd if=uramdisk.image.gz  bs=64 skip=1 of=initramfs.cpio.gz



#//============================================================== 
#//制作 initrd 根文件系统
#//============================================================== 
#//step 1： 解包
gunzip -kf arm_ramdisk.image.gz

#//step 2： mount文件系统
mv  -f arm_ramdisk.image  ramdisk.image
chmod u+rwx  ramdisk.image
mkdir -p tmp_mnt/
mount -o loop ramdisk.image tmp_mnt/

#//step 3： 修改文件系统

#//step 4： 打包
umount tmp_mnt/
gzip ramdisk.image        


#//step 5：  建立文件系统，添加uboot能够识别的头信息（64bytes）
mkimage -A arm -T ramdisk -C gzip -d ramdisk.image.gz    uramdisk.image.gz










