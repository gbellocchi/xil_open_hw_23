# =====================================================================
# Title:        zcu102
# Description:  Build Petalinux project for ZCU102 board.
# =====================================================================

#!/usr/bin/env bash

# Read input arguments.
# - targets
readonly TARGET_BOARD="$1"
readonly PROJECT_NAME="$2"
readonly HW_DESIGN_DIR="$3"
readonly DESIGN_NAME="$4"
readonly SCRIPTS_DIR="$5"
readonly PETALINUX_ROOT="$6"

# Print some user information about input parameters
echo -e "Building Petalinux project for...\n"
echo -e ">> Target board: $TARGET_BOARD"
echo -e ">> Project name: $PROJECT_NAME"
echo -e ">> FPGA HW directory: $HW_DESIGN_DIR"
echo -e ">> Design name: $DESIGN_NAME"
echo -e ">> Scripts directory: $SCRIPTS_DIR"
echo -e ">> Current directory: $PETALINUX_ROOT"

# Local config location.
readonly LOCAL_CFG="$SCRIPTS_DIR/local.cfg"

set -e

# Change working directory to path of script, so this script can be executed from anywhere.
cd "$PETALINUX_ROOT"

# Resolve symlinks.
cd "$(pwd -P)"

# Initialize Python environment suitable for PetaLinux.
python3.6 -m venv .venv
ln -sf python3.6 .venv/bin/python3
source .venv/bin/activate

# Create project.
if [ ! -d "$TARGET_BOARD" ]; then
    petalinux-create -t project -n "$TARGET_BOARD" --template zynqMP
fi
cd "$TARGET_BOARD"

# Initialize and set necessary configuration from config and local config.
petalinux-config --oldconfig --get-hw-description "$HW_DESIGN_DIR"

mkdir -p components/ext_sources
cd components/ext_sources
if [ ! -d "linux-xlnx" ]; then
    git clone --depth 1 --single-branch --branch xilinx-v2019.2.01 https://github.com/Xilinx/linux-xlnx.git
fi
cd linux-xlnx
git checkout tags/xilinx-v2019.2.01

cd ../../../

# sed -i 's|CONFIG_SUBSYSTEM_COMPONENT_LINUX__KERNEL_NAME_LINUX__XLNX=y||' project-spec/configs/config
# echo 'CONFIG_SUBSYSTEM_COMPONENT_LINUX__KERNEL_NAME_EXT__LOCAL__SRC=y' >> project-spec/configs/config
# echo 'CONFIG_SUBSYSTEM_COMPONENT_LINUX__KERNEL_NAME_EXT_LOCAL_SRC_PATH="${TOPDIR}/../components/ext_sources/linux-xlnx"' >> project-spec/configs/config
# echo 'CONFIG_SUBSYSTEM_MACHINE_NAME="zcu102-revb"' >> project-spec/configs/config

# # Image Packaging Configuration
# echo 'CONFIG_SUBSYSTEM_ROOTFS_SD=y' >> project-spec/configs/config
# echo 'CONFIG_SUBSYSTEM_SDROOT_DEV="/dev/mmcblk0p2"' >> project-spec/configs/config

sed -i 's|CONFIG_SUBSYSTEM_COMPONENT_LINUX__KERNEL_NAME_LINUX__XLNX||' project-spec/configs/config
sed -i 's|CONFIG_SUBSYSTEM_ROOTFS_INITRAMFS||' project-spec/configs/config
echo 'CONFIG_SUBSYSTEM_ROOTFS_SD=y' >> project-spec/configs/config
echo 'CONFIG_SUBSYSTEM_COMPONENT_LINUX__KERNEL_NAME_EXT__LOCAL__SRC=y' >> project-spec/configs/config
echo 'CONFIG_SUBSYSTEM_COMPONENT_LINUX__KERNEL_NAME_EXT_LOCAL_SRC_PATH="${TOPDIR}/../components/ext_sources/linux-xlnx"' >> project-spec/configs/config
echo 'CONFIG_SUBSYSTEM_SDROOT_DEV="/dev/mmcblk0p2"' >> project-spec/configs/config
echo 'CONFIG_SUBSYSTEM_MACHINE_NAME="zcu102-revb"' >> project-spec/configs/config

if [ -f "$LOCAL_CFG" ] && grep -q PT_ETH_MAC "$LOCAL_CFG"; then
    sed -e 's/PT_ETH_MAC/CONFIG_SUBSYSTEM_ETHERNET_PSU_ETHERNET_3_MAC/;t;d' "$LOCAL_CFG" >> project-spec/configs/config
fi

petalinux-config --oldconfig --get-hw-description "$HW_DESIGN_DIR"

echo "
/include/ \"system-conf.dtsi\"
/include/ \"${SCRIPTS_DIR}/dtsi/${DESIGN_NAME}.dtsi\"
/ {
};
" > project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi

# Configure RootFS.
rootfs_enable() {
    sed -i -e "s/# CONFIG_$1 is not set/CONFIG_$1=y/" project-spec/configs/rootfs_config
}
for pkg in \
    bash \
    bash-completion \
    bc \
    ed \
    grep \
    patch \
    sed \
    util-linux \
    util-linux-blkid \
    util-linux-lscpu \
    vim \
; do
  rootfs_enable $pkg
done

# Build PetaLinux.
set +e
petalinux-build
echo "First build might fail, this is expected..."
set -e
mkdir -p build/tmp/work/aarch64-xilinx-linux/external-hdf/1.0-r0/git/plnx_aarch64/

cp project-spec/hw-description/system.xsa build/tmp/work/aarch64-xilinx-linux/external-hdf/1.0-r0/git/plnx_aarch64/

petalinux-build

mkdir -p build/tmp/work/aarch64-xilinx-linux/external-hdf/1.0-r0/git/plnx_aarch64/

cd $PETALINUX_ROOT/$TARGET_BOARD/images/linux

# Generate images including bitstream with `petalinux-package`.
cp "${HW_DESIGN_DIR}/${PROJECT_NAME}.bit" ${PROJECT_NAME}.bit
echo "
the_ROM_image:
{
  [init] regs.init
  [bootloader] zynqmp_fsbl.elf
  [pmufw_image] pmufw.elf
  [destination_device=pl] ${PROJECT_NAME}.bit
  [destination_cpu=a53-0, exception_level=el-3, trustzone] bl31.elf
  [destination_cpu=a53-0, exception_level=el-2] u-boot.elf
}
# " > bootgen.bif