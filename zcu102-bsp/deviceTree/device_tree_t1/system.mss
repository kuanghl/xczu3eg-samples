
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
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = audio_ss_0_aud_pat_gen
 PARAMETER clock-names =  axi_aclk aud_clk axis_clk
 PARAMETER clocks = clk 71>, <&audio_ss_0_clk_wiz 0>, <&audio_ss_0_clk_wiz 0
 PARAMETER compatible = xlnx,aud-pat-gen-1.0
 PARAMETER reg = 0x0 0x90000000 0x0 0x10000
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = axi_clk_wiz
 PARAMETER HW_INSTANCE = audio_ss_0_clk_wiz
 PARAMETER clock-names =  s_axi_aclk clk_in1
 PARAMETER clock-output-names = clk_out1 clk_out2 clk_out3 clk_out4 clk_out5 clk_out6 clk_out7
 PARAMETER clocks = clk 71>, <&clk 71
 PARAMETER compatible = xlnx,clk-wiz-6.0 xlnx,clocking-wizard
 PARAMETER reg = 0x0 0x80020000 0x0 0x10000
 PARAMETER speed-grade = 2
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = hdmi_ctrl
 PARAMETER HW_INSTANCE = audio_ss_0_hdmi_acr_ctrl
 PARAMETER clock-names =  axi_aclk aud_clk hdmi_clk
 PARAMETER clocks = clk 71>, <&audio_ss_0_clk_wiz 0>, <&misc_clk_0
 PARAMETER compatible = xlnx,hdmi-acr-ctrl-1.0 xlnx,hdmi_act_ctrl
 PARAMETER reg = 0x0 0x88000000 0x0 0x10000
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
 PARAMETER DRIVER_NAME = dp
 PARAMETER HW_INSTANCE = psu_dp
 PARAMETER phy-names = dp-phy0
 PARAMETER phys = lane1 5 0 3 27000000
 PARAMETER xlnx,max-lanes = 1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_dpdma
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
 PARAMETER HW_INSTANCE = psu_pcie
 PARAMETER xlnx,pcie-mode = Root Port
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_pcie_attrib_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_pcie_dma
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_pcie_high1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_pcie_high2
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_pcie_low
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_pmu_global_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = qspips
 PARAMETER HW_INSTANCE = psu_qspi_0
 PARAMETER is-dual = 1
 PARAMETER spi-rx-bus-width = 4
 PARAMETER spi-tx-bus-width = 4
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_qspi_linear_0
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
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = psu_sata
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
 PARAMETER DRIVER_NAME = hdmi_tx_ss
 PARAMETER HW_INSTANCE = v_hdmi_tx_ss
 PARAMETER clock-names =  s_axi_cpu_aclk link_clk s_axis_audio_aclk video_clk s_axis_video_aclk
 PARAMETER clocks = clk 71>, <&misc_clk_1>, <&audio_ss_0_clk_wiz 0>, <&misc_clk_0>, <&clk 72
 PARAMETER compatible = xlnx,v-hdmi-tx-ss-3.1 xlnx,v-hdmi-tx-ss-3.0
 PARAMETER interrupt-names =  irq
 PARAMETER interrupt-parent = gic
 PARAMETER interrupts = 0 91 4
 PARAMETER reg = 0x0 0x80000000 0x0 0x20000
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = gpio
 PARAMETER HW_INSTANCE = v_tpg_ss_0_axi_gpio
 PARAMETER clock-names =  s_axi_aclk
 PARAMETER clocks = clk 72
 PARAMETER compatible = xlnx,axi-gpio-2.0 xlnx,xps-gpio-1.00.a
 PARAMETER reg = 0x0 0x80030000 0x0 0x1000
 PARAMETER xlnx,all-inputs = 0
 PARAMETER xlnx,all-inputs-2 = 0
 PARAMETER xlnx,all-outputs = 1
 PARAMETER xlnx,all-outputs-2 = 0
 PARAMETER xlnx,dout-default = 0x00000000
 PARAMETER xlnx,dout-default-2 = 0x00000000
 PARAMETER xlnx,gpio-width = 1
 PARAMETER xlnx,gpio2-width = 32
 PARAMETER xlnx,interrupt-present = 0
 PARAMETER xlnx,is-dual = 0
 PARAMETER xlnx,tri-default = 0xFFFFFFFF
 PARAMETER xlnx,tri-default-2 = 0xFFFFFFFF
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = tpg
 PARAMETER HW_INSTANCE = v_tpg_ss_0_v_tpg
 PARAMETER clock-names =  ap_clk
 PARAMETER clocks = clk 72
 PARAMETER compatible = xlnx,v-tpg-8.0 xlnx,v-tpg-5.0
 PARAMETER reg = 0x0 0x80040000 0x0 0x10000
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = vid_phy_ctrl
 PARAMETER HW_INSTANCE = vid_phy_controller
 PARAMETER clock-names =  mgtrefclk0_pad_p_in mgtrefclk0_pad_n_in vid_phy_tx_axi4s_aclk vid_phy_sb_aclk vid_phy_axi4lite_aclk drpclk
 PARAMETER clocks = misc_clk_2>, <&misc_clk_2>, <&misc_clk_1>, <&clk 71>, <&clk 71>, <&clk 71
 PARAMETER compatible = xlnx,vid-phy-controller-2.2 xlnx,vid-phy-controller-2.1
 PARAMETER interrupt-names =  irq
 PARAMETER interrupt-parent = gic
 PARAMETER interrupts = 0 89 4
 PARAMETER reg = 0x0 0x80050000 0x0 0x10000
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = generic
 PARAMETER HW_INSTANCE = video_frame_crc
 PARAMETER clock-names =  s_axi_aclk vid_in_axis_aclk
 PARAMETER clocks = clk 71>, <&clk 72
 PARAMETER compatible = xlnx,video-frame-crc-1.0
 PARAMETER reg = 0x0 0x80060000 0x0 0x10000
 PARAMETER xlnx,ppc-mode = 2
 PARAMETER xlnx,vid-in-axis-tdata-width = 96
 PARAMETER xlnx,vid-out-axis-tdata-width = 96
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = axi_iic
 PARAMETER HW_INSTANCE = zynq_us_ss_0_fmch_axi_iic
 PARAMETER clock-names =  s_axi_aclk
 PARAMETER clocks = clk 71
 PARAMETER compatible = xlnx,axi-iic-2.0 xlnx,xps-iic-2.00.a
 PARAMETER reg = 0x0 0x80031000 0x0 0x1000
END


