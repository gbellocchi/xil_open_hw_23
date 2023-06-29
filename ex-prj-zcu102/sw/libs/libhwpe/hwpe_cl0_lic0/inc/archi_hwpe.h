

/*
 * Copyright (C) 2018-2019 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Authors:     Francesco Conti <fconti@iis.ee.ethz.ch>
 * Contribute:  Gianluca Bellocchi <gianluca.bellocchi@unimore.it>
 */

#ifndef __ARCHI_HWPE_CL0_LIC0_H__
#define __ARCHI_HWPE_CL0_LIC0_H__

/* HWPE base address (with cluster alias) */

#define ARCHI_HWPE_ADDR_BASE 0x1b202000

/* Event unit */
// NB: Might be also referred to as ARCHI_HWPE_EU_OFFSET

#ifndef ARCHI_CL_EVT_ACC0
#define ARCHI_CL_EVT_ACC0 12
#endif

/* Basic archi */

#define MMULT_HW_PM_CPY_REG_TRIGGER                                 0x0

#define MMULT_HW_PM_CPY_REG_ACQUIRE                                 0x4

#define MMULT_HW_PM_CPY_REG_FINISHED                                0x8

#define MMULT_HW_PM_CPY_REG_STATUS                                  0xc

#define MMULT_HW_PM_CPY_REG_RUNNING_JOB                             0x10

#define MMULT_HW_PM_CPY_REG_SOFT_CLEAR                              0x14

/* Microcode processor registers archi */

  /* Microcode processor */

#define MMULT_HW_PM_CPY_REG_BYTECODE                                 0x20

#define MMULT_HW_PM_CPY_REG_BYTECODE0_OFFS                           0x0

#define MMULT_HW_PM_CPY_REG_BYTECODE1_OFFS                           0x4

#define MMULT_HW_PM_CPY_REG_BYTECODE2_OFFS                           0x8

#define MMULT_HW_PM_CPY_REG_BYTECODE3_OFFS                           0xc

#define MMULT_HW_PM_CPY_REG_BYTECODE4_OFFS                           0x10

#define MMULT_HW_PM_CPY_REG_BYTECODE5_LOOPS0_OFFS                    0x14

#define MMULT_HW_PM_CPY_REG_LOOPS1_OFFS                              0x18

/* TCDM registers archi */

// Input master ports
#define MMULT_HW_PM_CPY_REG_IN1_ADDR                         0x40

#define MMULT_HW_PM_CPY_REG_IN2_ADDR                         0x44

// Output master ports
#define MMULT_HW_PM_CPY_REG_OUT_R_ADDR                        0x48

/* Standard registers archi */

#define MMULT_HW_PM_CPY_REG_NB_ITER                         0x4c

#define MMULT_HW_PM_CPY_REG_LINESTRIDE                0x50

#define MMULT_HW_PM_CPY_REG_TILESTRIDE                0x54

#define MMULT_HW_PM_CPY_REG_CNT_LIMIT_OUT_R                 0x58

/* Custom registers archi */

/* Address generator archi */

// Input stream - in1 (programmable)
#define MMULT_HW_PM_CPY_REG_IN1_TRANS_SIZE                  0x5c
#define MMULT_HW_PM_CPY_REG_IN1_LINE_STRIDE                 0x60
#define MMULT_HW_PM_CPY_REG_IN1_LINE_LENGTH                 0x64
#define MMULT_HW_PM_CPY_REG_IN1_FEAT_STRIDE                 0x68
#define MMULT_HW_PM_CPY_REG_IN1_FEAT_LENGTH                 0x6c
#define MMULT_HW_PM_CPY_REG_IN1_FEAT_ROLL                   0x70
#define MMULT_HW_PM_CPY_REG_IN1_LOOP_OUTER                  0x74
#define MMULT_HW_PM_CPY_REG_IN1_REALIGN_TYPE                0x78
#define MMULT_HW_PM_CPY_REG_IN1_STEP                        0x7c
// Input stream - in2 (programmable)
#define MMULT_HW_PM_CPY_REG_IN2_TRANS_SIZE                  0x80
#define MMULT_HW_PM_CPY_REG_IN2_LINE_STRIDE                 0x84
#define MMULT_HW_PM_CPY_REG_IN2_LINE_LENGTH                 0x88
#define MMULT_HW_PM_CPY_REG_IN2_FEAT_STRIDE                 0x8c
#define MMULT_HW_PM_CPY_REG_IN2_FEAT_LENGTH                 0x90
#define MMULT_HW_PM_CPY_REG_IN2_FEAT_ROLL                   0x94
#define MMULT_HW_PM_CPY_REG_IN2_LOOP_OUTER                  0x98
#define MMULT_HW_PM_CPY_REG_IN2_REALIGN_TYPE                0x9c
#define MMULT_HW_PM_CPY_REG_IN2_STEP                        0xa0

// Input stream - out_r (programmable)
#define MMULT_HW_PM_CPY_REG_OUT_R_TRANS_SIZE                 0xa4
#define MMULT_HW_PM_CPY_REG_OUT_R_LINE_STRIDE                0xa8
#define MMULT_HW_PM_CPY_REG_OUT_R_LINE_LENGTH                0xac
#define MMULT_HW_PM_CPY_REG_OUT_R_FEAT_STRIDE                0xb0
#define MMULT_HW_PM_CPY_REG_OUT_R_FEAT_LENGTH                0xb4
#define MMULT_HW_PM_CPY_REG_OUT_R_FEAT_ROLL                  0xb8
#define MMULT_HW_PM_CPY_REG_OUT_R_LOOP_OUTER                 0xbc
#define MMULT_HW_PM_CPY_REG_OUT_R_REALIGN_TYPE               0xc0
#define MMULT_HW_PM_CPY_REG_OUT_R_STEP                       0xc4

#endif
