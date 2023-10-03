#ifndef TRYRTOS_CONFIG_H_
#define TRYRTOS_CONFIG_H_

#include "libc_memory.h"
#include "arch_context.h"
#include "libc_printf.h"
#include "board_init.h"
#include "tryrtos_thread.h"


/**
 * @brief  Define the free thread stack space capacity.
 */
#define TRYRTOS_IDLE_STACK_LENGTH               0x4000

/**
 * @brief  Define the maximum scheduling priority.
 */
#define TRYRTOS_MAX_SCHEDULER_PRIORITY          16

/**
 * @brief  Define the running time of each task of the same priority.
 */
#define TRYRTOS_MAX_TICK_SCHEDULE               10

/**
 * @brief  Redefine the context initialization interface.
 */
#define tryrtos_context_init(ptr, para, entry)  arch_context_init(ptr, para, entry)

/**
 * @brief  Redefine the context switch interface.
 */
#define tryrtos_context_switch(old, new)        arch_context_switch(old, new)

/**
 * @brief  Redefine the context switch interface.
 */
#define tryrtos_context_start(ptr)              arch_context_start(ptr)

/**
 * @brief  Redefine the context switch interface.
 */
#define tryrtos_context_first_start(ptr)        arch_context_first_start(ptr)

/**
 * @brief  Redefine the delay switch interface.
 */
#define tryrtos_loop_mdelay(x)                  udelay(x * 1000)

#endif /* TRYRTOS_CONFIG_H_ */