#ifndef ARCH_MPU_H_
#define ARCH_MPU_H_

#include "arch_compiler.h"

/* RACR bits */
#define MPU_RACR_B_SHIFT    (0)         /* Bufferable */
#define MPU_RACR_C_SHIFT    (1)         /* Cacheable */
#define MPU_RACR_S_SHIFT    (2)         /* Sharable. For normal memory only. */
#define MPU_RACR_TEX_SHIFT  (3)         /* Type extension */
#define MPU_RACR_AP_SHIFT   (8)         /* Access permission */
#define MPU_RACR_XN_SHIFT   (12)        /* Execution Never */

/* RACR Access permissions */
#define RACR_AP_NO_NO       (0)         /* Privileged NO, Unprivileged NO */
#define RACR_AP_RW_NO       (1)         /* Privileged RW, Unprivileged NO */
#define RACR_AP_RW_RO       (2)         /* Privileged RW, Unprivileged RO */
#define RACR_AP_RW_RW       (3)         /* Privileged RW, Unprivileged RW */
#define RACR_AP_RO_NO       (5)         /* Privileged RO, Unprivileged NO */
#define RACR_AP_RO_RO       (6)         /* Privileged RO, Unprivileged RO */

#define MPU_RACR_CONFIG(TEX, C, B, S, AP, XN) \
    ((B << MPU_RACR_B_SHIFT)      | \
     (C << MPU_RACR_C_SHIFT)      | \
     (S << MPU_RACR_S_SHIFT)      | \
     (TEX << MPU_RACR_TEX_SHIFT)  | \
     (AP << MPU_RACR_AP_SHIFT)    | \
     (XN << MPU_RACR_XN_SHIFT))

enum arch_mpu_region_type {
    MPU_REGION_STRONGORDERED = 0,
    MPU_REGION_DEVICE,
    MPU_REGION_NORMAL,
    MPU_REGION_NORMAL_NONCACHEABLE,
    MPU_REGION_NO_ACCESS,
    MPU_REGION_READONLY
};

/**
 * @brief  The enable the MPU.
 */
void arch_mpu_enable(void);

/**
 * @brief  The disable the MPU.
 */
void arch_mpu_disable(void);

/**
 * @brief  The clear all regions for the MPU.
 */
void arch_mpu_reset(void);

/**
 * @brief  The add the region for the MPU.
 * @param  region - the region number.
 * @param  base - the memory base.
 * @param  attr - the memory attr.
 * @param  size - the memory size.
 */
void arch_mpu_add_region(uint32_t region, uint32_t base, uint32_t attr, uint32_t size);

#endif /* ARCH_MPU_H_ */
