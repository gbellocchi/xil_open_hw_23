Reference benchmarks
==================================
Below are listed and described the proposed reference benchmarks where accelerators are integrated as standalone components following the usual Xilinx-based methodology.

**More information is to be found in our publication [1].**

## Proposed designs
Design | Description |
---------------|-----------------------|
[01_x_hw/][]|Standalone pure-hardware (HW) implementation. No further optimization is specified.|
[02_x_bl/][]|Hybrid hardware/software implementation. Data blocking (BL) is implemented.|
[03_x_bl_pm/][]|Hybrid hardware/software implementation. Datapath is optimized employing partial array partitioning and loop unrolling to implement spatial parallelism (PM).|
[04_x_loop/][]|Standalone pure-hardware implementation. Hardware loops (LOOP) are implemented.|
[05_x_pm/][]|Standalone pure-hardware implementation. Datapath is optimized employing total array partitioning and loop unrolling to further increase parallelism (PM).|

## References
1) "A RISC-V-based FPGA Overlay to Simplify Embedded Accelerator Deployment" - G. Bellocchi et al. (2021)

## Contacts
* E-mail: <name.surname@unimore.it>

[.]:.
[01_x_hw/]:01_x_hw/
[02_x_bl/]:02_x_bl/
[03_x_bl_pm/]:03_x_bl_pm/
[04_x_loop/]:04_x_loop/
[05_x_pm/]:05_x_pm/
