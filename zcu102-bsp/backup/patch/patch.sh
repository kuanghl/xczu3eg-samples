#!/bin/bash


mkdir -p ./project-spec/meta-user/recipes-bsp/fsbl/files
cp 0001-FSBL.patch ./project-spec/meta-user/recipes-bsp/fsbl/files
cp fsbl.bbappend   ./project-spec/meta-user/recipes-bsp/fsbl/fsbl_%.bbappend


petalinux-build -x mrproper
rm -rf ./components/plnx_workspace
petalinux-build -c bootloader
