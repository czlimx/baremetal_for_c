#ifndef ARCH_TLB_H_
#define ARCH_TLB_H_

#include "arch_compiler.h"

/**
 * @note Used for operating system.
 */
void arch_tlb_config_ttbr0(uint32_t base);

/**
 * @note Used for I/O addresses.
 */
void arch_tlb_config_ttbr1(uint32_t base);

/**
 * @note Whenever TTBCR.N is nonzero, the size of the translation table addressed by TTBR1 is 16KB.
 */
void arch_tlb_config_ttbcr(uint32_t n);

/**
 * @brief  The invalidate all TLB.
 */
void arch_tlb_invalidate_all(void);

/**
 * @brief  The invalidate all data TLB.
 */
void arch_tlb_invalidate_data_all(void);

/**
 * @brief  The invalidate data TLB by ASID.
 * @param  r0 - the ASID.
 */
void arch_tlb_invalidate_data_asid(uint32_t asid);

/**
 * @brief  The invalidate data TLB entry by MVA.
 * @param  r0 - the virtual page address.
 */
void arch_tlb_invalidate_data_page(uint32_t page);

/**
 * @brief  The invalidate all instruction TLB.
 */
void arch_tlb_invalidate_instruction_all(void);

/**
 * @brief  The invalidate instruction TLB by ASID.
 * @param  asid - the ASID.
 */
void arch_tlb_invalidate_instruction_asid(uint32_t asid);

/**
 * @brief  The invalidate instruction TLB entry by MVA.
 * @param  page - the virtual page address.
 */
void arch_tlb_invalidate_instruction_page(uint32_t page);


#endif /* ARCH_TLB_H_ */