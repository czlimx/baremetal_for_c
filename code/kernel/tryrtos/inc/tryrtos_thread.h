#ifndef TRYRTOS_THREAD_H_
#define TRYRTOS_THREAD_H_

#include "tryrtos_config.h"
#include "tryrtos_types.h"

/**
 * @brief  Define the current thread handler pointer.
 */
extern struct tryrtos_thread_type *tryrtos_cur_handler;

/**
 * @brief  Define the system reschedule flag.
 */
extern volatile bool tryrtos_need_reschedule;

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
 * @ms:     the delay ms value
 */
void tryrtos_thread_delay(struct tryrtos_thread_type *handle, uint32_t ms);

/**
 * @brief   The thread init processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_sort(struct tryrtos_thread_type *handle);

/**
 * @brief   The thread init processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_lookup(struct tryrtos_thread_type *handle);

/**
 * @brief   The thread init processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_switch(struct tryrtos_thread_type *handle);

/**
 * @brief   The interrupt handler call back interface. 
 */
void tryrtos_interrupt_call_back(void);

#endif /* TRYRTOS_THREAD_H_ */
