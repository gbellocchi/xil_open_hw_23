# Author: Gianluca Bellocchi <gianluca.bellocchi@unimore.it>

ROOT 			:= $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

PROJ_NAME 		:= matmul
ACCEL_NAME 		:= mmult_hw_pm_cpy

SRC_DIR			:= $(ROOT)/src
TCL_DIR			:= $(ROOT)/../../../common/tcl
RTL_DIR			:= $(ROOT)/rtl

TOOL_HLS		?= vivado_hls

SYN_DIR			:= $(ROOT)/$(PROJ_NAME)_proj/solution1/syn
IMPL_DIR		:= $(ROOT)/$(PROJ_NAME)_proj/solution1/impl

# -------- #
# RUN_MODE #
# -------- #
# Set to 0: to run setup
# Set to 1: to run setup and synthesis
# Set to 2: to run setup, synthesis and RTL simulation
# Set to 3: to run setup, synthesis, RTL simulation and RTL synthesis
# Any other value will run setup only

RUN_MODE		:= 0

.PHONY: clean
get_rtl:
	@rm -f $(RTL_DIR)/*
	@mkdir -p $(RTL_DIR) && cp -rf $(SYN_DIR)/verilog/* $(RTL_DIR)
run_hls:
	@rm -rf $(PROJ_NAME)_proj
	@$(TOOL_HLS) -f $(TCL_DIR)/run_hls.tcl $(ROOT) $(PROJ_NAME) $(ACCEL_NAME) $(RUN_MODE)
clean:
	@rm -rf $(PROJ_NAME)_proj
	@rm -f 	*.log *.jou