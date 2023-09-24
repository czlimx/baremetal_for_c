#ifndef ARCH_GICV2_H_
#define ARCH_GICV2_H_

#include "arch_compiler.h"
#include "device_info.h"

#define GICD_OFFSET         0x1000
#define GICC_OFFSET         0x2000

#define GICD_CTLR           (GIC_BASE + GICD_OFFSET + 0x0000)
#define GICD_TYPER          (GIC_BASE + GICD_OFFSET + 0x0004)
#define GICD_IIDR           (GIC_BASE + GICD_OFFSET + 0x0008)
#define GICD_IGROUPR(n)     (GIC_BASE + GICD_OFFSET + 0x0080 + (0x4 * n))
#define GICD_ISENABLER(n)   (GIC_BASE + GICD_OFFSET + 0x0100 + (0x4 * n))
#define GICD_ICENABLER(n)   (GIC_BASE + GICD_OFFSET + 0x0180 + (0x4 * n))
#define GICD_ISPENDR(n)     (GIC_BASE + GICD_OFFSET + 0x0200 + (0x4 * n))
#define GICD_ICPENDR(n)     (GIC_BASE + GICD_OFFSET + 0x0280 + (0x4 * n))
#define GICD_ISACTIVER(n)   (GIC_BASE + GICD_OFFSET + 0x0300 + (0x4 * n))
#define GICD_ICACTIVER(n)   (GIC_BASE + GICD_OFFSET + 0x0380 + (0x4 * n))
#define GICD_IPRIORITYR(n)  (GIC_BASE + GICD_OFFSET + 0x0400 + (0x4 * n))
#define GICD_ITARGETSR(n)   (GIC_BASE + GICD_OFFSET + 0x0800 + (0x4 * n))
#define GICD_ICFGR(n)       (GIC_BASE + GICD_OFFSET + 0x0C00 + (0x4 * n))
#define GICD_NSACR(n)       (GIC_BASE + GICD_OFFSET + 0x0E00 + (0x4 * n))
#define GICD_SGIR           (GIC_BASE + GICD_OFFSET + 0x0F00)
#define GICD_CPENDSGIR(n)   (GIC_BASE + GICD_OFFSET + 0x0F10 + (0x4 * n))
#define GICD_SPENDSGIR(n)   (GIC_BASE + GICD_OFFSET + 0x0F20 + (0x4 * n))

#define GICC_CTLR           (GIC_BASE + GICC_OFFSET + 0x0000)
#define GICC_PMR            (GIC_BASE + GICC_OFFSET + 0x0004)
#define GICC_BPR            (GIC_BASE + GICC_OFFSET + 0x0008)
#define GICC_IAR            (GIC_BASE + GICC_OFFSET + 0x000C)
#define GICC_EOIR           (GIC_BASE + GICC_OFFSET + 0x0010)
#define GICC_RPR            (GIC_BASE + GICC_OFFSET + 0x0014)
#define GICC_HPPIR          (GIC_BASE + GICC_OFFSET + 0x0018)
#define GICC_ABPR           (GIC_BASE + GICC_OFFSET + 0x001C)
#define GICC_AIAR           (GIC_BASE + GICC_OFFSET + 0x0020)
#define GICC_AEOIR          (GIC_BASE + GICC_OFFSET + 0x0024)
#define GICC_AHPPIR         (GIC_BASE + GICC_OFFSET + 0x0028)
#define GICC_APR(n)         (GIC_BASE + GICC_OFFSET + 0x00D0 + (0x4 * n))
#define GICC_NSAPR(n)       (GIC_BASE + GICC_OFFSET + 0x00E0 + (0x4 * n))
#define GICC_IIDR           (GIC_BASE + GICC_OFFSET + 0x00FC)
#define GICC_DIR            (GIC_BASE + GICC_OFFSET + 0x1000)

enum gicd_trigger_type {
    GICD_LEVEL_SENSITIVE = 0,
    GICD_EDGE_TRIGGER
};

enum gicd_encode_type {
    GICD_N_N_MODE = 0,
    GICD_1_N_MODE
};

enum gicd_access_type {
    GICD_NON_SECURE_ACCESS_PERMITTE = 0,
    GICD_NON_SECURE_WRITE_PERMITTE,
    GICD_NON_SECURE_ACCESS_PART,
    GICD_NON_SECURE_ACCESS_ALL
};

