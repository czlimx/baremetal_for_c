#ifndef ARCH_BARRIER_H_
#define ARCH_BARRIER_H_

#define arch_barrier_isb() asm volatile ("isb" : : : "memory")
#define arch_barrier_dsb() asm volatile ("dsb" : : : "memory")
#define arch_barrier_dmb() asm volatile ("dmb" : : : "memory")
#define arch_barrier_wfi() asm volatile ("wfi" : : : "memory")
#define arch_barrier_wfe() asm volatile ("wfe" : : : "memory")

#endif /* ARCH_BARRIER_H_ */
