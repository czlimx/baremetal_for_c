#ifndef DEVICE_MEMORY_H_
#define DEVICE_MEMORY_H_

#define CORE_CLOCK_PRE          500000000

/*
 * CORE = 500MHZ = 2ns;
 * 1 cycle counter = 1 cycle = 2ns;
 * 1us = 1000 / 2 = 500 cycle;
 */
#define PMU_US_TO_TICK(x)       (x * 500)
#define PMU_TICK_TO_US(x)       (x / 500)

#endif /* DEVICE_MEMORY_H_ */