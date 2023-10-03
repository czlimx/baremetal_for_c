    .global arch_context_first_start
    .global arch_context_start
    .global arch_context_init
    .global arch_context_switch

    .section .text.arch.context, "ax", %progbits
    .arm

/**
 * @brief  start target thread context.
 * @r0:    the stack potnter
 */
arch_context_first_start:
    mov    sp,  r0
    /* restore the floating point context::left to right  */
    ldmfd  sp!, {r3}
    fmxr   fpscr, r3 
	vpop   {d0-d15}

    /* restore the cpsr + spsr register::left to right  */
    ldmfd  sp!, {r2-r3}
    mov    r1,  sp
    msr    spsr_cxsf, r2
    msr    cpsr_cxsf, r3

    /* restore the general register: right to left */
    mov    sp,  r1
    ldmfd  sp!, {r0-r12, lr}

    /* goto entry, is nerver return */
    mov    pc, lr

/**
 * @brief  start target thread context.
 * @r0:    the stack potnter
 */
arch_context_start:
    mov    sp,  r0
    /* restore the floating point context::left to right  */
    ldmfd  sp!, {r3}
    fmxr   fpscr, r3 
	vpop   {d0-d15}

    /* restore the cpsr + spsr register::left to right  */
    ldmfd  sp!, {r2-r3}
    mov    r1,  sp
    msr    spsr_cxsf, r2
    msr    cpsr_cxsf, r3

    /* restore the general register: right to left */
    mov    sp,  r1
    ldmfd  sp!, {r0-r12, lr}

    /* goto entry, is nerver return */
    mov    pc, lr

/**
 * @brief  Init target thread context.
 * @r0:    the target stack potnter
 * @r1:    the thread parameter
 * @r2:    the thread entry
 */
arch_context_init:
    stmfd  sp!, {r4-r12, lr}

    /* init register default value */
    ldr    r4,  = #0x0
    /* init general register: right to left */
    stmfd  r0!, {r2}        // r14
    stmfd  r0!, {r4}        // r12
    stmfd  r0!, {r4}        // r11
    stmfd  r0!, {r4}        // r10
    stmfd  r0!, {r4}        // r9
    stmfd  r0!, {r4}        // r8
    stmfd  r0!, {r4}        // r7
    stmfd  r0!, {r4}        // r6
    stmfd  r0!, {r4}        // r5
    stmfd  r0!, {r4}        // r4
    stmfd  r0!, {r4}        // r3
    stmfd  r0!, {r4}        // r2
    stmfd  r0!, {r4}        // r1
    stmfd  r0!, {r1}        // r0
    
    /* init the cpsr + spsr register */
    mrs    r5, cpsr
    ldr    r6,  = #0x10     // user mode
    stmfd  r0!, {r5-r6}

    /* init the floating point context */
    stmfd  r0!, {r4}        // s31
    stmfd  r0!, {r4}        // s30
    stmfd  r0!, {r4}        // s29
    stmfd  r0!, {r4}        // s28
    stmfd  r0!, {r4}        // s27
    stmfd  r0!, {r4}        // s26
    stmfd  r0!, {r4}        // s25
    stmfd  r0!, {r4}        // s24
    stmfd  r0!, {r4}        // s23
    stmfd  r0!, {r4}        // s22
    stmfd  r0!, {r4}        // s21
    stmfd  r0!, {r4}        // s20
    stmfd  r0!, {r4}        // s19
    stmfd  r0!, {r4}        // s18
    stmfd  r0!, {r4}        // s17
    stmfd  r0!, {r4}        // s16
    stmfd  r0!, {r4}        // s15
    stmfd  r0!, {r4}        // s14
    stmfd  r0!, {r4}        // s13
    stmfd  r0!, {r4}        // s12
    stmfd  r0!, {r4}        // s11
    stmfd  r0!, {r4}        // s10
    stmfd  r0!, {r4}        // s09
    stmfd  r0!, {r4}        // s08
    stmfd  r0!, {r4}        // s07
    stmfd  r0!, {r4}        // s06
    stmfd  r0!, {r4}        // s05
    stmfd  r0!, {r4}        // s04
    stmfd  r0!, {r4}        // s03
    stmfd  r0!, {r4}        // s02
    stmfd  r0!, {r4}        // s01
    stmfd  r0!, {r4}        // s00
    stmfd  r0!, {r4}        // fpscr
    
    ldmfd  sp!, {r4-r12, pc}

/**
 * @brief  Switch target thread context.
 * @r0:    the old context potnter
 * @r1:    the new context potnter
 */
arch_context_switch:
    /* save general register: left to right */
    stmia  r0!, {r4-r14}

    /* save the cpsr + spsr register */
    mrs    r2,  spsr
    mrs    r3,  cpsr
    stmia  r0!, {r2-r3}

    /* save the floating point context */
    fmrx   r3,  fpscr
    stmia  r0!, {r3}
	vstmia r0!, {d0-d15}

    /* restore general register: left to right */
    ldmia  r1!, {r4-r14}

    /* restore the cpsr + spsr register */
    ldmia  r1!, {r2-r3}
    msr    spsr_cxsf, r2
    msr    cpsr_cxsf, r3

    /* restore the floating point context */
    ldmia  r1!, {r3}
    fmxr   fpscr, r3 
	vldmia r1!, {d0-d15}
	
    bx lr
