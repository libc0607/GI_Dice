#include "lis2dw12_reg.h"
#include "lis2dw12_glue.h"
#include "i2c.h"
#include <stdio.h>

stmdev_ctx_t acc_ctx;
float acc_mg[3];
lis_dice_8d_t ori;

int acc_init()
{
    uint8_t whoami, rst;
    lis2dw12_reg_t int_route;

    acc_ctx.write_reg = platform_write;
    acc_ctx.read_reg = platform_read;
    acc_ctx.handle = NULL;

    lis2dw12_device_id_get(&acc_ctx, &whoami);
    if (whoami != LIS2DW12_ID) {
        return -1;
    }
    lis2dw12_reset_set(&acc_ctx, PROPERTY_ENABLE);
    do {
        lis2dw12_reset_get(&acc_ctx, &rst);
    } while (rst);

    acce_get_int_event();

    // basic settings
    lis2dw12_block_data_update_set(&acc_ctx, PROPERTY_ENABLE);
    lis2dw12_power_mode_set(&acc_ctx, LIS2DW12_CONT_LOW_PWR_LOW_NOISE_12bit);
    lis2dw12_data_rate_set(&acc_ctx, LIS2DW12_XL_ODR_200Hz);
    lis2dw12_full_scale_set(&acc_ctx, LIS2DW12_2g);

    // enable free-fall detection
    lis2dw12_ff_dur_set(&acc_ctx, 0x06);
    lis2dw12_ff_threshold_set(&acc_ctx, LIS2DW12_FF_TSH_10LSb_FS2g);

    // enable double tap detection
    lis2dw12_tap_detection_on_z_set(&acc_ctx, PROPERTY_ENABLE);
    lis2dw12_tap_detection_on_y_set(&acc_ctx, PROPERTY_ENABLE);
    lis2dw12_tap_detection_on_x_set(&acc_ctx, PROPERTY_ENABLE);
    lis2dw12_tap_threshold_x_set(&acc_ctx, 12);
    lis2dw12_tap_threshold_y_set(&acc_ctx, 12);
    lis2dw12_tap_threshold_z_set(&acc_ctx, 12);
    lis2dw12_tap_dur_set(&acc_ctx, 7);
    lis2dw12_tap_quiet_set(&acc_ctx, 3);
    lis2dw12_tap_shock_set(&acc_ctx, 3);
    lis2dw12_tap_mode_set(&acc_ctx, LIS2DW12_BOTH_SINGLE_DOUBLE);

    // pin int1 routing
    lis2dw12_pin_int1_route_get(&acc_ctx, &int_route.ctrl4_int1_pad_ctrl);
    //int_route.ctrl4_int1_pad_ctrl.int1_ff = PROPERTY_ENABLE;            // route free-fall interrupt to int1
    int_route.ctrl4_int1_pad_ctrl.int1_tap = PROPERTY_ENABLE;           // double tap to int1
    lis2dw12_pin_int1_route_set(&acc_ctx, &int_route.ctrl4_int1_pad_ctrl);
    //lis2dw12_int_notification_set(&acc_ctx, LIS2DW12_INT_LATCHED);

    return 0;
}

// it seems that there's no "sleep mode" in this acce.
// but a very low data rate can be set to reduce the current
void acc_low_power()
{
    lis2dw12_power_mode_set(&acc_ctx, LIS2DW12_CONT_LOW_PWR_LOW_NOISE_12bit);
    lis2dw12_data_rate_set(&acc_ctx, LIS2DW12_XL_ODR_1Hz6_LP_ONLY);
}

inline int num_is_in_range(int num, int lower, int upper)
{
    return ((num > lower) && (num < upper))? 1: 0;
}


