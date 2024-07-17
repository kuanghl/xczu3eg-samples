#!/bin/bash


# bootgen -image  fpga.cfg   -w -process_bitstream bin
bootgen -w -image fpga.cfg -arch zynqmp -process_bitstream bin 
