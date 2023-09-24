
    .global arch_mpu_enable
    .global arch_mpu_disable
    .global arch_mpu_reset
    .global arch_mpu_add_region

    .section .text.arch.mpu, "ax", %progbits
    .arm

/**
 * @brief  The enable the MPU.
 */
arch_mpu_enable:
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #(1 << 0)           // MPU enable.
    orr r0, r0, #(1 << 17)          // MPU background region enable.
    mcr p15, 0, r0, c1, c0, 0       
    bx lr

/**
 * @brief  The disable the MPU.
 */
arch_mpu_disable:
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(1 << 0)           // MPU enable.
    bic r0, r0, #(1 << 17)          // MPU background region enable.
    mcr p15, 0, r0, c1, c0, 0       
    bx lr

/**
 * @brief  The clear all regions for the MPU.
 */
arch_mpu_reset:
    /* Read the MPUIR to determine the number of supported regions. */
    mrc p15, 0, r0, c0, c0, 4
    mov r1, r0, lsr #8
    and r1, r1, #0xFF                // R1 = region number

    /* write the group of register to bs accessed. */
    mov r3, #0
    mov r2, #0
1:
    mcr p15, 0, r2, c6, c2, 0
    mcr p15, 0, r3, c6, c2, 2
    add r2, r2, #1
    cmp r1, r2
    blo 1b
    bx lr

/**
 * @brief  The add the region for the MPU.
 * @param  r0 - the region number.
 * @param  r1 - the memory base.
 * @param  r2 - the memory attr.
 * @param  r3 - the memory size.
 */
arch_mpu_add_region:
    mcr p15, 0, r0, c6, c2, 0
    and r1, r1, #0xFFFFFFE0
    mcr p15, 0, r1, c6, c1, 0
    mcr p15, 0, r2, c6, c1, 4
    clz r3, r3
    add r3, r3, #1
    mov r3, r3, lsl #1
    orr r3, r3, #(1 << 0)
    mcr p15, 0, r3, c6, c1, 2
    bx lr

    .end
