/*
 * Genshin Impact Genius Invokation Element Dice
 *
 * HW Version: V1.2
 * Github: https://github.com/libc0607/GI_Dice
 *
 * Ref: CH573EVT V2.2, BLE_UART demo
 */

#include "CONFIG.h"
#include "HAL.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "dice_misc.h"
#include "lis2dw12_glue.h"
#include "apa102.h"

__attribute__((aligned(4))) u32 MEM_BUF[BLE_MEMHEAP_SIZE / 4];
extern void app_uart_init(void);

__attribute__((section(".highcode")))
__attribute__((noinline))
void Main_Circulation()
{
    while(1)
        TMOS_SystemProcess();
}

/*
__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode")))
void GPIOA_IRQHandler(void)
{
    GPIOA_ClearITFlagBit(PIN_ACC_INT);
}
*/

int main(void)
{
    int bat_mv;
    uint32_t color_bat;

    PWR_DCDCCfg(ENABLE);
    SetSysClock(FREQ_SOURCE);

    pin_init();
    UART0_DefInit();
    PRINT("%s\n", VER_LIB);
    acc_init();
    apa102_spi0_init();
    apa102_power_enable(TRUE);

    // blinky battery indicator
    bat_mv = get_battery_voltage_mv();
    color_bat = get_led_color_by_battery(bat_mv);
    apa102_turn_off_all(); apa102_set_color_all(LED_STAT_BRIGHTNESS_DEFAULT, color_bat); apa102_update(); DelayMs(BOOT_BLINK_INTERVAL);
    apa102_turn_off_all(); apa102_update(); DelayMs(BOOT_BLINK_INTERVAL);
    apa102_turn_off_all(); apa102_set_color_all(LED_STAT_BRIGHTNESS_DEFAULT, color_bat); apa102_update(); DelayMs(BOOT_BLINK_INTERVAL);
    apa102_turn_off_all(); apa102_update(); DelayMs(BOOT_BLINK_INTERVAL);
    apa102_turn_off_all(); apa102_set_color_all(LED_STAT_BRIGHTNESS_DEFAULT, color_bat); apa102_update(); DelayMs(BOOT_BLINK_INTERVAL);
    apa102_turn_off_all(); apa102_update();
    apa102_power_enable(FALSE);

    if (bat_mv < BAT_HALT_MV) {
        acc_low_power();
        DelayMs(1);
        pin_init_sleep();
        DelayMs(2);
        LowPower_Shutdown(0);
    }

    CH57X_BLEInit();
    HAL_Init();
    GAPRole_PeripheralInit();
    Peripheral_Init();
    app_uart_init();
    dice_process_init();

    Main_Circulation();
}
