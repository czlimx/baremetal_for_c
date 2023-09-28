
    .set SCTLR_I,   12     // Instruction cache enable.
    .set SCTLR_C,    2     // Data and unified caches enable.

    .global arch_icache_enable
    .global arch_icache_disable
    .global arch_dcache_enable
    .global arch_dcache_disable
    .global arch_icache_invalidate_all
    .global arch_icache_invalidate_range
    .global arch_dcache_invalidate_all
    .global arch_dcache_clean_all
    .global arch_dcache_flush_all
    .global arch_dcache_invalidate_range
    .global arch_dcache_clean_range
    .global arch_dcache_flush_range

    .section .text.arch.cache, "ax", %progbits
    .arm

/**
 * @brief  Instruction Cache enable.
 */
arch_icache_enable:
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #(1 << SCTLR_I)
    mcr p15, 0, r0, c1, c0, 0
    bx lr

/**
 * @brief  Instruction Cache disable.
 */
arch_icache_disable:
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(1 << SCTLR_I)
    mcr p15, 0, r0, c1, c0, 0
    bx lr

/**
 * @brief  Instruction Cache enable.
 */
arch_dcache_enable:
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #(1 << SCTLR_C)
    mcr p15, 0, r0, c1, c0, 0
    bx lr

/**
 * @brief  Instruction Cache disable.
 */
arch_dcache_disable:
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(1 << SCTLR_C)
    mcr p15, 0, r0, c1, c0, 0
    bx lr

/**
 * @brief  Instruction Cache Invalidate by Set/Way.
 */
arch_icache_invalidate_all:
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0
    bx lr

/**
 * @brief  Instruction Cache Invalidate by MVA to PoU.
 * @param  r0 - virtual address
 * @param  r1 - data length
 */
arch_icache_invalidate_range:
    stmfd sp!, {r4-r12}

    mov r2, #1
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
    mcr p15, 0, r0, c7, c5, 1
    add r0, r0, r3
    cmp r0, r2
    blo 1b

    dsb
    ldmfd sp!, {r4-r12}
    bx lr

/**
 * @brief  Data Cache line Invalidate by Set/Way.
 */
arch_dcache_invalidate_all:
    stmfd sp!, {r0-r12}
    dmb

    mrc p15, 1, r0, c0, c0, 1
    ands r3, r0, #0x7000000
    mov r3, r3, lsr #23
    beq 5f
    mov r10, #0

1:
    add r2, r10, r10, lsr #1
    mov r1, r0, lsr r2
    and r1, r1, #7
    cmp r1, #2
    blt 4f

    mcr p15, 2, r10, c0, c0, 0
    isb
    mrc p15, 1, r1, c0, c0, 0
    and r2, r1, #7
    add r2, r2, #4
    ldr r4, = 0x3FF
    ands r4, r4, r1, lsr #3
    clz r5, r4
    mov r9, r4

2:
    ldr r7, = 0x7FFF
    ands r7, r7, r1, lsr #13

3:
    orr r11, r10, r9, lsl r5
    orr r11, r11, r7, lsl r2
    mcr p15, 0, r11, c7, c6, 2
    subs r7, r7, #1
    bge 3b
    subs r9, r9, #1
    bge 2b

4:
    add r10, r10, #2
    cmp r3, r10
    bgt 1b
    dsb

5:
    ldmfd sp!, {r0-r12}
    bx lr

/**
 * @brief  Data Cache line Clean by Set/Way.
 */
arch_dcache_clean_all:
    stmfd sp!, {r0-r12}
    dmb

    mrc p15, 1, r0, c0, c0, 1
    ands r3, r0, #0x7000000
    mov r3, r3, lsr #23
    beq 5f
    mov r10, #0

1:
    add r2, r10, r10, lsr #1
    mov r1, r0, lsr r2
    and r1, r1, #7
    cmp r1, #2
    blt 4f

    mcr p15, 2, r10, c0, c0, 0
    isb
    mrc p15, 1, r1, c0, c0, 0
    and r2, r1, #7
    add r2, r2, #4
    ldr r4, = 0x3FF
    ands r4, r4, r1, lsr #3
    clz r5, r4
    mov r9, r4

2:
    ldr r7, = 0x7FFF
    ands r7, r7, r1, lsr #13

3:
    orr r11, r10, r9, lsl r5
    orr r11, r11, r7, lsl r2
    mcr p15, 0, r11, c7, c10, 2
    subs r7, r7, #1
    bge 3b
    subs r9, r9, #1
    bge 2b

4:
    add r10, r10, #2
    cmp r3, r10
    bgt 1b
    dsb

5:
    ldmfd sp!, {r0-r12}
    bx lr

/**
 * @brief  Data Cache line Clean and Invalidate by Set/Way.
 */
arch_dcache_flush_all:
    stmfd sp!, {r0-r12}
    dmb

    mrc p15, 1, r0, c0, c0, 1
    ands r3, r0, #0x7000000
    mov r3, r3, lsr #23
    beq 5f
    mov r10, #0

1:
    add r2, r10, r10, lsr #1
    mov r1, r0, lsr r2
    and r1, r1, #7
    cmp r1, #2
    blt 4f

    mcr p15, 2, r10, c0, c0, 0
    isb
    mrc p15, 1, r1, c0, c0, 0
    and r2, r1, #7
    add r2, r2, #4
    ldr r4, = 0x3FF
    ands r4, r4, r1, lsr #3
    clz r5, r4
    mov r9, r4

2:
    ldr r7, = 0x7FFF
    ands r7, r7, r1, lsr #13

3:
    orr r11, r10, r9, lsl r5
    orr r11, r11, r7, lsl r2
    mcr p15, 0, r11, c7, c14, 2
    subs r7, r7, #1
    bge 3b
    subs r9, r9, #1
    bge 2b

4:
    add r10, r10, #2
    cmp r3, r10
    bgt 1b
    dsb

5:
    ldmfd sp!, {r0-r12}
    bx lr

/**
 * @brief  Data Cache line Invalidate by VA to PoC. 
 * @param  r0 - virtual address
 * @param  r1 - data length
 */
arch_dcache_invalidate_range:
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
    mcr p15, 0, r0, c7, c6, 1
    add r0, r0, r3
    cmp r0, r2
    blo 1b

    dsb
    ldmfd sp!, {r4-r12}
    bx lr

/**
 * @brief  Clean data or unified cache line by virtual address to PoC.
 * @param  r0 - virtual address
 * @param  r1 - data length
 */
arch_dcache_clean_range:
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
    mcr p15, 0, r0, c7, c10, 1
    add r0, r0, r3
    cmp r0, r2
    blo 1b

    dsb
    ldmfd sp!, {r4-r12}
    bx lr

/**
 * @brief  Clean and Invalidate data or unified cache line by virtual address to PoC.
 * @param  r0 - virtual address
 * @param  r1 - data length
 */
arch_dcache_flush_range:
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
    mcr p15, 0, r0, c7, c14, 1
    add r0, r0, r3
    cmp r0, r2
    blo 1b

    dsb
    ldmfd sp!, {r4-r12}
    bx lr

    .end
