#ifndef ARCH_CPSR_H_
#define ARCH_CPSR_H_

#define arch_cpsr_irq_enable()                  asm volatile ("cpsie i" : : : "memory")
#define arch_cpsr_irq_disable()                 asm volatile ("cpsid i" : : : "memory")
#define arch_cpsr_fiq_enable()                  asm volatile ("cpsie f" : : : "memory")
#define arch_cpsr_fiq_disable()                 asm volatile ("cpsid f" : : : "memory")
#define arch_cpsr_async_abort_enable()          asm volatile ("cpsie a" : : : "memory")
#define arch_cpsr_async_abort_disable()         asm volatile ("cpsid a" : : : "memory")
#define arch_cpsr_switch_to_usr()               asm volatile ("cps #0x10": : :"memory")
#define arch_cpsr_switch_to_sys()               asm volatile ("cps #0x1F": : :"memory")
#define arch_cpsr_switch_to_fiq()               asm volatile ("cps #0x11": : :"memory")
#define arch_cpsr_switch_to_irq()               asm volatile ("cps #0x12": : :"memory")
#define arch_cpsr_switch_to_svc()               asm volatile ("cps #0x13": : :"memory")
#define arch_cpsr_switch_to_abt()               asm volatile ("cps #0x17": : :"memory")
#define arch_cpsr_switch_to_und()               asm volatile ("cps #0x1B": : :"memory")

#endif /* ARCH_CPSR_H_ */