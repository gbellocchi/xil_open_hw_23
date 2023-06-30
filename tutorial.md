
# Tutorial

## Getting started
1. Clone the repository submodules: `git submodule update --init --recursive`.
2. Open [setup.sh](setup.sh) and edit the `HERO_BOARD_IP` with your personal IP address. This information is required to access your board, reconfigure it and deploy applications.
3. Source [setup.sh](setup.sh) to invoke the environment needed to interact with the components of this repository.
4. Open [local.cfg](benchmarks/xilinx/common/board/local.cfg) and add your buildroot configurations. This information is required during the Petalinux build phase for reference benchmarks.

## Prerequisites

### AMD-Xilinx tools
We recommend to leverage the following tool versions:
+ Vivado HLS - 2019.2
+ Vitis HLS - 2022.2
+ Vivado 2019.2
+ Petalinux 2019.2

Though, more recent versions will work anyway.

### HERO
[HERO](third-party/hero) is included as a submodule. The installation process is described in a step-by-step guide provided at its repository source: https://github.com/pulp-platform/hero.

## Run pre-build ZCU102 project
Follow the instruction in this [user guide](ex-prj-zcu102/README.md) 

## Build an heterogeneous RISC-V-based FPGA overlay
Below are described the steps required to build an FPGA overlay emplying our proposed solution.

### Benchmark description
We provide a set of Matrix Multiplication (MatMul) implementations that are deployed employing our overlay-based methodology.

Below is described how to implement a _MatMul accelerator_, then integrate and deploy it.

Further description concerning the benchmarks can be found [here](benchmarks/pulp/matmul/README.md).

### Accelerator design employing AMD-Xilinx Vivado/Vitis HLS
Here are described the steps to build one of the HLS accelerator design. The same also applies for the others.
```Shell
cd $XIL_OPENHW_PATH/benchmarks/pulp/matmul/03_o_hw/hls
make clean run_hls TOOL_HLS=vivado_hls # or "vitis_hls"
make get_rtl
```

### System-level design
[GenOv](genov) is our main contribute for the _AMD Open Hardware Competition 2023_.

The tool accomplishes the crucial phase of *system-level design* (SLD), thus the integration of  application-specific accelerators inside a HW/SW platform. 

A step-by-step guide on how to generate an FPGA overlay is included in the [GenOv repository](https://github.com/gbellocchi/genov).

### FPGA build

The generated overlay can be built for a ZCU102 target by running the following command.

```Shell
cd $XIL_OPENHW_PATH/third-party/arov && make fpga TARGET_OV=xil_open_hw_23_mmult_hw
```

### Application development
The SW applications can be built employing HERO as a build system:

```Shell
cd $XIL_OPENHW_PATH/benchmarks/pulp/matmul/03_o_hw/app
make clean all
```

### ZCU102 deployment
A complete Linux environment with kernel and the base root filesystem for the [AMD-Xilinx ZCU102](https://github.com/pulp-platform/hero#xilinx-zcu102) can be built as follows.

First, add a line to the `local.cfg` file at the root of your repository (create that file if it does not exist), which defines the path to the bitstream:

```Shell
BR2_HERO_BITSTREAM=$XIL_OPENHW_PATH/hw/arov/fpga/build/xil_open_hw_23_mmult_hw/vivado_prj/hero_exilzcu102.sdk/hero_exilzcu102_wrapper.bit
```

Then,  continue as described in [here](https://github.com/pulp-platform/hero#xilinx-zcu102).

Once the board setup is ready, the application can be deployed by running:
```Shell
cd $XIL_OPENHW_PATH/benchmarks/pulp/matmul/03_o_hw/app && make run
```

## Reference benchmarks

### AArch64
We provide an AArch64-based MatMul implementation, as a baseline reference to the accelerator-based implementations.
These run on the application processor of the ZU9EG MPSoC mounted on the AMD Xilinx ZCU102.

To build, deploy and run the SW implementation, it is required to follow these steps:
```Shell
source $XIL_OPENHW_PATH/benchmarks/host/arm64/common/arm-env.sh
cd $XIL_OPENHW_PATH/benchmarks/host/arm64/matmul/01_arm_sw && make clean all 
make run_app
```

### AMD-Xilinx
We provide different increasingly optimized MatMul implementations that run as standalone application-specific accelerators.

Here are described the steps to build one of designs. The same steps also applies for the others.

To build the required hardware and FPGA bitstream:
```Shell
# HLS build
cd $XIL_OPENHW_PATH/benchmarks/xilinx/matmul/01_x_hw/hls
make clean run_hls TOOL_HLS=vivado_hls # or "vitis_hls"

# FPGA build
cd $XIL_OPENHW_PATH/benchmarks/xilinx/matmul/01_x_hw/fpga
make clean run_fpga

# Petalinux build (SD card image)
cd $XIL_OPENHW_PATH/benchmarks/xilinx/matmul/01_x_hw/petalinux
make clean_petalinux run_petalinux
```

Once the board setup is ready, the application can be built and deployed by running:

```Shell
# Application build
cd $XIL_OPENHW_PATH/benchmarks/xilinx/matmul/01_x_hw/app
make clean_local build_env build_app app_deploy
```
