#ifndef ARCH_COMPILER_H_
#define ARCH_COMPILER_H_

typedef long            size_t;
typedef unsigned int    uint32_t;
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef int             int32_t;
typedef char            int8_t;
typedef short           int16_t; 

#define NULL            ((void *)0)

#define readb(addr)     (*((volatile uint8_t  *)(long)(addr)))
#define readw(addr)     (*((volatile uint16_t *)(long)(addr)))
#define readl(addr)     (*((volatile uint32_t *)(long)(addr)))
#define writeb(v, addr) (*((volatile uint8_t  *)(long)(addr)) = (uint8_t )(v))
#define writew(v, addr) (*((volatile uint16_t *)(long)(addr)) = (uint16_t)(v))
#define writel(v, addr) (*((volatile uint32_t *)(long)(addr)) = (uint32_t)(v))

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