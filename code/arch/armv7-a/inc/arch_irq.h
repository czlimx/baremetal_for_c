#ifndef ARCH_IRQ_H_
#define ARCH_IRQ_H_

#include "arch_compiler.h"

#define ARCH_IRQ_MAX_PRIORITY           16

/**
 * @brief Define interrupt call back Type. 
 */
typedef void (*irq_handler_type)(void *para);

/**
 * @brief  Architecture-dependent interrupt handler.
 */
void arch_irq_handler(uint32_t irq);

/**
 * @brief  Architecture-dependent interrupt init.
 */
void arch_irq_init(void);

/**
 * @brief  Architecture-dependent interrupt register.
 */
void arch_irq_register(uint32_t irq, uint32_t priority, void *para, irq_handler_type handler);

/**
 * @brief  Architecture-dependent interrupt unregister.
 */
void arch_irq_unregister(uint32_t irq);

#endif /* ARCH_IRQ_H_ */