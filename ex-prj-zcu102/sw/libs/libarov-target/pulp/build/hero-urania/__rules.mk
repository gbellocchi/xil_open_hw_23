
#
# HEADER RULES
#

define declareInstallFile

$(PULP_SDK_INSTALL)/$(1): $(1)
	install -D $(1) $$@

INSTALL_HEADERS += $(PULP_SDK_INSTALL)/$(1)

endef


define declareWsInstallFile

$(PULP_SDK_WS_INSTALL)/$(1): $(1)
	install -D $(1) $$@

WS_INSTALL_HEADERS += $(PULP_SDK_WS_INSTALL)/$(1)

endef


$(foreach file, $(INSTALL_FILES), $(eval $(call declareInstallFile,$(file))))

$(foreach file, $(WS_INSTALL_FILES), $(eval $(call declareWsInstallFile,$(file))))


#
# CC RULES for domain: cluster
#

PULP_LIB_NAME_arov-target ?= arov-target

PULP_CL_EXTRA_SRCS_arov-target = 
PULP_CL_EXTRA_ASM_SRCS_arov-target = 
PULP_CL_EXTRA_OMP_SRCS_arov-target = 

arov-target_CL_OBJS =     $(patsubst %.cpp,$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/cl/%.o, $(patsubst %.c,$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/cl/%.o, $(PULP_LIB_CL_SRCS_arov-target) $(PULP_CL_SRCS_arov-target) $(PULP_LIB_CL_SRCS) $(PULP_APP_SRCS) $(PULP_CL_EXTRA_SRCS_arov-target)))
arov-target_CL_ASM_OBJS = $(patsubst %.S,$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/cl/%.o, $(PULP_LIB_CL_ASM_SRCS_arov-target) $(PULP_CL_ASM_SRCS_arov-target) $(PULP_LIB_CL_ASM_SRCS) $(PULP_APP_ASM_SRCS) $(PULP_CL_EXTRA_ASM_SRCS_arov-target))
arov-target_CL_OMP_OBJS = $(patsubst %.c,$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/cl/omp/%.o, $(PULP_LIB_CL_OMP_SRCS_arov-target) $(PULP_CL_OMP_SRCS_arov-target) $(PULP_LIB_CL_OMP_SRCS) $(PULP_APP_OMP_SRCS) $(PULP_CL_EXTRA_OMP_SRCS_arov-target))

ifneq '$(arov-target_CL_OMP_OBJS)' ''
PULP_LDFLAGS_arov-target += $(PULP_OMP_LDFLAGS_arov-target)
endif

-include $(arov-target_CL_OBJS:.o=.d)
-include $(arov-target_CL_ASM_OBJS:.o=.d)
-include $(arov-target_CL_OMP_OBJS:.o=.d)

arov-target_cl_cflags = $(PULP_CL_ARCH_CFLAGS) $(PULP_CFLAGS) $(PULP_CL_CFLAGS) $(PULP_CFLAGS_arov-target) $(PULP_CL_CFLAGS_arov-target) $(PULP_LIB_CFLAGS_arov-target)
arov-target_cl_omp_cflags = $(arov-target_cl_cflags) $(PULP_OMP_CFLAGS) $(PULP_CL_OMP_CFLAGS) $(PULP_OMP_CFLAGS_arov-target) $(PULP_CL_OMP_CFLAGS_arov-target)

$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/cl/%.o: %.c
	@mkdir -p `dirname $@`
	$(PULP_CL_CC) $(arov-target_cl_cflags) -MMD -MP -c $< -o $@

$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/cl/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(PULP_CL_CC) $(arov-target_cl_cflags) -MMD -MP -c $< -o $@

$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/cl/%.o: %.S
	@mkdir -p `dirname $@`
	$(PULP_CL_CC) $(arov-target_cl_cflags) -DLANGUAGE_ASSEMBLY -MMD -MP -c $< -o $@

$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/cl/omp/%.o: %.c
	@mkdir -p `dirname $@`
	touch libgomp.spec
	$(PULP_CL_CC) $(arov-target_cl_omp_cflags) -MMD -MP -c $< -o $@

arov-target_OBJS += $(arov-target_CL_OBJS) $(arov-target_CL_ASM_OBJS) $(arov-target_CL_OMP_OBJS)



#
# CC RULES for domain: fabric_controller
#

PULP_LIB_NAME_arov-target ?= arov-target

PULP_FC_EXTRA_SRCS_arov-target = /home/gbellocchi/workspace_pulp/xil_open_hw_23/benchmarks/pulp/matmul/04_hw_pm_cpy/libs/libarov-target/pulp/build/hero-urania/rt_conf.c
PULP_FC_EXTRA_ASM_SRCS_arov-target = 
PULP_FC_EXTRA_OMP_SRCS_arov-target = 

