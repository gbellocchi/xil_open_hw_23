ROOT := $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

# Boot board.
boot_zcu102: 
	@cd petalinux && make update_output install boot;

# Build benchmark application.
build_app:
	@cd app && make build_app;
build_env:
	@cd app && make build_env;
clean_env:
	@cd app && make clean_local;
	
# Build hls designs.
get_rtl:
	@cd hls && make get_rtl;
build_hls:
	@cd hls && make run_hls;
clean_hls:
	@cd hls && make clean;

# Build fpga designs.
build_fpga:
	@cd fpga && make run_fpga;
clean_fpga:
	@cd fpga && make clean;

# Build petalinux projects.
build_petalinux:
	@cd petalinux && make run_petalinux;
update_output:
	@cd petalinux && make update_output;
clean_petalinux:
	@cd petalinux && make clean_petalinux clean_output;
	
