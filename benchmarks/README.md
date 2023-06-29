Benchmarks
==================================
We contribute a variety of implementations of a Matrix Multiplication (AB) benchmark to show off the advantages of our **FPGA overlay** solution.
For instance, we compare with a baseline host processor  implementation, as well as a *reference* Xilinx-based approach based on the *Vitis/Vivado HLS design flow*. 

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
[host/]:host/arm64/matmul/
[pulp/]:pulp/matmul/
[xilinx/]:xilinx/matmul/
