
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

#ifndef __HAL_HWPE_CL0_LIC0_H__
#define __HAL_HWPE_CL0_LIC0_H__

#define HWPE_ADDR_BASE ARCHI_FC_HWPE_ADDR
#define HWPE_ADDR_SPACE 0x00000100

#define hwpe_write32(add, val_) (*(volatile unsigned int *)(long)(add) = val_)

static inline uint32_t hwpe_read32(uint32_t add)
{
  __asm__ __volatile__ ("" : : : "memory");
  uint32_t result = *(volatile uint32_t *)add;
  asm volatile("nop;");
  __asm__ __volatile__ ("" : : : "memory");
  return result;
}

#define HWPE_WRITE(value, offset) hwpe_write32(ARCHI_HWPE_ADDR_BASE + (offset), (value))
#define HWPE_READ(offset) hwpe_read32(ARCHI_HWPE_ADDR_BASE + (offset))

/* uloop hal */

static inline void hwpe_nb_iter_set(unsigned int value) {
  HWPE_WRITE(value, MMULT_HW_PM_CPY_REG_NB_ITER);
}

static inline void hwpe_linestride_set(unsigned int value) {
  HWPE_WRITE(value, MMULT_HW_PM_CPY_REG_LINESTRIDE);
}

static inline void hwpe_tilestride_set(unsigned int value) {
  HWPE_WRITE(value, MMULT_HW_PM_CPY_REG_TILESTRIDE);
}

static inline void hwpe_len_iter_set_out_r(unsigned int value) {
  HWPE_WRITE(value, MMULT_HW_PM_CPY_REG_CNT_LIMIT_OUT_R);
}

/* address generator hal - inputs */
static inline void hwpe_addr_gen_in1(
  unsigned int in1_trans_size,
  unsigned int in1_line_stride,
  unsigned int in1_line_length,
  unsigned int in1_feat_stride,
  unsigned int in1_feat_length,
  unsigned int in1_feat_roll,
  unsigned int in1_loop_outer,
  unsigned int in1_realign_type,
  unsigned int in1_step)
{
  HWPE_WRITE(in1_trans_size,    MMULT_HW_PM_CPY_REG_IN1_TRANS_SIZE  );
  HWPE_WRITE(in1_line_stride,   MMULT_HW_PM_CPY_REG_IN1_LINE_STRIDE );
  HWPE_WRITE(in1_line_length,   MMULT_HW_PM_CPY_REG_IN1_LINE_LENGTH );
  HWPE_WRITE(in1_feat_stride,   MMULT_HW_PM_CPY_REG_IN1_FEAT_STRIDE );
  HWPE_WRITE(in1_feat_length,   MMULT_HW_PM_CPY_REG_IN1_FEAT_LENGTH );
  HWPE_WRITE(in1_feat_roll,     MMULT_HW_PM_CPY_REG_IN1_FEAT_ROLL   );
  HWPE_WRITE(in1_loop_outer,    MMULT_HW_PM_CPY_REG_IN1_LOOP_OUTER  );
  HWPE_WRITE(in1_realign_type,  MMULT_HW_PM_CPY_REG_IN1_REALIGN_TYPE);
  HWPE_WRITE(in1_step,          MMULT_HW_PM_CPY_REG_IN1_STEP        );
}
/* address generator hal - inputs */
static inline void hwpe_addr_gen_in2(
  unsigned int in2_trans_size,
  unsigned int in2_line_stride,
  unsigned int in2_line_length,
  unsigned int in2_feat_stride,
  unsigned int in2_feat_length,
  unsigned int in2_feat_roll,
  unsigned int in2_loop_outer,
  unsigned int in2_realign_type,
  unsigned int in2_step)
{
  HWPE_WRITE(in2_trans_size,    MMULT_HW_PM_CPY_REG_IN2_TRANS_SIZE  );
  HWPE_WRITE(in2_line_stride,   MMULT_HW_PM_CPY_REG_IN2_LINE_STRIDE );
  HWPE_WRITE(in2_line_length,   MMULT_HW_PM_CPY_REG_IN2_LINE_LENGTH );
  HWPE_WRITE(in2_feat_stride,   MMULT_HW_PM_CPY_REG_IN2_FEAT_STRIDE );
  HWPE_WRITE(in2_feat_length,   MMULT_HW_PM_CPY_REG_IN2_FEAT_LENGTH );
  HWPE_WRITE(in2_feat_roll,     MMULT_HW_PM_CPY_REG_IN2_FEAT_ROLL   );
  HWPE_WRITE(in2_loop_outer,    MMULT_HW_PM_CPY_REG_IN2_LOOP_OUTER  );
  HWPE_WRITE(in2_realign_type,  MMULT_HW_PM_CPY_REG_IN2_REALIGN_TYPE);
  HWPE_WRITE(in2_step,          MMULT_HW_PM_CPY_REG_IN2_STEP        );
}

