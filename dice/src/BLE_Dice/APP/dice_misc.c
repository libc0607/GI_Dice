// bug:
// I've copied get_internal_temperature() directly from CH573EVT(V2.2)/ADC,
// but it'll output ~610 at my room temperature
// and, the example in EVT running on EVB gives that output too
// obviously it's a bug and I don't know why, the datasheet either
// however i'll keep it in ble report msg

#include "dice_misc.h"
#include "lis2dw12_glue.h"
#include "apa102.h"
#include "CH57x_common.h"
#include "peripheral.h"
#include "CH57xBLE_LIB.h"
#include "app_drv_fifo.h"


lis_dice_8d_t dice_ori_seq[DICE_ORI_SEQ_LEN] = {LIS_8D_NOT_MATCH};
uint8_t dice_ori_seq_p = 0;
int omni_h;
uint8_t dice_ble_report_msg[BLE_MSG_MAX_LEN] = {0};
signed short RoughCalib_Value = 0;

extern app_drv_fifo_t app_uart_rx_fifo;
extern app_drv_fifo_t app_uart_tx_fifo;
extern float acc_mg[3];
extern lis_dice_8d_t ori;
lis_dice_8d_t last_ori;
extern uint8 Peripheral_TaskID;

void dice_update_advert_data();

uint8_t dice_task_id = 0;

void dice_ori_push(lis_dice_8d_t d)
{
    dice_ori_seq[dice_ori_seq_p++] = d;
    dice_ori_seq_p = (dice_ori_seq_p >= DICE_ORI_SEQ_LEN)? 0: dice_ori_seq_p;
}

lis_dice_8d_t dice_ori_seq_stable()
{
    for (int i=0; i<DICE_ORI_SEQ_LEN-2; i++) {
        if ((dice_ori_seq[i] == LIS_8D_NOT_MATCH) || (dice_ori_seq[i] != dice_ori_seq[i+1])) {
            return LIS_8D_NOT_MATCH;
        }
    }
    return dice_ori_seq[0];
}

/*
int dice_ori_all_not_match()
{
    for (int i=0; i<DICE_ORI_SEQ_LEN-1; i++)
        if (dice_ori_seq[i] != LIS_8D_NOT_MATCH)
            return 0;
    return 1;
}
*/

void dice_set_led_by_ori(lis_dice_8d_t ori)
{
    apa102_turn_off_all();
    omni_h = 0;
    switch (ori) {
        case LIS_8D_A: apa102_set_color(LED_8D_A_INDEX, LED_DISP_BRIGHTNESS_DEFAULT_L, LED_8D_A_COLOR); break;
        case LIS_8D_B: apa102_set_color(LED_8D_B_INDEX, LED_DISP_BRIGHTNESS_DEFAULT_L, LED_8D_B_COLOR); break;
        case LIS_8D_C: apa102_set_color(LED_8D_C_INDEX, LED_DISP_BRIGHTNESS_DEFAULT_L, LED_8D_C_COLOR); break;
        case LIS_8D_D: apa102_set_color(LED_8D_D_INDEX, LED_DISP_BRIGHTNESS_DEFAULT_L, LED_8D_D_COLOR); break;
        case LIS_8D_E: apa102_set_color(LED_8D_E_INDEX, LED_DISP_BRIGHTNESS_DEFAULT_L, LED_8D_E_COLOR); break;
        case LIS_8D_F: apa102_set_color(LED_8D_F_INDEX, LED_DISP_BRIGHTNESS_DEFAULT_L, LED_8D_F_COLOR); break;
        case LIS_8D_G: apa102_set_color(LED_8D_G_INDEX, LED_DISP_BRIGHTNESS_DEFAULT_L, LED_8D_G_COLOR); break;
        case LIS_8D_H: apa102_set_color(LED_8D_H_INDEX, LED_DISP_BRIGHTNESS_DEFAULT_L, LED_8D_H_COLOR); break;
        case LIS_8D_NOT_MATCH: break;
        default: break;
    }
}

uint16_t dice_gen_ble_report_msg()
{
    return sprintf(dice_ble_report_msg, "#%d,%d,%d,%d,%d,%d\r\n",
            get_battery_voltage_mv(),
            get_internal_temperature(),
            ori, (int)acc_mg[0], (int)acc_mg[1], (int)acc_mg[2]);
}

