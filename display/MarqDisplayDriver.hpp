/*
 * MarqDisplayDriver.hpp
 *
 *  Created on: Apr 20, 2020
 *      Author: gdbeckstein
 */

#ifndef MARQUESAS_BSP_DISPLAY_MARQDISPLAYDRIVER_HPP_
#define MARQUESAS_BSP_DISPLAY_MARQDISPLAYDRIVER_HPP_

/**
 * Only enabled if mbed-lvgl is present
 * The below macro should only be non-zero if LVGL is present and enabled
 */
#if LV_COLOR_DEPTH

#include "LVGLDisplayDriver.h"

class MarqDisplayDriver : public LVGLDisplayDriver
{
public:

    friend class LittlevGL;

    MarqDisplayDriver(mbed::Span<lv_color_t> primary_display_buffer = mbed::Span<lv_color_t, 0>(),
                mbed::Span<lv_color_t> secondary_display_buffer = mbed::Span<lv_color_t, 0>()) :
                    LVGLDisplayDriver(primary_display_buffer, secondary_display_buffer) {
    }

    virtual ~MarqDisplayDriver() {
    }

    /*
     * @brief Flush the content of the internal buffer to the specific area on the display
     * You can use DMA or any hardware acceleration to do this operation in the background but
     * this function must block the caller until the transfer is complete!
     */
    virtual void flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
    }
};


#endif



#endif /* MARQUESAS_BSP_DISPLAY_MARQDISPLAYDRIVER_HPP_ */
