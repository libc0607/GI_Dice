#ifndef __APA102_H__
#define __APA102_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "dice_misc.h"
#include "CH57x_common.h"
#include <stdint.h>

void apa102_set_rgb(uint8_t led_num, uint8_t brightness, uint8_t r, uint8_t g, uint8_t b);
void apa102_set_color(uint8_t led_num, uint8_t brightness, uint32_t color);
void apa102_set_rgb_all(uint8_t brightness, uint8_t r, uint8_t g, uint8_t b);
void apa102_set_color_all(uint8_t brightness, uint32_t color);
void apa102_turn_off_all();
void apa102_update();
void apa102_power_enable(int en);
void apa102_spi0_init();
void apa102_set_brightness_all(uint8_t brightness);

#ifdef __cplusplus
}
#endif

#endif
