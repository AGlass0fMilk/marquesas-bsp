/*
 * ltdc_config.c
 *
 *  Created on: Apr 16, 2020
 *      Author: gdbeckstein
 */

#include "ltdc_config.h"

#include "stm32h7xx.h"

LTDC_HandleTypeDef hltdc;

int ltdc_init(void) {

    /* USER CODE BEGIN LTDC_Init 0 */

    RCC_PeriphCLKInitTypeDef periph_clk_init_struct;
    /* LTDC Initialization -------------------------------------------------------*/

      /*## LTDC Clock Configuration ###########################################*/
      /* RK043FN48H LCD clock configuration */
      /* LCD clock configuration */
      /* PLL3_VCO Input = HSE_VALUE/PLL3M = 5 Mhz */
      /* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 800 Mhz */
      /* PLLLCDCLK = PLL3_VCO Output/PLL3R = 800/83 = 9.63 Mhz */
      /* LTDC clock frequency = PLLLCDCLK = 9.63 Mhz */
      periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
      periph_clk_init_struct.PLL3.PLL3M = 5;
      periph_clk_init_struct.PLL3.PLL3N = 160;
      periph_clk_init_struct.PLL3.PLL3FRACN = 0;
      periph_clk_init_struct.PLL3.PLL3P = 2;
      periph_clk_init_struct.PLL3.PLL3Q = 2;
      periph_clk_init_struct.PLL3.PLL3R = 40;
      HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);

      /* LTDC Initialization -------------------------------------------------------*/
      /* DeInit */
      HAL_LTDC_DeInit(&hltdc);


    /* USER CODE END LTDC_Init 0 */

    LTDC_LayerCfgTypeDef pLayerCfg = { 0 };
//    LTDC_LayerCfgTypeDef pLayerCfg1 = { 0 };

    /* USER CODE BEGIN LTDC_Init 1 */

    /* USER CODE END LTDC_Init 1 */
    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync = 9;
    hltdc.Init.VerticalSync = 3;
    hltdc.Init.AccumulatedHBP = 55;         // 46 HBP + 10 Sync = 56-1 = 55
    hltdc.Init.AccumulatedVBP = 26;         // 23 VBP + 4 sync = 27-1 = 26
    hltdc.Init.AccumulatedActiveW = 855;    // 56AHBP+800 pixels = 856-1 = 855
    hltdc.Init.AccumulatedActiveH = 506;    // 27AVBP+480 pixels = 507-1 = 506
    hltdc.Init.TotalWidth = 1055;           // 856 + 210 HFP = 1066-1 = 1055
    hltdc.Init.TotalHeigh = 528;            // 507 + 22 VFP = 529-1 = 528
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK) {
        // TODO - can we call mbed_error here?
        //Error_Handler();
    }
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = 800;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = 480;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    pLayerCfg.FBStartAdress = 0xC0000000;
    pLayerCfg.ImageWidth = 800;
    pLayerCfg.ImageHeight = 480;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK) {
        // TODO - can we call mbed_error here?
        //Error_Handler();
    }
//    pLayerCfg1.WindowX0 = 0;
//    pLayerCfg1.WindowX1 = 0;
//    pLayerCfg1.WindowY0 = 0;
//    pLayerCfg1.WindowY1 = 0;
//    pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
//    pLayerCfg1.Alpha = 0;
//    pLayerCfg1.Alpha0 = 0;
//    pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
//    pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
//    pLayerCfg1.FBStartAdress = 0;
//    pLayerCfg1.ImageWidth = 0;
//    pLayerCfg1.ImageHeight = 0;
//    pLayerCfg1.Backcolor.Blue = 0;
//    pLayerCfg1.Backcolor.Green = 0;
//    pLayerCfg1.Backcolor.Red = 0;
//    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK) {
//        // TODO - can we call mbed_error here?
//        //Error_Handler();
//    }
    /* USER CODE BEGIN LTDC_Init 2 */

    /* USER CODE END LTDC_Init 2 */

    return 0;
}

