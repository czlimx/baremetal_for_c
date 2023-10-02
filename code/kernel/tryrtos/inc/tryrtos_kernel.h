#ifndef TRYRTOS_KERNEL_H_
#define TRYRTOS_KERNEL_H_

/**
 * @brief   The kernel init processing. 
 */
void tryrtos_kernel_init(void);

/**
 * @brief   The kernel start processing. 
 */
void tryrtos_kernel_start(void);

/**
 * @brief   The idle thread entry. 
 */
void tryrtos_idle_entry(void *para);

/**
 * @brief  The idle first function for call back.
 */
void tryrtos_idle_entry_call_back(void *para);

#endif /* TRYRTOS_KERNEL_H_ */