#include "arch_tlb.h"
#include "sdrv_uart.h"
#include "sdrv_intc.h"
#include "sdrv_timer.h"
#include "arch_irq.h"
#include "libc_printf.h"
#include "board_init.h"

/**
 * Output a character to a custom device like UART, used by the printf() function
 * This function is declared here only. You have to write your custom implementation somewhere
 * \param character Character to output
 */
void _putchar(char character)
{
    sdrv_uart_send(UART_0_BASE, character);
}

const sdrv_uart_config_type default_uart = {
    .dma_enable     = false,
    .fifo_enable    = true,
    .rx_fifo_level  = UART_FIFO_LEVEL_8,
    .tx_fifo_level  = UART_FIFO_LEVEL_36,
    .baudrate       = 115200U,
    .parity         = UART_PARITY_NO,
    .stopbits       = UART_STOPBITS_ONE_BITS,
    .wordlength     = UART_WORDLENGTH_8_BITS
};

/**
 * @brief  The early page table init for mmu.
 */
static void early_mmu_config(void)
{
    /* default 0x80000000 with short-descriptor format table */
    arch_tlb_config_ttbr0(0x80000000);
    arch_tlb_config_ttbr1(0x80004000);
    arch_tlb_config_ttbcr(1);

    /* first-level descriptor formats for 0x00000000 - 0x7FFFFFFF with section for ttbr0 */
    uint32_t  attribute    = 0;
    uint32_t  table_frame  = 0x00000000;
    uint32_t *table_base   = (uint32_t *)0x80000000;
    for (uint32_t i = 0; i < 4096; i++)
    {
        if (table_frame < 0x80000000)
        {
            if (table_frame < 0x20000000)        // 0x00000000 - 0x1FFFFFFF (GPMC:512MB) -- section
                attribute = 0x90C12;             // Strongly-ordered, Shareable, XN, PXN, NS, Domain0, global, Full access           
            else if (table_frame < 0x44000000)   // 0x20000000 - 0x44000000 (BootROM:576MB) -- section
                attribute = 0x90012;             // Strongly-ordered, Shareable, XN, PXN, NS, Domain0, global, no access   
            else                                 // 0x44000000 - 0x7FFFFFFF (Peripheral:960MB) -- section
                attribute = 0x90C16;             // Device, Shareable, XN, PXN, NS, Domain0, global, Full access
            table_base[i] = (table_frame  & 0xFFF00000) | attribute;
        }
        else
        {
            attribute = 0x00000;                 // invaild
            table_base[i] = attribute;
        }
        
        table_frame += 0x100000;             // 1MB
    }

    /* first-level descriptor formats for 0x00000000 - 0x7FFFFFFF with section for ttbr1 */
    table_base   = (uint32_t *)0x80004000;
    table_frame  = 0x00000000;
    uint32_t second_frame = 0x80008000;
    for (uint32_t i = 0; i < 4096; i++)
    {
        // 0xC0000000 - 0xDFFFFFFF (VA::SDRAM:512MB) -- page table
        if ((table_frame < 0xE0000000) && (table_frame >= 0xC0000000))
        {
            attribute = 0x9;                 // no-PXN, NS, Domain0
            table_base[i] = (second_frame  & 0xFFFFFC00) | attribute;
            second_frame += 0x400;           // (1MB / 4KB) * 4
        }
        else
        {
            attribute = 0x0;                 // invaild
            table_base[i] = attribute;
        }
        table_frame += 0x100000;             // 1MB   
    }

    /* second-level descriptor formats for 0x80000000 - 0x9FFFFFFF with page table */
    uint32_t *page_base = (uint32_t *)0x80008000;
    uint32_t  pa_frame = 0x80000000;
    for (uint32_t i = 0; i < 0x20000; i++)
    {
        /* 0x80000000 - 0x9FFFFFFF (PA::SDRAM:512MB) -- Page table */
        if (pa_frame < 0x81000000)
        {
            attribute = 0x00403;            // Strongly-ordered, shareable, XN, PXN, NS, Domain0, global, no access
        }
        else if (pa_frame < 0x82000000)
        {
            attribute = 0x0043B;            // normal, shareable, XN, PXN, NS, Domain0, global, Full access
                                            // Outer and Inner Write-Through, no Write-Allocate
        }
        else
        {
            attribute = 0x0087E;            // normal, no-shareable, no-XN, no-PXN, NS, Domain0, no-global, Full access
                                            // Outer and Inner Write-Back, Write-Allocate
        }
        page_base[i] = (pa_frame  & 0xFFFFF000) | attribute;
        pa_frame += 0x1000;                 // 4KB
    }
}

/**
 * @brief  The early init for board.
 */
void board_early_init(void)
{
    /* configure mmu page table */
    early_mmu_config();
}

/**
 * @brief  The early init for timer.
 */
void sdrv_timer_init(uint32_t base)
{
    /* Select the master osc CLK_32KHZ as Timer2 clock source */
    writel(0x2, 0x44E00508);

    /* Reset the counter */
    sdrv_dtimer_soft_reset(base);

    /* Load the counter with the initial count value with 1ms */
    sdrv_dtimer_counter_set(base, 0xffffff00);

    /* Load the load register with the reload count value with 1ms */
    sdrv_dtimer_reload_set(base, 0xffffff00);

    /* Configure the DMTimer for Auto-reload and compare mode */
    sdrv_dtimer_mode_configure(base, TIMER_TRIGGER_RELOAD);

    /* Enable the DMTimer interrupts */
    sdrv_dtimer_int_enable(base, TIMER_INTERRUPT_OVF);

    /* Enable the DMTimer2 INTC */
    arch_irq_register(AM335X_INT_TINT2, ARCH_IRQ_MAX_PRIORITY - 1, NULL, sdrv_timer_intc_handler);

    /* enable the timer2 */
    sdrv_dtimer_enable(base);
}

/**
 * @brief  The init for board.
 */
void board_init(void)
{
    /* configure and init uart */
    sdrv_uart_init(UART_0_BASE, &default_uart);

    /* test print to log */
    printf("\r\nhello, the board started successfully!!!\r\n");
}
