#ifndef ARCH_TCM_H_
#define ARCH_TCM_H_

#include "arch_compiler.h"

/**
 * @brief  The remap the ATCM.
 * @param  base - the base address.
 *
 * @note   The base address must be aligned to the size of the TCM.
 */
void arch_tcma_remap(uint32_t base);

/**
 * @brief  The remap the BTCM.
 * @param  base - the base address.
 *
 * @note   The base address must be aligned to the size of the TCM.
 */
void arch_tcmb_remap(uint32_t base);

#endif /* ARCH_TCM_H_ */
