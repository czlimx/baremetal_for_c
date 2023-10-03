#ifndef ARCH_CONTEXT_H_
#define ARCH_CONTEXT_H_

#include "arch_compiler.h"

/**
 * @brief  Start target thread context.
 * @ptr:   the context potnter
 */
void arch_context_first_start(uint32_t *ptr);

/**
 * @brief  Start target thread context.
 * @ptr:   the context potnter
 */
void arch_context_start(uint32_t *ptr);

/**
 * @brief  Init target thread context.
 * @ptr:   the target stack potnter
 * @para:  the thread parameter
 * @entry: the thread entry
 * 
 * @return the newest stack pointer
 */
uint32_t *arch_context_init(uint32_t *ptr, void *para, void *entry);

/**
 * @brief  Switch target thread context.
 * @old:   the old context potnter
 * @new:   the new context potnter
 */
void arch_context_switch(uint32_t *old, uint32_t *new);

#endif /* ARCH_CONTEXT_H_ */
