/*
 * ltdc_config.h
 *
 *  Created on: Apr 16, 2020
 *      Author: gdbeckstein
 */

#ifndef MARQUESAS_BSP_DISPLAY_LTDC_CONFIG_H_
#define MARQUESAS_BSP_DISPLAY_LTDC_CONFIG_H_

/**
 * Initialize the LTDC peripheral to interface to the connected display over
 * 24-bit RGB parallel interface
 *
 * @retval 0 on success
 */
int ltdc_init(void);

// TODO - provide access to LTDC instance handle?



#endif /* MARQUESAS_BSP_DISPLAY_LTDC_CONFIG_H_ */
