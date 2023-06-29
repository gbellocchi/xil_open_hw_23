FPGA overlay benchmarks
==================================
Below are listed and described the proposed **FPGA overlay** benchmarks.

**More information is to be found in our publication [1].**

## Proposed designs
Design | Description |
---------------|-----------------------|
[01_o_sw/][]|Pure-software (SW) implementation. Soft-core implements a single-buffered control routine and process data.|
[02_o_sw_db/][]|Soft-core implements a double-buffered (DB) control routine and process data.|
[03_o_hw/][]|Hybrid hardware/software implementation. Hardware (HW) acceleration is performed with no datapath optimizations. Soft-core implements a double-buffered control routine.|
[04_o_hw_pm_cpy/][]|Hybrid hardware/software implementation. Datapath is optimized employing partial array partitioning and loop unrolling to implement spatial parallelism (PM). Soft-core implements a double-buffered control routine.|
[05_o_hw_pm/][]|Hybrid hardware/software implementation. The interface of the accelerator is parallelized to better accomodate the optimized datapath with the required bandwidth. Soft-core implements a double-buffered control routine.|

## References
1) "A RISC-V-based FPGA Overlay to Simplify Embedded Accelerator Deployment" - G. Bellocchi et al. (2021)

## Contacts
* E-mail: <name.surname@unimore.it>

[.]:.
[01_o_sw/]:01_o_sw/
[02_o_sw_db/]:02_o_sw_db/
[03_o_hw/]:03_hw/
[04_o_hw_pm_cpy/]:04_hw_pm_cpy/
[05_o_hw_pm/]:05_hw_pm/
