Benchmarks
==================================
We contribute a set of benchmarking suite where our **FPGA overlay** solution is compared with  a  reference  Xilinx-based methodology that leverages  the standard Vitis/Vivado HLS design flow. 
We also include a host processor  implementation, as a baseline.

**More information is to be found in our publication [1].**

## Proposed designs
Design | Description |
---------------|-----------------------|
[host/][]|Host processor baseline implementation running at 1.2GHz.|
[pulp/][]|**FPGA overlay** implementations running at 100MHz. |
[xilinx/][]|Reference implementations running at 150MHz.|

## References
1) "A RISC-V-based FPGA Overlay to Simplify Embedded Accelerator Deployment" - G. Bellocchi et al. (2021)

## Contacts
* E-mail: <name.surname@unimore.it>

[.]:.
[host/]:host/
[pulp/]:pulp/
[xilinx/]:xilinx/
