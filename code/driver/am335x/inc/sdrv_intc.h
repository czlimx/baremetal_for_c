#ifndef DRIVER_INTC_H_
#define DRIVER_INTC_H_

#define MAX_INTC_NUMBER             128

#define INTCPS_BASE                 0x48200000
#define INTC_REVISION               0x00
#define INTC_SYSCONFIG              0x10
#define INTC_SYSSTATUS              0x14
#define INTC_SIR_IRQ                0x40
#define INTC_SIR_FIQ                0x44
#define INTC_CONTROL                0x48
#define INTC_PROTECTION             0x4C
#define INTC_IDLE                   0x50
#define INTC_IRQ_PRIORITY           0x60
#define INTC_FIQ_PRIORITY           0x64
#define INTC_THRESHOLD              0x68
#define INTC_ITR0                   0x80
#define INTC_MIR0                   0x84
#define INTC_MIR_CLEAR0             0x88
#define INTC_MIR_SET0               0x8C
#define INTC_ISR_SET0               0x90
#define INTC_ISR_CLEAR0             0x94
#define INTC_PENDING_IRQ0           0x98
#define INTC_PENDING_FIQ0           0x9C
#define INTC_ILR0                   0x100

#define INTC_ITR(n)                 (INTC_ITR0 +        (n * 0x20))
#define INTC_MIR(n)                 (INTC_MIR0 +        (n * 0x20))
#define INTC_MIR_CLEAR(n)           (INTC_MIR_CLEAR0 +  (n * 0x20))
#define INTC_MIR_SET(n)             (INTC_MIR_SET0 +    (n * 0x20))
#define INTC_ISR_SET(n)             (INTC_ISR_SET0 +    (n * 0x20))
#define INTC_ISR_CLEAR(n)           (INTC_ISR_CLEAR0 +  (n * 0x20))
#define INTC_PENDING_IRQ(n)         (INTC_PENDING_IRQ0 +(n * 0x20))
#define INTC_PENDING_FIQ(n)         (INTC_PENDING_FIQ0 +(n * 0x20))
#define INTC_ILR(n)                 (INTC_ILR0 +        (n * 0x04))

