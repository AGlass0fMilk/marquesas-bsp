/*
 * bsp_initialization.c
 *
 *  Created on: Apr 15, 2020
 *      Author: gdbeckstein
 */

#include "sdram_ext.h"
#include "ltdc_config.h"

/**
 * @brief Setup the target board-specific configuration
 * of the microcontroller
 *
 * This is a "strong" definition of the bsp initialization called in
 * SystemInit. See system_stm32h7xx.c for more information.
 *
 * @param None
 * @retval None
 */
void TargetBSP_Init(void) {

    // Some peripherals are only initialized by the M7 at startup
#if defined(CORE_CM7)
    // Initialize external SDRAM for frame buffer
    ext_sdram_init();
#endif

}


