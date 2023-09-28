#ifndef DRV_AM335X_UART_H_
#define DRV_AM335X_UART_H_

#include "arch_compiler.h"

#define UART_0_BASE                             0x44E09000
#define UART_1_BASE                             0x48022000
#define UART_2_BASE                             0x48024000
#define UART_3_BASE                             0x481A6000
#define UART_4_BASE                             0x481A8000
#define UART_5_BASE                             0x481AA000

#define UART_OFFSET_THR                         0x0U
#define UART_OFFSET_RHR                         0x0U
#define UART_OFFSET_DLL                         0x0U
#define UART_OFFSET_IER_IRDA                    0x4U
#define UART_OFFSET_IER_CIR                     0x4U
#define UART_OFFSET_IER_UART                    0x4U
#define UART_OFFSET_DLH                         0x4U

#define UART_OFFSET_EFR                         0x8U
#define UART_EFR_AUTOCTSEN                      7U
#define UART_EFR_AUTORTSEN                      6U
#define UART_EFR_SPECIALCHARDETECT              5U
#define UART_EFR_ENHANCEDEN                     4U
#define UART_EFR_SWFLOWCONTROL                  3U
#define UART_EFR_SWFLOWCONTROL_MASK             0xFU


#define UART_OFFSET_IIR_UART                    0x8U
#define UART_OFFSET_IIR_CIR                     0x8U

#define UART_OFFSET_FCR                         0x8U
#define UART_FCR_RX_FIFO_TRIG                   6U
#define UART_FCR_RX_FIFO_TRIG_MASK              0x3U
#define UART_FCR_TX_FIFO_TRIG                   4U
#define UART_FCR_TX_FIFO_TRIG_MASK              0x3U
#define UART_FCR_DMA_MODE                       3U
#define UART_FCR_TX_FIFO_CLEAR                  2U
#define UART_FCR_RX_FIFO_CLEAR                  1U
#define UART_FCR_FIFO_EN                        0U

#define UART_OFFSET_IIR_IRDA                    0x8U

#define UART_OFFSET_LCR                         0xCU
#define UART_LCR_DIV_EN                         7U
#define UART_LCR_BREAK_EN                       6U
#define UART_LCR_PARITY_TYPE2                   5U
#define UART_LCR_PARITY_TYPE1                   4U
#define UART_LCR_PARITY_EN                      3U
#define UART_LCR_NB_STOP                        2U
#define UART_LCR_CHAR_LENGTH                    1U
#define UART_LCR_CHAR_LENGTH_MASK               0x3U

#define UART_OFFSET_MCR                         0x10U
#define UART_MCR_TCRTLR                         6U
#define UART_MCR_XONEN                          5U
#define UART_MCR_LOOPBACKEN                     4U
#define UART_MCR_CDSTSCH                        3U
#define UART_MCR_RISTSCH                        2U
#define UART_MCR_RTS                            1U
#define UART_MCR_DTR                            0U


#define UART_OFFSET_XON1_ADDR1                  0x10U
#define UART_OFFSET_XON2_ADDR2                  0x14U
#define UART_OFFSET_LSR_CIR                     0x14U
#define UART_OFFSET_LSR_IRDA                    0x14U
#define UART_OFFSET_LSR_UART                    0x14U
#define UART_LSR_UART_RXFIFOSTS                 7U
#define UART_LSR_UART_TXSRE                     6U
#define UART_LSR_UART_TXFIFOE                   5U
#define UART_LSR_UART_RXBI                      4U
#define UART_LSR_UART_RXFE                      3U
#define UART_LSR_UART_RXPE                      2U
#define UART_LSR_UART_RXOE                      1U
#define UART_LSR_UART_RXFIFOE                   0U

