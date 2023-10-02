#include "arch_cpsr.h"
#include "arch_cpu.h"
#include "board_init.h"
#include "sdrv_timer.h"
#include "board_config.h"

/**
 * @brief  The udelay for pmu.
 */
void udelay(uint32_t us)
{
    arch_tick_delay(PMU_US_TO_TICK(us));
}

/**
 * @brief  The interrupt call back for timer.
 */
void sdrv_timer_intc_handler(void* para)
{
    //tryrtos_kernel_tick_handler();
    sdrv_dtimer_int_status_clear(DTIMER2_BASE, TIMER_INTERRUPT_OVF);
    (void)para;
}

void tryrtos_idle_entry_call_back(void *para)
{
    /* configure timer for 1ms tick */
    sdrv_timer_init(DTIMER2_BASE);
    (void)para;
}

/**
 * @brief  The Main functional logic processing interface.
 */
int main(void)
{
    /* early init for tryrtos */
    //tryrtos_kernel_init();

    /* start running tryrtos */
    //tryrtos_kernel_start();

    return 0;
}