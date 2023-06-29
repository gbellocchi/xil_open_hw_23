ROOT := $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
DIRECTORIES := 01_x_hw  02_x_bl  03_x_bl_pm  04_x_loop  05_x_pm

# Build benchmark application
build_app:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make build_app;)
build_env:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make build_env;)
clean_env:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make clean_env;)

# Build petalinux projects
update_output:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make update_output;)
build_petalinux:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make build_petalinux;)
clean_petalinux:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make clean_petalinux;)

# Build fpga designs
build_fpga:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make build_fpga;)
clean_fpga:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make clean_fpga;)

# Build hls designs
get_rtl:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make get_rtl;)
build_hls:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make build_hls;)
clean_hls:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir) && make clean_hls;)