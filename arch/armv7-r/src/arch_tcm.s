
    .global arch_tcma_remap
    .global arch_tcmb_remap

    .section .text.arch.tcm, "ax", %progbits
    .arm

/**
 * @brief  The remap the ATCM.
 * @param  r0 - the base address.
 *
 * @note   The base address must be aligned to the size of the TCM.
 */
arch_tcma_remap:
    mrc p15, 0, r2, c9, c1, 1	// Read ATCM Region Register
	lsr r2, r2, #2
	and r2, r2, #0x1f	        // ATCM Region Register [6:2] : Size	
	mov r1, #0x200
	lsl r1, r1, r2		        // r1: ATCM size
    sub r1, r1, #1
    and r0, r0, r1              // align to the size of ATCM 
    orr r0, r0, #(1 << 0)
    mcr p15, 0, r0, c9, c1, 1
    bx lr

/**
 * @brief  The remap the BTCM.
 * @param  r0 - the base address.
 *
 * @note   The base address must be aligned to the size of the TCM.
 */
arch_tcmb_remap:
    mrc p15, 0, r2, c9, c1, 0	// Read BTCM Region Register
	lsr r2, r2, #2
	and r2, r2, #0x1f	        // BTCM Region Register [6:2] : Size	
	mov r1, #0x200
	lsl r1, r1, r2		        // r1: BTCM size
    sub r1, r1, #1
    and r0, r0, r1              // align to the size of BTCM 
    orr r0, r0, #(1 << 0)
    mcr p15, 0, r0, c9, c1, 0
    bx lr

    .end
