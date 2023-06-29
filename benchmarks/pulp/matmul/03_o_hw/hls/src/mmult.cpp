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

#include "mmult.h"

void mmult_sw( data_t *in1,   
               data_t *in2,   
               data_t *out,   
               data_t mat_dim  
             )
{
    for (int i = 0; i < mat_dim; i++){
        for (int j = 0; j < mat_dim; j++){
            for (int k = 0; k < mat_dim; k++){
                out[i * mat_dim + j] += in1[i * mat_dim + k] * in2[k * mat_dim  + j];
            }
        }
    }
}

void mmult_hw(
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
    data_t &out)
{

    #pragma HLS INTERFACE axis port=in1_0
    #pragma HLS INTERFACE axis port=in1_1
    #pragma HLS INTERFACE axis port=in1_2
    #pragma HLS INTERFACE axis port=in1_3
    #pragma HLS INTERFACE axis port=in1_4
    #pragma HLS INTERFACE axis port=in1_5
    #pragma HLS INTERFACE axis port=in1_6
    #pragma HLS INTERFACE axis port=in1_7
    #pragma HLS INTERFACE axis port=in1_8
    #pragma HLS INTERFACE axis port=in1_9
    #pragma HLS INTERFACE axis port=in1_10
    #pragma HLS INTERFACE axis port=in1_11
    #pragma HLS INTERFACE axis port=in1_12
    #pragma HLS INTERFACE axis port=in1_13
    #pragma HLS INTERFACE axis port=in1_14
    #pragma HLS INTERFACE axis port=in1_15

    #pragma HLS INTERFACE axis port=in2_0
    #pragma HLS INTERFACE axis port=in2_1
    #pragma HLS INTERFACE axis port=in2_2
    #pragma HLS INTERFACE axis port=in2_3
    #pragma HLS INTERFACE axis port=in2_4
    #pragma HLS INTERFACE axis port=in2_5
    #pragma HLS INTERFACE axis port=in2_6
    #pragma HLS INTERFACE axis port=in2_7
    #pragma HLS INTERFACE axis port=in2_8
    #pragma HLS INTERFACE axis port=in2_9
    #pragma HLS INTERFACE axis port=in2_10
    #pragma HLS INTERFACE axis port=in2_11
    #pragma HLS INTERFACE axis port=in2_12
    #pragma HLS INTERFACE axis port=in2_13
    #pragma HLS INTERFACE axis port=in2_14
    #pragma HLS INTERFACE axis port=in2_15

    #pragma HLS INTERFACE axis port=out

    const int mat_size = DATA_SIZE;
    const int block_size = BLOCK_SIZE;
    const int partition_size = PARTITION_SIZE;

    data_t res = 0;
    
    loop: for(int k = 0; k < partition_size; k++){
    #pragma HLS PIPELINE
        res += in1_0[k]*in2_0[k];
        res += in1_1[k]*in2_1[k];
        res += in1_2[k]*in2_2[k];
        res += in1_3[k]*in2_3[k];
        res += in1_4[k]*in2_4[k];
        res += in1_5[k]*in2_5[k];
        res += in1_6[k]*in2_6[k];
        res += in1_7[k]*in2_7[k];
        res += in1_8[k]*in2_8[k];
        res += in1_9[k]*in2_9[k];
        res += in1_10[k]*in2_10[k];
        res += in1_11[k]*in2_11[k];
        res += in1_12[k]*in2_12[k];
        res += in1_13[k]*in2_13[k];
        res += in1_14[k]*in2_14[k];
        res += in1_15[k]*in2_15[k];
    }
    
    out = res;
    
}
