#ifndef ARCH_CACHE_H_
#define ARCH_CACHE_H_

/**
 * @brief  Floating point and SIMD extensions enable.
 */
void arch_fpu_enable(void);

/**
 * @brief  Floating point and SIMD extensions disable.
 */
void arch_fpu_disable(void);

#endif /* ARCH_CACHE_H_ */
