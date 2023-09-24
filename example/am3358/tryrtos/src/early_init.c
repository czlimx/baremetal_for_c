#include "arch_tlb.h"
#include "arch_mmu.h"
#include "arch_compiler.h"

void early_mmu_config(void)
{
    /* default 0x80000000 with short-descriptor format table */
    arch_tlb_config_ttbr0(0x80000000);
    arch_tlb_config_ttbcr(0);

    /* first-level descriptor formats for 0x00000000 - 0x7FFFFFFF with section */
    uint32_t  attribute    = 0;
    uint32_t  table_frame  = 0x00000000;
    uint32_t *table_base   = (uint32_t *)0x80000000;
    for (uint32_t i = 0; i < 2048; i++)
    {
        if (table_frame < 0x20000000)        // 0x00000000 - 0x1FFFFFFF (GPMC:512MB) -- section
            attribute = 0x90C12;             // Strongly-ordered, Shareable, XN, PXN, NS, Domain0, global, Full access           
        else if (table_frame < 0x44000000)   // 0x20000000 - 0x44000000 (BootROM:576MB) -- section
            attribute = 0x90012;             // Strongly-ordered, Shareable, XN, PXN, NS, Domain0, global, no access   
        else                                 // 0x44000000 - 0x7FFFFFFF (Peripheral:960MB) -- section
            attribute = 0x90C16;             // Device, Shareable, XN, PXN, NS, Domain0, global, Full access

        table_base[i] = (table_frame  & 0xFFF00000) | attribute;
        table_frame += 0x100000;             // 1MB
    }

    /* first-level descriptor formats for 0x80000000 - 0x9FFFFFFF with page table */
    table_base   = (uint32_t *)0x80002000;
    uint32_t second_frame = 0x80004000;
    for (uint32_t i = 0; i < 512; i++)
    {
        // 0x80000000 - 0x9FFFFFFF (SDRAM:512MB) -- Page table
        attribute = 0x9;                    // normal, no-shareable, no-XN, no-PXN, NS, Domain0, global, Full access
        table_base[i] = (second_frame  & 0xFFFFFC00) | attribute;
        second_frame += 0x400;              // (1MB / 4KB) * 4  
    }

    /* first-level descriptor formats for 0xA0000000 - 0xFFFFFFFF with Supersection */
    table_base   = (uint32_t *)0x80002800;
    table_frame  = 0xA0000000;
    for (uint32_t i = 0; i < 1536; i+=16)
    {
        // 0xA0000000 - 0xFFFFFFFF (Reserved:1536MB) -- Supersection
        attribute = 0xD0012;                // Strongly-ordered, Shareable, XN, PXN, NS, Domain0, global, no access
        for (uint32_t j = 0; j < 16; j++)
            table_base[i + j] = (table_frame  & 0xFF000000) | attribute;
        table_frame += 0x1000000;           // 16MB
    }

    /* second-level descriptor formats for 0x80000000 - 0x9FFFFFFF with page table */
    uint32_t *page_base = (uint32_t *)0x80004000;
    uint32_t  pa_frame = 0x80000000;
    for (uint32_t i = 0; i < 0x20000; i++)
    {
        /* 0x80000000 - 0x9FFFFFFF (SDRAM:512MB) -- Page table */
        if (pa_frame < 0x81000000)
        {
            attribute = 0x0040B;            // normal, shareable, XN, PXN, NS, Domain0, global, no access
                                            // Outer and Inner Write-Through, no Write-Allocate
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
