    .global do_prefetch_abort
    .global do_data_abort
    .global do_irq

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

/**
 * @brief  interrupt handler.
 */
do_irq:
    /* update return link addr */
    sub lr, lr, #4

    /* save general register */
    stmfd sp!, {r0-r12, lr}

    bl sdrv_irq_handler

    /* restore general register */
    ldmfd sp!, {r0-r12, pc}^

    .end
