/*
 * sram_ext.c
 *
 *  Created on: Apr 14, 2020
 *      Author: gdbeckstein
 */

#include "sdram_ext.h"

#include "stm32h7xx.h"

/**
 * This code is based off of an example from the STM32CubeH7 package.
 *
 * The specific project is:
 * en.stm32cubeh7_v1-7-0/STM32Cube_FW_H7_V1.7.0/Projects/...
 * STM32H745I-DISCO/Examples/FMC/FMC_SDRAM_DataMemory
 *
 * See system_stm32h7xx.c there, specifically SystemInit_ExtMemCtl.
 *
 * This configures the Flexible Memory Controller (FMC) peripheral
 * to interface with an external SDRAM chip on FMC Bank 5 (external SDRAM bank 1)
 *
 * The FMC is configured to use a 32-bit wide data bus and an 11-bit wide address bus.
 *
 * The specific SDRAM chip this was written for is ISSI IS42S32200L
 * This chip is 4 banks of 2048 rows by 256 columns by 32 bits = 8MB
 * Thus the FMC is configured to use 11 row bits and 8 column bits
 */

void ext_sdram_init(void) {

    __IO uint32_t tmp = 0;

    register uint32_t tmpreg = 0, timeout = 0xFFFF;
    register __IO uint32_t index;

    /* Enable GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH and GPIOI
     * interface clock */
    RCC->AHB4ENR |= 0x000001FC;

    /* Delay after an RCC peripheral clock enabling */
    tmp = READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOEEN);

    /** FMC GPIO Configuration
     PC2_C   ------> FMC_SDNE0
     PD0   ------> FMC_D2
     PD1   ------> FMC_D3
     PD8   ------> FMC_D13
     PD9   ------> FMC_D14
     PD10   ------> FMC_D15
     PD14   ------> FMC_D0
     PD15   ------> FMC_D1
     PE0   ------> FMC_NBL0
     PE1   ------> FMC_NBL1
     PE7   ------> FMC_D4
     PE8   ------> FMC_D5
     PE9   ------> FMC_D6
     PE10   ------> FMC_D7
     PE11   ------> FMC_D8
     PE12   ------> FMC_D9
     PE13   ------> FMC_D10
     PE14   ------> FMC_D11
     PE15   ------> FMC_D12
     PF0   ------> FMC_A0
     PF1   ------> FMC_A1
     PF2   ------> FMC_A2
     PF3   ------> FMC_A3
     PF4   ------> FMC_A4
     PF5   ------> FMC_A5
     PF11   ------> FMC_SDNRAS
     PF12   ------> FMC_A6
     PF13   ------> FMC_A7
     PF14   ------> FMC_A8
     PF15   ------> FMC_A9
     PG0   ------> FMC_A10
     PG4   ------> FMC_BA0
     PG5   ------> FMC_BA1
     PG8   ------> FMC_SDCLK
     PG15   ------> FMC_SDNCAS
     PH2   ------> FMC_SDCKE0
     PH5   ------> FMC_SDNWE
     PH8   ------> FMC_D16
     PH9   ------> FMC_D17
     PH10   ------> FMC_D18
     PH11   ------> FMC_D19
     PH12   ------> FMC_D20
     PH13   ------> FMC_D21
     PH14   ------> FMC_D22
     PH15   ------> FMC_D23
     PI0   ------> FMC_D24
     PI1   ------> FMC_D25
     PI2   ------> FMC_D26
     PI3   ------> FMC_D27
     PI4   ------> FMC_NBL2
     PI5   ------> FMC_NBL3
     PI6   ------> FMC_D28
     PI7   ------> FMC_D29
     PI9   ------> FMC_D30
     PI10   ------> FMC_D31
     */

    /** PCx pins used:
     * PC2_C (FMC_SDNE0)
     */

    /* Connect PCx pins to FMC Alternate function */
    GPIOC->AFR[0] = 0x00000C00;
    /* Configure PCx pins in Alternate function mode */
    GPIOC->MODER = 0x00000020;
    /* Configure PCx pins speed to 100MHz */
    GPIOC->OSPEEDR = 0x00000030;
    /* Configure PCx pins Output type to push-pull */
    GPIOC->OTYPER = 0x00000000;
    /* Configure PCx pins in Pull-up */
    GPIOC->PUPDR = 0x00000010;

    /** PDx pins used:
     * PD0 (FMC_D2)
     * PD1 (FMC_D3)
     * PD8 (FMC_D13)
     * PD9 (FMC_D14)
     * PD10 (FMC_D15)
     * PD14 (FMC_D0)
     * PD15 (FMC_D1)
     */

    /* Connect PDx pins to FMC Alternate function */
    GPIOD->AFR[0] = 0x000000CC;
    GPIOD->AFR[1] = 0xCC000CCC;
    /* Configure PDx pins in Alternate function mode */
    GPIOD->MODER = 0xAFEAFFFA;
    /* Configure PDx pins speed to 100 MHz */
    GPIOD->OSPEEDR = 0xF03F000F;
    /* Configure PDx pins Output type to push-pull */
    GPIOD->OTYPER = 0x00000000;
    /* Configure PDx pins in Pull-up */
    GPIOD->PUPDR = 0x50150005;

    /** PEx pins used:
     * PE0 (FMC_NBL0)
     * PE1 (FMC_NBL1)
     * PE7 (FMC_D4)
     * PE8 (FMC_D5)
     * PE9 (FMC_D6)
     * PE10 (FMC_D7)
     * PE11 (FMC_D8)
     * PE12 (FMC_D9)
     * PE13 (FMC_D10)
     * PE14 (FMC_D11)
     * PE15 (FMC_D12)
     */

    /* Connect PEx pins to FMC Alternate function */
    GPIOE->AFR[0] = 0xC00000CC;
    GPIOE->AFR[1] = 0xCCCCCCCC;
    /* Configure PEx pins in Alternate function mode */
    GPIOE->MODER = 0xAAAABFFA;
    /* Configure PEx pins speed to 100 MHz */
    GPIOE->OSPEEDR = 0xFFFFC00F;
    /* Configure PEx pins Output type to push-pull */
    GPIOE->OTYPER = 0x00000000;
    /* Configure PEx pins in Pull-up */
    GPIOE->PUPDR = 0x55554005;

    /** PFx pins used:
     * PF0 (FMC_A0)
     * PF1 (FMC_A1)
     * PF2 (FMC_A2)
     * PF3 (FMC_A3)
     * PF4 (FMC_A4)
     * PF5 (FMC_A5)
     * PF11 (FMC_SDNRAS)
     * PF12 (FMC_A6)
     * PF13 (FMC_A7)
     * PF14 (FMC_A8)
     * PF15 (FMC_A9)
     */

    /* Connect PFx pins to FMC Alternate function */
    GPIOF->AFR[0] = 0x00CCCCCC;
    GPIOF->AFR[1] = 0xCCCCC000;
    /* Configure PFx pins in Alternate function mode */
    GPIOF->MODER = 0xAABFFAAA;
    /* Configure PFx pins speed to 100 MHz */
    GPIOF->OSPEEDR = 0xFFC00FFF;
    /* Configure PFx pins Output type to push-pull */
    GPIOF->OTYPER = 0x00000000;
    /* Configure PFx pins in Pull-up */
    GPIOF->PUPDR = 0x55400555;

    /** PGx pins used:
     * PG0 (FMC_A10)
     * PG4 (FMC_BA0)
     * PG5 (FMC_BA1)
     * PG8 (FMC_SDCLK)
     * PG15 (FMC_SDNCAS)
     */

    /* Connect PGx pins to FMC Alternate function */
    GPIOG->AFR[0] = 0x00CC000C;
    GPIOG->AFR[1] = 0xC000000C;
    /* Configure PGx pins in Alternate function mode */
    GPIOG->MODER = 0xBFFEFAFE;
    /* Configure PGx pins speed to 100 MHz */
    GPIOG->OSPEEDR = 0xC0030F03;
    /* Configure PGx pins Output type to push-pull */
    GPIOG->OTYPER = 0x00000000;
    /* Configure PGx pins in Pull-up */
    GPIOG->PUPDR = 0x40010501;

    /** PHx pins used:
     * PH2 (FMC_SDCKE0)
     * PH5 (FMC_SDNWE)
     * PH8 (FMC_D16)
     * PH9 (FMC_D17)
     * PH10 (FMC_D18)
     * PH11 (FMC_D19)
     * PH12 (FMC_D20)
     * PH13 (FMC_D21)
     * PH14 (FMC_D22)
     * PH15 (FMC_D23)
     */

    /* Connect PHx pins to FMC Alternate function */
    GPIOH->AFR[0] = 0x00C00C00;
    GPIOH->AFR[1] = 0xCCCCCCCC;
    /* Configure PHx pins in Alternate function mode */
    GPIOH->MODER = 0xAAAAFBEF;
    /* Configure PHx pins speed to 100 MHz */
    GPIOH->OSPEEDR = 0xFFFF0C30;
    /* Configure PHx pins Output type to push-pull */
    GPIOH->OTYPER = 0x00000000;
    /* Configure PHx pins in Pull-up */
    GPIOH->PUPDR = 0x55550410;

    /** PIx pins used:
     * PI0 (FMC_D24)
     * PI1 (FMC_D25)
     * PI2 (FMC_D26)
     * PI3 (FMC_D27)
     * PI4 (FMC_NBL2)
     * PI5 (FMC_NBL3)
     * PI6 (FMC_D28)
     * PI7 (FMC_D29)
     * PI9 (FMC_D30)
     * PI10 (FMC_D31)
     */

    /* Connect PIx pins to FMC Alternate function */
    GPIOI->AFR[0] = 0xCCCCCCCC;
    GPIOI->AFR[1] = 0x00000CC0;
    /* Configure PIx pins in Alternate function mode */
    GPIOI->MODER = 0xFFEBAAAA;
    /* Configure PIx pins speed to 100 MHz */
    GPIOI->OSPEEDR = 0x003CFFFF;
    /* Configure PIx pins Output type to push-pull */
    GPIOI->OTYPER = 0x00000000;
    /* Configure PIx pins in Pull-up */
    GPIOI->PUPDR = 0x00145555;

    /*-- FMC Configuration ------------------------------------------------------*/
    /* Enable the FMC interface clock */
    (RCC->AHB3ENR |= (RCC_AHB3ENR_FMCEN));
    /*SDRAM Timing and access interface configuration*/
    /*LoadToActiveDelay  = 2
     ExitSelfRefreshDelay = 6
     SelfRefreshTime      = 4
     RowCycleDelay        = 6
     WriteRecoveryTime    = 2
     RPDelay              = 2
     RCDDelay             = 2
     SDBank             = FMC_SDRAM_BANK1
     ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_8
     RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_11
     MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_32
     InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4
     CASLatency         = FMC_SDRAM_CAS_LATENCY_2
     WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE
     SDClockPeriod      = FMC_SDRAM_CLOCK_PERIOD_2
     ReadBurst          = FMC_SDRAM_RBURST_ENABLE
     ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0*/

    /**
     * TODO - Fine-tune timing and FMC clock
     *
     * I was having issues when sourcing the FMC clock with a divider of 2.
     * I believe the input clock to the FMC is set to the CM7 core clock over 2,
     * so this divider would yield an SDRAM clock of 120MHz, which should be okay for
     * our memory chip.
     *
     * Changing the FMC divider input to 3 (the only other option) appears to work reliably
     * Theoretically this would mean the SDRAM clock is 80MHz...
     *
     * We may be able to do some additional testing and adjust the clock configuration
     * for the FMC source to achieve a maximum stable frequency (I'd say 100MHz maybe?)
     */

    FMC_Bank5_6_R->SDCR[0] = 0x00001D60; // Configure bank 5 (SDRAM 1)
    FMC_Bank5_6_R->SDCR[1] = 0x000002D0; // Disable bank 6 (SDRAM 2)

    /**
     * Timing parameters calculation
     * TRCD = 20ns = 3 clock cycles (20ns * 120MHz = 2.4 => 3 clock cycles)
     * TRP = 20ns = 3 clock cycles
     * TWR = 1CLK + 7ns = 2 clock cycles
     * TRC = 70ns = 8.4 => 9 clock cycles
     * TRAS = 42ns = 5.04 => 6 clock cycles
     * TXSR = 77ns = 9.24 => 10 clock cycles
     * TMRD = 2 cycles
     */

    FMC_Bank5_6_R->SDTR[0] = 0x02218591;
    FMC_Bank5_6_R->SDTR[1] = 0x0FFFFFFF;

    /* SDRAM initialization sequence */
    /* Clock enable command on bank 1 */
    FMC_Bank5_6_R->SDCMR = 0x00000011;

    /*
     * This apparently checks a flag called
     * FMC_SDSR_BUSY that is no longer documented in
     * the H7 manual for some reason???
     */
    tmpreg = FMC_Bank5_6_R->SDSR & 0x00000020;
    while ((tmpreg != 0) && (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6_R->SDSR & 0x00000020;
    }

    /* Delay */
    for (index = 0; index < 1000; index++)
        ;

    /* PALL command on bank 1 */
    FMC_Bank5_6_R->SDCMR = 0x000000012;
    timeout = 0xFFFF;
    while ((tmpreg != 0) && (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6_R->SDSR & 0x00000020;
    }

    /** Issue auto-refresh command w/ 8 auto-refresh cycles on bank 1 */
    FMC_Bank5_6_R->SDCMR = 0x000000F3;
    timeout = 0xFFFF;
    while ((tmpreg != 0) && (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6_R->SDSR & 0x00000020;
    }

    /** Issue load mode register command on bank 1
     * Mode register = 0x220
     * => Single-bit write, CAS Latency = 2, sequential bursts
     */
    FMC_Bank5_6_R->SDCMR = 0x00044014;
    timeout = 0xFFFF;
    while ((tmpreg != 0) && (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6_R->SDSR & 0x00000020;
    }

    /* Set refresh count
     * 64ms / 2048 rows = 31.25us
     * 31.25us * 120MHz = 3750 => subtract 100 for margin
     * = 3650 = 0xE42
     */
    tmpreg = FMC_Bank5_6_R->SDRTR;
//    FMC_Bank5_6_R->SDRTR = (tmpreg | (0x00000E42 << 1));
    FMC_Bank5_6_R->SDRTR = (tmpreg | (0x000001C0 << 1));


    /* Disable write protection */
    tmpreg = FMC_Bank5_6_R->SDCR[1];
    FMC_Bank5_6_R->SDCR[1] = (tmpreg & 0xFFFFFDFF);

    /*FMC controller Enable*/
    FMC_Bank1_R->BTCR[0] |= 0x80000000;

    // External SRAM should be ready to use!

    (void) (tmp);

}

