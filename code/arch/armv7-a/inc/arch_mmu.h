#ifndef ARCH_MMU_H_
#define ARCH_MMU_H_

#define MMU_PAGE_TABLE(Domain, NS, PXN) \
    ((Domain    << 5)      | \
     (NS        << 3)      | \
     (PXN       << 2)      | \
     (1         << 0))                         // page table

#define MMU_SMALL_PAGE_CONFIG(nG, S, TEX, AP, C, B, XN) \
    ((nG    << 11)      | \
     (S     << 10)      | \
     (TEX   << 6)       | \
     (AP    << 4)       | \
     (C     << 3)       | \
     (B     << 2)       | \
     (XN    << 0)       | \
     (1     << 1))                             // small page

/**
 * @brief  The enables MMU.
 */
void arch_mmu_enable(void);

/**
 * @brief  The disable MMU.
 */
void arch_mmu_disable(void);

#endif /* ARCH_MMU_H_ */
