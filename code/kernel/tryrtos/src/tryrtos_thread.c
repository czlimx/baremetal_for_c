#include "tryrtos_thread.h"
#include "tryrtos_types.h"
#include "tryrtos_tick.h"

/**
 * @brief  Define the current thread handler pointer.
 */
struct tryrtos_thread_type *tryrtos_cur_handler = NULL;

/**
 * @brief  Define the system reschedule flag.
 */
volatile bool tryrtos_need_reschedule = false;

/**
 * @brief Define all priority hash map tables.
 */
static struct libc_list_type tryrtos_ready_array[TRYRTOS_MAX_SCHEDULER_PRIORITY];
/**
 * @brief Define delay list head.
 */
static struct libc_list_type tryrtos_delay_head;

/**
 * @brief Register the thread into the ready hash table.
 * 
 * @node: the list node
 * @priority: the index for hash map table
 */
static void tryrtos_thread_register(struct libc_list_type *node, uint8_t priority)
{
    if (priority >= TRYRTOS_MAX_SCHEDULER_PRIORITY)
        return;

    /* add the target priority to ready list array after for head */
    libc_list_add(node, &tryrtos_ready_array[priority]);
}

/**
 * @brief Unregister the thread into the ready hash table.
 * 
 * @node: the list node
 * @priority: the index for hash map table
 */
static void tryrtos_thread_unregister(struct libc_list_type *node, uint8_t priority)
{
    if (priority >= TRYRTOS_MAX_SCHEDULER_PRIORITY)
        return;

    /* remove the target priority to ready list array after for head */
    libc_list_del(node);
}

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
                           uint32_t stack_len)
{
    if (NULL == handle)
        return;

    if (NULL == name)
        return;

    if (NULL == stack_end)
        return;

    if (0U == stack_len)
        return;

    /* init thread configure infomation */
    memcpy(handle->name, name, strlen(name));
    handle->para = para;
    handle->priority = priority;
    handle->entry = entry;

    /* init thread satck infomation */
    handle->stack_end = stack_end;
    handle->stack_len = stack_len;
    handle->stack_top = stack_end + stack_len;
    
    /* init thread scheduler infomation */
    handle->temporary_priority = priority;
    tryrtos_thread_register(&handle->node, handle->priority);

    /* init thread current tick infomation */
    handle->delay_tick = 0U;
    handle->running_tick = 0U;

    /* init thread context infomation */
    handle->stack_ptr = tryrtos_context_init(handle->stack_top, 
                                             handle->para, 
                                             handle->entry);

    /* update the state */
    handle->state = TRYRTOS_THREAD_READY;
}

/**
 * @brief   The thread destruction processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_destroy(struct tryrtos_thread_type *handle)
{
    if (NULL == handle)
        return;
    
    /* update the state */
    handle->state = TRYRTOS_THREAD_DESTROY;

    /* remove from target list */
    tryrtos_thread_unregister(&handle->node, handle->priority);
}

/**
 * @brief   The thread init processing. 
 */
void tryrtos_thread_init(void)
{
    /* init head for all ready list */
    for (uint32_t i = 0; i < TRYRTOS_MAX_SCHEDULER_PRIORITY; i++)
        libc_list_init(&tryrtos_ready_array[i]);

    /* init delay list */
    libc_list_init(&tryrtos_delay_head);

    /* init the reschedule flag */
    tryrtos_need_reschedule = false;
}

/**
 * @brief   The thread init processing. 
 * @handle: the handle for thread
 * @ms:     the delay ms value
 */
void tryrtos_thread_delay(struct tryrtos_thread_type *handle, uint32_t ms)
{
    if (NULL == handle)
        return;

    if (0U == ms)
        return;

    /* init thread delay tick infomation */
    handle->delay_tick = ms;

    /* update the state */
    handle->state = TRYRTOS_THREAD_DELAY;

    /* move the node to the delay list*/
    libc_list_move(&handle->node, &tryrtos_delay_head);
}

/**
 * @brief   The thread init processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_sort(struct tryrtos_thread_type *handle)
{
    (void)handle;
}

/**
 * @brief   The thread init processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_lookup(struct tryrtos_thread_type *handle)
{
    (void)handle;
}

/**
 * @brief   The thread init processing. 
 * @handle: the handle for thread
 */
void tryrtos_thread_switch(struct tryrtos_thread_type *handle)
{
    struct tryrtos_thread_type *temp_handler = NULL;

    if (handle == NULL)
        return;

    /* clear the forgo tick */
    handle->forgo_tick = TRYRTOS_MAX_TICK_SCHEDULE;

    /* init the reschedule flag */
    tryrtos_need_reschedule = false;

    if (handle == tryrtos_cur_handler)
        return;

    if ((TRYRTOS_THREAD_READY != handle->state) &&
        (TRYRTOS_THREAD_PENDING != handle->state))
        return;

    if (tryrtos_cur_handler != NULL)
        tryrtos_cur_handler->state = TRYRTOS_THREAD_PENDING;

    /* switch the thread context */
    if (TRYRTOS_THREAD_READY == handle->state)
    {
        /* update the state */
        tryrtos_cur_handler = handle;
        handle->state = TRYRTOS_THREAD_RUNNING;
        tryrtos_context_start(handle->stack_ptr);
    }
    else
    {
        /* update the state */
        temp_handler = tryrtos_cur_handler;
        tryrtos_cur_handler = handle;
        handle->state = TRYRTOS_THREAD_RUNNING;
        tryrtos_context_switch(temp_handler->stack_ptr, handle->stack_ptr);
    }
}

/**
 * @brief   The interrupt handler call back interface. 
 */
void tryrtos_interrupt_call_back(void)
{
    if (tryrtos_need_reschedule == false)
        return;

    /* tryrtos_thread_lookup */
}

/**
 * @brief   The tick interrupt handler. 
 */
void tryrtos_tick_handler(void)
{
    struct libc_list_type *node = tryrtos_delay_head.next;
    struct tryrtos_thread_type *handle = NULL;

    /* update the system tick */
    tryrtos_tick_add();

    /* update the current thread tick */
    tryrtos_cur_handler->running_tick++;

    /* update the current thread forgo tick */
    if (tryrtos_cur_handler->forgo_tick > 0)
        tryrtos_cur_handler->forgo_tick--;
    if (tryrtos_cur_handler->forgo_tick == 0U)
        tryrtos_need_reschedule = true;

    /* update all delay list tick */
    if (true == libc_list_is_empty(&tryrtos_delay_head))
        return;
    
    /* Traverse all delay linked lists and update thread status */
    do
    {
        handle = libc_list_entry(node, struct tryrtos_thread_type, node);

        /* update the thread delay tick value */
        if (handle->delay_tick > 0)
            handle->delay_tick--;

        if (handle->delay_tick == 0U)
        {
            /* update the thread state */
            handle->state = TRYRTOS_THREAD_PENDING;

            /* move the thread to ready list */
            libc_list_move(&handle->node, &tryrtos_ready_array[handle->priority]);
        }

        node = node->next;
        
    } while (false == libc_list_is_head(node, &tryrtos_delay_head));
}
