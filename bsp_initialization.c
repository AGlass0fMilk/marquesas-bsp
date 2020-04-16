/*
 * bsp_initialization.c
 *
 *  Created on: Apr 15, 2020
 *      Author: gdbeckstein
 */

#include "sdram_ext.h"

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

    // Only initialize external SRAM for the M7 core
#if defined(CORE_CM7)
    ext_sdram_init();
#endif

}


