#include "arch_cpsr.h"
#include "arch_cpu.h"
#include "board_init.h"
#include "sdrv_timer.h"
#include "board_config.h"
#include "tryrtos_tick.h"
#include "tryrtos_kernel.h"
#include "libc_printf.h"
#include "tryrtos_thread.h"

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
    tryrtos_tick_handler();
    sdrv_dtimer_int_status_clear(DTIMER2_BASE, TIMER_INTERRUPT_OVF);
    (void)para;
}

/**
 * @brief  The idle first function for call back.
 */
void tryrtos_idle_entry_call_back(void *para)
{
    /* configure timer for 1ms tick */
    sdrv_timer_init(DTIMER2_BASE);
    (void)para;
}


static struct tryrtos_thread_type tryrtos_thread_0_handler;
static struct tryrtos_thread_type tryrtos_thread_1_handler;
static struct tryrtos_thread_type tryrtos_thread_2_handler;
static struct tryrtos_thread_type tryrtos_thread_3_handler;
static struct tryrtos_thread_type tryrtos_thread_4_handler;
static struct tryrtos_thread_type tryrtos_thread_5_handler;
static uint32_t tryrtos_thread_0_stack[0x1000];
static uint32_t tryrtos_thread_1_stack[0x1000];
static uint32_t tryrtos_thread_2_stack[0x1000];
static uint32_t tryrtos_thread_3_stack[0x1000];
static uint32_t tryrtos_thread_4_stack[0x1000];
static uint32_t tryrtos_thread_5_stack[0x1000];

void tryrtos_thread_0_entry(void *para)
{
    (void)para;

    for (;;)
    {
        printf("thread 0 is running\r\n");
    }
}

void tryrtos_thread_1_entry(void *para)
{
    (void)para;

    for (;;)
    {
        printf("thread 1 is running\r\n");
    }
}

void tryrtos_thread_2_entry(void *para)
{
    (void)para;

    for (;;)
    {
        printf("thread 2 is running\r\n");
    }
}

void tryrtos_thread_3_entry(void *para)
{
    (void)para;

    for (;;)
    {
        printf("thread 3 is running\r\n");
    }
}

void tryrtos_thread_4_entry(void *para)
{
    (void)para;

    for (;;)
    {
        printf("thread 4 is running\r\n");
    }
}

void tryrtos_thread_5_entry(void *para)
{
    (void)para;

    for (;;)
    {
        printf("thread 5 is running\r\n");
    }
}

/**
 * @brief  The Main functional logic processing interface.
 */
int main(void)
{
    /* early init for tryrtos */
    tryrtos_kernel_init();

    /* create thread for test */
    tryrtos_thread_create(&tryrtos_thread_0_handler, 
                          "tryrtos 0 thread", 
                          0, 
                          NULL,
                          tryrtos_thread_0_entry,
                          tryrtos_thread_0_stack, 
                          0x4000);

    tryrtos_thread_create(&tryrtos_thread_1_handler, 
                          "tryrtos 1 thread", 
                          0, 
                          NULL,
                          tryrtos_thread_1_entry,
                          tryrtos_thread_1_stack, 
                          0x4000);

    tryrtos_thread_create(&tryrtos_thread_2_handler, 
                          "tryrtos 2 thread", 
                          1, 
                          NULL,
                          tryrtos_thread_2_entry,
                          tryrtos_thread_2_stack, 
                          0x4000);

    tryrtos_thread_create(&tryrtos_thread_3_handler, 
                          "tryrtos 3 thread", 
                          1, 
                          NULL,
                          tryrtos_thread_3_entry,
                          tryrtos_thread_3_stack, 
                          0x4000);

    tryrtos_thread_create(&tryrtos_thread_4_handler, 
                          "tryrtos 4 thread", 
                          1, 
                          NULL,
                          tryrtos_thread_4_entry,
                          tryrtos_thread_4_stack, 
                          0x4000);

    tryrtos_thread_create(&tryrtos_thread_5_handler, 
                          "tryrtos 5 thread", 
                          1, 
                          NULL,
                          tryrtos_thread_5_entry,
                          tryrtos_thread_5_stack, 
                          0x4000);

    /* start running tryrtos */
    tryrtos_kernel_start();

    return 0;
}