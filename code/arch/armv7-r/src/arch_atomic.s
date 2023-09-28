    .global arch_atomic_set
    .global arch_atomic_try_set
    .global arch_atomic_add
    .global arch_atomic_try_add
    .global arch_atomic_sub
    .global arch_atomic_try_sub

    .section .text.arch.atomic, "ax", %progbits
    .arm

/**
 * @brief  Atomic set. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 */
arch_atomic_set:
1:  ldrex r2, [r0]
    strex r3, r1, [r0]
    teq r3, #0
    bne 1b
    bx lr

/**
 * @brief  Atomic try set. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 * @return 0 - success, other - failure
 */
arch_atomic_try_set:
    ldrex r2, [r0]
    strex r3, r1, [r0]
    mov r0, r3
    bx lr

/**
 * @brief  Atomic add. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 */
arch_atomic_add:
1:  ldrex r2, [r0]
    add r2, r2, r1
    strex r3, r2, [r0]
    teq r3, #0
    bne 1b
    bx lr

/**
 * @brief  Atomic try add. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 * @return 0 - success, other - failure
 */
arch_atomic_try_add:
    ldrex r2, [r0]
    add r2, r2, r1
    strex r3, r2, [r0]
    mov r0, r3
    bx lr

/**
 * @brief  Atomic sub. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 */
arch_atomic_sub:
1:  ldrex r2, [r0]
    sub r2, r2, r1
    strex r3, r2, [r0]
    teq r3, #0
    bne 1b
    bx lr

/**
 * @brief  Atomic try sub. 
 * @param  r0 - virtual address
 * @param  r1 - data value
 * @return 0 - success, other - failure
 */
arch_atomic_try_sub:
    ldrex r2, [r0]
    sub r2, r2, r1
    strex r3, r2, [r0]
    mov r0, r3
    bx lr

    .end
