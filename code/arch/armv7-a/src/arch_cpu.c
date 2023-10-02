#include "arch_pmu.h"

/**
 * @brief  The get the MPIDR register.
 * @return the register value.
 */
void arch_alignment_check_enable(void)
{
    asm volatile (
        "mrc p15, #0, r0, c1, c0, #0\n"
        "orr r0, r0, #2\n"
        "mcr p15, #0, r0, c1, c0, #0" 
        : : : "cc" 
    );
}

/**
 * @brief  The get the MPIDR register.
 * @return the register value.
 */
uint32_t arch_cpu_get_mpidr(void)
{
    uint32_t mpidr = 0;
    asm volatile ("mrc p15, 0, %0, c0, c0, 5" : "=r"(mpidr) : : "cc" );
    return mpidr;
}

/**
 * @brief  The used the Cycle Counter delay.
 * @param  tick - the udelay to tick value
 */ 
void arch_tick_delay(uint32_t tick)
{
    volatile uint32_t tickTo = 0, startTick = 0, currentTick = 0;

    startTick = arch_pmu_cycle_counter_get_counter();
    tickTo = startTick + tick;

    if (tickTo > startTick)
    {
        /* tickTo not overflowed */
        do
        {
            currentTick = arch_pmu_cycle_counter_get_counter();
        } while ((currentTick < tickTo) && (currentTick > startTick));
    }
    else
    {
        /* currentTick overflowed */
        do
        {
            currentTick = arch_pmu_cycle_counter_get_counter();
        } while ((currentTick > startTick) || (currentTick < tickTo));
    }
}
