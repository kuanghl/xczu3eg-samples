# Patch for FSBL
# Note: do_configure_prepend task section is required only for 2017.1 release
# Refer https://github.com/Xilinx/meta-xilinx-tools/blob/rel-v2017.2/classes/xsctbase.bbclass#L29-L35
  
do_configure_prepend() {
    if [ -d "${S}/patches" ]; then
       rm -rf ${S}/patches
    fi
  
    if [ -d "${S}/.pc" ]; then
       rm -rf ${S}/.pc
    fi
}



do_compile_prepend(){

   install -m 0644 ${TOPDIR}/../project-spec/hw-description/psu_init.c ${B}/fsbl/psu_init.c

   install -m 0644 ${TOPDIR}/../project-spec/hw-description/psu_init.h ${B}/fsbl/psu_init.h

}

  
SRC_URI_append = " \
        file://0001-FSBL.patch \
        "
  
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
  
#Add debug for FSBL(optional)
XSCTH_BUILD_DEBUG = "1"
  
#Enable appropriate FSBL debug flags
YAML_COMPILER_FLAGS_append = " -DXPS_BOARD_ZCU102"
  
# Note: This is not required if you are using Yocto
# CAUTION!: EXTERNALXSCTSRC and EXTERNALXSCTSRC_BUILD is required only for 2018.2 and below petalinux releases
EXTERNALXSCTSRC = ""
EXTERNALXSCTSRC_BUILD = ""

