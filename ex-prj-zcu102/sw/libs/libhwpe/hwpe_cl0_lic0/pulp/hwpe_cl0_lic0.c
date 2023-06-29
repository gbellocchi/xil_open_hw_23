

/* =====================================================================
 * Project:      LibHWPE
 * Title:        hwpe_cl0_lic0
 * Description:  Software APIs for mmult_hw_pm_cpy.
 * ===================================================================== */
/*
 * Copyright (C) 2022 University of Modena and Reggio Emilia.
 *
 * Author: Gianluca Bellocchi, University of Modena and Reggio Emilia.
 *
 */

/* HWPE */

// Library

#include <libhwpe/hwpe_cl0_lic0.h>

// Hardware abstraction layer

#include <libhwpe/archi/hwpe_cl0_lic0.h>
#include <libhwpe/hal/hwpe_cl0_lic0.h>

/* PULP peripherals */

#include <archi/eu/eu_v3.h>
#include <hal/eu/eu_v3.h>

/* ==================================================================================== */

/* Initialization */

void arov_cl0_lic0_init(mmult_hw_pm_cpy_wrapper_struct *wrapper) {

    // Set type ID -- Accelerator nature
    wrapper->id.type   = MMULT_HW_PM_CPY;

    // Set cluster ID -- About the cluster where the accelerator is integrated
    wrapper->id.cid    = 0;

    // Set accelerator ID -- About the position of the accelerator in the LIC/HCI accelerator region
    wrapper->id.aid    = 0;
};

/* Activation */

int arov_cl0_lic0_activate() {

    // Activate wrapper
    int offload_id;
    hwpe_cg_enable();
    while((offload_id = hwpe_acquire_job()) < 0);
    return offload_id;
};

/* Programming */

void arov_cl0_lic0_program(mmult_hw_pm_cpy_wrapper_struct *wrapper) {

    /*
     * STANDARD REGISTERS
     */

    // Iteration length

    // Number of engine computations before an event is generated

    hwpe_len_iter_set_out_r(wrapper->ctrl.fsm.n_engine_runs - 1);

    // Address generator programming

    hwpe_addr_gen_in1(
        wrapper->in1.addr_gen.trans_size,
        wrapper->in1.addr_gen.line_stride,
        wrapper->in1.addr_gen.line_length,
        wrapper->in1.addr_gen.feat_stride,
        wrapper->in1.addr_gen.feat_length,
        wrapper->in1.addr_gen.feat_roll,
        wrapper->in1.addr_gen.loop_outer,
        wrapper->in1.addr_gen.realign_type,
        wrapper->in1.addr_gen.step
    );
    hwpe_addr_gen_in2(
        wrapper->in2.addr_gen.trans_size,
        wrapper->in2.addr_gen.line_stride,
        wrapper->in2.addr_gen.line_length,
        wrapper->in2.addr_gen.feat_stride,
        wrapper->in2.addr_gen.feat_length,
        wrapper->in2.addr_gen.feat_roll,
        wrapper->in2.addr_gen.loop_outer,
        wrapper->in2.addr_gen.realign_type,
        wrapper->in2.addr_gen.step
    );

    hwpe_addr_gen_out_r(
        wrapper->out_r.addr_gen.trans_size,
        wrapper->out_r.addr_gen.line_stride,
        wrapper->out_r.addr_gen.line_length,
        wrapper->out_r.addr_gen.feat_stride,
        wrapper->out_r.addr_gen.feat_length,
        wrapper->out_r.addr_gen.feat_roll,
        wrapper->out_r.addr_gen.loop_outer,
        wrapper->out_r.addr_gen.realign_type,
        wrapper->out_r.addr_gen.step
    );

    /*
     * CUSTOM REGISTERS
     */

    // Set user custom registers

    /*
     * TCDM REGISTERS
     */

    // Program controller with L1 buffer address

    hwpe_in1_addr_set((int32_t)wrapper->in1.tcdm.ptr);
    hwpe_in2_addr_set((int32_t)wrapper->in2.tcdm.ptr);

    hwpe_out_r_addr_set((int32_t)wrapper->out_r.tcdm.ptr);
};

/* Data memory interaction */

void arov_cl0_lic0_update_buffer_addr(mmult_hw_pm_cpy_wrapper_struct *wrapper) {

    /*
     * TCDM REGISTERS
     */

    // Program controller with L1 buffer address

    hwpe_in1_addr_set((int32_t)wrapper->in1.tcdm.ptr);
    hwpe_in2_addr_set((int32_t)wrapper->in2.tcdm.ptr);

    hwpe_out_r_addr_set((int32_t)wrapper->out_r.tcdm.ptr);
};

/* Processing */

void arov_cl0_lic0_compute() {
    hwpe_trigger_job();
};

/* Synchronization via Event Unit */

void arov_cl0_lic0_wait_eu() {

    // Cores go to sleep and EU is programmed to wait for
    // hardware event coming from the accelerator region.

    __asm__ __volatile__ ("" : : : "memory");
    eu_evt_maskWaitAndClr(1 << ARCHI_CL_EVT_ACC0);
    __asm__ __volatile__ ("" : : : "memory");
};

/* Synchronization via Active Core Polling */

void arov_cl0_lic0_wait_polling() {

    // The core starts polling on the accelerator to verify
    // whether It has terminated its operations.

    while(!hwpe_get_finished()){
      asm volatile ("nop");
    }
};

/* Termination */

int arov_cl0_lic0_is_finished() {

    // Check if accelerator has terminated its operation
    int is_finished = hwpe_get_finished();
    return is_finished;
};

/* Deactivation */

void arov_cl0_lic0_free() {
    hwpe_soft_clear();
    hwpe_cg_disable();
};