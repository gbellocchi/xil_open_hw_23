# ------------------------------------------------------------------- #
# 	Author:      Gianluca Bellocchi <gianluca.bellocchi@unimore.it>   #
# ------------------------------------------------------------------- #

ROOT := $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

CSRCS = main.c
# CFLAGS += -v

ifeq ($(HERO_OV_OPENMP_TESTS),)
$(error HERO_OV_OPENMP_TESTS is not set)
else
-include $(HERO_OV_OPENMP_TESTS)/common/default.mk
endif 

INCPATHS += -I$(PULP_SDK_HOME)/install/include

# Link AROV library
LIBPATHS +=-L../libs/libarov-target/lib/
LDFLAGS_PULP += -larov-target
LDFLAGS += -larov-target

# Link HWPE libraries
LIBPATHS +=-L../libs/libhwpe/hwpe_cl0_lic0/lib/
LDFLAGS_PULP += -lhwpe_cl0_lic0
LDFLAGS += -lhwpe_cl0_lic0