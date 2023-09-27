#ifndef SDRV_DTIMER_H_
#define SDRV_DTIMER_H_

#include "arch_compiler.h"

#define DTIMER2_BASE            0x48040000

#define DMTIMER_TIDR 			0x00U 			/**< Identification Register Section */
#define DMTIMER_TIOCP_CFG 		0x10U 			/**< Timer OCP Configuration Register Section */
#define DMTIMER_IRQ_EOI 		0x20U 			/**< Timer IRQ End-of-Interrupt Register Section */
#define DMTIMER_IRQSTATUS_RAW 	0x24U 			/**< Timer Status Raw Register Section */
#define DMTIMER_IRQSTATUS 		0x28U 			/**< Timer Status Register Section */
#define DMTIMER_IRQENABLE_SET 	0x2CU 			/**< Timer Interrupt Enable Set Register Section */
#define DMTIMER_IRQENABLE_CLR 	0x30U 			/**< Timer Interrupt Enable Clear Register Section */
#define DMTIMER_IRQWAKEEN 		0x34U 			/**< Timer IRQ Wakeup Enable Register Section */
#define DMTIMER_TCLR 			0x38U 			/**< Timer Control Register Section */
#define DMTIMER_TCRR 			0x3CU 			/**< Timer Counter Register Section */
#define DMTIMER_TLDR 			0x40U 			/**< Timer Load Register Section */
#define DMTIMER_TTGR 			0x44U 			/**< Timer Trigger Register Section */
#define DMTIMER_TWPS 			0x48U 			/**< Timer Write Posting Bits Register Section */
#define DMTIMER_TMAR 			0x4CU 			/**< Timer Match Register Section */
#define DMTIMER_TCAR1 			0x50U 			/**< Timer Capture Register Section */
#define DMTIMER_TSICR 			0x54U 			/**< Timer Synchronous Interface Control Register Section */
#define DMTIMER_TCAR2 			0x58U 			/**< Timer Capture Register Section */

/**
 * @brief Describe timer pend status bit information
 */
enum sdrv_dtimer_pend_status {
    TIMER_W_PEND_TCLR = 0,
    TIMER_W_PEND_TCRR,
    TIMER_W_PEND_TLDR,
    TIMER_W_PEND_TTGR,
    TIMER_W_PEND_TMAP
};

/**
 * @brief Describe timer pend status bit information
 */
enum sdrv_dtimer_trigger_mode {
    TIMER_TRIGGER_RELOAD = 0,
    TIMER_TRIGGER_COMPARE,
    TIMER_TRIGGER_ALL
};

/**
 * @brief Describe timer pend status bit information
 */
enum sdrv_dtimer_interrupt {
    TIMER_INTERRUPT_MAT = 0,
    TIMER_INTERRUPT_OVF,
    TIMER_INTERRUPT_TCAR
};

void sdrv_dtimer_soft_reset(const uint32_t base);

void sdrv_dtimer_enable(const uint32_t base);

void sdrv_dtimer_disable(const uint32_t base);

void sdrv_dtimer_mode_configure(const uint32_t base, const uint32_t mode);

void sdrv_dtimer_prescaler_clk_enable(const uint32_t base, const uint32_t ptv);

void sdrv_dtimer_prescaler_clk_disable(const uint32_t base);

void sdrv_dtimer_counter_set(const uint32_t base, const uint32_t counter);

void sdrv_dtimer_reload_set(const uint32_t base, const uint32_t reload);

void sdrv_dtimer_compare_set(const uint32_t base, const uint32_t compare);

void sdrv_dtimer_int_status_clear(const uint32_t base, const enum sdrv_dtimer_interrupt bit);

void sdrv_dtimer_int_enable(const uint32_t base, const enum sdrv_dtimer_interrupt bit);

void sdrv_dtimer_int_disable(const uint32_t base, const enum sdrv_dtimer_interrupt bit);

#endif /* SDRV_DTIMER_H_ */
