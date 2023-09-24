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
 * @param  udelay - the udelay value
 */
void arch_udelay(uint32_t udelay);

/**
 * @brief  The early init for CPU.
 */
void _early_arch_init(void);

#endif /* ARCH_CPU_H_ */