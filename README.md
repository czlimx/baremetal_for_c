# Support description
Embedded bare metal sample code supports armv7-m, armv7-a, armv7-r and armv8-a instruction ISA;

# Support platform description
|  ISA   |  armv7-m   | armv7-a  |  armv7-r   |  armv8-a   |
|  ----  |  ----      | ----     |  ----      |  ----      |
|  CPU   |  Cortex-M7 | Cortex-A8/Cortex-A15  |  Cortex-R5F|  Cortex-A53  |
|  Chip  |  STM32H750 | AM3358/AM5718         |  E3640     |  H6/AM6254   |

# Processor architecture module support
|  ISA   |  Module   |
|  ----   |  ----   |
|  armv7-a   |  atomic, branch_predictors, I/Dcache, exception, vectors, fpu, gicv2, vic, mmu, pmu, tlb  |
|  armv7-r   |  atomic, branch_predictors, I/Dcache, exception, vectors, fpu, gicv2, tcm, mpu, pmu, tlb  |
|  armv7-m   |  atomic, branch_predictors, I/Dcache, exception, vectors, fpu, nvic, tcm, mpu, pmu, tlb  |
|  armv8-a   |  atomic, branch_predictors, I/Dcache, exception, vectors, fpu, gicv3, mmu, pmu, tlb  |

# Build support
```python
release.sh <board> <rtos>

example:
    release.sh am3358 tryrtos
```

# Note
The compilation tool uses cmake, and the compilers are: 
|  ISA     |  toolchain     |
|  ----    |  ----          |
|  armv7   |  arm-none-eabi |
|  armv8   |  aarch64-none-linux-gnu |