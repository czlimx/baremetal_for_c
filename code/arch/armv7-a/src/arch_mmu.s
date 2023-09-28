// @ #define CONTEXTIDR          CP15_REG(c13, 0, c0, 1)    /*! Context ID Register | 上下文ID寄存器*/	
// @ #define TPIDRURW            CP15_REG(c13, 0, c0, 2)    /*! User Read/Write Thread ID Register | 用户读/写线程ID寄存器*/	
// @ #define TPIDRURO            CP15_REG(c13, 0, c0, 3)    /*! User Read-Only Thread ID Register | 用户只读写线程ID寄存器*/	
// @  // ASID 
// @ MRC p15, 0, <Rt>, c13, c0, 1    ; Read CONTEXTIDR into Rt
// @ MCR p15, 0, <Rt>, c13, c0, 1    ; Write Rt to CONTEXTIDR


    .global arch_mmu_enable
    .global arch_mmu_disable

    .section .text.arch.mmu, "ax", %progbits
    .arm

MMU_AP_CLIENTD:
    .word  0x55555555

/**
 * @brief  The enables MMU.
 */
arch_mmu_enable:
    /* Remap disabled. The TEX[2:0], C, and B bits in 
       the translation table descriptor define the
       memory region attributes. */
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1 << 28)
    mcr p15, #0, r0, c1, c0, #0

    /* In the translation table descriptors, 
       AP[0] is an access permissions bit. */
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1 << 29)
    mcr p15, #0, r0, c1, c0, #0

    /* enable client for domain 0 */
    ldr r0, MMU_AP_CLIENTD
    mcr p15, #0, r0, c3, c0, #0
    dsb

    mrc p15, #0, r0, c1, c0, #0
    orr r0, r0, #(0x1 << 0)
    mcr p15, #0, r0, c1, c0, #0
    bx lr

/**
 * @brief  The disable MMU.
 */
arch_mmu_disable:
    mrc p15, #0, r0, c1, c0, #0
    bic r0, r0, #(0x1 << 0)
    mcr p15, #0, r0, c1, c0, #0
    bx lr
