#include "sdrv_intc.h"

    .global sdrv_irq_handler

    .section .text.drv.irq, "ax", %progbits
    .arm

sdrv_irq_handler:
    /* save spsr to r11, atpcs is 0~3*/
    mrs r11, spsr

    /* read current interrupt threshold */
    ldr r0, =INTCPS_BASE + INTC_THRESHOLD
    ldr r12, [r0]

    /* update current priority to threshold */
    ldr r1, =INTCPS_BASE + INTC_IRQ_PRIORITY
    ldr r2, [r1]
    and r2, r2, #0x3F
    str r2, [r0]

    /* get current IRQ number */
    ldr r1, =INTCPS_BASE + INTC_SIR_IRQ
    ldr r0, [r1]
    and r0, r0, #0x7F

    /* allow new IRQ */
    ldr r1, =INTCPS_BASE + INTC_CONTROL
    ldr r2, [r1]
    orr r2, r2, #0x1
    str r2, [r1]

    /* save general register */
    stmfd sp!, {r11-r12, lr}

    /* Data Synchronization Barrier */
    dsb

    /* Read-modify-write the CPSR to enable IRQs */
    cpsie i

    /* current register value
     * R0 :IRQ number
     * R11:SPSR
     * R12:IRQ threshold
     */
    bl arch_irq_handler

    /* Read-modify-write the CPSR to disable IRQs */
    cpsid i

    /* restore general register */
    ldmfd sp!, {r11-r12, lr}

    /* Restore the INTC_THRESHOLD register from R12 */
    ldr r0, =INTCPS_BASE + INTC_THRESHOLD
    str r12, [r0]

    /* Restore spsr */
    msr spsr_cxsf, r11

    /* return back */
    bx lr

    .end
