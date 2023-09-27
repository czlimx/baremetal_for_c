#include "sdrv_intc.h"

/**
 * @brief init for IRQ.
 */
void drv_irq_init(void)
{
    uint32_t sysconfig = 0;
    uint32_t status = 0;
    
    /* softreset intc*/
    sysconfig = readl(INTCPS_BASE + INTC_SYSCONFIG);
    sysconfig |= (1 << 1);
    writel(sysconfig, INTCPS_BASE + INTC_SYSCONFIG);

    /* wait for intc reset done*/
    while (0 == status) {
        status = readl(INTCPS_BASE + INTC_SYSSTATUS) & 0x1;
    }
}

/** 
 * @brief config priority for IRQ.
 */
void drv_irq_set_priority(uint32_t irq, uint32_t priority)
{
    if (irq > (MAX_INTC_NUMBER - 1))
        return;

    writel(((priority & 0x3F) << 2), INTCPS_BASE + INTC_ILR(irq));
}

/**
 * @brief enable IRQ number.
 */
void drv_irq_enable(uint32_t irq)
{
    unsigned int group = 0;
    unsigned int bit = 0;

    if (irq > (MAX_INTC_NUMBER - 1))
        return;

    group = irq / 32;
    bit = irq % 32;

    writel((1 << bit), INTCPS_BASE + INTC_MIR_CLEAR(group));
}

/**
 * @brief disable IRQ number.
 */
void drv_irq_disable(uint32_t irq)
{
    unsigned int group = 0;
    unsigned int bit = 0;

    if (irq > (MAX_INTC_NUMBER - 1))
        return;

    group = irq / 32;
    bit = irq % 32;

    writel((1 << bit), INTCPS_BASE + INTC_MIR_SET(group));
}

/**
 * @brief clear IRQ status.
 */
void drv_irq_clear_status(uint32_t irq)
{
    unsigned int group = 0;
    unsigned int bit = 0;

    if (irq > (MAX_INTC_NUMBER - 1))
        return ;

    group = irq / 32;
    bit = irq % 32;

    writel((1 << bit), INTCPS_BASE + INTC_ISR_CLEAR(group));
}

/**
 * @brief trigger IRQ number.
 */
void drv_irq_trigger(uint32_t irq)
{
    unsigned int group = 0;
    unsigned int bit = 0;

    if (irq > (MAX_INTC_NUMBER - 1))
        return ;

    group = irq / 32;
    bit = irq % 32;

    writel((1 << bit), INTCPS_BASE + INTC_ISR_SET(group));
}
