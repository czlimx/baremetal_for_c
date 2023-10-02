#include "arch_irq.h"
#include "sdrv_intc.h"
#include "arch_cpsr.h"

/**
 * @brief Define architecture-dependent interrupt handling data types.
*/
struct arch_irq_handler_type
{
    irq_handler_type handler;
    void *para;
};

/**
 * @brief Create all interrupt processing vector tables.
*/
static struct arch_irq_handler_type arch_irq_handler_array[MAX_INTC_NUMBER];

/**
 * @brief Architecture-dependent default interrupt handler.
*/
static void arch_default_irq_handler(void *para)
{
    (void)para;
}

/**
 * @brief  Architecture-dependent interrupt handler.
 */
void arch_irq_handler(uint32_t irq)
{
    /* clear IRQ status*/
    sdrv_irq_clear_status(irq);

    /* handler interrupt */
    arch_irq_handler_array[irq].handler(arch_irq_handler_array[irq].para);
}

/**
 * @brief  Architecture-dependent interrupt init.
 */
void arch_irq_init(void)
{
    /* config default interrupt handler */
    for (uint32_t i = 0; i < MAX_INTC_NUMBER; i++)
    {
        arch_irq_handler_array[i].para = NULL;
        arch_irq_handler_array[i].handler = arch_default_irq_handler;
    }

    /* enable INTC module */
    sdrv_irq_init();
}

/**
 * @brief  Architecture-dependent interrupt register.
 */
void arch_irq_register(uint32_t irq, uint32_t priority, void *para, irq_handler_type handler)
{
    if (handler == NULL)
        return;

    if (priority > (ARCH_IRQ_MAX_PRIORITY - 1))
        return;

    /* update interrupt handler */
    arch_irq_handler_array[irq].para = para;
    arch_irq_handler_array[irq].handler = handler;

    /* config priority for IRQ */
    sdrv_irq_set_priority(irq, priority);

    /* enable IRQ number */
    sdrv_irq_enable(irq);
}

/**
 * @brief  Architecture-dependent interrupt unregister.
 */
void arch_irq_unregister(uint32_t irq)
{
    /* disable IRQ number */
    sdrv_irq_disable(irq);

    /* update interrupt handler */
    arch_irq_handler_array[irq].para = NULL;
    arch_irq_handler_array[irq].handler = arch_default_irq_handler;
}
