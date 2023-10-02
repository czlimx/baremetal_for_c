#ifndef ARCH_CPU_H_
#define ARCH_CPU_H_

#include "arch_compiler.h"

/**
 *  @brief alignment check enable.
 */
void arch_alignment_check_enable(void);

/**
 * @brief  The get the MPIDR register.
 * @return the register value.
 */
uint32_t arch_cpu_get_mpidr(void);

/**
 * @brief  The used the Cycle Counter delay.
 * @param  tick - the udelay to tick value
 */ 
void arch_tick_delay(uint32_t tick);

#endif /* ARCH_CPU_H_ */