ROOT 			:= $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
DIRECTORIES 	:= 01_o_sw 02_o_sw_db 03_o_hw 04_o_hw_pm_cpy 05_o_hw_pm
	
# Build benchmark application.
build_app:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir)/app && make -s all;)
clean_app:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir)/app && make -s clean;)
	
# Build hls designs.
get_rtl:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir)/hls && make get_rtl;)
build_hls:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir)/hls && make -s run_hls;)
clean_hls:
	@$(foreach dir,$(DIRECTORIES), cd $(ROOT)/$(dir)/hls && make -s clean;)