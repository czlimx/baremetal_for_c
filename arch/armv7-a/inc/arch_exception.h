#ifndef ARCH_EXCEPTION_H_
#define ARCH_EXCEPTION_H_

/**
 * @brief  Prefetch instruction abort exception.
 */
void do_prefetch_abort(void);

/**
 * @brief  Prefetch data abort exception.
 */
void do_data_abort(void);

/**
 * @brief  interrupt exception.
 */
void do_irq(void);

#endif /* ARCH_EXCEPTION_H_ */
