#ifndef ARCH_ATOMIC_H_
#define ARCH_ATOMIC_H_

/**
 * @brief  Atomic set. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 */
void arch_atomic_set(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic try set. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 * @return 0 - success, other - failure
 */
uint32_t arch_atomic_try_set(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic add. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 */
void arch_atomic_add(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic try add. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 * @return 0 - success, other - failure
 */
uint32_t arch_atomic_try_add(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic sub. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 */
void arch_atomic_sub(uint32_t *addr, uint32_t value);

/**
 * @brief  Atomic try sub. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 * @return 0 - success, other - failure
 */
uint32_t arch_atomic_try_sub(uint32_t *addr, uint32_t value);

#endif /* ARCH_ATOMIC_H_ */