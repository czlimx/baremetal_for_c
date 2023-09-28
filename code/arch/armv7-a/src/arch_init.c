#include "arch_branch_predictor.h"
#include "arch_cache.h"
#include "arch_fpu.h"
#include "arch_exception.h"
#include "arch_cpsr.h"
#include "arch_pmu.h"
#include "arch_irq.h"
#include "device_info.h"
#include "board_init.h"
#include "arch_mmu.h"
#include "arch_tlb.h"
#include "string.h"
#include "arch_cpu.h"

extern uint32_t _bss_start_[], _bss_end_[];

/**
 * @brief  The early init for CPU.
 */
void _early_arch_init(void)
{
    /* clear bss section */
    memset((void*)_bss_start_, 0, _bss_end_ - _bss_start_);

    /* board early init */
    board_early_init();

    /* invalidate all tlb */
    arch_tlb_invalidate_all();

    /* enable MMU */
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

    /* init for board */
    board_init();
}
