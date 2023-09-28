#include "sdrv_uart.h"

/**
 * @brief Description amm35x uart baudrate correspondence
 */
typedef struct {
    uint32_t rate;      /**< Baud Rate */
    uint32_t dlh;       /**< DLH */
    uint32_t dll;       /**< DLL */
} sdrv_uart_baudrate_type;

static const sdrv_uart_baudrate_type uart_baudrate_array[] = {
    {300,       0x27, 0x10},
    {600,       0x13, 0x88},
    {1200,      0x09, 0xC4},
    {2400,      0x04, 0xE2},
    {4800,      0x02, 0x71},
    {9600,      0x01, 0x38},
    {14400,     0x00, 0xD0},
    {19200,     0x00, 0x9C},
    {28800,     0x00, 0x68},
    {38400,     0x00, 0x4E},
    {57600,     0x00, 0x34},
    {115200,    0x00, 0x1A},
};

/**
 * @brief Find the appropriate baud rate for the DLH and DLL
 * @param  baudrate         uart baud rate
 * @param  dlh              dlh pointer
 * @param  dll              dll pointer
 * @return 0 success, other failure
 */
static bool sdrv_uart_find_rate(const uint32_t baudrate, uint32_t *dlh, uint32_t *dll)
{
    if ((NULL == dlh) || (NULL == dll))
        return false;

    uint32_t number = sizeof(uart_baudrate_array) / sizeof(uart_baudrate_array[0]);

    for (uint32_t i = 0; i < number; i++)
    {
        if (baudrate == uart_baudrate_array[i].rate)
        {
            *dlh = uart_baudrate_array[i].dlh;
            *dll = uart_baudrate_array[i].dll;
            return true;
        }
    }

    return false;
}

/**
 * @brief software reset uart
 * @param  base_address     uart module base address
 */
static void sdrv_uart_reset(const uint32_t base_address)
{
    uint32_t value = 0x0U, retval = 0x0U;

    /* Initiate a software reset */
    value = readl(base_address + UART_OFFSET_SYSC);
    value &= ~(0x1U << UART_SYSC_SOFTRESET);
    writel(value, base_address + UART_OFFSET_SYSC);

    /* Wait for the end of the reset operation */
    while (0x1U != ((retval >> UART_SYSS_RESETDONE) & 0x1U))
    {
        retval = readl(base_address + UART_OFFSET_SYSS);
    }
}

/**
 * @brief configure fifo and dma for uart
 * @param  base_address     uart module base address
 * @param  rx_fifo          RX FIFO Water level
 * @param  tx_fifo          TX FIFO Water level
 * @param  dma_enable       DMA enable
 * @param  fifo_enable      FIFO enable
 */