/*
 * The function to determine which side of the dice is facing up
 *
 * About tuning
 * The reason for hard-coding parameters is to avoid using math.h,
 * But this RISC-V in CH57x has hardware mul&div, it should not be too slow
 *
 * So, for my hardware, when an octahedron faces down stationary,
 *   a. Judging if it's upper 4 sides or the lower 4 sides by the z-axis reading,
 *      and the reading should within a certain range which can be calculated. 8 -> 4
 *   b. An axis in x or y must be near 0, 4 -> 2
 *   c. The other axis must be a value within a certain range,
 *      the positive or negative value of this value is used to choose 2 -> 1
 * If none of these values falls within the preset range, it will not light up.
 * Anyway, in Genshin, it will only light up when it's stoped.
 *
 * First assume that the x-axis reading of the acceleration sensor is near 0,
 * the base of the isosceles triangle is 2a, the waist is sqrt(3)a,
 * the vertex angle is 2ж╚, and the gravitational acceleration is g;
 * we will get
 *   cos(ж╚) = sqrt(6)/3, sin(ж╚) = sqrt(3)/3
 *   and ж╚ is about 35.3бу
 * Ideally, when the octahedron is faced down and stationary,
 * The absolute value of its z-axis acce. should be
 *   abs(acce(z)) = g * sin(ж╚) = g * sqrt(3)/3
 * y-axis should be
 *   abs(acce(y)) = g * sin(ж╚) = g * sqrt(3)/3
 * Considering the manufacturing mismatches,
 * set the angle error range is +-5бу, the value of ж╚ is about 30бу~40бу
 * Then the z-axis should within [g*sin(30бу), g*sin(40бу)]
 * the y-axis should within [g*cos(40бу), g*cos(30бу)]
 */
lis_dice_8d_t acce_get_8d()
{
    uint8_t reg = 0;
    uint8_t i = 0;
    int32_t tmp = 0;
    lis_dice_8d_t ori = LIS_8D_NOT_MATCH;
    int16_t raw_acc[3];

    lis2dw12_flag_data_ready_get(&acc_ctx, &reg);
    while ((!reg) && i<READ_TIMEOUT_MS) {
        DelayMs(1);
        lis2dw12_flag_data_ready_get(&acc_ctx, &reg);
        i++;
    }
    if (!reg) {
        return ori;
    }

    memset(raw_acc, 0x00, 3 * sizeof(int16_t));
    lis2dw12_acceleration_raw_get(&acc_ctx, raw_acc);

    // range (-2000, +2000), unit: mg
    acc_mg[0] = lis2dw12_from_fs2_to_mg(raw_acc[0]);    // x
    acc_mg[1] = lis2dw12_from_fs2_to_mg(raw_acc[1]);    // y
    acc_mg[2] = lis2dw12_from_fs2_to_mg(raw_acc[2]);    // z

    // 1. check if abs(x+y+z) = g
    // it seems to be not necessary...?
    /*
    tmp = (acc_mg[0] * acc_mg[0]) + (acc_mg[1] * acc_mg[1]) + (acc_mg[2] * acc_mg[2]);
    if (!num_is_in_range(tmp, LIS_8D_GRAV_THRESH_UPPER*LIS_8D_GRAV_THRESH_UPPER,
                              LIS_8D_GRAV_THRESH_LOWER*LIS_8D_GRAV_THRESH_LOWER)) {
        return ori;
    }
*/
    // 2. check z abs
    if (num_is_in_range(acc_mg[2], LIS_8D_Z_ABS_THRESH_LOWER, LIS_8D_Z_ABS_THRESH_UPPER)) {
        // 2.1 z up
        if (num_is_in_range(acc_mg[1], (-1)*LIS_8D_ZERO_ABS_THRESH, LIS_8D_ZERO_ABS_THRESH)) {
            // 2.1.1 y zero
            if (num_is_in_range(acc_mg[0], LIS_8D_XY_ABS_THRESH_LOWER, LIS_8D_XY_ABS_THRESH_UPPER)) {
                // 2.1.1.1 x+
                ori = LIS_8D_A;
            } else if (num_is_in_range(acc_mg[0], (-1)*LIS_8D_XY_ABS_THRESH_UPPER, (-1)*LIS_8D_XY_ABS_THRESH_LOWER)) {
                // 2.1.1.2 x-
                ori = LIS_8D_B;
            }
        } else if (num_is_in_range(acc_mg[0], (-1)*LIS_8D_ZERO_ABS_THRESH, LIS_8D_ZERO_ABS_THRESH)) {
            // 2.1.2 x zero
            if (num_is_in_range(acc_mg[1], LIS_8D_XY_ABS_THRESH_LOWER, LIS_8D_XY_ABS_THRESH_UPPER)) {
                // 2.1.2.1 y+
                ori = LIS_8D_C;
            } else if (num_is_in_range(acc_mg[1], (-1)*LIS_8D_XY_ABS_THRESH_UPPER, (-1)*LIS_8D_XY_ABS_THRESH_LOWER)) {
                // 2.1.2.2 y-
                ori = LIS_8D_D;
            }
        }
    } else if (num_is_in_range(acc_mg[2], (-1)*LIS_8D_Z_ABS_THRESH_UPPER, (-1)*LIS_8D_Z_ABS_THRESH_LOWER)) {
        // 2.2 z down
        if (num_is_in_range(acc_mg[1], (-1)*LIS_8D_ZERO_ABS_THRESH, LIS_8D_ZERO_ABS_THRESH)) {
            // 2.2.1 y zero
            if (num_is_in_range(acc_mg[0], LIS_8D_XY_ABS_THRESH_LOWER, LIS_8D_XY_ABS_THRESH_UPPER)) {
                // 2.2.1.1 x+
                ori = LIS_8D_E;
            } else if (num_is_in_range(acc_mg[0], (-1)*LIS_8D_XY_ABS_THRESH_UPPER, (-1)*LIS_8D_XY_ABS_THRESH_LOWER)) {
                // 2.2.1.2 x-
                ori = LIS_8D_F;
            }
        } else if (num_is_in_range(acc_mg[0], (-1)*LIS_8D_ZERO_ABS_THRESH, LIS_8D_ZERO_ABS_THRESH)) {
            // 2.2.2 x zero
            if (num_is_in_range(acc_mg[1], LIS_8D_XY_ABS_THRESH_LOWER, LIS_8D_XY_ABS_THRESH_UPPER)) {
                // 2.2.2.1 y+
                ori = LIS_8D_G;
            } else if (num_is_in_range(acc_mg[1], (-1)*LIS_8D_XY_ABS_THRESH_UPPER, (-1)*LIS_8D_XY_ABS_THRESH_LOWER)) {
                // 2.2.2.2 y-
                ori = LIS_8D_H;
            }
        }
    }

    return ori;
}

