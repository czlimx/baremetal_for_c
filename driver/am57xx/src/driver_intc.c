#include "driver_intc.h"
#include "arch_compiler.h"
#include "arch_gicv2.h"

struct drv_intc_handler_type
{
    interrupt_handler handler;
    void *para;
};

static struct drv_intc_handler_type interrupt_handler_array[MAX_INTC_NUMBER];

static void drv_intc_default_interrupt_handler(void *para)
{
    (void)para;
}

void drv_intc_init(void)
{
    /* enable GIC Distributo */
    arch_gicd_enable();

    /* enable GIC CPU interface */
    arch_gicc_enable();

    /* clear all interrupt */
    for (uint32_t i = 0; i < MAX_INTC_NUMBER; i++)
    {
        arch_gicd_clear_active(i);
        arch_gicd_clear_pending(i);
        arch_gicd_clear_enable(i);

        /* config default interrupt handler */
        interrupt_handler_array[i].para = NULL;
        interrupt_handler_array[i].handler = drv_intc_default_interrupt_handler;
    }

    /* config default binary point 
     * 3 : group priority [7:4], subpriority [3:0]
    */
    arch_gicc_set_binary_point(3);

    /* update default interrupt priority mask 0xF0, 16 priority level */
    arch_gicc_set_priority_mask(0xF0);

    /* open cpsr.if for IRQ FIQ */
    asm volatile ("cpsie if");
}

void drv_intc_deinit(void)
{
    /* open cpsr.if for IRQ FIQ */
    asm volatile ("cpsid if");

    /* diabale GIC Distributo */
    arch_gicd_enable();

    /* diabale GIC CPU interface */
    arch_gicc_enable();
}

void drv_intc_register(uint32_t number, uint32_t priority, void *para, interrupt_handler handler)
{
    if (handler == NULL)
        return;

    if (priority > 15)
        return;

    /* config priority for IRQ */
    arch_gicd_set_priority(number, priority);

    /* update interrupt handler */
    interrupt_handler_array[number].para = para;
    interrupt_handler_array[number].handler = handler;
}

void drv_intc_unregister(uint32_t number)
{
    /* update interrupt handler */
    interrupt_handler_array[number].para = NULL;
    interrupt_handler_array[number].handler = drv_intc_default_interrupt_handler;
}

void drv_intc_handler(void)
{
    /* get current penging interrupt */
    uint32_t ack = arch_gicc_acknowledge();
    //uint32_t cpu = (ack >> 10) & 0x7;
    uint32_t irq = (ack >> 00) & 0x3FF;

    /* handler interrupt */
    interrupt_handler_array[irq].handler(interrupt_handler_array[irq].para);
}