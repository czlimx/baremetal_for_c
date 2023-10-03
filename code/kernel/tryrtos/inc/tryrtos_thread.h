#ifndef TRYRTOS_THREAD_H_
#define TRYRTOS_THREAD_H_

#include "tryrtos_config.h"
#include "tryrtos_types.h"

/**
 * @brief  Define the current thread handler pointer.
 */
extern struct tryrtos_thread_type *tryrtos_cur_handler;

/**
 * @brief  Define the system handler flag.
 */
extern struct tryrtos_thread_handle_type tryrtos_handler;

/**
 * @brief   The thread creation processing.
 * @handle:     the handle for thread
 * @name：      the name for thread
 * @priority:   the priority for thread
 * @para:       the parameter for thread entry
 * @entry:      the entry for thread
 * @stack_end:  the end of stack
 * @stack_len:  the number of stack
 * 
 * @note The larger the number, the lower the priority; 
 *       the smaller the number, the higher the priority.
*/
void tryrtos_thread_create(struct tryrtos_thread_type *handle, 
                           char *name, 
                           uint8_t priority, 
                           void *para, 
                           tryrtos_entry entry,
                           uint32_t *stack_end, 
                           uint32_t stack_len);

/**
 * @brief   The thread destruction processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_destroy(struct tryrtos_thread_type *handle);

/**
 * @brief   The thread init processing. 
 */
void tryrtos_thread_init(void);

/**
 * @brief   The thread init processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_switch(struct tryrtos_thread_type *handle);

/**
 * @brief   The tick interrupt handler. 
 */
void tryrtos_tick_handler(void);

/**
 * @brief   The Realize proactively giving up the CPU usage interface. 
 */
void tryrtos_thread_yield(void);

/**
 * @brief   The Realize actively calling delay to give up the running interface. 
 */
void tryrtos_thread_delay(uint32_t ms);

/**
 * @brief   The interrupt handler call back interface. 
 */
void tryrtos_interrupt_call_back(void);

#endif /* TRYRTOS_THREAD_H_ */
