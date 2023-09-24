#include "arch_gicv2.h"
#include "arch_compiler.h"

/**
 * @brief Enable the interrupt distributor using the GIC's CTLR register.
 */
void arch_gicd_enable(void)
{
    uint32_t value = readl(GICD_CTLR);
    /* Group 0 interrupts forwarded, subject to the priority rules. */
    value |= (1 << 0);
    /* Group  interrupts forwarded, subject to the priority rules. */
    value |= (1 << 1);
    writel(value, GICD_CTLR);
}

/**
 * @brief Disable the interrupt distributor using the GIC's CTLR register.
 */
void arch_gicd_disable(void)
{
    uint32_t value = readl(GICD_CTLR);
    /* Group 0 interrupts not forwarded. */
    value &= ~(1 << 0);
    /* Group 1 interrupts not forwarded. */
    value &= ~(1 << 1);
    writel(value, GICD_CTLR);
}

/**
 * @brief Read the GIC's TYPER register.
 * @return uint32_t 
 *         [15:11] LSPI           the value of this field is the maximum number of implemented lockable SPIs.
 *         [10]    SecurityExtn   Indicates whether the GIC implements the Security Extensions.
 *         [7:5]   CPUNumber      Indicates the number of implemented CPU interfaces.
 *         [4:0]   ITLinesNumber  Indicates the maximum number of interrupts that the GIC supports.
 */
uint32_t arch_gicd_get_infomation(void)
{
    return readl(GICD_TYPER);
}

/**
 * @brief Reads the GIC's IIDR register.
 * @return uint32_t Provides information about the implementer and revision of the Distributor.
 */
uint32_t arch_gicd_get_identification(void)
{
    return readl(GICD_IIDR);
}

/**
 * @brief Set Each bit controls whether the corresponding interrupt is in Group 0 or Group 1.
 */
void arch_gicd_set_group(uint32_t number, uint32_t group)
{
    uint32_t gro    = number / 4;
    uint32_t bit    = number % 4;
    uint32_t value  = 0;

    value  = readl(GICD_IGROUPR(gro));
    if (group == 0)
        value &= ~(0x1 << bit);
    else 
        value |=  (0x1 << bit);
    writel(value, GICD_IGROUPR(gro));
}

/**
 * @brief Enables the given interrupt using GIC's ISENABLER register.
 */
void arch_gicd_set_enable(uint32_t number)
{
    uint32_t group = number / 32;
    uint32_t bit   = number % 32;
    uint32_t value = 0;
    
    value  = readl(GICD_ISENABLER(group));
    value |= (0x1 << bit);
    writel(value, GICD_ISENABLER(group));
}

/**
 * @brief Disables the given interrupt using GIC's ICENABLER register.
 */
void arch_gicd_clear_enable(uint32_t number)
{
    uint32_t group = number / 32;
    uint32_t bit   = number % 32;
    uint32_t value = 0;
    
    value  = readl(GICD_ICENABLER(group));
    value |= (0x1 << bit);
    writel(value, GICD_ICENABLER(group));
}

/**
 * @brief Sets the given interrupt as pending using GIC's ISPENDR register.
 */
void arch_gicd_set_pending(uint32_t number)
{
    uint32_t group = number / 32;
    uint32_t bit   = number % 32;
    uint32_t value = 0;

    value  = readl(GICD_ISPENDR(group));
    value |= (0x1 << bit);
    writel(value, GICD_ISPENDR(group));
}

/**
 * @brief Clears the given interrupt from being pending using GIC's ICPENDR register.
 */
void arch_gicd_clear_pending(uint32_t number)
{
    uint32_t group = number / 32;
    uint32_t bit   = number % 32;
    uint32_t value = 0;

    value  = readl(GICD_ICPENDR(group));
    value |= (0x1 << bit);
    writel(value, GICD_ICPENDR(group));
}

/**
 * @brief Sets the given interrupt as pending using GIC's GICD_ISACTIVER register.
 */
void arch_gicd_set_active(uint32_t number)
{
    uint32_t group = number / 32;
    uint32_t bit   = number % 32;
    uint32_t value = 0;

    value  = readl(GICD_ISACTIVER(group));
    value |= (0x1 << bit);
    writel(value, GICD_ISACTIVER(group));
}

/**
 * @brief Clears the given interrupt from being pending using GIC's GICD_ICACTIVER register.
 */
void arch_gicd_clear_active(uint32_t number)
{
    uint32_t group = number / 32;
    uint32_t bit   = number % 32;
    uint32_t value = 0;
    
    value  = readl(GICD_ICACTIVER(group));
    value |=  (0x1 << bit);
    writel(value, GICD_ICACTIVER(group));
}

/**
 * @brief Set the priority for the given interrupt in the GIC's IPRIORITYR register.
 * @note am5718 just support 32 priority (priority[11111000]), so priority << 3
 */
void arch_gicd_set_priority(uint32_t number, uint32_t priority)
{
    uint32_t group = number / 4;
    uint32_t bit   = number % 4;
    uint32_t value = 0;

    value  = readl(GICD_IPRIORITYR(group));
    value &= ~(0xFF << bit);
    value |=  ((priority & 0xFF) << bit);
    writel(value, GICD_IPRIORITYR(group));
}

