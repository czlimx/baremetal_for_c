#ifndef TRYRTOS_TYPES_H_
#define TRYRTOS_TYPES_H_

#include "arch_compiler.h"
#include "libc_list.h"

/**
 * @brief Define thread entry function type.
 */
typedef void (*tryrtos_entry)(void *);

/**
 * @brief Define thread state during task running.
 */
enum tryrtos_state_type {
    TRYRTOS_THREAD_UNINIT = 0,
    TRYRTOS_THREAD_READY,
    TRYRTOS_THREAD_PENDING,
    TRYRTOS_THREAD_RUNNING,
    TRYRTOS_THREAD_DELAY,
    TRYRTOS_THREAD_DESTROY
};

/**
 * @brief Define a collection of thread members.
 */
struct tryrtos_thread_type {
    /* the configure attribute */
    void *para;                             /** @brief the parameter for entry */
    char name[256];                         /** @brief the name for thread */
    uint8_t priority;                       /** @brief the priority for thread */
    tryrtos_entry entry;                    /** @brief the entry for thread */

    /* the schedule attribute */
    uint64_t forgo_tick;                    /** @brief the forgo tick count for same priority scheduling*/
    uint64_t delay_tick;                    /** @brief the delay tick count */
    uint64_t running_tick;                  /** @brief the runing tick count */
    uint8_t  temporary_priority;            /** @brief the temporary priority to resolving priority inversion */
    enum tryrtos_state_type state;          /** @brief the current state for thread */
    struct libc_list_type node;             /** @brief the list node for thread */

    /* the stack attribute */
    uint32_t *stack_top;                    /** @brief the top pointer of stack */
    uint32_t *stack_end;                    /** @brief the end pointer of stack */
    uint32_t  stack_len;                    /** @brief the number of stack */
    uint32_t *stack_ptr;                    /** @brief the pointer for init context after */
};

#endif /* TRYRTOS_TYPES_H_ */
