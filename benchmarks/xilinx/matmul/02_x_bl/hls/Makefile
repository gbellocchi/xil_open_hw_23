ROOT 			:= $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

PROJ_NAME 		:= xil_02
ACCEL_NAME 		:= mmult_hw

SRC_DIR			:= $(ROOT)/src
COMMON			:= $(ROOT)/../../../common
TCL_DIR			:= $(COMMON)/tcl
RTL_DIR			:= $(ROOT)/rtl

SYN_DIR			:= $(ROOT)/$(PROJ_NAME)_proj/solution1/syn
IMPL_DIR		:= $(ROOT)/$(PROJ_NAME)_proj/solution1/impl

TOOL_HLS		?= vivado_hls

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
	@mkdir -p $(RTL_DIR)
	@rm -f $(RTL_DIR)/*
	@cp -rf $(SYN_DIR)/verilog/* $(RTL_DIR)
run_hls:
	@rm -rf $(PROJ_NAME)_proj
	@$(TOOL_HLS) -f $(TCL_DIR)/run_hls.tcl $(ROOT) $(PROJ_NAME) $(ACCEL_NAME) $(RUN_MODE)
clean:
	@rm -rf $(PROJ_NAME)_proj
	@rm -f 	*.log *.jou