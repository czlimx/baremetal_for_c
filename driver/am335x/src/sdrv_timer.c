#include "sdrv_timer.h"

static void sdrv_dtimer_wait_for_writel(const uint32_t base, const enum sdrv_dtimer_pend_status bit)
{
    uint32_t value = 0x1U;

    if (((readl(base + DMTIMER_TSICR) >> 2) & 0x1U) != 0x1U)
        return ;

    while (0x1U == value)
        value = (readl(base + DMTIMER_TWPS) >> bit) & 0x1U;
}

void sdrv_dtimer_soft_reset(const uint32_t base)
{
    uint32_t value = 0x1U;

    rmwr32(base + DMTIMER_TIOCP_CFG, 0, 1, 0x1U);
    while (0x1U == value)
        value = (readl(base + DMTIMER_TIOCP_CFG) >> 0) & 0x1U;
}

void sdrv_dtimer_enable(const uint32_t base)
{
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TCLR);
    rmwr32(base + DMTIMER_TCLR, 0, 1, 0x1U);
}

void sdrv_dtimer_disable(const uint32_t base)
{
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TCLR);
    rmwr32(base + DMTIMER_TCLR, 0, 1, 0x0U);
}

void sdrv_dtimer_mode_configure(const uint32_t base, const uint32_t mode)
{
    uint32_t value = 0;

    /* Wait for previous write to complete */
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TCLR);

    /* Clear the AR and CE field of TCLR */
    value = readl(base + DMTIMER_TCLR);
    value &= ~(0x1U << 1U);
    value &= ~(0x1U << 6U);
    writel(value, base + DMTIMER_TCLR);

    /* Wait for previous write to complete */
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TCLR);

    /* Set the timer mode in TCLR register */
    value = readl(base + DMTIMER_TCLR);
    if (TIMER_TRIGGER_RELOAD == mode)
        value |= (0x1U << 1U);
    else if (TIMER_TRIGGER_COMPARE == mode)
        value |= (0x1U << 6U);
    else
    {
        value |= (0x1U << 1U);
        value |= (0x1U << 6U);
    }
    writel(value, base + DMTIMER_TCLR);
}

void sdrv_dtimer_prescaler_clk_enable(const uint32_t base, const uint32_t ptv)
{
    uint32_t value = 0;

    /* Wait for previous write to complete */
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TCLR);

    /* Clear the PTV field of TCLR */
    value = readl(base + DMTIMER_TCLR);
    value &= ~(0x7U << 2U);
    writel(value, base + DMTIMER_TCLR);

    /* Wait for previous write to complete */
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TCLR);

    /* Set the PTV field and enable the pre-scaler clock */
    value = readl(base + DMTIMER_TCLR);
    value |= ((ptv & 0x7U) << 2U);
    value |= (0x1U << 5U);
    writel(value, base + DMTIMER_TCLR);
}

void sdrv_dtimer_prescaler_clk_disable(const uint32_t base)
{
    /* Wait for previous write to complete */
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TCLR);

    /* Disable Pre-scaler clock */
    rmwr32(base + DMTIMER_TCLR, 5, 1, 0x0U);
}

void sdrv_dtimer_counter_set(const uint32_t base, const uint32_t counter)
{
    /* Wait for previous write to complete */
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TCRR);

    /* Set the counter value */
    writel(counter, base + DMTIMER_TCRR);
}

void sdrv_dtimer_reload_set(const uint32_t base, const uint32_t reload)
{
    /* Wait for previous write to complete */
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TLDR);

    /* Load the register with the re-load value */
    writel(reload, base + DMTIMER_TLDR);
}

void sdrv_dtimer_compare_set(const uint32_t base, const uint32_t compare)
{
    /* Wait for previous write to complete */
    sdrv_dtimer_wait_for_writel(base, TIMER_W_PEND_TMAP);

    /* Load the register with the re-load value */
    writel(compare, base + DMTIMER_TMAR);
}

void sdrv_dtimer_int_status_clear(const uint32_t base, const enum sdrv_dtimer_interrupt bit)
{
    /* Clear the interrupt status from IRQSTATUS register */
    rmwr32(base + DMTIMER_IRQSTATUS, bit, 1, 0x1U);
    (void)readl(base + DMTIMER_IRQSTATUS);
}

void sdrv_dtimer_int_enable(const uint32_t base, const enum sdrv_dtimer_interrupt bit)
{
    /* Enable the DMTimer interrupts represented by intFlags */
    rmwr32(base + DMTIMER_IRQENABLE_SET, bit, 1, 0x1U);
}

void sdrv_dtimer_int_disable(const uint32_t base, const enum sdrv_dtimer_interrupt bit)
{
    /* Disable the DMTimer interrupts represented by intFlags */
    rmwr32(base + DMTIMER_IRQENABLE_CLR, bit, 1, 0x1U);
}