lis_dice_int1_event_t acce_get_int_event()
{
    lis2dw12_all_sources_t src;

    lis2dw12_all_sources_get(&acc_ctx, &src);
    if (src.wake_up_src.ff_ia) {
        return INT_FREE_FALL;
    }
    if (src.tap_src.double_tap) {
        if (src.tap_src.x_tap) {
            return INT_DTAP_X;
        }
        if (src.tap_src.y_tap) {
            return INT_DTAP_Y;
        }
        if (src.tap_src.z_tap) {
            return INT_DTAP_Z;
        }
    }
    return INT_NONE;
}

// called by lis2dw12 driver provided by ST
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{
    if (!I2C_Start())
        return -1;

    I2C_SendByte(LIS2DW12_I2C_ADD_H & 0xFE);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return -1;
    }
    I2C_SendByte(reg);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return -1;
    }
    for (uint16_t i=0; i<len; i++) {
        I2C_SendByte(*(bufp+i));
        if (!I2C_WaitAck()) {
            I2C_Stop();
            return -1;
        }
    }
    I2C_Stop();
    return 0;
}

// called by lis2dw12 driver provided by ST
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
    if (!I2C_Start())
        return -1;

    I2C_SendByte(LIS2DW12_I2C_ADD_H & 0xFE);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return -1;
    }
    I2C_SendByte(reg);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return -1;
    }
    if (!I2C_Start())
        return -1;
    I2C_SendByte(LIS2DW12_I2C_ADD_H | 0x01);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return -1;
    }
    for (uint16_t i=0; i<len; i++) {
        *(bufp+i) = I2C_ReadByte();
        if (i == len-1) {
            I2C_NoAck();
        } else {
            I2C_Ack();
        }
    }
    I2C_Stop();
    return 0;
}

