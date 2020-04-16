/*
 * sram_ext.c
 *
 *  Created on: Apr 14, 2020
 *      Author: gdbeckstein
 */

#include "sram_ext.h"
#include "sram_device.h"

#include "stm32h7xx_hal_rcc.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h7xx_hal_sram.h"

#include "objects.h"

#include "mbed_error.h"

static SDRAM_HandleTypeDef hsdram1;

void ext_sram_init(void) {

    /** Set up the FMC clock */
    // Select HCLK3 as source of FMC clock
    RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;
    RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FMC;
    RCC_PeriphClkInit.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK; // (typically 240MHz, half M7 core frequency)
#if defined(DUAL_CORE)
    while (LL_HSEM_1StepLock(HSEM, CFG_HW_RCC_SEMID)) {
    }
#endif /* DUAL_CORE */
    if (HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit) != HAL_OK) {
        error("HAL_RCCEx_PeriphCLKConfig error\n");
    }
#if defined(DUAL_CORE)
    LL_HSEM_ReleaseLock(HSEM, CFG_HW_RCC_SEMID, HSEM_CR_COREID_CURRENT);
#endif /* DUAL_CORE */

    /** Configure FMC SDRAM timing */
    FMC_SDRAM_TimingTypeDef SdramTiming = {0};

    /** Perform the SDRAM1 memory initialization sequence
    */
    hsdram1.Instance = FMC_SDRAM_DEVICE;
    /* hsdram1.Init */
    hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
    hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
    hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_11;
    hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
    hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
    hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
    hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
    hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
    /* SdramTiming */
    SdramTiming.LoadToActiveDelay = 2;
    SdramTiming.ExitSelfRefreshDelay = 6;
    SdramTiming.SelfRefreshTime = 4;
    SdramTiming.RowCycleDelay = 6;
    SdramTiming.WriteRecoveryTime = 2;
    SdramTiming.RPDelay = 2;
    SdramTiming.RCDDelay = 2;

    /**
     * Internally, HAL_SDRAM_Init calls HAL_SDRAM_MspInit, which subsequently calls
     * HAL_FSM_MspInit, which initializes the pins used by the FMC.
     */
    if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
    {
        MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_MEMORY_SUBSYSTEM,
                MBED_ERROR_CODE_INITIALIZATION_FAILED),
                "External SDRAM initialization failed");
    }

    /**
     * Now the FMC and associated hardware (pins, clocks, etc) are configured,
     * we can start the initialization sequence specific to the connected memory device.
     *
     * See the header comments of stm32h7xx_hal_sdram.c for SDRAM initialization checklist
     *
     * This function is implemented by the configured SRAM device of the target.
     *
     */
    if(bsp_sram_init(&hsdram1)) {
        MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_MEMORY_SUBSYSTEM,
                    MBED_ERROR_CODE_INITIALIZATION_FAILED),
                    "External SDRAM initialization failed");
    }


}

