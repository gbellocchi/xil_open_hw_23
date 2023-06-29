#!/bin/bash

echo "Xilinx Open Hardware Design Competition 2023"

XIL_OPENHW_PATH=$(dirname "$(readlink -e "${BASH_SOURCE[0]}")")

# HERO
export HERO_OV_HOME_DIR=$XIL_OPENHW_PATH/hero
export HERO_OV_HW_EXPORT=$XIL_OPENHW_PATH/arov/ov_cfg
export HERO_INSTALL=$HERO_OV_HOME_DIR/install
export PULP_RISCV_GCC_TOOLCHAIN=$HERO_INSTALL

# Tools
export UNIMORE=1
export VIVADO="vivado"
export PETALINUX_VER=""

export VSIM=vsim
export VSIM_PATH=$XIL_OPENHW_PATH/arov/vsim

# Deployment setup
export HERO_BOARD_IP= # FILL your board IP
export HERO_TARGET_HOST=root@$HERO_BOARD_IP
export HERO_BOARD_HOSTNAME=$HERO_TARGET_HOST
export HERO_BOARD_LIB_PATH=/run/media/mmcblk0p2/usr/lib:/run/media/mmcblk0p2/lib
export HERO_BOARD_DRIVER_PATH=/run/media/mmcblk0p2/lib/modules/4.19.0/extra

source $HERO_OV_HOME_DIR/env/exilzcu102.sh