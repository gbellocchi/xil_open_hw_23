# Repository
git submodule update --init --recursive
export XIL_OPENHW_PATH=*path-to-xil_open_hw_23*

# GenOv
make py_env_init
make clean all

# Run PULP benchmarks
Open ${XIL_OPENHW_PATH}/build/local.cfg and insert "BR2_HERO_BITSTREAM" with one of the following paths:

- "*full-path-to-xil_open_hw_23*/build/pulp/hw/hw_baseline/hero_exilzcu102.sdk//hero_exilzcu102_wrapper.bit"
- "*full-path-to-xil_open_hw_23*/build/pulp/hw/hw_baseline/hero_exilzcu102.sdk//hero_exilzcu102_wrapper.bit"
- "*full-path-to-xil_open_hw_23*/build/pulp/hw/hw_baseline/hero_exilzcu102.sdk//hero_exilzcu102_wrapper.bit"