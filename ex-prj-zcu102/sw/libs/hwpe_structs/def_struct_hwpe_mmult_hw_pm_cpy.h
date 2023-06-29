

/* =====================================================================
 * Project:      HWPE structures
 * Title:        def_struct_mmult_hw_pm_cpy
 * Description:  Definition of C structures for HWPE wrappers.
 * ===================================================================== */
/*
 * Copyright (C) 2022 University of Modena and Reggio Emilia.
 *
 * Author: Gianluca Bellocchi, University of Modena and Reggio Emilia.
 *
 */

#ifndef __HWPE_STRUCTS_MMULT_HW_PM_CPY_H__
#define __HWPE_STRUCTS_MMULT_HW_PM_CPY_H__

#include <common_structs/def_struct_hwpe_common.h>

/* Definition - Types */

typedef struct hwpe_stream_struct mmult_hw_pm_cpy_stream_struct;
typedef struct mmult_hw_pm_cpy_custom_regs_struct mmult_hw_pm_cpy_custom_regs_struct;
typedef struct mmult_hw_pm_cpy_ctrl_struct mmult_hw_pm_cpy_ctrl_struct;
typedef struct mmult_hw_pm_cpy_wrapper_struct mmult_hw_pm_cpy_wrapper_struct;

/* Definition - Functions */

typedef void (*Program_Mmult_Hw_Pm_Cpy)(mmult_hw_pm_cpy_wrapper_struct *_wrapper);
typedef void (*Command_Mmult_Hw_Pm_Cpy)();

/* Definition - Structs */

struct mmult_hw_pm_cpy_custom_regs_struct {
};

struct mmult_hw_pm_cpy_ctrl_struct {
    hwpe_engine_struct engine;
    hwpe_fsm_struct fsm;
    mmult_hw_pm_cpy_custom_regs_struct custom_regs;
};

struct mmult_hw_pm_cpy_wrapper_struct {

    hwpe_id id;

    mmult_hw_pm_cpy_stream_struct in1;
    mmult_hw_pm_cpy_stream_struct in2;
    mmult_hw_pm_cpy_stream_struct out_r;

    mmult_hw_pm_cpy_ctrl_struct           ctrl;

    Program_Mmult_Hw_Pm_Cpy init;
    Program_Mmult_Hw_Pm_Cpy program;
    Program_Mmult_Hw_Pm_Cpy update_buffer_addr;
    Command_Mmult_Hw_Pm_Cpy compute;
    Command_Mmult_Hw_Pm_Cpy wait;
    Command_Mmult_Hw_Pm_Cpy clear;
};

#endif