tmosEvents dice_ProcessEvent(tmosTaskID task_id, tmosEvents events)
{
    uint8 *msgPtr;
    uint16_t ble_msg_len;
    uint32_t omni_color;
    uint8_t uart_buf;
    int bat_mv;

    if (events & SYS_EVENT_MSG) {
        msgPtr = tmos_msg_receive(task_id);
        if (msgPtr) {
            tmos_msg_deallocate(msgPtr);
        }
        return events ^ SYS_EVENT_MSG;
    }

    // event 1: update omni led color
    if (events & DICE_EVENT_OMNI_LED_UPDATE) {
        if (ori == LED_OMNI_ORI) {
            apa102_power_enable(TRUE);
            omni_color = omni_rgb(omni_h, LED_OMNI_S, LED_OMNI_V);
            omni_h += LED_OMNI_STEP;
            apa102_turn_off_all();
            apa102_set_color(LED_OMNI_ID, LED_DISP_BRIGHTNESS_DEFAULT_L, omni_color);
            apa102_update();
        }
        tmos_start_task(dice_task_id, DICE_EVENT_OMNI_LED_UPDATE, OMNI_LED_UPDATE_PERIOD_TICKS);
        return events ^ DICE_EVENT_OMNI_LED_UPDATE;
    }

    // event 2: check orientation, set led
    if (events & DICE_EVENT_ACCE_UPDATE) {
        dice_ori_push(acce_get_8d());
        last_ori = ori;
        ori = dice_ori_seq_stable();
        if (ori != LIS_8D_NOT_MATCH && ori!= LED_OMNI_ORI) {
            apa102_power_enable(TRUE);
            apa102_turn_off_all();
            dice_set_led_by_ori(ori);
            apa102_update();
        //} else if (dice_ori_all_not_match()) {
        } else if (ori == LIS_8D_NOT_MATCH) {
            apa102_turn_off_all();
            apa102_update();
            apa102_power_enable(FALSE);
        }
        // idle state detector
        if (last_ori != ori) {
            tmos_stop_task(dice_task_id, DICE_EVENT_AUTO_POWEROFF);
            tmos_start_task(dice_task_id, DICE_EVENT_AUTO_POWEROFF, AUTO_POWEROFF_TICKS);
        }

        tmos_start_task(dice_task_id, DICE_EVENT_ACCE_UPDATE, ACCE_UPDATE_PERIOD_TICKS);
        return events ^ DICE_EVENT_ACCE_UPDATE;
    }

    // event 4: update advert data, send debug msg via vuart
    if (events & DICE_EVENT_BLE_REPORT) {

        // vuart->ble
        ble_msg_len = dice_gen_ble_report_msg();
        app_drv_fifo_write(&app_uart_rx_fifo, dice_ble_report_msg, &ble_msg_len);
        tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);

        // update advert data
        dice_update_advert_data();

        // restart task
        tmos_start_task(dice_task_id, DICE_EVENT_BLE_REPORT, BLE_REPORT_PERIOD_TICKS);
        return events ^ DICE_EVENT_BLE_REPORT;
    }

    // when DICE_EVENT_FIND_DICE_ON, ACCE_UPDATE and OMNI_LED_UPDATE will be disabled,
    // turn all leds on for ~1s(FIND_DICE_ON_PERIOD_TICKS) to find the specific dice;
    // after FIND_DICE_ON_PERIOD_TICKS, event DICE_EVENT_FIND_DICE_OFF turns off the leds
    // then restart ACCE_UPDATE and OMNI_LED_UPDATE

    // event 5: find dice on, recv msg from vuart
    if (events & DICE_EVENT_FIND_DICE_ON) {
        // ble->vuart
        ble_msg_len = sizeof(uart_buf);
        // thanks to tmos, the fifo is safe now; just read out all chars
        while (app_drv_fifo_is_empty(&app_uart_tx_fifo) == FALSE) {
            if (APP_DRV_FIFO_RESULT_SUCCESS != app_drv_fifo_read(&app_uart_tx_fifo, &uart_buf, &ble_msg_len)) {
                break;
            }
            if (uart_buf != FIND_DICE_CHAR) {
                break;
            }
            // if we get FIND_DICE_CHAR; stop update, turn all leds on
            // then start "find_dice_off" task as led delay
            apa102_power_enable(TRUE);
            tmos_stop_task(dice_task_id, DICE_EVENT_ACCE_UPDATE);
            tmos_stop_task(dice_task_id, DICE_EVENT_OMNI_LED_UPDATE);
            tmos_start_task(dice_task_id, DICE_EVENT_FIND_DICE_OFF, FIND_DICE_ON_PERIOD_TICKS);
            DelayMs(2); // for apa102 power stable
            apa102_set_color_all(LED_LOW, COLOR_WHITE);
            apa102_update();
            return events ^ DICE_EVENT_FIND_DICE_ON;
        }
        tmos_start_task(dice_task_id, DICE_EVENT_FIND_DICE_ON, FIND_DICE_PERIOD_TICKS);
        return events ^ DICE_EVENT_FIND_DICE_ON;
    }

    // event 6: find dice off, recv msg from vuart
    if (events & DICE_EVENT_FIND_DICE_OFF) {
        // turn off leds
        apa102_set_color_all(LED_LOW, COLOR_BLACK);
        apa102_update();
        apa102_power_enable(FALSE);
        app_drv_fifo_flush(&app_uart_tx_fifo);
        // start "find_dice_off" task
        tmos_start_task(dice_task_id, DICE_EVENT_ACCE_UPDATE, ACCE_UPDATE_PERIOD_TICKS);
        tmos_start_task(dice_task_id, DICE_EVENT_OMNI_LED_UPDATE, ACCE_UPDATE_PERIOD_TICKS+OMNI_LED_UPDATE_PERIOD_TICKS);
        tmos_start_task(dice_task_id, DICE_EVENT_FIND_DICE_ON, FIND_DICE_PERIOD_TICKS);
        return events ^ DICE_EVENT_FIND_DICE_OFF;
    }

    // event 7: check battery voltage start
    if (events & DICE_EVENT_BAT_STAT_START) {
        bat_mv = get_battery_voltage_mv();
        if (bat_mv < BAT_WARN_MV) {
            apa102_power_enable(TRUE);
            tmos_stop_task(dice_task_id, DICE_EVENT_ACCE_UPDATE);
            tmos_stop_task(dice_task_id, DICE_EVENT_OMNI_LED_UPDATE);
            tmos_start_task(dice_task_id, DICE_EVENT_BAT_STAT_END, BAT_STAT_PERIOD_TICKS);
            apa102_set_color_all(LED_LOW, get_led_color_by_battery(bat_mv));
            apa102_update();
        }
        return events ^ DICE_EVENT_BAT_STAT_START;
    }

    // event 8: check battery voltage end
    if (events & DICE_EVENT_BAT_STAT_END) {
        bat_mv = get_battery_voltage_mv();
        apa102_power_enable(FALSE);
        if (bat_mv < BAT_HALT_MV) {
            acc_low_power();
            DelayMs(1);
            pin_init_sleep();
            DelayMs(2);
            LowPower_Shutdown(0);
        } else {
            tmos_start_task(dice_task_id, DICE_EVENT_ACCE_UPDATE, ACCE_UPDATE_PERIOD_TICKS);
            tmos_start_task(dice_task_id, DICE_EVENT_OMNI_LED_UPDATE, ACCE_UPDATE_PERIOD_TICKS+OMNI_LED_UPDATE_PERIOD_TICKS);
            tmos_start_task(dice_task_id, DICE_EVENT_BAT_STAT_START, CHECK_BAT_PERIOD_TICKS);
            apa102_turn_off_all();
        }
        return events ^ DICE_EVENT_BAT_STAT_END;
    }

    // event 9: after idle (ori. not change) for AUTO_POWEROFF_TICKS, go sleep to save battery
    if (events & DICE_EVENT_AUTO_POWEROFF) {
        apa102_power_enable(FALSE);
        acc_low_power();
        DelayMs(1);
        pin_init_sleep();
        DelayMs(1);
        LowPower_Shutdown(0);
        return events ^ DICE_EVENT_AUTO_POWEROFF;
    }

    return 0;
}

