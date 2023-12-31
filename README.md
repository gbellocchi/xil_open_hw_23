
# GenOv
Project name: **_GenOv: Streamlining the Design and Optimization of Heterogeneous RISC-V-based FPGA Overlays_**

Team Number: *xohw23-150*

Team: *Gianluca Bellocchi*, *Alessandro Capotondi*

Supervisor: *Andrea Marongiu*

***If you want to use _GenOv_ and the other released items, you can cite our paper [1].***

## Description
**GenOv** is an open-source design automation tool to seamlessly generate and optimize heterogeneous FPGA overlays built around the RISC-V instruction set architecture (ISA). [1].
It offers *plug-and-play* integration of HLS-compiled IPs given a customizable accelerator interface - or *accelerator wrapper* - which provides shared-memory communication to the overlay cores. 

Our FPGA overlays are an extension of HERO, an open-source research platform for heterogeneous multi-/many-core architectures based on the Parallel Ultra Low Power (PULP) Platform [2,3].

## Repository
The repository is organized in the following way. 
Platform | Description |
---------------|-----------------------|
[genov/][]|Repository of **GenOv**, a design automation tool to generate and specialize heterogeneous RISC-V-based FPGA overlays [1].|
[benchmarks/][]|Set of Matrix Multiplication (MatMul) implementations to show off the advantages of our **FPGA overlay** solution. |
[ex-prj-zcu102/][]|An exemplary implementation of our **FPGA overlay** integrating a HLS-based MatMul accelerator. The folder comprises HW/SW project files, as well as a ready-to-use SD card image for [Zynq UltraScale+ MPSoC ZCU102](https://www.mouser.it/new/xilinx/xilinx-zynq-ultrascale-zcu102-eval-kit/) boards.|
[hw/][]|Hardware subsystem. |
[third-party/][]|Third-party repositories. |

## Tutorial
We include a [TUTORIAL](tutorial.md) to guide the user in its first steps using **GenOv**.

This will provide a baseline understanding of how to:
+ Build and run the provided MatMul benchmarks;
+ Deploy the pre-built ZCU102 image under [ex-prj-zcu102/][];
+ Reuse the proposed approach for other projects.

## References
1) **"A RISC-V-based FPGA Overlay to Simplify Embedded Accelerator Deployment" - G. Bellocchi et al. (2021)**
2) "HERO: An open-source research platform for HW/SW exploration of heterogeneous manycore systems" - A. Kurth et al. (2018)
3) "PULP: A parallel ultra low power platform for next generation IoT applications" - D. Rossi et al. (2015)

## Contacts
* E-mail: <name.surname@unimore.it>

[.]:.
[genov/]:https://github.com/gbellocchi/genov
[benchmarks/]:benchmarks/
[ex-prj-zcu102/]:ex-prj-zcu102/
[hw/]:hw/
[third-party/]:third-party/