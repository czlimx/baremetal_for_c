    
    .global arch_tlb_config_ttbr0
    .global arch_tlb_config_ttbr1
    .global arch_tlb_config_ttbcr
    .global arch_tlb_invalidate_data_all
    .global arch_tlb_invalidate_data_asid
    .global arch_tlb_invalidate_data_page
    .global arch_tlb_invalidate_instruction_all
    .global arch_tlb_invalidate_instruction_asid
    .global arch_tlb_invalidate_instruction_page
    .global arch_tlb_invalidate_all

    .section .text.arch.tlb, "ax", %progbits
    .arm
/**
 * @note Used for operating system.
 */
arch_tlb_config_ttbr0:
    mcr p15, 0, r0, c2, c0, 0
    bx lr

/**
 * @note Used for I/O addresses.
 */
arch_tlb_config_ttbr1:
    mcr p15, 0, r0, c2, c0, 1
    bx lr

/**
 * @note Whenever TTBCR.N is nonzero, the size of the translation table addressed by TTBR1 is 16KB.
 */
arch_tlb_config_ttbcr:
    mcr p15, 0, r0, c2, c0, 2
    bx lr

/**
 * @brief  The invalidate all TLB.
 */
arch_tlb_invalidate_all:
    mcr p15, 0, r0, c8, c7, 0
    bx lr

/**
 * @brief  The invalidate all data TLB.
 */
arch_tlb_invalidate_data_all:
    mcr p15, 0, r0, c8, c6, 0
    bx lr

/**
 * @brief  The invalidate data TLB by ASID.
 * @param  r0 - the ASID.
 */
arch_tlb_invalidate_data_asid:
    mcr p15, 0, r0, c8, c6, 2
    bx lr

/**
 * @brief  The invalidate data TLB entry by MVA.
 * @param  r0 - the virtual page address.
 */
arch_tlb_invalidate_data_page:
    mcr p15, 0, r0, c8, c6, 1
    bx lr

/**
 * @brief  The invalidate all instruction TLB.
 */
arch_tlb_invalidate_instruction_all:
    mcr p15, 0, r0, c8, c5, 0
    bx lr

/**
 * @brief  The invalidate instruction TLB by ASID.
 * @param  r0 - the ASID.
 */
arch_tlb_invalidate_instruction_asid:
    mcr p15, 0, r0, c8, c5, 2
    bx lr

/**
 * @brief  The invalidate instruction TLB entry by MVA.
 * @param  r0 - the virtual page address.
 */
arch_tlb_invalidate_instruction_page:
    mcr p15, 0, r0, c8, c5, 1
    bx lr

    .end
