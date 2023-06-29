ROOT 				:= $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

# user parameters
TARGET_BOARD 		:= zcu102
PROJ_NAME 			:= xil_03
DESIGN_NAME 		:= matmul

# directories
BUILD_DIR			:= $(ROOT)
OUT_DIR				:= $(BUILD_DIR)/output
HW_DESIGN_DIR		:= $(BUILD_DIR)/../fpga/hw_design
COMMON				:= $(BUILD_DIR)/../../../common
SCRIPTS_DIR			:= $(COMMON)/board

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #

# ------- #
#  BOARD  #
# ------- #

reboot_zcu102:
	@$(SCRIPTS_DIR)/$@.sh

update_boardenv:
	@$(SCRIPTS_DIR)/$@.sh \
		$(TARGET_BOARD) $(PROJ_NAME) $(OUT_DIR)

update_output:
	@rm -rf $(OUT_DIR)/$(TARGET_BOARD)
	@mkdir -p $(OUT_DIR)/$(TARGET_BOARD)
	@cp -r $(ROOT)/$(TARGET_BOARD)/images $(OUT_DIR)/$(TARGET_BOARD)

update_bitstream:
	@$(SCRIPTS_DIR)/$@.sh \
		$(TARGET_BOARD) $(PROJ_NAME) $(HW_DESIGN_DIR) ${ROOT} $(BUILD_DIR)

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #

# ------------------------- #
#  BUILD LINUX ENVIRONMENT  #
# ------------------------- #

run_petalinux:
	@$(SCRIPTS_DIR)/$(TARGET_BOARD).sh \
		$(TARGET_BOARD) $(PROJ_NAME) $(HW_DESIGN_DIR) $(DESIGN_NAME) $(SCRIPTS_DIR) $(ROOT)
clean_petalinux:
	@rm -rf $(TARGET_BOARD)

clean_output:
	@rm -rf $(OUT_DIR)/*

# ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ #