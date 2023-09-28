#ifndef ARCH_TCM_H_
#define ARCH_TCM_H_

#include "arch_compiler.h"

/**
 * @brief  The remap the TCM.
 * @param  base - the base address.
 *
 * @note   The base address must be aligned to the size of the TCM.
 */
void arch_tcm_remap(uint32_t base);

#endif /* ARCH_TCM_H_ */