/* address generator hal - outputs */
static inline void hwpe_addr_gen_out_r(
  unsigned int  out_r_trans_size,
  unsigned int  out_r_line_stride,
  unsigned int  out_r_line_length,
  unsigned int  out_r_feat_stride,
  unsigned int  out_r_feat_length,
  unsigned int  out_r_feat_roll,
  unsigned int  out_r_loop_outer,
  unsigned int  out_r_realign_type,
  unsigned int  out_r_step)
{
  HWPE_WRITE(out_r_trans_size,    MMULT_HW_PM_CPY_REG_OUT_R_TRANS_SIZE  );
  HWPE_WRITE(out_r_line_stride,   MMULT_HW_PM_CPY_REG_OUT_R_LINE_STRIDE );
  HWPE_WRITE(out_r_line_length,   MMULT_HW_PM_CPY_REG_OUT_R_LINE_LENGTH );
  HWPE_WRITE(out_r_feat_stride,   MMULT_HW_PM_CPY_REG_OUT_R_FEAT_STRIDE );
  HWPE_WRITE(out_r_feat_length,   MMULT_HW_PM_CPY_REG_OUT_R_FEAT_LENGTH );
  HWPE_WRITE(out_r_feat_roll,     MMULT_HW_PM_CPY_REG_OUT_R_FEAT_ROLL   );
  HWPE_WRITE(out_r_loop_outer,    MMULT_HW_PM_CPY_REG_OUT_R_LOOP_OUTER  );
  HWPE_WRITE(out_r_realign_type,  MMULT_HW_PM_CPY_REG_OUT_R_REALIGN_TYPE);
  HWPE_WRITE(out_r_step,          MMULT_HW_PM_CPY_REG_OUT_R_STEP        );
}

/* basic hal */

static inline void hwpe_trigger_job() {
  HWPE_WRITE(0, MMULT_HW_PM_CPY_REG_TRIGGER);
}

static inline int hwpe_acquire_job() {
  return HWPE_READ(MMULT_HW_PM_CPY_REG_ACQUIRE);
}

static inline int hwpe_get_finished() {
  return HWPE_READ(MMULT_HW_PM_CPY_REG_FINISHED);
}

static inline unsigned int hwpe_get_status() {
  return HWPE_READ(MMULT_HW_PM_CPY_REG_STATUS);
}

static inline void hwpe_soft_clear() {
  HWPE_WRITE(0, MMULT_HW_PM_CPY_REG_SOFT_CLEAR);
}

static inline void hwpe_cg_enable() {
  return;
}

static inline void hwpe_cg_disable() {
  return;
}

static inline void hwpe_bytecode_set(unsigned int offs, unsigned int value) {
  HWPE_WRITE(value, MMULT_HW_PM_CPY_REG_BYTECODE+offs);
}

/* tcdm master port hal */

// input in1
static inline void hwpe_in1_addr_set(int32_t value) {
  HWPE_WRITE(value, MMULT_HW_PM_CPY_REG_IN1_ADDR);
}
// input in2
static inline void hwpe_in2_addr_set(int32_t value) {
  HWPE_WRITE(value, MMULT_HW_PM_CPY_REG_IN2_ADDR);
}

// output out_r
static inline void hwpe_out_r_addr_set(int32_t value) {
  HWPE_WRITE(value, MMULT_HW_PM_CPY_REG_OUT_R_ADDR);
}

#endif /* __HAL_HWPE_H__ */