void dice_process_init()
{
    dice_task_id = TMOS_ProcessEventRegister(dice_ProcessEvent);
    tmos_start_task(dice_task_id, DICE_EVENT_ACCE_UPDATE, ACCE_UPDATE_PERIOD_TICKS);
    tmos_start_task(dice_task_id, DICE_EVENT_BLE_REPORT, BLE_REPORT_PERIOD_TICKS);
    tmos_start_task(dice_task_id, DICE_EVENT_FIND_DICE_ON, FIND_DICE_PERIOD_TICKS);
    tmos_start_task(dice_task_id, DICE_EVENT_OMNI_LED_UPDATE, ACCE_UPDATE_PERIOD_TICKS+OMNI_LED_UPDATE_PERIOD_TICKS);
    tmos_start_task(dice_task_id, DICE_EVENT_BAT_STAT_START, CHECK_BAT_PERIOD_TICKS);
    tmos_start_task(dice_task_id, DICE_EVENT_AUTO_POWEROFF, AUTO_POWEROFF_TICKS);
}

void pin_init()
{
    GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(PIN_BAT_ADC, GPIO_ModeIN_Floating);   // battery adc input
    GPIOA_ModeCfg(PIN_ACC_INT, GPIO_ModeIN_Floating);    // acce int1 (push-pulled by acce)
    GPIOB_ModeCfg(PIN_LED_EN, GPIO_ModeOut_PP_5mA);     // led power enable
    GPIOB_ModeCfg(PIN_I2C_SDA, GPIO_ModeIN_PU);         // i2c sda
    GPIOB_ModeCfg(PIN_I2C_SCL, GPIO_ModeOut_PP_5mA);    // i2c scl

    // debug uart
    GPIOB_SetBits(PIN_UART_TX);
    GPIOB_ModeCfg(PIN_UART_RX, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(PIN_UART_TX, GPIO_ModeOut_PP_5mA);
    UART0_DefInit();

    dice_ori_seq_p = 0;
}

void pin_init_sleep()
{
    GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(PIN_BAT_ADC, GPIO_ModeIN_Floating);   // battery adc input
    GPIOA_ModeCfg(PIN_LED_DAT | PIN_LED_CLK, GPIO_ModeIN_Floating); // led_clk & led_dat
    GPIOB_ModeCfg(PIN_LED_EN, GPIO_ModeOut_PP_5mA);         // led power enable
    GPIOB_ModeCfg(PIN_I2C_SDA, GPIO_ModeIN_Floating);       // i2c sda
    GPIOB_ModeCfg(PIN_I2C_SCL, GPIO_ModeIN_Floating);       // i2c scl
    GPIOB_ModeCfg(PIN_UART_RX, GPIO_ModeIN_Floating);
    GPIOB_ModeCfg(PIN_UART_TX, GPIO_ModeIN_Floating);

    //GPIOA_ModeCfg(PIN_ACC_INT, GPIO_ModeIN_Floating);        // acce int1 (push-pulled by acce)
    //GPIOA_ITModeCfg(PIN_ACC_INT, GPIO_ITMode_RiseEdge); // int rising
    //PFIC_EnableIRQ(GPIO_A_IRQn);
    //PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_GPIO_WAKE, Edge_LongDelay);
}

int get_internal_temperature()
{
    uint16_t buf = 0;

    ADC_InterTSSampInit();
    for (uint8_t i=0; i<8; i++) {
        buf += ADC_ExcutSingleConver();
    }

    return adc_to_temperature_celsius(buf/8);
}

int get_battery_voltage_mv()
{

    uint32_t adc_result = 0;

    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_1_2); // buf_en is set here

    // cal using ch7
    ADC_ChannelCfg(7);
    RoughCalib_Value = ADC_DataCalib_Rough();

    ADC_ChannelCfg(BAT_ADC_CHN);
    for (uint8_t i=0; i<8; i++) {
        adc_result = adc_result + ADC_ExcutSingleConver() + RoughCalib_Value;
    }

    return (int)((((adc_result/8)-1024)*1050)/512);
}

