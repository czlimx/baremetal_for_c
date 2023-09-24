#include "arch_mpu.h"
#include "arch_branch_predictor.h"
#include "arch_cache.h"
#include "arch_fpu.h"
#include "arch_exception.h"
#include "arch_cpsr.h"
#include "arch_pmu.h"
#include "device_info.h"

#define DEFAULT_PMU_1MS_COUNTER     (0xFFFFFFFF - (1000000 / ((1000000000 / CORE_CLOCK_PRE) * 64)))

static int32_t arch_pmu_cycle_counter_irq_flag = 0;

const uint32_t arch_mpu_config[] = {
    [MPU_REGION_STRONGORDERED] = MPU_RACR_CONFIG(
        0, 0, 0,    /* See "TEX[2:0], C and B encodings" */
        0,          /* S bit is not used for strong ordered. */
        RACR_AP_RW_RW,
        1           /* XN */
    ),

    [MPU_REGION_DEVICE] = MPU_RACR_CONFIG(
        0, 0, 1,
        0,          /* S bit is not used for device memory */
        RACR_AP_RW_RW,
        1           /* XN */
    ),

    [MPU_REGION_NORMAL] = MPU_RACR_CONFIG(
        0, 1, 1,    /* cacheable, WB, no WA */
        0,          /* Not shared. R5 L1 cache does not cache shared
                       normal regions */
        RACR_AP_RW_RW,
        0           /* non XN */
    ),

    [MPU_REGION_NORMAL_NONCACHEABLE] = MPU_RACR_CONFIG(
        1, 0, 0,    /* non-cacheable */
        0,
        RACR_AP_RW_RW,
        0           /* non XN */
    ),

    [MPU_REGION_NO_ACCESS] = MPU_RACR_CONFIG(
        0,
        0,
        0,
        0,
        RACR_AP_NO_NO,
        0
    ),

    [MPU_REGION_READONLY] = MPU_RACR_CONFIG(
        0, 1, 1,    /* cacheable, WB, no WA */
        0,          /* Not shared. R5 L1 cache does not cache shared
                       normal regions */
        RACR_AP_RO_NO,
        0           /* non XN */
    ),
};

void _early_init(void)
{
    /* enable FPU */
    arch_fpu_enable();

    /* enable alignment check */
    arch_alignment_check_enable();

    /* enable branch predictor */
    arch_branch_predictor_invalidate_all();
    arch_branch_predictor_enable();

    /* enable pmu */
    arch_pmu_user_access_enable();
    arch_pmu_cycle_counter_init();
    arch_pmu_cycle_counter_set_counter(DEFAULT_PMU_1MS_COUNTER);
    arch_pmu_cycle_counter_enable_irq();
    arch_pmu_cycle_counter_enable();

    /* enable MMU */


    /* enable Dcache */
    //arch_dcache_invalidate_all();
    //arch_dcache_enable();

    /* enable Icache */
    //arch_icache_invalidate_all();
    //arch_icache_enable();

    

    /* switch SYS mode */
    arch_cpsr_switch_to_sys();

    for (;;);
}