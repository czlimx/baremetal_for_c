#ifndef TRYRTOS_TICK_H_
#define TRYRTOS_TICK_H_

#include "tryrtos_types.h"

/**
 * @brief The system tick for tryrtos.
 */
extern uint64_t tryrtos_kernel_tick;

/**
 * @brief  set -- set tick value
 * @value: target tick value
 */
void tryrtos_tick_set(uint64_t value);

/**
 * @brief  clear -- clear tick value to 0
 */
void tryrtos_tick_clear(void);

/**
 * @brief  add -- add tick value
 */
void tryrtos_tick_add(void);

/**
 * @brief  sub -- inc tick value
 */
void tryrtos_tick_sub(void);

#endif /* TRYRTOS_TICK_H_ */
