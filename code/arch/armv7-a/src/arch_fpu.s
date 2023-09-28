
    .global arch_fpu_enable
    .global arch_fpu_disable

    .section .text.arch.fpu, "ax", %progbits
    .arm

/**
 * @brief  Floating point and SIMD extensions enable.
 */
arch_fpu_enable:
    /* In order to enable privileged and user access 
       to floating point and SIMD extensions, 
       CPACR.{cp10, cp11} = 0b11 must be set. */
    mrc p15, 0, r0, c1, c0, 2
    orr r0, r0, #(0xF << 20)
    mcr p15, 0, r0, c1, c0, 2

    // enable privilege and user access FPSCR with set FPEXC.EN = 1
    vmrs r0, fpexc
    orr r0, r0, #(1 << 30)
    vmsr fpexc, r0

    // enable Exception bit with set FPEXC.EX = 1
    vmrs r0, fpexc
    orr r0, r0, #(1 << 31)
    vmsr fpexc, r0

    bx lr

/**
 * @brief  Floating point and SIMD extensions disable.
 */
arch_fpu_disable:
    // disable Exception bit with set FPEXC.EX = 1
    vmrs r0, fpexc
    bic r0, r0, #(1 << 31)
    vmsr fpexc, r0

    // disable privilege and user access FPSCR with set FPEXC.EN = 1
    vmrs r0, fpexc
    bic r0, r0, #(1 << 30)
    vmsr fpexc, r0

    bx lr

    .end
