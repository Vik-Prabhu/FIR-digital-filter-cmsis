#include "fir_conv.h"

void FIR_Conv_Init(fir_conv_HandleTypeDef *c, const float32_t *kernel)
{
    uint32_t i;
    for(i = 0; i < KERNEL_LENGTH; i++)
    {
        c->kernel_timereversed_taps[i] = kernel[KERNEL_LENGTH - 1 - i] * KERNEL_GAIN;
    }

    /*
    * pcoeffs = filter coefficients time reversed order, length=numTaps
    * pstate = working memory, length=nunTaps+blocksize-1
    */

    arm_fir_init_f32(&(c->fir_processor), KERNEL_LENGTH, c->kernel_timereversed_taps, c->fir_state_buffer, BLOCK_LENGTH);

}

void FIR_Conv_Update(fir_conv_HandleTypeDef *c, float32_t *input)
{
    arm_fir_f32(&(c->fir_processor), input, (c->fir_output_buffer), BLOCK_LENGTH);
}

