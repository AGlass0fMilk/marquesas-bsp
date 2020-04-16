/*
 * sram_device.h
 *
 *  Created on: Apr 14, 2020
 *      Author: gdbeckstein
 */

#ifndef MARQUESAS_BSP_SRAM_MEMORY_CONFIGS_SRAM_DEVICE_H_
#define MARQUESAS_BSP_SRAM_MEMORY_CONFIGS_SRAM_DEVICE_H_

#include "stm32h7xx_hal_sdram.h"

// TODO Have this API also provide memory timing parameters, etc
// Maybe it doesn't have to be so generic...

/**
 * Perform the board's SRAM chip initialization sequence
 *
 * @retval 0 on success
 */
int bsp_sram_init(SDRAM_HandleTypeDef *hsdram);

#endif /* MARQUESAS_BSP_SRAM_MEMORY_CONFIGS_SRAM_DEVICE_H_ */