uint32_t get_led_color_by_battery(int bat_mv)
{
    if (bat_mv > BAT_FULL_MV)
        return COLOR_BLUE;
    else if (bat_mv > BAT_GOOD_MV)
        return COLOR_GREEN;
    else if (bat_mv > BAT_HALF_MV)
            return COLOR_YELLOW;
    else if (bat_mv > BAT_WARN_MV)
            return COLOR_ORANGE;
    else //if (bat_mv ~ BAT_HALT_MV)
        return COLOR_RED;
}

/*
 * A rough Omni Element color generator with very low performance
 * Actually it's a conversion from HSV color space to RGB
 * I'm lazy to rewrite it using fixed-point, but it's still faster than refreshing the screen on my Vision XD
 *
 * Parameter: h: random (int), s: 0~255, v: 0~255
 * s and v should be constant, then pass in continuously changing (++ or --) h to get different colors
 * For the effect in the gameplay, you should give a lower s and high v to get close to white light,
 * but if you adjust too much it is harder to see the effect
 */
uint32_t omni_rgb(int h, uint8_t s, uint8_t v)
{
    float C, X, Y, Z, H, S, V, R, G, B;
    int i;
    uint8_t r, g, b;

    h = (h > 0)? (h % 360): (((-1)*h) % 360);
    H = (float)h/60.0f;
    i = (int)H;
    C = H - i;
    V = (float)(v)/255;
    S = (float)(s)/255;
    X = V * (1 - S);
    Y = V * (1 - S * C);
    Z = V * (1 - S * (1 - C));
    switch (i) {
        case 0: R = V; G = Z; B = X; break;
        case 1: R = Y; G = V; B = X; break;
        case 2: R = X; G = V; B = Z; break;
        case 3: R = X; G = Y; B = V; break;
        case 4: R = Z; G = X; B = V; break;
        case 5: R = V; G = X; B = Y; break;
    }
    r = (R*255>255)? 255: ((R*255<0)? 0: R*255);
    g = (G*255>255)? 255: ((G*255<0)? 0: G*255);
    b = (B*255>255)? 255: ((B*255<0)? 0: B*255);

    return (uint32_t) ((r<<16) | (g<<8) | b);
}