static void sdrv_uart_configure_fifo_and_dma(const uint32_t base_address, const sdrv_uart_config_type *config)
{
    uint32_t value = 0x0U, old_lcr = 0x0U, old_efr = 0x0U, old_mcr = 0x0U;

    /* 1. Switch to register configuration mode B to access the UARTi.UART_EFR register
     * a. Save the current UARTi.UART_LCR register value.
     * b. Set the UARTi.UART_LCR register value to 0x00BF.
     */
    old_lcr = readl(base_address + UART_OFFSET_LCR);
    writel(0x00BF, base_address + UART_OFFSET_LCR);

    /* 2. Enable register submode TCR_TLR to access the UARTi.UART_TLR register
     * a. Save the UARTi.UART_EFR[4] ENHANCED_EN value.
     * b. Set the UARTi.UART_EFR[4] ENHANCED_EN bit to 1.
     */
    value = readl(base_address + UART_OFFSET_EFR);
    old_efr = (value >> UART_EFR_ENHANCEDEN) & 0x1U;
    value |= (0x1U << UART_EFR_ENHANCEDEN);
    writel(value, base_address + UART_OFFSET_EFR);

    /* 3. Switch to register configuration mode A to access the UARTi.UART_MCR register
     * a. Set the UARTi.UART_LCR register value to 0x0080.
     */
    writel(0x0080, base_address + UART_OFFSET_LCR);

    /* 4. Enable register submode TCR_TLR to access the UARTi.UART_TLR register
     * a. Save the UARTi.UART_MCR[6] TCR_TLR value.
     * b. Set the UARTi.UART_MCR[6] TCR_TLR bit to 1.
     */
    value = readl(base_address + UART_OFFSET_MCR);
    old_mcr = (value >> UART_MCR_TCRTLR) & 0x1U;
    value |= (0x1U << UART_MCR_TCRTLR);
    writel(value, base_address + UART_OFFSET_MCR);

    /* 5. Enable the FIFO; load the new FIFO triggers and the new DMA mode */
    value = (0x1U << UART_FCR_TX_FIFO_CLEAR) | (0x1U << UART_FCR_RX_FIFO_CLEAR);
    if (true == config->fifo_enable)
        value |= (0x1U << UART_FCR_FIFO_EN);

    if (true == config->dma_enable)
        value |= (0x1U << UART_FCR_DMA_MODE);

    value |= ((config->rx_fifo_level & UART_FCR_RX_FIFO_TRIG_MASK) << UART_FCR_RX_FIFO_TRIG);
    value |= ((config->tx_fifo_level & UART_FCR_TX_FIFO_TRIG_MASK) << UART_FCR_TX_FIFO_TRIG);
    writel(value, base_address + UART_OFFSET_FCR);

    /* 6. Switch to register configuration mode B to access the UARTi.UART_EFR register
     * a. Set the UARTi.UART_LCR register value to 0x00BF.
     */
    writel(0x00BF, base_address + UART_OFFSET_LCR);

    /* 7/8. Load the new FIFO triggers, define for FCR */
    writel(0x00, base_address + UART_OFFSET_TLR);
    writel(0x00, base_address + UART_OFFSET_SCR);

    /* 9. Restore the UARTi.UART_EFR[4] ENHANCED_EN value saved */
    value = readl(base_address + UART_OFFSET_EFR);
    if (old_efr)
        value |=  (0x1U << UART_EFR_ENHANCEDEN);
    else
        value &= ~(0x1U << UART_EFR_ENHANCEDEN);
    writel(value, base_address + UART_OFFSET_EFR);

    /* 10. Switch to register configuration mode A to access the UARTi.UART_MCR register
     * a. Set the UARTi.UART_LCR register value to 0x0080.
     */
    writel(0x0080, base_address + UART_OFFSET_LCR);

    /* 11. Restore the UARTi.UART_MCR[6] TCR_TLR value saved */
    value = readl(base_address + UART_OFFSET_MCR);
    if (old_mcr)
        value |=  (0x1U << UART_MCR_TCRTLR);
    else
        value &= ~(0x1U << UART_MCR_TCRTLR);
    writel(value, base_address + UART_OFFSET_MCR);

    /* 12. Restore the UARTi.UART_LCR value saved */
    writel(old_lcr, base_address + UART_OFFSET_LCR);
}

