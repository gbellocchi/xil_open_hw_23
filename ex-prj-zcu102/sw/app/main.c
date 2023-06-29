/*
 * Copyright 2019 ETH Zurich, University of Bologna
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

/* Libraries */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <errno.h>

/* Include platform libraries */
#include <common_structs/def_struct_soc_perf_eval.h>
#include <hero-target.h>
#include <arov-target.h>

/* Include overlay-bench library */
#include "../../../common/overlay-bench.h"

// #define CHECKSUM

#ifdef CHECKSUM

/* Checksum */

void check_result(
    uint32_t* test_res,
    uint32_t* golden_res, 
    unsigned width, unsigned height, unsigned stripe_height)
{
    uint32_t n_analyzed = 0;
    uint32_t n_errors = 0;
    uint32_t err_row = 0;
    uint32_t err_col = 0;

    loop_A: for (unsigned ii = 0; ii < width; ii+=stripe_height){
      loop_B: for (unsigned jj = 0; jj < height; jj+=stripe_height){
        loop_C: for (unsigned i = 0; i < stripe_height; i++){
          loop_D: for (unsigned j = 0; j < stripe_height; j++){
            if( test_res[(ii + i) * width + jj + j] != golden_res[(ii + i) * width + jj + j] ) { 
              n_errors++;
              if(n_errors==1) n_analyzed = (ii + i) * width + jj + j;
              if(n_errors==1) err_row = ii + i;
              if(n_errors==1) err_col = jj + j; 
            }
          }
        }
      }
    }

    if(n_errors == 0)
        printf("Checksum completed SUCCESFULLY!\n\n");
    else{ 
        printf("Number of data analyzed before first error: %d.\n", n_analyzed);
        printf("Number of errors: %d.\n", n_errors);
        printf("Total number of elements: %d.\n\n", width*height);
        printf("ERROR: Result mismatch in Row %u, Column %u!\n", err_row, err_col);
        printf("Tested result is %d.\n", test_res[err_row*width+err_col]);
        printf("Golden result is %d.\n\n", golden_res[err_row*width+err_col]);
    }
}

/* Golden result calculation */

void mmult_sw(uint32_t* in1, uint32_t* in2, uint32_t* out_sw, uint32_t mat_dim, uint32_t stripe_height)
{
  loop_A: for (unsigned ii = 0; ii < mat_dim; ii+=stripe_height){
    loop_B: for (unsigned jj = 0; jj < mat_dim; jj+=stripe_height){
      loop_C: for (unsigned i = 0; i < stripe_height; i++){
        loop_D: for (unsigned j = 0; j < stripe_height; j++){
          loop_E: for (unsigned k = 0; k < mat_dim; k++){
            out_sw[(ii + i) * mat_dim + jj + j] += in1[(ii + i) * mat_dim + k] * in2[(jj + j) * mat_dim + k];
          }
        }
      }
    }
  }
}

#endif

/* Offloaded program */

#pragma omp declare target

