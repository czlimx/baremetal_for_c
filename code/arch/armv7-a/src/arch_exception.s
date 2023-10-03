    .global do_prefetch_abort
    .global do_data_abort
    .global do_irq
    .extern sdrv_irq_handler
    .weak   board_interrupt_call_back

    .section .text.arch.exception, "ax", %progbits
    .arm

/**
 * @brief  Prefetch instruction abort handler.
 */
do_prefetch_abort:
    b do_prefetch_abort

/**
 * @brief  Prefetch data abort handler.
 */
do_data_abort:
    b do_data_abort


board_interrupt_call_back:
    bx lr

/**
 * @brief  interrupt handler.
 */
do_irq:
    /* update return link addr */
    sub lr, lr, #4

    /* save general register */
    stmfd sp!, {r0-r12, lr}

    /* handling interrupt exceptions */
    bl sdrv_irq_handler
    bl board_interrupt_call_back

    /* restore general register */
    ldmfd sp!, {r0-r12, pc}^

    .end