static void sdrv_uart_configure_protocol(const uint32_t base_address, const sdrv_uart_config_type *config)
{
    uint32_t value = 0x0U, old_efr = 0x0U, dlh = 0x0U, dll = 0x0U;

    if (true != sdrv_uart_find_rate(config->baudrate, &dlh, &dll))
        return ;

    /* 1. Disable UART to access the UARTi.UART_DLL and UARTi.UART_DLH registers:
     * a. Set the UARTi.UART_MDR1[2:0] MODE_SELECT bit field to 0x7.
     */
    writel(0x7, base_address + UART_OFFSET_MDR1);

    /* 2. Switch to register configuration mode B to access the UARTi.UART_EFR register
     * a. Set the UARTi.UART_LCR register value to 0x00BF.
     */
    writel(0x00BF, base_address + UART_OFFSET_LCR);

    /* 3. Enable register submode TCR_TLR to access the UARTi.UART_TLR register
     * a. Save the UARTi.UART_EFR[4] ENHANCED_EN value.
     * b. Set the UARTi.UART_EFR[4] ENHANCED_EN bit to 1.
     */
    value = readl(base_address + UART_OFFSET_EFR);
    old_efr = (value >> UART_EFR_ENHANCEDEN) & 0x1U;
    value |= (0x1U << UART_EFR_ENHANCEDEN);
    writel(value, base_address + UART_OFFSET_EFR);

    /* 4. Switch to register operational mode to access the UARTi.UART_IER register:
     * a. Set the UARTi.UART_LCR register value to 0x0000.
     */
    writel(0x0000, base_address + UART_OFFSET_LCR);

    /* 5. Clear the UARTi.UART_IER register (set the UARTi.UART_IER[4] SLEEP_MODE bit 
     *    to 0 to change the UARTi.UART_DLL and UARTi.UART_DLH registers).
     * a. Set the UARTi.UART_IER register value to 0x0000.
     */
    writel(0x0000, base_address + UART_OFFSET_IER_UART);

    /* 6. Switch to register configuration mode B to access the UARTi.UART_EFR register
     * a. Set the UARTi.UART_LCR register value to 0x00BF.
     */
    writel(0x00BF, base_address + UART_OFFSET_LCR);

    /* 7. Load the new divisor value:
     * a. Set the UARTi.UART_DLL[7:0] CLOCK_LSB and UARTi.UART_DLH[5:0] CLOCK_MSB bit 
     *    fields to the desired values.
     */
    writel(dlh, base_address + UART_OFFSET_DLH);
    writel(dll, base_address + UART_OFFSET_DLL);

    /* 8. Switch to register operational mode to access the UARTi.UART_IER register:
     * a. Set the UARTi.UART_LCR register value to 0x0000.
     */
    writel(0x0000, base_address + UART_OFFSET_LCR);

    /* 9. Load the new interrupt configuration */
    writel(0x0000, base_address + UART_OFFSET_IER_UART);

    /* 10. Switch to register configuration mode B to access the UARTi.UART_EFR register
     * a. Set the UARTi.UART_LCR register value to 0x00BF.
     */
    writel(0x00BF, base_address + UART_OFFSET_LCR);

    /* 11. Restore the UARTi.UART_EFR[4] ENHANCED_EN value saved */
    value = readl(base_address + UART_OFFSET_EFR);
    if (old_efr)
        value |=  (0x1U << UART_EFR_ENHANCEDEN);
    else
        value &= ~(0x1U << UART_EFR_ENHANCEDEN);
    writel(value, base_address + UART_OFFSET_EFR);

    /* 12. Load the new protocol formatting (parity, stop-bit, character length) 
     *     and switch to register operational mode 
     */
    value = config->wordlength & UART_LCR_CHAR_LENGTH_MASK;
    if ((UART_STOPBITS_ONEHALF_BITS == config->stopbits) && 
        (UART_WORDLENGTH_5_BITS == config->wordlength))
        value |= (0x1U << UART_LCR_NB_STOP);
    else if ((UART_STOPBITS_TWO_BITS == config->stopbits) && 
        (UART_WORDLENGTH_5_BITS != config->wordlength))
        value |= (0x1U << UART_LCR_NB_STOP);
    else
        value &= ~(0x1U << UART_LCR_NB_STOP);

    if (UART_PARITY_NO == config->parity) 
        value &= ~(0x1U << UART_LCR_PARITY_EN);
    else if (UART_PARITY_ODD == config->parity)
    {
        value |=  (0x1U << UART_LCR_PARITY_EN);
        value &= ~(0x1U << UART_LCR_PARITY_TYPE1);
        value &= ~(0x1U << UART_LCR_PARITY_TYPE2);
    }
    else
    {
        value |=  (0x1U << UART_LCR_PARITY_EN);
        value |=  (0x1U << UART_LCR_PARITY_TYPE1);
        value &= ~(0x1U << UART_LCR_PARITY_TYPE2);
    }
        
    value &= ~(0x1U << UART_LCR_DIV_EN);
    value &= ~(0x1U << UART_LCR_BREAK_EN);
    writel(value, base_address + UART_OFFSET_LCR);

    /* 13. Load the new UART mode:
     * a. Set the UARTi.UART_MDR1[2:0] MODE_SELECT bit field to the desired value
     */
    writel(0x00U, base_address + UART_OFFSET_MDR1);
}

void sdrv_uart_init(const uint32_t base_address, const sdrv_uart_config_type *config)
{
    if (NULL == config)
        return ;

    sdrv_uart_reset(base_address);
    sdrv_uart_configure_fifo_and_dma(base_address, config);
    sdrv_uart_configure_protocol(base_address, config);
}

void sdrv_uart_send(const uint32_t base_address, const int data)
{
    uint32_t value  = 0x0U;
    do 
    {
        value = readl(base_address + UART_OFFSET_LSR_UART);
        value = (value >> UART_LSR_UART_TXFIFOE) & 0x1U;
    } while (value != 0x1U);

    writel(data, base_address + UART_OFFSET_THR);
}

