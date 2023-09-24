#include "arch_branch_predictor.h"
#include "arch_cache.h"
#include "arch_fpu.h"
#include "arch_exception.h"
#include "arch_cpsr.h"
#include "arch_pmu.h"
#include "arch_irq.h"
#include "device_info.h"
#include "early_init.h"
#include "arch_mmu.h"
#include "arch_tlb.h"

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
 * @param  udelay - the udelay value
 */
void arch_udelay(uint32_t udelay)
{
    volatile uint32_t tickTo = 0, startTick = 0, currentTick = 0;

    startTick = arch_pmu_cycle_counter_get_counter();
    tickTo = startTick + PMU_US_TO_TICK(udelay);

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

/**
 * @brief  The early init for CPU.
 */
void _early_arch_init(void)
{
    /* invalidate all tlb */
    arch_tlb_invalidate_all();

    /* enable MMU */
    early_mmu_config();
    arch_mmu_enable();

    /* enable Dcache */
    arch_dcache_invalidate_all();
    arch_dcache_enable();

    /* enable Icache */
    arch_icache_invalidate_all();
    arch_icache_enable();

    /* enable branch predictor */
    arch_branch_predictor_invalidate_all();
    arch_branch_predictor_enable();

    /* enable alignment check */
    arch_alignment_check_enable();

    /* enable async abort */
    arch_cpsr_async_abort_enable();

    /* enbale irq */
    arch_irq_init();

    /* enable pmu */
    arch_pmu_user_access_enable();
    arch_pmu_cycle_counter_init();
    arch_pmu_cycle_counter_enable();

    /* enable FPU */
    arch_fpu_enable();
}
