/*
 * IS42S32200L.c
 *
 *  Created on: Apr 14, 2020
 *      Author: gdbeckstein
 */

#include "sram_device.h"

#include "mbed_wait_api.h"

// TODO - some sort of preprocessor configuration system
//#if MEMORY_DEVICE == "IS42S32200L"
//
//#endif

int bsp_sram_init(SDRAM_HandleTypeDef *hsdram) {

    FMC_SDRAM_CommandTypeDef Command;

    /**
     * IS42S32200L datasheet excerpt:
     *
     *      With at least one COMMAND INHIBIT or NOP command
     *      having been applied, a PRECHARGE command should
     *      be applied once the 100μs delay has been satisfied.
     *
     * This is handled in the sdram_msp implementation
     */

    __IO uint32_t tmpmrd = 0;
    /* Configure a clock configuration enable command */
    Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

    /* Step 4: Insert 100 ms delay */
    HAL_Delay(100);

    /* Step 5: Configure a PALL (precharge all) command */
    Command.CommandMode = FMC_SDRAM_CMD_PALL;
    Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

    /* Step 6 : Configure a Auto-Refresh command */
    Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber = 4;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

    /* Step 7: Program the external memory mode register */
    tmpmrd = (uint32_t) SDRAM_MODEREG_BURST_LENGTH_2
            | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL | SDRAM_MODEREG_CAS_LATENCY_3
            | SDRAM_MODEREG_OPERATING_MODE_STANDARD
            | SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = tmpmrd;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

    HAL_SDRAM_ProgramRefreshRate(hsdram, 0x56A - 20);

    return 0;

}

