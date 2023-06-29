/**********
Copyright (c) 2018, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********/

#include <stdint.h>
using namespace std;

#include "ap_int.h"
typedef int32_t data_t;

/*
    Take a DATA_SIZE such that:
    - it is divisible by BLOCK_SIZE,
    - the BLOCK_SIZE can actually be allocated in the L1 memory when moving to HERO

    If Double buffering: L1 size (B) / 2 = 64x1024 = (DxBx2 + B^2)xsizeof(datatype) = Rectangular blocks + Squared output block, 
        where: 
            D (B) = data_size = matrix dimension (in Bytes)
            B (B) = block_size = block dimension (in Bytes)
*/

#define DATA_SIZE 512
#define BLOCK_SIZE 8
#define FSM_CALLS 64
#define PARTITION_SIZE 32
#define PARALLEL_STREAMS 16

//Declaring the software function
void mmult_sw( data_t *in1, data_t *in2, data_t *out, data_t dim);

//Declaring the hardware function
void mmult_hw_pm(
    data_t in1_0[PARTITION_SIZE],
    data_t in1_1[PARTITION_SIZE],
    data_t in1_2[PARTITION_SIZE],
    data_t in1_3[PARTITION_SIZE],
    data_t in1_4[PARTITION_SIZE],
    data_t in1_5[PARTITION_SIZE],
    data_t in1_6[PARTITION_SIZE],
    data_t in1_7[PARTITION_SIZE],
    data_t in1_8[PARTITION_SIZE],
    data_t in1_9[PARTITION_SIZE],
    data_t in1_10[PARTITION_SIZE],
    data_t in1_11[PARTITION_SIZE],
    data_t in1_12[PARTITION_SIZE],
    data_t in1_13[PARTITION_SIZE],
    data_t in1_14[PARTITION_SIZE],
    data_t in1_15[PARTITION_SIZE],
    data_t in2_0[PARTITION_SIZE],
    data_t in2_1[PARTITION_SIZE],
    data_t in2_2[PARTITION_SIZE],
    data_t in2_3[PARTITION_SIZE],
    data_t in2_4[PARTITION_SIZE],
    data_t in2_5[PARTITION_SIZE],
    data_t in2_6[PARTITION_SIZE],
    data_t in2_7[PARTITION_SIZE],
    data_t in2_8[PARTITION_SIZE],
    data_t in2_9[PARTITION_SIZE],
    data_t in2_10[PARTITION_SIZE],
    data_t in2_11[PARTITION_SIZE],
    data_t in2_12[PARTITION_SIZE],
    data_t in2_13[PARTITION_SIZE],
    data_t in2_14[PARTITION_SIZE],
    data_t in2_15[PARTITION_SIZE],
    data_t &out);