#define UART_OFFSET_TCR                         0x18U
#define UART_OFFSET_MSR                         0x18U
#define UART_OFFSET_XOFF1                       0x18U
#define UART_OFFSET_SPR                         0x1CU
#define UART_OFFSET_TLR                         0x1CU
#define UART_OFFSET_XOFF2                       0x1CU
#define UART_OFFSET_MDR1                        0x20U
#define UART_OFFSET_MDR2                        0x24U
#define UART_OFFSET_TXFLL                       0x28U
#define UART_OFFSET_SFLSR                       0x28U
#define UART_OFFSET_RESUME                      0x2CU
#define UART_OFFSET_TXFLH                       0x2CU
#define UART_OFFSET_RXFLL                       0x30U
#define UART_OFFSET_SFREGL                      0x30U
#define UART_OFFSET_SFREGH                      0x34U
#define UART_OFFSET_RXFLH                       0x34U
#define UART_OFFSET_BLR                         0x38U
#define UART_OFFSET_UASR                        0x38U
#define UART_OFFSET_ACREG                       0x3CU
#define UART_OFFSET_SCR                         0x40U
#define UART_OFFSET_SSR                         0x44U
#define UART_OFFSET_EBLR                        0x48U
#define UART_OFFSET_MVR                         0x50U

#define UART_OFFSET_SYSC                        0x54U
#define UART_SYSC_AUTOIDLE                      0U
#define UART_SYSC_SOFTRESET                     1U
#define UART_SYSC_ENAWAKEUP                     2U
#define UART_SYSC_IDLEMODE                      3U
#define UART_SYSC_IDLEMODE_MASK                 0x3U

#define UART_OFFSET_SYSS                        0x58U
#define UART_SYSS_RESETDONE                     0U

#define UART_OFFSET_WER                         0x5CU
#define UART_OFFSET_CFPS                        0x60U
#define UART_OFFSET_RXFIFO_LVL                  0x64U
#define UART_OFFSET_TXFIFO_LVL                  0x68U
#define UART_OFFSET_IER2                        0x6CU
#define UART_OFFSET_ISR2                        0x70U
#define UART_OFFSET_FREQ_SEL                    0x74U
#define UART_OFFSET_MDR3                        0x80U
#define UART_OFFSET_TX_DMA_THRESHOLD            0x84U

typedef enum {
    UART_FIFO_LEVEL_8 = 0U,
    UART_FIFO_LEVEL_16,
    UART_FIFO_LEVEL_24,
    UART_FIFO_LEVEL_36
} sdrv_uart_fifo_level_type;

/**
 * @brief Description wordlength information
 */
typedef enum {
    UART_WORDLENGTH_5_BITS = 0U,                /**< 5bits for cycle wordlength */
    UART_WORDLENGTH_6_BITS,                     /**< 6bits for cycle wordlength */
    UART_WORDLENGTH_7_BITS,                     /**< 7bits for cycle wordlength */
    UART_WORDLENGTH_8_BITS                      /**< 8bits for cycle wordlength */
} sdrv_uart_wordlength_type;

/**
 * @brief Description stopbits information
 */
typedef enum {
    UART_STOPBITS_ONE_BITS = 0U,                /**< 1.0bits for cycle stopbits */
    UART_STOPBITS_ONEHALF_BITS,                 /**< 1.5bits for cycle stopbits */
    UART_STOPBITS_TWO_BITS                      /**< 2.0bits for cycle stopbits */
} sdrv_uart_stopbits_type;

/**
 * @brief Description parity information
 */
typedef enum {
    UART_PARITY_NO = 0U,                        /**< no   parity */
    UART_PARITY_ODD,                            /**< odd  parity */
    UART_PARITY_EVEN                            /**< even parity */
} sdrv_uart_parity_type;

/**
 * @brief Description configure information for uart
 */
typedef struct {
    bool dma_enable;                            /**< uart module dma enable */
    bool fifo_enable;                           /**< uart module fifo enable */
    uint32_t baudrate;                          /**< Transmission baud rate */
    sdrv_uart_fifo_level_type rx_fifo_level;     /**< tx/rx fifo Water level */
    sdrv_uart_fifo_level_type tx_fifo_level;     /**< tx/rx fifo Water level */
    sdrv_uart_parity_type parity;                /**< parity identification */
    sdrv_uart_stopbits_type stopbits;            /**< stopbits identification */
    sdrv_uart_wordlength_type wordlength;        /**< wordlength identification */
} sdrv_uart_config_type;

/**
 * @brief init uart hardware register according to the parameters passed in
 * @param  base_address     uart module base address
 * @param  config           uart configuration pointer
 */
void sdrv_uart_init(const uint32_t base_address, const sdrv_uart_config_type *config);

/**
 * @brief send character data through uart
 * @param  base_address     uart module base address
 * @param  c                the character to be sent
 */
void sdrv_uart_send(const uint32_t base_address, const int data);

#endif /* DRV_AM335X_UART_H_ */