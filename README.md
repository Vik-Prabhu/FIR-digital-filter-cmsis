# FIR Digital Filter — STM32F446RE

A FIR (Finite Impulse Response) low-pass digital filter implemented on the STM32F446RE using the ARM CMSIS-DSP library (`arm_fir_f32`). Filter coefficients were generated using the [tfilter](http://t-filter.engineerjs.com/) online tool.

---

## Hardware

| | |
|---|---|
| **Board** | NUCLEO-F446RE |
| **MCU** | STM32F446RE (Cortex-M4F) |
| **FPU** | Yes (hard float, `fpv4-sp-d16`) |

---

## Dependencies

- [**CMSIS-DSP v4**](https://github.com/ARM-software/CMSIS_4/releases/tag/v4.5.0) — `arm_fir_f32`, `arm_fir_init_f32`
- **STM32 HAL** — UART, GPIO, CRC
- **tfilter** — FIR coefficient generation

---

## Project Structure

```
Core/
├── Inc/
│   ├── fir_conv.h          # FIR handle typedef and API
│   └── tfilter_coeff.h     # Generated filter coefficients
└── Src/
    ├── main.c              # Entry point, FIR init
    └── fir_conv.c          # FIR init and update wrappers
Middlewares/
└── Third_Party/ARM_CMSIS/CMSIS/
    ├── Include/            # arm_math.h, core_cm4.h
    └── Lib/GCC/            # libarm_cortexM4lf_math.a
```

---

## How It Works

1. Filter coefficients are generated externally (tfilter) and stored in `tfilter_coeff.h` as a `float32_t` array.
2. `FIR_Conv_Init()` time-reverses the coefficients (as required by `arm_fir_init_f32`) and initializes the CMSIS `arm_fir_instance_f32` processor.
3. `FIR_Conv_Update()` processes a block of input samples through `arm_fir_f32` and writes results to the output buffer.

```c
FIR_Conv_Init(&conv, (const float32_t *)filter_taps);   // once at startup
FIR_Conv_Update(&conv, input_block);                    // called per block
```

---

## References

- [Phil's Lab — FIR Filter Theory](https://www.youtube.com/watch?v=lDskXTR6psY)
- [Phil's Lab — CMSIS-DSP FIR on STM32](https://www.youtube.com/watch?v=uNNNj9AZisM)
- [ARM CMSIS-DSP FIR Example](https://arm-software.github.io/CMSIS_5/latest/DSP/html/group__FIRLPF.html)
