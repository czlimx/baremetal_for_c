#ifndef ARCH_CACHE_H_
#define ARCH_CACHE_H_

#include "arch_compiler.h"

/**
 * @brief  Instruction Cache enable.
 * @note   It is strongly recommended to invalidate all icache before enabling.
 */
void arch_icache_enable(void);

/**
 * @brief  Instruction Cache disable.
 */
void arch_icache_disable(void);

/**
 * @brief  Instruction Cache enable.
 * @note   It is strongly recommended to invalidate all dcache before enabling.
 */
void arch_dcache_enable(void);

/**
 * @brief  Instruction Cache disable.
 * @note   It is strongly recommended to flush all dcache before disabling.
 */
void arch_dcache_disable(void);

/**
 * @brief  Instruction Cache Invalidate by Set/Way.
 */
void arch_icache_invalidate_all(void);

/**
 * @brief  Instruction Cache Invalidate by MVA to PoU.
 * @param  addr - virtual address
 * @param  len - data length
 */
void arch_icache_invalidate_range(void *addr, uint32_t len);

/**
 * @brief  Data Cache line Invalidate by Set/Way.
 */
void arch_dcache_invalidate_all(void);

/**
 * @brief  Data Cache line Clean by Set/Way.
 */
void arch_dcache_clean_all(void);

/**
 * @brief  Data Cache line Clean and Invalidate by Set/Way.
 */
void arch_dcache_flush_all(void);

/**
 * @brief  Data Cache line Invalidate by VA to PoC. 
 * @param  addr - virtual address
 * @param  len - data length
 */
void arch_dcache_invalidate_range(void *addr, uint32_t len);

/**
 * @brief  Clean data or unified cache line by virtual address to PoC.
 * @param  addr - virtual address
 * @param  len - data length
 */
void arch_dcache_clean_range(void *addr, uint32_t len);

/**
 * @brief  Clean and Invalidate data or unified cache line by virtual address to PoC.
 * @param  addr - virtual address
 * @param  len - data length
 */
void arch_dcache_flush_range(void *addr, uint32_t len);

#endif /* ARCH_CACHE_H_ */
