#ifndef __DICE_MISC_H__
#define __DICE_MISC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "lis2dw12_glue.h"
#include "CH57xBLE_LIB.h"

#define PIN_LED_EN  GPIO_Pin_23
#define PIN_LED_DAT GPIO_Pin_14
#define PIN_LED_CLK GPIO_Pin_13
#define PIN_BAT_ADC GPIO_Pin_15
#define BAT_ADC_CHN CH_EXTIN_5
#define PIN_ACC_INT GPIO_Pin_9
#define PIN_I2C_SCL GPIO_Pin_13
#define PIN_I2C_SDA GPIO_Pin_12

// Debug UART0£¬set at Properties - C/C++ General - Symbols - #DEBUG
#define PIN_UART_TX GPIO_Pin_7  // pb7
#define PIN_UART_RX GPIO_Pin_4  // pb4

//The buffer length should be a power of 2
#define APP_UART_TX_BUFFER_LENGTH    128U
#define APP_UART_RX_BUFFER_LENGTH    128U

// mod ch57x_common.h also
#define FREQ_SYS        24000000
#define FREQ_SOURCE     CLK_SOURCE_PLL_24MHz

#define BAT_HALT_MV     3300
#define BAT_WARN_MV     3500
#define BAT_HALF_MV     3800
#define BAT_GOOD_MV     3950
#define BAT_FULL_MV     4150

#define BOOT_BLINK_INTERVAL  200

#define LED_STAT_BRIGHTNESS_DEFAULT LED_VERY_LOW   // 0~31
#define LED_DISP_BRIGHTNESS_DEFAULT_L LED_VERY_LOW  // 0~31
#define LED_DISP_BRIGHTNESS_DEFAULT_H LED_VERY_LOW  // 0~31
#define LED_VERY_LOW    1
#define LED_LOW         3
#define LED_MEDIUM      7
#define LED_HIGH        15
#define LED_PRO         23
#define LED_PRO_MAX     31

#define COLOR_RED       0xff0000
#define COLOR_GREEN     0x00ff00
#define COLOR_BLUE      0x0000ff
#define COLOR_ORANGE    0xff7500
#define COLOR_YELLOW    0xfff143
#define COLOR_WHITE     0xffffff
#define COLOR_BLACK     0x000000
#define COLOR_DENDRO    0x11ff00    // No exact comparison, just an estimate
#define COLOR_ANEMO     0x00ffee
#define COLOR_HYDRO     0x0022ff
#define COLOR_PYRO      0xff0707
#define COLOR_ELECTRO   0x9900cc
#define COLOR_GEO       0xFF9900
#define COLOR_CYRO      0xccffff
#define COLOR_OMNI      0xffffff

// from lis_8d to led index
#define LED_8D_A_INDEX  7
#define LED_8D_B_INDEX  5
#define LED_8D_C_INDEX  4
#define LED_8D_D_INDEX  6
#define LED_8D_E_INDEX  0
#define LED_8D_F_INDEX  2
#define LED_8D_G_INDEX  3
#define LED_8D_H_INDEX  1

// These need to be adjusted according to the actual hardware
#define LED_OMNI_ID        LED_8D_D_INDEX
#define LED_OMNI_ORI       LIS_8D_D
#define LED_OMNI_S         120
#define LED_OMNI_V         120
#define LED_OMNI_STEP      2
#define LED_8D_A_COLOR     COLOR_CYRO
#define LED_8D_B_COLOR     COLOR_ANEMO
#define LED_8D_C_COLOR     COLOR_HYDRO
#define LED_8D_D_COLOR     COLOR_BLACK  // omni
#define LED_8D_E_COLOR     COLOR_GEO
#define LED_8D_F_COLOR     COLOR_PYRO
#define LED_8D_G_COLOR     COLOR_ELECTRO
#define LED_8D_H_COLOR     COLOR_DENDRO

// note: temperature threshold not used, see dice_misc.c
#define TEMPERATURE_HIGH    65

// A human-readable ble report msg and here's the buffer length
// "#", bat_mv, temp(bug), ori, acc_x, acc_y, acc_z, \r\n
// "#3900,40,8,-1000,-1999,-1111\r\n"
#define BLE_MSG_MAX_LEN 32

// broadcaster
#define ADVERT_DATA_LEN     13
#define ADVERT_BAT_OFFSET   ((ADVERT_DATA_LEN)-2)
#define ADVERT_ORI_OFFSET   ((ADVERT_DATA_LEN)-1)
//#define SCANRSP_DATA_LEN     13
#define SCANRSP_DATA_LEN     19
#define SCANRSP_BAT_OFFSET   ((SCANRSP_DATA_LEN)-2)
#define SCANRSP_ORI_OFFSET   ((SCANRSP_DATA_LEN)-1)


// when got same last N orientation, we assume it's stable
// it acts like a low-pass filter
#define DICE_ORI_SEQ_LEN    8

// dice events
#define DICE_EVENT_ACCE_UPDATE      0x0001
#define DICE_EVENT_OMNI_LED_UPDATE  0x0002
#define DICE_EVENT_BLE_REPORT       0x0004
#define DICE_EVENT_FIND_DICE_ON     0x0008
#define DICE_EVENT_FIND_DICE_OFF    0x0010
#define DICE_EVENT_BAT_STAT_START   0x0020
#define DICE_EVENT_BAT_STAT_END     0x0040
#define DICE_EVENT_AUTO_POWEROFF    0x0080

// dice event period, *625us
#define ACCE_UPDATE_PERIOD_TICKS 160    // ~100ms
#define OMNI_LED_UPDATE_PERIOD_TICKS 26 // ~16ms (60fps)
#define BLE_REPORT_PERIOD_TICKS 400     // ~250ms
#define FIND_DICE_PERIOD_TICKS 400     // ~250ms
#define FIND_DICE_ON_PERIOD_TICKS 1600     // ~1000ms
#define CHECK_BAT_PERIOD_TICKS    16000      // ~10000ms
#define BAT_STAT_PERIOD_TICKS       800     // ~500ms
#define AUTO_POWEROFF_TICKS         (1600*600)  // default: halt after idle for 10min

#define FIND_DICE_CHAR  'F'

void pin_init_sleep();
void pin_init();
int get_internal_temperature();
int get_battery_voltage_mv();
lis_dice_8d_t dice_ori_seq_stable();
void dice_ori_push(lis_dice_8d_t d);
uint32_t omni_rgb(int h, uint8_t s, uint8_t v);
tmosEvents dice_ProcessEvent(tmosTaskID task_id, tmosEvents events);
void dice_process_init();
uint32_t get_led_color_by_battery(int bat_mv);
int dice_ori_all_not_match();
void dice_update_advert_data();

#ifdef __cplusplus
}
#endif

#endif
