/*
 * app_init.c
 *
 *  Created on: Apr 20, 2020
 *      Author: gdbeckstein
 */

#include "ltdc_config.h"

// TODO - some preprocessor to remove this? Just in case the user wants to override
//#if APP_INIT

#if defined(CORE_CM7)

/**
 * Called right before main(), after all OS initialization has happened
 */
void mbed_main(void) {

    // Initialize LTDC display interface
    ltdc_init();
}

#endif
