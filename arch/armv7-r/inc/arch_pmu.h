#ifndef ARCH_PMU_H_
#define ARCH_PMU_H_

#include "arch_compiler.h"

/**
 * @brief  The enables User mode access to the Performance Monitors.
 */
void arch_pmu_user_access_enable(void);

/**
 * @brief  The disables User mode access to the Performance Monitors.
 */
void arch_pmu_user_access_disable(void);

/**
 * @brief  The enable the Cycle Count.
 */    
void arch_pmu_cycle_counter_enable(void);

/**
 * @brief  The disable the Cycle Count.
 */  
void arch_pmu_cycle_counter_disable(void);

/**
 * @brief  The init the Cycle Count.
 */  
void arch_pmu_cycle_counter_init(void);

/**
 * @brief  The enable the Cycle Count IRQ.
 */
void arch_pmu_cycle_counter_enable_irq(void);

/**
 * @brief  The disable the Cycle Count IRQ.
 */
void arch_pmu_cycle_counter_disable_irq(void);

/**
 * @brief  The set the Cycle Counter.
 * @param  count - the counter value
 */
void arch_pmu_cycle_counter_set_counter(uint32_t count);

/**
 * @brief  The set the Cycle Counter.
 * @param  count - the counter value
 */
uint32_t arch_pmu_cycle_counter_get_counter(void);

/**
 * @brief  The enable the Event Counter.
 * @param  id - the counter id
 */
void arch_pmu_event_counter_enable(uint32_t id);

/**
 * @brief  The disable the Event Counter.
 * @param  id - the counter id
 */
void arch_pmu_event_counter_disable(uint32_t id);

/**
 * @brief  The init the all Event Counter.
 */
void arch_pmu_event_counter_init(void);

/**
 * @brief  The software increment the Event Counter.
 * @param  id - the counter id
 */
void arch_pmu_event_counter_increment(uint32_t id);

/**
 * @brief  The select counter and event for the Event Counter.
 * @param  id - the counter id
 * @param  event - the event id
 */
void arch_pmu_event_counter_select(uint32_t id, uint32_t event);

/**
 * @brief  The read and clear counter for the Event Counter.
 * @param  id - the counter id
 * @return the event counter value
 */
uint32_t arch_pmu_event_counter_read(uint32_t id);

/**
 * @brief  The enable Event Counter IRQ.
 * @param  r0 - the counter id
 */
void arch_pmu_event_counter_enable_irq(void);

/**
 * @brief  The disable Event Counter IRQ.
 * @param  r0 - the counter id
 */
void arch_pmu_event_counter_disable_irq(void);

/**
 * @brief  The IRQ handler for the Performance Monitors.
 */
void arch_pmu_irq_handler(void *para);

/**
 * @brief  The call back function for the Performance Monitors interrupt.
 */
void arch_pmu_irq_call_back(void);

#endif /* ARCH_PMU_H_ */
