#ifndef __FIR_CONV_H
#define __FIR_CONV_H

#include "main.h"  // need to be defined before arm_math.h is included, since it contains the definition of __FPU_PRESENT macro
#include "tfilter_coeff.h"

// Define BEFORE any includes that pull in arm_math.h
#ifndef ARM_MATH_CM4
    #define ARM_MATH_CM4
#endif

// #ifndef __FPU_PRESENT          // <-- add this
//     #define __FPU_PRESENT 1
// #endif

#include "arm_math.h"

#define KERNEL_GAIN 1.0f
#define KERNEL_LENGTH FILTER_TAP_NUM
#define BLOCK_LENGTH 32

typedef struct{
    arm_fir_instance_f32 fir_processor;
    float32_t fir_state_buffer[BLOCK_LENGTH + KERNEL_LENGTH - 1];
    float32_t kernel_timereversed_taps[KERNEL_LENGTH];
    float32_t fir_output_buffer[BLOCK_LENGTH];
} fir_conv_HandleTypeDef;

void FIR_Conv_Init(fir_conv_HandleTypeDef *c, const float32_t *kernel);
void FIR_Conv_Update(fir_conv_HandleTypeDef *c, float32_t *input);

#endif /* __FIR_CONV_H */


