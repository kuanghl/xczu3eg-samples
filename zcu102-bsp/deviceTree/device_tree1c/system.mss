
 PARAMETER VERSION = 2.2.0


BEGIN OS
 PARAMETER OS_NAME = device_tree
 PARAMETER PROC_INSTANCE = psu_cortexa53_0
 PARAMETER console_device = psu_uart_0
 PARAMETER main_memory = psu_ddr_0
END


BEGIN PROCESSOR
 PARAMETER DRIVER_NAME = cpu_cortexa53
 PARAMETER HW_INSTANCE = psu_cortexa53_0
END


BEGIN DRIVER
 PARAMETER DRIVER_NAME = scugic
 PARAMETER HW_INSTANCE = psu_acpu_gic
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_adma_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_adma_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_adma_2
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_adma_3
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_adma_4
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_adma_5
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_adma_6
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_adma_7
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_afi_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_afi_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_afi_2
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_afi_3
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_afi_4
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_afi_5
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_afi_6
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ams
 PARAMETER HW_INSTANCE = psu_ams
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_apm_0
 PARAMETER xlnx,enable-32bit-filter-id = 1
 PARAMETER xlnx,enable-advanced = 1
 PARAMETER xlnx,enable-event-count = 1
 PARAMETER xlnx,enable-event-log = 0
 PARAMETER xlnx,enable-profile = 0
 PARAMETER xlnx,enable-trace = 0
 PARAMETER xlnx,fifo-axis-depth = 32
 PARAMETER xlnx,fifo-axis-tdata-width = 56
 PARAMETER xlnx,fifo-axis-tid-width = 1
 PARAMETER xlnx,global-count-width = 32
 PARAMETER xlnx,have-sampled-metric-cnt = 1
 PARAMETER xlnx,metric-count-scale = 1
 PARAMETER xlnx,metrics-sample-count-width = 32
 PARAMETER xlnx,num-monitor-slots = 6
 PARAMETER xlnx,num-of-counters = 10
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_apm_1
 PARAMETER xlnx,enable-32bit-filter-id = 1
 PARAMETER xlnx,enable-advanced = 1
 PARAMETER xlnx,enable-event-count = 1
 PARAMETER xlnx,enable-event-log = 0
 PARAMETER xlnx,enable-profile = 0
 PARAMETER xlnx,enable-trace = 0
 PARAMETER xlnx,fifo-axis-depth = 32
 PARAMETER xlnx,fifo-axis-tdata-width = 56
 PARAMETER xlnx,fifo-axis-tid-width = 1
 PARAMETER xlnx,global-count-width = 32
 PARAMETER xlnx,have-sampled-metric-cnt = 1
 PARAMETER xlnx,metric-count-scale = 1
 PARAMETER xlnx,metrics-sample-count-width = 32
 PARAMETER xlnx,num-monitor-slots = 1
 PARAMETER xlnx,num-of-counters = 3
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_apm_2
 PARAMETER xlnx,enable-32bit-filter-id = 1
 PARAMETER xlnx,enable-advanced = 1
 PARAMETER xlnx,enable-event-count = 1
 PARAMETER xlnx,enable-event-log = 0
 PARAMETER xlnx,enable-profile = 0
 PARAMETER xlnx,enable-trace = 0
 PARAMETER xlnx,fifo-axis-depth = 32
 PARAMETER xlnx,fifo-axis-tdata-width = 56
 PARAMETER xlnx,fifo-axis-tid-width = 1
 PARAMETER xlnx,global-count-width = 32
 PARAMETER xlnx,have-sampled-metric-cnt = 1
 PARAMETER xlnx,metric-count-scale = 1
 PARAMETER xlnx,metrics-sample-count-width = 32
 PARAMETER xlnx,num-monitor-slots = 1
 PARAMETER xlnx,num-of-counters = 3
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_apm_5
 PARAMETER xlnx,enable-32bit-filter-id = 1
 PARAMETER xlnx,enable-advanced = 1
 PARAMETER xlnx,enable-event-count = 1
 PARAMETER xlnx,enable-event-log = 0
 PARAMETER xlnx,enable-profile = 0
 PARAMETER xlnx,enable-trace = 0
 PARAMETER xlnx,fifo-axis-depth = 32
 PARAMETER xlnx,fifo-axis-tdata-width = 56
 PARAMETER xlnx,fifo-axis-tid-width = 1
 PARAMETER xlnx,global-count-width = 32
 PARAMETER xlnx,have-sampled-metric-cnt = 1
 PARAMETER xlnx,metric-count-scale = 1
 PARAMETER xlnx,metrics-sample-count-width = 32
 PARAMETER xlnx,num-monitor-slots = 1
 PARAMETER xlnx,num-of-counters = 3
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_apu
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = canps
 PARAMETER HW_INSTANCE = psu_can_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_cci_gpv
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_cci_reg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_coresight_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_crf_apb
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_crl_apb
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_csudma
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ctrl_ipi
 PARAMETER compatible = xlnx,PERIPHERAL-1.0
 PARAMETER reg = 0x0 0xff380000 0x0 0x80000
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ddrps
 PARAMETER HW_INSTANCE = psu_ddr_0
 PARAMETER reg = 0x0 0x0 0x0 0x7ff00000
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ddrps
 PARAMETER HW_INSTANCE = psu_ddr_1
 PARAMETER reg = 0x0 0x0 0x0 0x7ff00000>, <0x00000008 0x00000000 0x0 0x80000000
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ddr_phy
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ddr_qos_ctrl
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ddr_xmpu0_cfg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ddr_xmpu1_cfg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ddr_xmpu2_cfg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ddr_xmpu3_cfg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ddr_xmpu4_cfg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ddr_xmpu5_cfg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ddrcps
 PARAMETER HW_INSTANCE = psu_ddrc_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_efuse
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = emacps
 PARAMETER HW_INSTANCE = psu_ethernet_3
 PARAMETER phy-mode = rgmii-id
 PARAMETER xlnx,ptp-enet-clock = 0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_fpd_gpv
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_fpd_slcr
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_fpd_slcr_secure
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_fpd_xmpu_cfg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_fpd_xmpu_sink
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_gdma_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_gdma_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_gdma_2
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_gdma_3
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_gdma_4
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_gdma_5
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_gdma_6
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = dmaps
 PARAMETER HW_INSTANCE = psu_gdma_7
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = gpiops
 PARAMETER HW_INSTANCE = psu_gpio_0
 PARAMETER emio-gpio-width = 32
 PARAMETER gpio-mask-high = 0
 PARAMETER gpio-mask-low = 22016
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_gpu
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = iicps
 PARAMETER HW_INSTANCE = psu_i2c_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = iicps
 PARAMETER HW_INSTANCE = psu_i2c_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_iou_scntr
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_iou_scntrs
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_iousecure_slcr
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_iouslcr_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ipi_0
 PARAMETER xlnx,base-address = 0xFF300000
 PARAMETER xlnx,bit-position = 0
 PARAMETER xlnx,buffer-base = 0xFF990400
 PARAMETER xlnx,buffer-index = 2
 PARAMETER xlnx,cpu-name = APU
 PARAMETER xlnx,int-id = 67
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_lpd_slcr
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_lpd_slcr_secure
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_lpd_xppu
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_lpd_xppu_sink
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_mbistjtag
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_message_buffers
 PARAMETER compatible = xlnx,PERIPHERAL-1.0
 PARAMETER reg = 0x0 0xff990000 0x0 0x10000
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ocmcps
 PARAMETER HW_INSTANCE = psu_ocm
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ocm_ram_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_ocm_xmpu_cfg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_pmu_global_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_r5_0_atcm_global
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_r5_0_btcm_global
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_r5_1_atcm_global
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_r5_1_btcm_global
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_r5_tcm_ram_global
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_rcpu_gic
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_rpu
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_rsa
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_rtc
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = sdps
 PARAMETER HW_INSTANCE = psu_sd_1
 PARAMETER clock-frequency = 187481262
 PARAMETER xlnx,mio_bank = 1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_serdes
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_siou
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_smmu_gpv
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_smmu_reg
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ttcps
 PARAMETER HW_INSTANCE = psu_ttc_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ttcps
 PARAMETER HW_INSTANCE = psu_ttc_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ttcps
 PARAMETER HW_INSTANCE = psu_ttc_2
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = ttcps
 PARAMETER HW_INSTANCE = psu_ttc_3
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = uartps
 PARAMETER HW_INSTANCE = psu_uart_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = uartps
 PARAMETER HW_INSTANCE = psu_uart_1
 PARAMETER port-number = 1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_usb_0
 PARAMETER xlnx,usb-polarity = 0
 PARAMETER xlnx,usb-reset-mode = 0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = usbps
 PARAMETER HW_INSTANCE = psu_usb_xhci_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = scuwdt
 PARAMETER HW_INSTANCE = psu_wdt_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = scuwdt
 PARAMETER HW_INSTANCE = psu_wdt_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = axi_dma
 PARAMETER HW_INSTANCE = zcu102_system_wrapper_i_zcu102_system_i_MobileNetV1_SSD_inf_dm_0_indata_outdata
 PARAMETER clock-names =  s_axi_lite_aclk m_axi_mm2s_aclk m_axi_s2mm_aclk
 PARAMETER clocks = misc_clk_0>, <&misc_clk_0>, <&misc_clk_0
 PARAMETER compatible = xlnx,axi-dma-7.1 xlnx,axi-dma-1.00.a
 PARAMETER interrupt-names =  s2mm_introut
 PARAMETER interrupt-parent = gic
 PARAMETER interrupts = 0 90 4
 PARAMETER reg = 0x0 0xa0400000 0x0 0x10000
 PARAMETER xlnx,addrwidth = 32
 PARAMETER xlnx,sg-length-width = 20
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = axi_dma
 PARAMETER HW_INSTANCE = zcu102_system_wrapper_i_zcu102_system_i_MobileNetV1_SSD_inf_dm_1_inweight
 PARAMETER clock-names =  s_axi_lite_aclk m_axi_mm2s_aclk
 PARAMETER clocks = misc_clk_0>, <&misc_clk_0
 PARAMETER compatible = xlnx,axi-dma-7.1 xlnx,axi-dma-1.00.a
 PARAMETER reg = 0x0 0xa0410000 0x0 0x10000
 PARAMETER xlnx,addrwidth = 32
 PARAMETER xlnx,sg-length-width = 26
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = axi_vdma
 PARAMETER HW_INSTANCE = zcu102_system_wrapper_i_zcu102_system_i_vdma_1_sensor
 PARAMETER clock-names =  s_axi_lite_aclk m_axi_s2mm_aclk s_axis_s2mm_aclk
 PARAMETER clocks = misc_clk_0>, <&misc_clk_0>, <&misc_clk_0
 PARAMETER compatible = xlnx,axi-vdma-6.3 xlnx,axi-vdma-1.00.a
 PARAMETER interrupt-names =  s2mm_introut
 PARAMETER interrupt-parent = gic
 PARAMETER interrupts = 0 89 4
 PARAMETER reg = 0x0 0xa1210000 0x0 0x10000
 PARAMETER xlnx,addrwidth = 32
 PARAMETER xlnx,flush-fsync = 1
 PARAMETER xlnx,num-fstores = 3
END

