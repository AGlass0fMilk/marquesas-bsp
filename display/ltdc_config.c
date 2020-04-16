/*
 * ltdc_config.c
 *
 *  Created on: Apr 16, 2020
 *      Author: gdbeckstein
 */

#include "ltdc_config.h"

#include "stm32h7xx.h"

int ltdc_init(void) {

    __IO uint32_t tmp = 0;

    /** Enable GPIOA, GPIOB, GPIOC, GPIOE,
     * GPIOF, GPIOG, GPIOH, GPIOI, GPIOJ, and
     * GPIOK interface clocks
     */
    RCC->AHB4ENR |= 0x7F7;
    /* Delay after an RCC peripheral clock enabling */
    tmp = READ_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOKEN);

    /**LTDC GPIO Configuration
     *
     PA1     ------> LTDC_R2
     PA3     ------> LTDC_B5
     PA4     ------> LTDC_VSYNC
     PA5     ------> LTDC_R4
     PA8     ------> LTDC_B3
     PA10     ------> LTDC_B1
     PB0     ------> LTDC_R3
     PB1     ------> LTDC_R6
     PB8     ------> LTDC_B6
     PB9     ------> LTDC_B7
     PC0     ------> LTDC_R5
     PC6     ------> LTDC_HSYNC
     PE4     ------> LTDC_B0
     PE5     ------> LTDC_G0
     PE6     ------> LTDC_G1
     PF10     ------> LTDC_DE
     PG7     ------> LTDC_CLK
     PG10     ------> LTDC_B2
     PG12     ------> LTDC_B4
     PH3     ------> LTDC_R1
     PH4     ------> LTDC_G5
     PI11     ------> LTDC_G6
     PI15     ------> LTDC_R0
     PJ6     ------> LTDC_R7
     PJ9     ------> LTDC_G2
     PJ10     ------> LTDC_G3
     PJ11     ------> LTDC_G4
     PK2     ------> LTDC_G7
     */

    /** PAx pins used:
     * PA1 (LTDC_R2)
     * PA3 (LTDC_B5)
     * PA4 (LTDC_VSYNC)
     * PA5 (LTDC_R4)
     * PA8 (LTDC_B3)
     * PA10 (LTDC_B1)
     */

    /** Connect PAx pins to LTDC Alternate function */
    GPIOA->AFR[0] = 0x00000000;


    return 0;
}

