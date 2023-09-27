#ifndef ARCH_COMPILER_H_
#define ARCH_COMPILER_H_

#include <stdint.h>

#define true	            1
#define false	            0
#define bool	            _Bool

// typedef unsigned int        uint32_t;
// typedef unsigned char       uint8_t;
// typedef unsigned short      uint16_t;
// typedef unsigned long long  uint64_t;
// typedef int                 sint32_t;
// typedef char                sint8_t;
// typedef short               sint16_t; 
// typedef long long           sint64_t;
// typedef __SIZE_TYPE__       size_t;
// //typedef long int            ptrdiff_t;
// typedef long long           intmax_t;
// typedef unsigned long long  uintmax_t;
// typedef int			        intptr_t;
// typedef unsigned int		uintptr_t;

#define NULL            ((void *)0)

#define readb(addr)     (*((volatile uint8_t  *)(long)(addr)))
#define readw(addr)     (*((volatile uint16_t *)(long)(addr)))
#define readl(addr)     (*((volatile uint32_t *)(long)(addr)))
#define writeb(v, addr) (*((volatile uint8_t  *)(long)(addr)) = (uint8_t )(v))
#define writew(v, addr) (*((volatile uint16_t *)(long)(addr)) = (uint16_t)(v))
#define writel(v, addr) (*((volatile uint32_t *)(long)(addr)) = (uint32_t)(v))

/**
 * @brief Set/clear the bit starting from the specified address.
 * @param addr - the base addr
 * @param startbit - the target start bit.
 * @param width - the operating width.
 * @param val - the target value.
*/
static inline void rmwr32(const uint32_t addr, const uint32_t startbit, const uint32_t width, const uint32_t val)
{
    uint32_t value = 0;

    value = readl(addr);
    value &= ~((( 0x1U << width) - 1U) << startbit);
    value |=  ((((0x1U << width) - 1U) & val) << startbit);
    writel(value, addr);
}

#define bit(nr)         (1UL << (nr))
/* Compute the number of elements in the given array */
#define array_size(a)   (sizeof(a) / sizeof((a)[0]))

#endif /* ARCH_COMPILER_H_ */
