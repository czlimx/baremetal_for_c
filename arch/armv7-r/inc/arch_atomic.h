#ifndef ARCH_ATOMIC_H_
#define ARCH_ATOMIC_H_

#include "arch_compiler.h"

/**
 * @brief  Atomic set. 
 * @param  addr - virtual address
 * @param  value - data value
 */
void arch_atomic_set(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic try set. 
 * @param  addr - virtual address
 * @param  value - data value
 * @return 0 - success, other - failure
 */
uint32_t arch_atomic_try_set(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic add. 
 * @param  addr - virtual address
 * @param  value - data value
 */
void arch_atomic_add(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic try add. 
 * @param  addr - virtual address
 * @param  value - data value
 * @return 0 - success, other - failure
 */
uint32_t arch_atomic_try_add(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic sub. 
 * @param  addr - virtual address
 * @param  value - data value
 */
void arch_atomic_sub(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic try sub. 
 * @param  addr - virtual address
 * @param  value - data value
 * @return 0 - success, other - failure
 */
uint32_t arch_atomic_try_sub(uint32_t *addr, uint32_t value);

#endif /* ARCH_ATOMIC_H_ */