/**
 * @brief Read the current interrupt priority from GIC's IPRIORITYR register.
 */
uint32_t arch_gicd_get_priority(uint32_t number)
{
    uint32_t group = number / 4;
    uint32_t bit   = number % 4;

    return (readl(GICD_IPRIORITYR(group)) >> bit) & 0xFF;
}

/**
 * @brief Sets the GIC's ITARGETSR register for the given interrupt.
 */
void arch_gicd_set_target(uint32_t number, uint32_t cpuid)
{
    uint32_t group = number / 4;
    uint32_t bit   = number % 4;
    uint32_t value = 0;

    value  = readl(GICD_ITARGETSR(group));
    value &= ~(0xFF << bit);
    value |=  ((cpuid & 0xFF) << bit);
    writel(value, GICD_ITARGETSR(group));
}

/**
 * @brief Read the GIC's ITARGETSR register.
 */
uint32_t arch_gicd_get_target(uint32_t number)
{
    uint32_t group = number / 4;
    uint32_t bit   = number % 4;
    return (readl(GICD_ITARGETSR(group)) >> bit) & 0xFF;
}


/**
 * @brief Read the GIC's GICD_ICFGR register.
 */
void arch_gicd_config_trigger(enum gicd_trigger_type trigger, enum gicd_encode_type encode, uint32_t number)
{
    uint32_t group = number / 16;
    uint32_t bit   = number % 16;
    uint32_t value = 0;

    value  = readl(GICD_ICFGR(group));
    if (trigger == GICD_LEVEL_SENSITIVE)
        value &= ~(0x1 << (bit + 1));
    else
        value |=  (0x1 << (bit + 1));

    if (encode == GICD_N_N_MODE)
        value &= ~(0x1 << bit);
    else
        value |=  (0x1 << bit);
    writel(value, GICD_ICFGR(group));
}

/**
 * @brief Read the GIC's GICD_NSACR register.
 */
void arch_gicd_config_access(enum gicd_access_type access, uint32_t number)
{
    uint32_t group = number / 16;
    uint32_t bit   = number % 16;
    uint32_t value = 0;

    value  = readl(GICD_NSACR(group));
    value &= ~(0x3 << bit);
    value |=  ((access & 0x3) << bit);
    writel(value, GICD_NSACR(group));
}

/**
 * @brief Read the GIC's GICD_SGIR register.
 */
void arch_gicd_generate_interrupt(enum gicd_target_list_filter_type filter, uint32_t cpu_umask, uint32_t number)
{
    uint32_t value = 0;

    value |= (filter & 0x3) << 24;
    value |= (cpu_umask & 0xFF) << 16;
    value |= (number & 0xF) << 0;
    writel(value, GICD_SGIR);
}

/**
 * @brief Read the GIC's GICD_SPENDSGIR register.
 */
void arch_gicd_sgi_set_pending(uint32_t cpuid, uint32_t number)
{
    uint32_t group = number / 4;
    uint32_t bit   = number % 4;
    uint32_t value = 0;

    value  = readl(GICD_SPENDSGIR(group));
    value |=  ((cpuid & 0xFF) << bit);
    writel(value, GICD_SPENDSGIR(group));
}

/**
 * @brief Read the GIC's GICD_CPENDSGIR register.
 */
void arch_gicd_sgi_clear_pending(uint32_t cpuid, uint32_t number)
{
    uint32_t group = number / 4;
    uint32_t bit   = number % 4;
    uint32_t value = 0;

    value  = readl(GICD_CPENDSGIR(group));
    value |=  ((cpuid & 0xFF) << bit);
    writel(value, GICD_CPENDSGIR(group));
}

void arch_gicc_enable(void)
{
    uint32_t value = readl(GICC_CTLR);
    value |= (1 << 0);
    value |= (1 << 1);
    writel(value, GICC_CTLR);
}

void arch_gicc_disable(void)
{
    uint32_t value = readl(GICC_CTLR);
    value &= ~(1 << 0);
    value &= ~(1 << 1);
    writel(value, GICC_CTLR);
}

void arch_gicc_set_priority_mask(uint32_t priority)
{
    writel((priority & 0xFF), GICC_PMR);
}

/**
 * @brief 
 * @param  pointy example 2 :group priority [7:3], subpriority [2:0]
 */
void arch_gicc_set_binary_point(uint32_t pointy)
{
    writel((pointy & 0x7), GICC_BPR);
}

uint32_t arch_gicc_acknowledge(void)
{
    return readl(GICC_IAR);
}

void arch_gicc_end_of_interrupt(uint32_t cpuid, uint32_t number)
{
    writel(((cpuid & 0x7) >> 10) | (number & 0x3FF), GICC_EOIR);
}

void arch_gicc_set_running_priority(uint32_t priority)
{
    writel((priority & 0xFF), GICC_RPR);
}

void arch_gicc_get_highest_priority(uint32_t priority)
{
    writel((priority & 0xFF), GICC_HPPIR);
}
