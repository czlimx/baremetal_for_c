
    .global arch_tcm_remap

    .section .text.arch.tcm, "ax", %progbits
    .arm

/**
 * @brief  The remap the ATCM.
 * @param  r0 - the base address.
 *
 * @note   The base address must be aligned to the size of the TCM.
 *         You are not advised to change the initialization sequence.
 */
arch_tcm_remap:
    mrc p15, 0, r2, c9, c1, 0	// Read TCM Region Register
	lsr r2, r2, #2
	and r2, r2, #0x1f	        // ATCM Region Register [6:2] : Size
	mov r1, #0x200
	lsl r3, r1, r2		        // r3: TCM size
    sub r4, r3, #1              // r4: base align mask
    and r0, r0, r4
    add r5, r0, r3              // r5: BTCM base address

    orr r0, r0, #(1 << 0)
    mcr p15, 0, r0, c9, c1, 0
    orr r5, r5, #(1 << 0)
    mcr p15, 0, r5, c9, c1, 1

    bx lr

    .end
