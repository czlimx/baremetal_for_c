
    .global arch_branch_predictor_enable
    .global arch_branch_predictor_disable
    .global arch_branch_predictor_invalidate_all
    .global arch_branch_predictor_invalidate_range

    .section .text.arch.branch_predictor, "ax", %progbits
    .arm

/**
 * @brief  Branch prediction enable.
 */
arch_branch_predictor_enable:
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #(0x1 << 11)
    mcr p15, 0, r0, c1, c0, 0
    bx lr

/**
 * @brief  Branch prediction disable.
 */
arch_branch_predictor_disable:
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(0x1 << 11)
    mcr p15, 0, r0, c1, c0, 0
    bx lr

/**
 * @brief  Invalidate all branch predictors.
 */
arch_branch_predictor_invalidate_all:
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 6
    bx lr

/**
 * @brief  Invalidate branch predictor by MVA to PoU. 
 * @param  r0 - virtual address
 * @param  r1 - data length
 */
arch_branch_predictor_invalidate_range:
    stmfd sp!, {r4-r12}

    mov r2, #0
    mcr p15, 2, r2, c0, c0, 0
    isb
    mrc p15, 1, r2, c0, c0, 0
    and r2, r2, #7
    add r2, r2, #2
    mov r3, #1
    mov r3, r3, lsl r2

    add r2, r0, r1
    sub r4, r3, #1
    bic r0, r0, r4
1:
    mcr p15, 0, r0, c7, c5, 7
    add r0, r0, r3
    cmp r0, r2
    blo 1b

    dsb
    ldmfd sp!, {r4-r12}
    bx lr

    .end