arov-target_FC_OBJS =     $(patsubst %.cpp,$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/fc/%.o, $(patsubst %.c,$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/fc/%.o, $(PULP_LIB_FC_SRCS_arov-target) $(PULP_FC_SRCS_arov-target) $(PULP_LIB_FC_SRCS)  $(PULP_FC_EXTRA_SRCS_arov-target)))
arov-target_FC_ASM_OBJS = $(patsubst %.S,$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/fc/%.o, $(PULP_LIB_FC_ASM_SRCS_arov-target) $(PULP_FC_ASM_SRCS_arov-target) $(PULP_LIB_FC_ASM_SRCS)  $(PULP_FC_EXTRA_ASM_SRCS_arov-target))
arov-target_FC_OMP_OBJS = $(patsubst %.c,$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/fc/omp/%.o, $(PULP_LIB_FC_OMP_SRCS_arov-target) $(PULP_FC_OMP_SRCS_arov-target) $(PULP_LIB_FC_OMP_SRCS)  $(PULP_FC_EXTRA_OMP_SRCS_arov-target))

ifneq '$(arov-target_FC_OMP_OBJS)' ''
PULP_LDFLAGS_arov-target += $(PULP_OMP_LDFLAGS_arov-target)
endif

-include $(arov-target_FC_OBJS:.o=.d)
-include $(arov-target_FC_ASM_OBJS:.o=.d)
-include $(arov-target_FC_OMP_OBJS:.o=.d)

arov-target_fc_cflags = $(PULP_FC_ARCH_CFLAGS) $(PULP_CFLAGS) $(PULP_FC_CFLAGS) $(PULP_CFLAGS_arov-target) $(PULP_FC_CFLAGS_arov-target) $(PULP_LIB_CFLAGS_arov-target)
arov-target_fc_omp_cflags = $(arov-target_fc_cflags) $(PULP_OMP_CFLAGS) $(PULP_FC_OMP_CFLAGS) $(PULP_OMP_CFLAGS_arov-target) $(PULP_FC_OMP_CFLAGS_arov-target)

$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/fc/%.o: %.c
	@mkdir -p `dirname $@`
	$(PULP_FC_CC) $(arov-target_fc_cflags) -MMD -MP -c $< -o $@

$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/fc/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(PULP_FC_CC) $(arov-target_fc_cflags) -MMD -MP -c $< -o $@

$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/fc/%.o: %.S
	@mkdir -p `dirname $@`
	$(PULP_FC_CC) $(arov-target_fc_cflags) -DLANGUAGE_ASSEMBLY -MMD -MP -c $< -o $@

$(CONFIG_BUILD_DIR)/$(PULP_LIB_NAME_arov-target)/fc/omp/%.o: %.c
	@mkdir -p `dirname $@`
	touch libgomp.spec
	$(PULP_FC_CC) $(arov-target_fc_omp_cflags) -MMD -MP -c $< -o $@

arov-target_OBJS += $(arov-target_FC_OBJS) $(arov-target_FC_ASM_OBJS) $(arov-target_FC_OMP_OBJS)



#
# AR RULES for library: arov-target
#

PULP_LIB_NAME_arov-target ?= arov-target

$(CONFIG_BUILD_DIR)/lib$(PULP_LIB_NAME_arov-target).a: $(arov-target_OBJS)
	@mkdir -p `dirname $@`
	@rm -f $@
	$(PULP_AR) -r $@ $^

$(PULP_SDK_INSTALL)/lib/hero-urania/lib$(PULP_LIB_NAME_arov-target).a: $(CONFIG_BUILD_DIR)/lib$(PULP_LIB_NAME_arov-target).a
	@mkdir -p `dirname $@`
	cp $^ $@ 


TARGETS += $(CONFIG_BUILD_DIR)/lib$(PULP_LIB_NAME_arov-target).a
CLEAN_TARGETS += $(CONFIG_BUILD_DIR)/lib$(PULP_LIB_NAME_arov-target).a $($(PULP_LIB_NAME_arov-target)_OBJS)
INSTALL_TARGETS += $(PULP_SDK_INSTALL)/lib/hero-urania/lib$(PULP_LIB_NAME_arov-target).a


header:: $(INSTALL_HEADERS) $(WS_INSTALL_HEADERS)

fullclean::
	rm -rf $(CONFIG_BUILD_DIR)

clean:: $(GEN_TARGETS) $(CONFIG_BUILD_DIR)/config.mk
	rm -rf $(CLEAN_TARGETS)

prepare:: $(GEN_TARGETS) $(CONFIG_BUILD_DIR)/config.mk
	pulp-run $(pulpRunOpt) prepare

runner:: $(GEN_TARGETS) $(CONFIG_BUILD_DIR)/config.mk
	pulp-run $(pulpRunOpt) $(RUNNER_CMD)

power:: $(GEN_TARGETS) $(CONFIG_BUILD_DIR)/config.mk
	pulp-run $(pulpRunOpt) power

gen: $(GEN_TARGETS_FORCE)

build:: $(GEN_TARGETS) $(CONFIG_BUILD_DIR)/config.mk $(TARGETS)

all:: build prepare

install:: $(INSTALL_TARGETS)

run::
	pulp-run $(pulpRunOpt)

.PHONY: clean header prepare all install run
