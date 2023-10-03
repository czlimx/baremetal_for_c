#include "tryrtos_kernel.h"
#include "tryrtos_thread.h"
#include "tryrtos_types.h"
#include "tryrtos_tick.h"

/**
 * @brief  Define the free thread handler.
 */
static struct tryrtos_thread_type tryrtos_idle_handler;

/**
 * @brief  Define the free thread stack space capacity.
 */
static uint32_t tryrtos_idle_stack[TRYRTOS_IDLE_STACK_LENGTH / sizeof(uint32_t)];

/**
 * @brief   The idle thread entry. 
 */
void tryrtos_idle_entry(void *para)
{
    /* Call the first thread processing interface of the upper layer app */
    tryrtos_idle_entry_call_back(para);

    for (;;)
    {
        /* Check if any tasks need to be scheduled */
        //tryrtos_interrupt_call_back();
        
        //uint64_t busy_tick = tryrtos_kernel_tick - tryrtos_idle_handler.running_tick;
        //uint32_t cpu_load  = busy_tick / tryrtos_kernel_tick;
        //printf("CPU load is %d%%\r\n", cpu_load);

        tryrtos_thread_yield();
    }
}

/**
 * @brief   The kernel init processing. 
 */
void tryrtos_kernel_init(void)
{
    tryrtos_thread_init();
}

/**
 * @brief   The kernel start processing. 
 */
void tryrtos_kernel_start(void)
{
    tryrtos_thread_create(&tryrtos_idle_handler, 
                          "tryrtos idle thread", 
                          TRYRTOS_MAX_SCHEDULER_PRIORITY - 1, 
                          NULL,
                          tryrtos_idle_entry,
                          tryrtos_idle_stack, 
                          TRYRTOS_IDLE_STACK_LENGTH);
    /* update the state */
    tryrtos_handler.current = &tryrtos_idle_handler;
    tryrtos_idle_handler.state = TRYRTOS_THREAD_RUNNING;
    tryrtos_context_first_start(tryrtos_idle_handler.stack_ptr);
}

