    .extern arch_pmu_irq_call_back
    
    .global arch_pmu_user_access_enable
    .global arch_pmu_user_access_disable
    .global arch_pmu_cycle_counter_enable
    .global arch_pmu_cycle_counter_disable
    .global arch_pmu_cycle_counter_init
    .global arch_pmu_cycle_counter_enable_irq
    .global arch_pmu_cycle_counter_disable_irq
    .global arch_pmu_cycle_counter_set_counter
    .global arch_pmu_cycle_counter_delay
    .global arch_pmu_event_counter_enable
    .global arch_pmu_event_counter_disable
    .global arch_pmu_event_counter_init
    .global arch_pmu_event_counter_increment
    .global arch_pmu_event_counter_select
    .global arch_pmu_event_counter_read
    .global arch_pmu_event_counter_enable_irq
    .global arch_pmu_event_counter_disable_irq
    .global arch_pmu_irq_handler

    .section .text.arch.pmu, "ax", %progbits
    .arm

/**
 * @brief  The enables User mode access to the Performance Monitors.
 */
arch_pmu_user_access_enable:
    // PMUSERENR[0] enable User mode to access PMU.
    mrc p15, 0, r0, c9, c14, 0
    orr r0, r0, #(1 << 0)
    mcr p15, 0, r0, c9, c14, 0
    bx lr

/**
 * @brief  The disables User mode access to the Performance Monitors.
 */
arch_pmu_user_access_disable:
    // PMUSERENR[0] disable User mode to access PMU.
    mrc p15, 0, r0, c9, c14, 0
    bic r0, r0, #(1 << 0)
    mcr p15, 0, r0, c9, c14, 0
    bx lr

/**
 * @brief  The enable the Cycle Count.
 */    
arch_pmu_cycle_counter_enable:
    // PMCNTENSET[31] enable cycle counter.
    mrc p15, 0, r0, c9, c12, 1
    orr r0, r0, #(1 << 31)
    mcr p15, 0, r0, c9, c12, 1
    bx lr

/**
 * @brief  The disable the Cycle Count.
 */  
arch_pmu_cycle_counter_disable:
    // PMCNTENCLR[31] disable cycle counter.
    mrc p15, 0, r0, c9, c12, 2
    orr r0, r0, #(1 << 31)
    mcr p15, 0, r0, c9, c12, 2
    bx lr

/**
 * @brief  The init the Cycle Count.
 */  
arch_pmu_cycle_counter_init:
    // PMCR[2] Cycle counter reset.
    mrc p15, 0, r0, c9, c12, 0
    orr r0, r0, #(1 << 2)
    mcr p15, 0, r0, c9, c12, 0

    // PMCR[3] 64th Cycle count divider
    mrc p15, 0, r0, c9, c12, 0
    orr r0, r0, #(1 << 3)
    mcr p15, 0, r0, c9, c12, 0
    bx lr

/**
 * @brief  The enable the Cycle Count IRQ.
 */
arch_pmu_cycle_counter_enable_irq:
    // PMINTENSET[31] enable PMCCNTR overflow interrupt.
    mrc p15, 0, r0, c9, c14, 1
    orr r0, r0, #(1 << 31)
    mcr p15, 0, r0, c9, c14, 1
    bx lr

/**
 * @brief  The disable the Cycle Count IRQ.
 */
arch_pmu_cycle_counter_disable_irq:
    // PMINTENCLR[31] disable PMCCNTR overflow interrupt.
    mrc p15, 0, r0, c9, c14, 2
    orr r0, r0, #(1 << 31)
    mcr p15, 0, r0, c9, c14, 2

    bx lr

/**
 * @brief  The set the Cycle Counter.
 * @param  r0 - the counter value
 */
arch_pmu_cycle_counter_set_counter:
    // write PMCCNTR Register.
    mcr p15, 0, r0, c9, c13, 0
    bx lr

/**
 * @brief  The used the Cycle Counter delay.
 * @param  r0 - the tick value
 */
arch_pmu_cycle_counter_delay:
    // PMCR[2] Cycle counter reset.
    mrc p15, 0, r1, c9, c12, 0
    orr r1, r1, #(1 << 2)
    mcr p15, 0, r1, c9, c12, 0
1:
    // read PMCCNTR Register.
    mcr p15, 0, r1, c9, c13, 0
    cmp r1, r0
    blt 1b
    bx lr

/**
 * @brief  The enable the Event Counter.
 * @param  r0 - the counter id
 */
arch_pmu_event_counter_enable:
    mov r2, #1
    mrc p15, 0, r1, c9, c12, 1
    orr r1, r2, lsl r0
    mcr p15, 0, r1, c9, c12, 1
    bx lr

/**
 * @brief  The disable the Event Counter.
 * @param  r0 - the counter id
 */
arch_pmu_event_counter_disable:
    mov r2, #1
    mrc p15, 0, r1, c9, c12, 2
    orr r1, r2, lsl r0
    mcr p15, 0, r1, c9, c12, 2
    bx lr

/**
 * @brief  The init the all Event Counter.
 */
arch_pmu_event_counter_init:
    // Event counter reset.
    mrc p15, 0, r0, c9, c12, 0
    orr r0, r0, #(1 << 1)
    mcr p15, 0, r0, c9, c12, 0
    bx lr

/**
 * @brief  The software increment the Event Counter.
 * @param  r0 - the counter id
 */
arch_pmu_event_counter_increment:
    mov r1, #1
    mov r1, r1, lsl r0
    mcr p15, 0, r1, c9, c12, 4
    bx lr

/**
 * @brief  The select counter and event for the Event Counter.
 * @param  r0 - the counter id
 * @param  r1 - the event id
 */
arch_pmu_event_counter_select:
    // PMSELR.SEL selects an event counter.
    mcr p15, 0, r0, c9, c12, 5

    // PMXEVTYPER configures which event increments that event counter.
    mcr p15, 0, r1, c9, c13, 1
    bx lr

/**
 * @brief  The read and clear counter for the Event Counter.
 * @param  r0 - the counter id
 * @return the event counter value
 */
arch_pmu_event_counter_read:
    // PMSELR.SEL selects an event counter.
    mcr p15, 0, r0, c9, c12, 5
    // reads the value of the selected event counter.
    mrc p15, 0, r0, c9, c13, 2
    // clear the value of the selected event counter.
    mov r1, #0
    mcr p15, 0, r1, c9, c13, 2
    bx lr

/**
 * @brief  The enable Event Counter IRQ.
 * @param  r0 - the counter id
 */
arch_pmu_event_counter_enable_irq:
    // PMINTENSET[31] enable PMCCNTR overflow interrupt.
    mov r1, #1
    mov r1, r1, lsl r0
    mrc p15, 0, r0, c9, c14, 1
    orr r0, r0, r1
    mcr p15, 0, r0, c9, c14, 1
    bx lr

/**
 * @brief  The disable Event Counter IRQ.
 * @param  r0 - the counter id
 */
arch_pmu_event_counter_disable_irq:
    // PMINTENCLR[31] disable PMCCNTR overflow interrupt.
    mov r1, #1
    mov r1, r1, lsl r0
    mrc p15, 0, r0, c9, c14, 2
    orr r0, r0, r1
    mcr p15, 0, r0, c9, c14, 2
    bx lr

/**
 * @brief  The IRQ handler for the Performance Monitors.
 */
arch_pmu_irq_handler:
    stmfd sp!, {lr}
    mrc p15, 0, r0, c9, c12, 3
    mcr p15, 0, r0, c9, c12, 3
    bl arch_pmu_interrupt_call_back
    ldmfd sp!, {lr}
    bx lr

    .end
