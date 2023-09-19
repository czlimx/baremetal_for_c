
    .global arch_mpu_enable
    .global arch_mpu_disable

    .section .text.arch.mpu, "ax", %progbits
    .arm

/**
 * @brief  The remap the ATCM.
 * @param  r0 - the base address.
 *
 * @note   The base address must be aligned to the size of the TCM.
 */
arch_mpu_enable:
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #(1 << 0)           // MPU enable.
    orr r0, r0, #(1 << 17)          // MPU background region enable.
    mcr p15, 0, r0, c1, c0, 0       
    bx lr

arch_mpu_disable:
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(1 << 0)           // MPU enable.
    bic r0, r0, #(1 << 17)          // MPU background region enable.
    mcr p15, 0, r0, c1, c0, 0       
    bx lr

arch_mpu_reset:
    /* get mpu DRegion */
    mrc p15, 0, r0, c0, c0, 4
    mov r1, r0, lsr #8
    and r1, r1, 0xFF                // R1 = region number