enum gicd_target_list_filter_type {
    GCID_FORWARD_TARGET_LIST = 0,
    GCID_FORWARD_EXCEPT_REQUEST,
    GCID_FORWARD_REQUEST,
    GCID_FORWARD_RESERVED
};


/**
 * @brief Enable the interrupt distributor using the GIC's CTLR register.
 */
void arch_gicd_enable(void);

/**
 * @brief Disable the interrupt distributor using the GIC's CTLR register.
 */
void arch_gicd_disable(void);

/**
 * @brief Read the GIC's TYPER register.
 * @return uint32_t 
 *         [15:11] LSPI           the value of this field is the maximum number of implemented lockable SPIs.
 *         [10]    SecurityExtn   Indicates whether the GIC implements the Security Extensions.
 *         [7:5]   CPUNumber      Indicates the number of implemented CPU interfaces.
 *         [4:0]   ITLinesNumber  Indicates the maximum number of interrupts that the GIC supports.
 */
uint32_t arch_gicd_get_infomation(void);

/**
 * @brief Reads the GIC's IIDR register.
 * @return uint32_t Provides information about the implementer and revision of the Distributor.
 */
uint32_t arch_gicd_get_identification(void);

/**
 * @brief Set Each bit controls whether the corresponding interrupt is in Group 0 or Group 1.
 */
void arch_gicd_set_group(uint32_t number, uint32_t group);

/**
 * @brief Enables the given interrupt using GIC's ISENABLER register.
 */
void arch_gicd_set_enable(uint32_t number);

/**
 * @brief Disables the given interrupt using GIC's ICENABLER register.
 */
void arch_gicd_clear_enable(uint32_t number);

/**
 * @brief Sets the given interrupt as pending using GIC's ISPENDR register.
 */
void arch_gicd_set_pending(uint32_t number);

/**
 * @brief Clears the given interrupt from being pending using GIC's ICPENDR register.
 */
void arch_gicd_clear_pending(uint32_t number);

/**
 * @brief Sets the given interrupt as pending using GIC's GICD_ISACTIVER register.
 */
void arch_gicd_set_active(uint32_t number);

/**
 * @brief Clears the given interrupt from being pending using GIC's GICD_ICACTIVER register.
 */
void arch_gicd_clear_active(uint32_t number);

/**
 * @brief Set the priority for the given interrupt in the GIC's IPRIORITYR register.
 */
void arch_gicd_set_priority(uint32_t number, uint32_t priority);

/**
 * @brief Read the current interrupt priority from GIC's IPRIORITYR register.
 */
uint32_t arch_gicd_get_priority(uint32_t number);

/**
 * @brief Sets the GIC's ITARGETSR register for the given interrupt.
 */
void arch_gicd_set_target(uint32_t number, uint32_t cpuid);

/**
 * @brief Read the GIC's ITARGETSR register.
 */
uint32_t arch_gicd_get_target(uint32_t number);

/**
 * @brief Read the GIC's GICD_ICFGR register.
 */
void arch_gicd_config_trigger(enum gicd_trigger_type trigger, enum gicd_encode_type encode, uint32_t number);

/**
 * @brief Read the GIC's GICD_NSACR register.
 */
void arch_gicd_config_access(enum gicd_access_type access, uint32_t number);

/**
 * @brief Read the GIC's GICD_SGIR register.
 */
void arch_gicd_generate_interrupt(enum gicd_target_list_filter_type filter, uint32_t cpu_umask, uint32_t number);

/**
 * @brief Read the GIC's GICD_SPENDSGIR register.
 */
void arch_gicd_sgi_set_pending(uint32_t cpuid, uint32_t number);

/**
 * @brief Read the GIC's GICD_CPENDSGIR register.
 */
void arch_gicd_sgi_clear_pending(uint32_t cpuid, uint32_t number);

void arch_gicc_enable(void);

void arch_gicc_disable(void);

void arch_gicc_set_priority_mask(uint32_t priority);

void arch_gicc_set_binary_point(uint32_t pointy);

uint32_t arch_gicc_acknowledge(void);

void arch_gicc_end_of_interrupt(uint32_t cpuid, uint32_t number);

void arch_gicc_set_running_priority(uint32_t priority);

void arch_gicc_get_highest_priority(uint32_t priority);

#endif /* ARCH_GIC_H_ */
