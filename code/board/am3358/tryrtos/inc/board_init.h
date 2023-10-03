#ifndef EXAMPLE_EARLAY_INIT_H_
#define EXAMPLE_EARLAY_INIT_H_

#include "arch_compiler.h"

/**
 * @brief  The early init for board.
 */
void board_early_init(void);

/**
 * @brief  The early init for timer.
 */
void sdrv_timer_init(uint32_t base);

/**
 * @brief  The interrupt call back for timer.
 */
void sdrv_timer_intc_handler(void* para);

/**
 * @brief  The init for board.
 */
void board_init(void);

/**
 * @brief  The udelay for pmu.
 */
void udelay(uint32_t us);

/**
 * @brief  The call back for interrupt.
 */
void board_interrupt_call_back(void);

#endif /* EXAMPLE_EARLAY_INIT_H_ */