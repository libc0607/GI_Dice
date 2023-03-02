#include "apa102.h"
#include "dice_misc.h"
#include "CH57x_common.h"

// 8 LEDs, 32-bits per LED, 32-bits start & end, 40*8bits total
__attribute__((aligned(4))) uint8_t apa102_buf[40] = {
        0x00, 0x00, 0x00, 0x00,
        0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00,
        0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00,
        0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00,
        0xE0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0xFF, 0xFF
};

void apa102_set_rgb(uint8_t led_num, uint8_t brightness, uint8_t r, uint8_t g, uint8_t b)
{
    if (led_num>7)
        return;
    apa102_buf[(led_num+1)*4] = 0xE0 | brightness;
    apa102_buf[((led_num+1)*4)+1] = b;
    apa102_buf[((led_num+1)*4)+2] = g;
    apa102_buf[((led_num+1)*4)+3] = r;
}

void apa102_set_rgb_all(uint8_t brightness, uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i=0; i<8; i++)
        apa102_set_rgb(i, brightness, r, g, b);
}

void apa102_set_color(uint8_t led_num, uint8_t brightness, uint32_t color)
{
    if (led_num>7)
        return;
    apa102_buf[(led_num+1)*4] = 0xE0 | brightness;
    apa102_buf[((led_num+1)*4)+1] = (uint8_t) (color & 0x000000ff);
    apa102_buf[((led_num+1)*4)+2] = (uint8_t) ((color & 0x0000ff00) >> 8);
    apa102_buf[((led_num+1)*4)+3] = (uint8_t) ((color & 0x00ff0000) >> 16);
}

void apa102_set_brightness_all(uint8_t brightness)
{
    for (uint8_t i=0; i<8; i++)
        apa102_buf[(i+1)*4] = 0xE0 | brightness;
}

void apa102_set_color_all(uint8_t brightness, uint32_t color)
{
    for (uint8_t i=0; i<8; i++)
        apa102_set_color(i, brightness, color);
}

void apa102_turn_off_all()
{
    for (uint8_t i=0; i<8; i++)
        apa102_set_rgb(i, 0, 0, 0, 0);
}

void apa102_update()
{
    //SPI0_MasterTrans(apa102_buf, sizeof(apa102_buf));
    SPI0_MasterDMATrans(apa102_buf, sizeof(apa102_buf));
}

void apa102_power_enable(int en)
{
    if (en == TRUE) {
        GPIOB_SetBits(PIN_LED_EN);
    } else if (en == FALSE){
        GPIOB_ResetBits(PIN_LED_EN);
    }
}

void apa102_spi0_init()
{
    GPIOA_ModeCfg(PIN_LED_CLK, GPIO_ModeOut_PP_5mA);
    GPIOA_ModeCfg(PIN_LED_DAT, GPIO_ModeOut_PP_5mA);
    GPIOA_SetBits(PIN_LED_DAT);
    GPIOA_SetBits(PIN_LED_CLK);
    SPI0_MasterDefInit();
    SPI0_DataMode(Mode3_HighBitINFront);
}