#define AM335X_INT_EMUINT             0	        /* Emulation interrupt (EMUICINTR) */
#define AM335X_INT_COMMTX             1	        /* CortexA8 COMMTX */
#define AM335X_INT_COMMRX             2	        /* CortexA8 COMMRX */
#define AM335X_INT_BENCH              3	        /* CortexA8 NPMUIRQ */
#define AM335X_INT_ELM_IRQ            4	        /* Sinterrupt (Error location process completion) */
#define AM335X_INT_NMI                7	        /* nmi_int */
#define AM335X_INT_L3DEBUG            9	        /* l3_FlagMux_top_FlagOut1 */
#define AM335X_INT_L3APPINT           10	    /* l3_FlagMux_top_FlagOut0  */
#define AM335X_INT_PRCMINT            11	    /* irq_mpu */
#define AM335X_INT_EDMACOMPINT        12	    /* tpcc_int_pend_po0 */
#define AM335X_INT_EDMAMPERR          13	    /* tpcc_mpint_pend_po */
#define AM335X_INT_EDMAERRINT         14	    /* tpcc_errint_pend_po */
#define AM335X_INT_ADC_TSC_GENINT     16	    /* gen_intr_pend */
#define AM335X_INT_USBSSINT           17	    /* usbss_intr_pend */
#define AM335X_INT_USB0               18	    /* usb0_intr_pend */
#define AM335X_INT_USB1               19	    /* usb1_intr_pend */
#define AM335X_INT_PRUSS1_EVTOUT0     20	    /* pr1_host_intr0_intr_pend */
#define AM335X_INT_PRUSS1_EVTOUT1     21	    /* pr1_host_intr1_intr_pend */
#define AM335X_INT_PRUSS1_EVTOUT2     22	    /* pr1_host_intr2_intr_pend */
#define AM335X_INT_PRUSS1_EVTOUT3     23	    /* pr1_host_intr3_intr_pend */
#define AM335X_INT_PRUSS1_EVTOUT4     24	    /* pr1_host_intr4_intr_pend */
#define AM335X_INT_PRUSS1_EVTOUT5     25	    /* pr1_host_intr5_intr_pend */
#define AM335X_INT_PRUSS1_EVTOUT6     26	    /* pr1_host_intr6_intr_pend */
#define AM335X_INT_PRUSS1_EVTOUT7     27	    /* pr1_host_intr7_intr_pend */
#define AM335X_INT_MMCSD1INT          28	    /* MMCSD1  SINTERRUPTN */
#define AM335X_INT_MMCSD2INT          29	    /* MMCSD2  SINTERRUPT */
#define AM335X_INT_I2C2INT            30	    /* I2C2  POINTRPEND */
#define AM335X_INT_eCAP0INT           31	    /* ecap_intr_intr_pend */
#define AM335X_INT_GPIOINT2A          32	    /* GPIO 2  POINTRPEND1 */
#define AM335X_INT_GPIOINT2B          33	    /* GPIO 2  POINTRPEND2 */
#define AM335X_INT_USBWAKEUP          34	    /* USBSS  slv0p_Swakeup */
#define AM335X_INT_LCDCINT            36	    /* LCDC  lcd_irq */
#define AM335X_INT_GFXINT             37	    /* SGX530  THALIAIRQ */
#define AM335X_INT_ePWM2INT           39	    /* (PWM Subsystem)  epwm_intr_intr_pend */
#define AM335X_INT_3PGSWRXTHR0        40	    /* (Ethernet)  c0_rx_thresh_pend (RX_THRESH_PULSE) */
#define AM335X_INT_3PGSWRXINT0        41	    /* CPSW (Ethernet)  c0_rx_pend */
#define AM335X_INT_3PGSWTXINT0        42	    /* CPSW (Ethernet)  c0_tx_pend */
#define AM335X_INT_3PGSWMISC0         43	    /* CPSW (Ethernet)  c0_misc_pend */
#define AM335X_INT_UART3INT           44	    /* UART3  niq */
#define AM335X_INT_UART4INT           45	    /* UART4  niq */
#define AM335X_INT_UART5INT           46	    /* UART5  niq */
#define AM335X_INT_eCAP1INT           47	    /* (PWM Subsystem)  ecap_intr_intr_pend */
#define AM335X_INT_DCAN0_INT0         52	    /* DCAN0  dcan_intr0_intr_pend */
#define AM335X_INT_DCAN0_INT1         53	    /* DCAN0  dcan_intr1_intr_pend */
#define AM335X_INT_DCAN0_PARITY       54	    /* DCAN0  dcan_uerr_intr_pend */
#define AM335X_INT_DCAN1_INT0         55	    /* DCAN1  dcan_intr0_intr_pend */
#define AM335X_INT_DCAN1_INT1         56	    /* DCAN1  dcan_intr1_intr_pend */
#define AM335X_INT_DCAN1_PARITY       57	    /* DCAN1  dcan_uerr_intr_pend */
#define AM335X_INT_ePWM0_TZINT        58	    /* eHRPWM0 TZ interrupt (PWM  epwm_tz_intr_pend Subsystem) */
#define AM335X_INT_ePWM1_TZINT        59	    /* eHRPWM1 TZ interrupt (PWM  epwm_tz_intr_pend Subsystem) */
#define AM335X_INT_ePWM2_TZINT        60	    /* eHRPWM2 TZ interrupt (PWM  epwm_tz_intr_pend Subsystem) */
#define AM335X_INT_eCAP2INT           61	    /* eCAP2 (PWM Subsystem)  ecap_intr_intr_pend */
#define AM335X_INT_GPIOINT3A          62	    /* GPIO 3  POINTRPEND1 */
#define AM335X_INT_GPIOINT3B          63	    /* GPIO 3  POINTRPEND2 */
#define AM335X_INT_MMCSD0INT          64	    /* MMCSD0  SINTERRUPTN */
#define AM335X_INT_SPI0INT            65	    /* McSPI0  SINTERRUPTN */
#define AM335X_INT_TINT0              66	    /* Timer0  POINTR_PEND */
#define AM335X_INT_TINT1_1MS          67	    /* DMTIMER_1ms  POINTR_PEND */
#define AM335X_INT_TINT2              68	    /* DMTIMER2  POINTR_PEND */
#define AM335X_INT_TINT3              69	    /* DMTIMER3  POINTR_PEND */
#define AM335X_INT_I2C0INT            70	    /* I2C0  POINTRPEND */
#define AM335X_INT_I2C1INT            71	    /* I2C1  POINTRPEND */
#define AM335X_INT_UART0INT           72	    /* UART0  niq */
#define AM335X_INT_UART1INT           73	    /* UART1  niq */
#define AM335X_INT_UART2INT           74	    /* UART2  niq */
#define AM335X_INT_RTCINT             75	    /* RTC  timer_intr_pend */
#define AM335X_INT_RTCALARMINT        76	    /* RTC  alarm_intr_pend */
#define AM335X_INT_MBINT0             77	    /* Mailbox0 (mail_u0_irq)  initiator_sinterrupt_q_n */
#define AM335X_INT_M3_TXEV            78	    /* Wake M3 Subsystem  TXEV */
#define AM335X_INT_eQEP0INT           79	    /* eQEP0 (PWM Subsystem)  eqep_intr_intr_pend */
#define AM335X_INT_MCATXINT0          80	    /* McASP0  mcasp_x_intr_pend */
#define AM335X_INT_MCARXINT0          81	    /* McASP0  mcasp_r_intr_pend */
#define AM335X_INT_MCATXINT1          82	    /* McASP1  mcasp_x_intr_pend */
#define AM335X_INT_MCARXINT1          83	    /* McASP1  mcasp_r_intr_pend */
#define AM335X_INT_ePWM0INT           86	    /* (PWM Subsystem)  epwm_intr_intr_pend */
#define AM335X_INT_ePWM1INT           87	    /* (PWM Subsystem)  epwm_intr_intr_pend */
#define AM335X_INT_eQEP1INT           88	    /* (PWM Subsystem)  eqep_intr_intr_pend */
#define AM335X_INT_eQEP2INT           89	    /* (PWM Subsystem)  eqep_intr_intr_pend */
#define AM335X_INT_DMA_INTR_PIN2      90	    /* External DMA/Interrupt Pin2  */
#define AM335X_INT_WDT1INT            91	    /* (Public Watchdog) WDTIMER1 PO_INT_PEND */
#define AM335X_INT_TINT4              92	    /* DMTIMER4  POINTR_PEN */
#define AM335X_INT_TINT5              93	    /* DMTIMER5  POINTR_PEN */
#define AM335X_INT_TINT6              94	    /* DMTIMER6  POINTR_PEND */
#define AM335X_INT_TINT7              95	    /* DMTIMER7  POINTR_PEND */
#define AM335X_INT_GPIOINT0A          96	    /* GPIO 0  POINTRPEND1 */
#define AM335X_INT_GPIOINT0B          97	    /* GPIO 0  POINTRPEND2 */
#define AM335X_INT_GPIOINT1A          98	    /* GPIO 1  POINTRPEND1 */
#define AM335X_INT_GPIOINT1B          99	    /* GPIO 1  POINTRPEND2 */
#define AM335X_INT_GPMCINT            100	    /* GPMC  gpmc_sinterrupt */
#define AM335X_INT_DDRERR0            101	    /* EMIF  sys_err_intr_pend */
#define AM335X_INT_TCERRINT0          112	    /* TPTC0  tptc_erint_pend_po */
#define AM335X_INT_TCERRINT1          113	    /* TPTC1  tptc_erint_pend_po */
#define AM335X_INT_TCERRINT2          114	    /* TPTC2  tptc_erint_pend_po */
#define AM335X_INT_ADC_TSC_PENINT     115	    /* ADC_TSC  pen_intr_pend */
#define AM335X_INT_SMRFLX_Sabertooth  120	    /* Smart Reflex 0  intrpen */
#define AM335X_INT_SMRFLX_Core        121	    /* Smart Reflex 1  intrpend */
#define AM335X_INT_DMA_INTR_PIN0      123       /* pi_x_dma_event_intr0 (xdma_event_intr0) */
#define AM335X_INT_DMA_INTR_PIN1      124	    /* pi_x_dma_event_intr1 (xdma_event_intr1) */
#define AM335X_INT_SPI1INT            125	    /* McSPI1  SINTERRUPTN */

#define ARCH_MPU_IRQ_NUMBER           AM335X_INT_BENCH

#ifndef ASSEMBLY

#include "arch_compiler.h"

/**
 * @brief init for IRQ.
 */
void sdrv_irq_init(void);

/**
 * @brief config priority for IRQ.
 */
void sdrv_irq_set_priority(uint32_t irq, uint32_t priority);

/**
 * @brief enable IRQ number.
 */
void sdrv_irq_enable(uint32_t irq);

/**
 * @brief disable IRQ number.
 */
void sdrv_irq_disable(uint32_t irq);

/**
 * @brief clear IRQ status.
 */
void sdrv_irq_clear_status(uint32_t irq);

/**
 * @brief trigger IRQ number.
 */
void sdrv_irq_trigger(uint32_t irq);

/**
 * @brief trigger IRQ number.
 */
void sdrv_irq_handler(void);

#endif /* ASSEMBLY */

#endif /* DRIVER_INTC_H_ */