int mmult_hw(
  __host uint32_t * __restrict__ l3_in1,
  __host uint32_t * __restrict__ l3_in2,
  __host uint32_t * __restrict__ l3_out,
  uint32_t width, uint32_t height, uint32_t stripe_height)
{
    
  uint32_t t_pulp_0,  t_pulp_1;  

  /* ------------------------------------------------------------------------------- */

  t_pulp_0 = hero_get_clk_counter();

  /* DRAM offsets */

  uint32_t in1_dram_offset;
  uint32_t in2_dram_offset;
  uint32_t out_dram_offset;

  /* TCDM ouput buffer offsets */

  uint32_t l1_buffer_out_offset;

  int cnt_out;
  int cnt_out_limit;

  /* DMA jobs */

  hero_dma_job_t dma_buffer_in1;
  hero_dma_job_t dma_buffer_in2;
  hero_dma_job_t dma_buffer_out;

  /* Hardware accelerator */

  hwpe_addr_gen_struct addr_gen_in1;
  hwpe_addr_gen_struct addr_gen_in2;
  hwpe_addr_gen_struct addr_gen_out;

  /* Allocate L1 with single buffers for each stripe data type */

  DEVICE_PTR l1_buffer_in1 = (DEVICE_PTR)hero_l1malloc(width * stripe_height * sizeof(uint32_t));
  DEVICE_PTR l1_buffer_in2 = (DEVICE_PTR)hero_l1malloc(width * stripe_height * sizeof(uint32_t));
  DEVICE_PTR l1_buffer_out = (DEVICE_PTR)hero_l1malloc(width * stripe_height * sizeof(uint32_t));

  /* Allocate accelerator-rich overlay */

  arov_struct overlay;
  
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.trans_size              = width * stripe_height;
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.line_stride             = 0;
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.line_length             = width * stripe_height;
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.feat_stride             = 0;
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.feat_length             = 1;
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.feat_roll               = 0;
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.loop_outer              = 0;
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.realign_type            = 0; 
  overlay.mmult_hw_pm_cpy_0_0.in1.addr_gen.step                    = 4; 

  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.trans_size              = width * stripe_height;
  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.line_stride             = 0;
  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.line_length             = width * stripe_height;
  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.feat_stride             = 0;
  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.feat_length             = 1;
  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.feat_roll               = 0;
  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.loop_outer              = 0;
  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.realign_type            = 0; 
  overlay.mmult_hw_pm_cpy_0_0.in2.addr_gen.step                    = 4;

  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.trans_size            = stripe_height * stripe_height + 1;
  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.line_stride           = sizeof(uint32_t);
  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.line_length           = 1;
  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.feat_stride           = width * sizeof(uint32_t);
  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.feat_length           = stripe_height;
  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.feat_roll             = stripe_height;
  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.loop_outer            = 0;
  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.realign_type          = 0; 
  overlay.mmult_hw_pm_cpy_0_0.out_r.addr_gen.step                  = 4;

  // Buffer pointers
  overlay.mmult_hw_pm_cpy_0_0.in1.tcdm.ptr                         = (DEVICE_PTR)l1_buffer_in1; 
  overlay.mmult_hw_pm_cpy_0_0.in2.tcdm.ptr                         = (DEVICE_PTR)l1_buffer_in2;
  overlay.mmult_hw_pm_cpy_0_0.out_r.tcdm.ptr                       = (DEVICE_PTR)l1_buffer_out;

  // FSM
  overlay.mmult_hw_pm_cpy_0_0.ctrl.fsm.n_engine_runs               = 1;

  /* Initialize DRAM offsets */

  in1_dram_offset = 0;
  in2_dram_offset = 0;
  out_dram_offset = 0;

  /* Initialize TCDM ouput buffer offsets */

  l1_buffer_out_offset = 0;

  cnt_out = 0;
  cnt_out_limit = 64;

  /* Initialize accelerator and program address generator */

  arov_program(&overlay, 0, 0);

  /* Compute stripe by stripe */

  loop_A: for(int ii = 0; ii < width; ii += stripe_height){

    /* Update in1 DRAM offset */

    in1_dram_offset = ii * width * sizeof(uint32_t);

    /* DMA transfer trigger for IN1 */

    dma_buffer_in1 = hero_memcpy_host2dev_async((DEVICE_PTR)l1_buffer_in1, (HOST_PTR)l3_in1 + in1_dram_offset, width * stripe_height * sizeof(uint32_t));

    loop_B: for(int jj = 0; jj < height; jj += stripe_height){

      /* Update in2 DRAM offset */

      in2_dram_offset = jj * height * sizeof(uint32_t);

      /* Update output buffer */

      l1_buffer_out_offset = jj * sizeof(uint32_t);

      uint32_t new_addr = (uint32_t)l1_buffer_out + (uint32_t)l1_buffer_out_offset;

      overlay.mmult_hw_pm_cpy_0_0.out_r.tcdm.ptr = (uint32_t)new_addr;
      arov_update_buffer_addr(&overlay, 0, 0);

      /* DMA transfer trigger for IN2 */

      dma_buffer_in2 = hero_memcpy_host2dev_async((DEVICE_PTR)l1_buffer_in2, (HOST_PTR)l3_in2 + in2_dram_offset, width * stripe_height * sizeof(uint32_t));
      
      /* Wait for end of input DMA transfers */

      hero_dma_wait(dma_buffer_in1);
      hero_dma_wait(dma_buffer_in2);

      /* Computation */

      arov_compute(&overlay, 0, 0);
      arov_wait_eu(&overlay, 0, 0);

    }

    /* DMA transfer trigger for OUT */

    uint64_t ext_out_addr = (uint64_t)l3_out + (uint64_t)out_dram_offset;
    uint32_t local_out_addr = (uint32_t)l1_buffer_out;
           
    hero_memcpy_dev2host(ext_out_addr, local_out_addr, width * stripe_height * sizeof(uint32_t));

    /* Update out DRAM offset */

    out_dram_offset += stripe_height * width * sizeof(uint32_t);

  }

  /* Cleanup */

  hero_l1free((DEVICE_PTR)l1_buffer_in1);
  hero_l1free((DEVICE_PTR)l1_buffer_in2);
  hero_l1free((DEVICE_PTR)l1_buffer_out);

  /* ------------------------------------------------------------------------------- */

  t_pulp_1 = hero_get_clk_counter();

  return 0;
}

#pragma omp end declare target

/* Main program */

