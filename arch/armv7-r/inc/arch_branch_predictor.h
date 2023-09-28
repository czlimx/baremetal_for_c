#ifndef ARCH_BRANCH_PREDICTOR_H_
#define ARCH_BRANCH_PREDICTOR_H_

#include "arch_compiler.h"

/**
 * @brief  Branch prediction enable.
 */
void arch_branch_predictor_enable(void);

/**
 * @brief  Branch prediction disable.
 */
void arch_branch_predictor_disable(void);

/**
 * @brief  Invalidate all branch predictors.
 */
void arch_branch_predictor_invalidate_all(void);

/**
 * @brief  Invalidate branch predictor by MVA to PoU. 
 * @param  addr - virtual address
 * @param  len - data length
 */
void arch_branch_predictor_invalidate_range(void *addr, uint32_t len);

#endif /* ARCH_BRANCH_PREDICTOR_H_ */