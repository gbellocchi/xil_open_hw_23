
# GenOv
Project name: **_GenOv: Streamlining the Design and Optimization of Heterogeneous RISC-V-based FPGA Overlays_**

Team Number: *xohw23-150*

Team: *Gianluca Bellocchi*

Supervisor: *Andrea Marongiu*

## Description
**GenOv** is an open-source design automation tool targeting accelerator-rich FPGA overlays [1].
It offers *plug-and-play* integration of HLS-compiled IPs given a customizable accelerator interface - or *wrapper* - which provides shared-memory communication to the overlay cores. 

Our FPGA overlays are built around the RISC-V instruction set architecture (ISA), as an extension of HERO, an open-source research platform for heterogeneous multi-/many-core architectures based on the Parallel Ultra Low Power (PULP) Platform [2,3].

## Repository
The repository is organized in the following way. 
Platform | Description |
---------------|-----------------------|
[benchmarks/][]|Set of Matrix Multiplication (MatMul) implementations to show off the advantages of our **FPGA overlay** solution. |
[ex-prj-zcu102/][]|An exemplary implementation of our **FPGA overlay** integrating a HLS-based MatMul accelerator. The folder comprises HW/SW project files, as well as a ready-to-use SD card image for [Zynq UltraScale+ MPSoC ZCU102](https://www.mouser.it/new/xilinx/xilinx-zynq-ultrascale-zcu102-eval-kit/) boards.|
[genov/][]|Repository of **GenOv** [1].|
[hero/][]|Repository of **HERO** [2,3].|

## Tutorial
We include a [TUTORIAL](tutorial.md) to:
+ Guide the user in its first steps using **GenOv**;
+ Build and run the repository benchmarks;
+ Run the provided ZCU102 image;
+ Offer tips about how to *reuse* the proposed methodology for other projects.

## References
1) **"A RISC-V-based FPGA Overlay to Simplify Embedded Accelerator Deployment" - G. Bellocchi et al. (2021)**
2) "HERO: An open-source research platform for HW/SW exploration of heterogeneous manycore systems" - A. Kurth et al. (2018)
3) "PULP: A parallel ultra low power platform for next generation IoT applications" - D. Rossi et al. (2015)

## Contacts
* E-mail: <name.surname@unimore.it>

[.]:.
[benchmarks/]:benchmarks/
[ex-prj-zcu102/]:ex-prj-zcu102/
[genov/]:https://github.com/gbellocchi/genov
[hero/]:https://github.com/pulp-platform/hero
