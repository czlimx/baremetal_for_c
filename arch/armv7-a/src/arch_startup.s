    .set SYS_MODE,	0x1F
	.set SVC_MODE,	0x13
	.set IRQ_MODE,	0x12
    .set ABT_MODE,	0x17

    .set SCTLR_V,   13     // Vectors bit.
    .set SCTLR_I,   12     // Instruction cache enable.
    .set SCTLR_Z,   11     // Branch prediction enable.
    .set SCTLR_C,    2     // Data and unified caches enable.
    .set SCTLR_A,    1     // MMU enable.
    .set SCTLR_M,    0     // MMU enable.
    
    .extern _stack_top
    .extern _early_arch_init
    .extern _vector_table
    .section .text.arch.startup, "ax", %progbits
    .arm

    .global do_reset, _start
_start:
do_reset:
    /* enter svc mode and mask intrrupt and async abort */
    cpsid aif, #SVC_MODE

    /* set SCTLR.V = 0, Low exception vectors = VBAR */
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1U << SCTLR_V)
    mcr p15, #0, r0, c1, c0, #0
    ldr r0, = _vector_table
    mcr p15, #0, r0, c12,c0, #0

    /* disable mmu */
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1U << SCTLR_M)
    mcr p15, #0, r0, c1, c0, #0

    /* disable Branch prediction */
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1U << SCTLR_Z)
    mcr p15, #0, r0, c1, c0, #0

    /* disable Instruction cache */
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1U << SCTLR_I)
    mcr p15, #0, r0, c1, c0, #0

    /* disable Data and unified caches */
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1U << SCTLR_C)
    mcr p15, #0, r0, c1, c0, #0

    /* disable Alignment check */
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1U << SCTLR_A)
    mcr p15, #0, r0, c1, c0, #0

    /* setup stack for all mode */
    ldr r0, = _stack_end
    cps #ABT_MODE
    sub r0, r0, #0x1000
    mov sp, r0
    cps #IRQ_MODE
    sub r0, r0, #0x1000
    mov sp, r0
    cps #SVC_MODE
    sub r0, r0, #0x1000
    mov sp, r0
    cps #SYS_MODE
    sub r0, r0, #0x1000
    mov sp, r0
    cps #SVC_MODE

    /* goto early init entry */
    bl _early_arch_init

loop:
    b loop

    .end