int main(int argc, char *argv[])
{
  printf("\n|-------------------|\n");
  printf("| Test - Beginning. |");
  printf("\n|-------------------|\n");

  /* Performance measurement */

  timer_host t_alloc;
  timer_host t_fpga_offload;
  timer_host t_clean;

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  printf("\n|----------------------------------------------------|\n");
  printf("| DRAM - Declaration, allocation and initialization. |");
  printf("\n|----------------------------------------------------|\n\n");

clock_gettime(CLOCK_REALTIME, &t_alloc.t0);

  /* Matrix dimension */

  unsigned width          = 512;
  unsigned height         = 512;
  unsigned stripe_height  = 8;

  /* General */

  int pulp_error;

  /* Allocate DRAM arrays */

  uint32_t* l3_in1      = (__host uint32_t*)hero_l3malloc(width*height*sizeof(uint32_t));
  uint32_t* l3_in2      = (__host uint32_t*)hero_l3malloc(width*height*sizeof(uint32_t)); 
  uint32_t* l3_test     = (__host uint32_t*)hero_l3malloc(width*height*sizeof(uint32_t)); 

  if ( (l3_in1 == NULL) || (l3_in2 == NULL) || (l3_test == NULL) ) {
    printf("ERROR: malloc() failed!\n");
    return -ENOMEM;
  }

clock_gettime(CLOCK_REALTIME, &t_alloc.t1);

t_alloc.t_meas = ((t_alloc.t1.tv_sec - t_alloc.t0.tv_sec) + (t_alloc.t1.tv_nsec - t_alloc.t0.tv_nsec)/1000000000.0)*1000.0;

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /* I/O arrays initialization */

  for(int i=0; i<width*height; i++){
    l3_in1[i] = rand() % 255;
    l3_in2[i] = rand() % 255;
  }
  memset(l3_test, 0, width * height * sizeof(uint32_t));

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /* Allocate and initialize golden results */

  uint32_t* l3_golden   = (__host uint32_t*)hero_l3malloc(width*height*sizeof(uint32_t)); 

  if ( (l3_golden == NULL) ) {
    printf("ERROR: malloc() failed!\n");
    return -ENOMEM;
  }

  memset(l3_golden, 0, width * height * sizeof(uint32_t));

#ifdef CHECKSUM

  /* Check L3 test/golden results have been correctly inizialized */

  printf("Initialization checksum... ");
  check_result(l3_test, l3_golden, width, height, stripe_height); 

  /* Calculate golden results */

  mmult_sw( l3_in1, l3_in2, l3_golden, width, stripe_height);

#endif

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  printf("|------------------------|\n");
  printf("| Execute MMULT on PULP. |");
  printf("\n|------------------------|\n\n");

  /* Warm-up */

  unsigned tmp_1 = 1;
  unsigned tmp_2 = 2;
  #pragma omp target device(BIGPULP_MEMCPY) \
    map(to:         l3_in1[0:width*height], l3_in2[0:width*height], width, stripe_height)                            \
    map(tofrom:     l3_test[0:width*height])
  {
      tmp_2 = tmp_1;
  }
  tmp_1 = tmp_2;

clock_gettime(CLOCK_REALTIME, &t_fpga_offload.t0);

  /* Offloaded application */

  #pragma omp target device(BIGPULP_MEMCPY) \
              map(to:         l3_in1[0:width*height], l3_in2[0:width*height], width, stripe_height)                            \
              map(from:       l3_test[0:width*height]) 
  {
    pulp_error = mmult_hw(l3_in1, l3_in2, l3_test, width, height, stripe_height);
  }

clock_gettime(CLOCK_REALTIME, &t_fpga_offload.t1);

t_fpga_offload.t_meas = ((t_fpga_offload.t1.tv_sec - t_fpga_offload.t0.tv_sec) + (t_fpga_offload.t1.tv_nsec - t_fpga_offload.t0.tv_nsec)/1000000000.0)*1000.0;

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifdef CHECKSUM

  printf("\n|-----------|\n");
  printf("| Checksum. |");
  printf("\n|-----------|\n\n");

  if(pulp_error) return 1;

  /* Post-computation checksum */

  printf("Post-computation checksum... ");
  check_result(l3_test, l3_golden, width, height, stripe_height);

#endif

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  printf("\n|---------|\n");
  printf("| Cleanup. |");
  printf("\n|---------|\n\n");

clock_gettime(CLOCK_REALTIME, &t_clean.t0);

  /* Cleanup */  

  hero_l3free(l3_in1);
  hero_l3free(l3_in2);
  hero_l3free(l3_test);
  hero_l3free(l3_golden);

clock_gettime(CLOCK_REALTIME, &t_clean.t1);

t_clean.t_meas = ((t_clean.t1.tv_sec - t_clean.t0.tv_sec) + (t_clean.t1.tv_nsec - t_clean.t0.tv_nsec)/1000000000.0)*1000.0;

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /* Results - ARM measurements */

  printf("\n|-----------------------------|\n");
  printf("| Results - ARM measurements. |");
  printf("\n|-----------------------------|\n");

  printf("\n  - I/O arrays allocation and initialization:\n");
  printf("  -     - Execution time (ms):    %.3f ms\n", t_alloc.t_meas );

  printf("\n  - Offloading + PULP application:\n");
  printf("  -     - Execution time (ms):    %.3f ms\n", t_fpga_offload.t_meas);

  printf("\n  - Cleaning:\n");
  printf("  -     - Execution time (ms):    %.3f ms\n", t_clean.t_meas );

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  printf("\n|-------------|\n");
  printf("| Test - End. |");
  printf("\n|-------------|\n\n");

  return 0;
}