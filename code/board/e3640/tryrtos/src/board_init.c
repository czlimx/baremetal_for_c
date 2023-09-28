#include "arch_mpu.h"
#include "arch_compiler.h"

static void early_mpu_config(void)
{
    /* reset mpu register to default */
    arch_mpu_reset();

    /* add memory protect region */
    arch_mpu_add_region(0, 0, 0, 0x20000);          // TCM region
}

/**
 * @brief  The early init for board.
 */
void board_early_init(void)
{
    /* configure the mpu region */
    early_mpu_config();
}

/**
 * @brief  The init for board.
 */
void board_init(void)
{

}
