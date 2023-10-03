#ifndef DEVICE_MEMORY_H_
#define DEVICE_MEMORY_H_

#include "tryrtos_config.h"

#define CORE_CLOCK_PRE          500000000

/* 
 * CORE = 500MHZ = 2ns; 
 * 1 cycle counter = 1 cycle = 2ns;
 * 1us = 1000 / 2 = 500 cycle;
 */
#define PMU_US_TO_TICK(x)       (x * 500)
#define PMU_TICK_TO_US(x)       (x / 500)

#define MMU_VA_TO_PA(x)         (x - 0x40000000)

#ifndef arch_interrupt_call_back
#define arch_interrupt_call_back()
#endif

#endif /* DEVICE_MEMORY_H_ */
