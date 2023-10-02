#include "tryrtos_thread.h"
#include "tryrtos_tick.h"

/**
 * @brief The system tick for tryrtos.
 */
uint64_t tryrtos_kernel_tick = 0;

/**
 * @brief  set -- set tick value
 * @value: target tick value
 */
void tryrtos_tick_set(uint64_t value)
{
    tryrtos_kernel_tick = value;
}

/**
 * @brief  clear -- clear tick value to 0
 */
void tryrtos_tick_clear(void)
{
    tryrtos_kernel_tick = 0;
}

/**
 * @brief  add -- add tick value
 */
void tryrtos_tick_add(void)
{
    tryrtos_kernel_tick++;
}

/**
 * @brief  sub -- inc tick value
 */
void tryrtos_tick_sub(void)
{
    tryrtos_kernel_tick--;
}
