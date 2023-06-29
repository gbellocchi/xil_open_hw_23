# =====================================================================
# Title:        update_bitstream
# Description:  Retrieve new bitstream and re-compile project outputs.
# =====================================================================
#
# Copyright (C) 2022 University of Modena and Reggio Emilia.
#
# Author: Gianluca Bellocchi, University of Modena and Reggio Emilia.
#
# =====================================================================

#!/usr/bin/env bash

# Read input arguments.
# - targets
readonly TARGET_BOARD="$1"
readonly PROJECT_NAME="$2"
readonly HW_DESIGN_DIR="$3"
# - environment
readonly PETALINUX_ROOT="$4"
readonly BUILD_DIR="$5"

# Print some user information about input parameters
echo -e "Building Petalinux project for...\n"
echo -e ">> Target board: $TARGET_BOARD"
echo -e ">> Target board: $PROJECT_NAME"
echo -e ">> Target bitstream path: $HW_DESIGN_DIR"
echo -e ">> Script root: $PETALINUX_ROOT"
echo -e ">> Project location: $BUILD_DIR"

set -e

# Change working directory to path of script, so this script can be executed from anywhere.
cd "$PETALINUX_ROOT"

# Resolve symlinks.
cd "$(pwd -P)"

# Print some user information about configuration settings
echo -e "\nBuilding Petalinux project with the following configuration settings...\n"
echo -e ">> Bitstream location: $HW_DESIGN_DIR"

# retrieve project name
PETALINUX_PRJ_NAME=$TARGET_BOARD 

# move to project location 
cd "$BUILD_DIR/$PETALINUX_PRJ_NAME/images/linux"

if [ ! -f regs.init ]; then
  echo ".set. 0xFF41A040 = 0x3;" > regs.init
fi

# Generate images including bitstream with `petalinux-package`.
cp $HW_DESIGN_DIR/*.bit ${PETALINUX_PRJ_NAME}.bit
echo "
the_ROM_image:
{
  [init] regs.init
  [bootloader] zynqmp_fsbl.elf
  [pmufw_image] pmufw.elf
  [destination_device=pl] ${PETALINUX_PRJ_NAME}.bit
  [destination_cpu=a53-0, exception_level=el-3, trustzone] bl31.elf
  [destination_cpu=a53-0, exception_level=el-2] u-boot.elf
}
# " > bootgen.bif
$PETALINUX_VER petalinux-package --boot --force \
  --fsbl zynqmp_fsbl.elf \
  --fpga ${PETALINUX_PRJ_NAME}.bit \
  --u-boot u-boot.elf \
  --pmufw pmufw.elf \
  --bif bootgen.bif