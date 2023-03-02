#ifndef __LIS_GLUE_H__
#define __LIS_GLUE_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include "math.h" // see https://www.wch.cn/bbs/thread-91375-1.html

#define READ_TIMEOUT_MS 50

// see the comments at acce_get_8d()
// TO-DO: these args needs fine tuning
/*
#define LIS_8D_Z_ABS_THRESH_LOWER   500 // sin(30deg)*1000
#define LIS_8D_Z_ABS_THRESH_UPPER   643 // sin(40deg)*1000
#define LIS_8D_XY_ABS_THRESH_UPPER  866 // cos(30deg)*1000
#define LIS_8D_XY_ABS_THRESH_LOWER  766 // cos(40deg)*1000
#define LIS_8D_ZERO_ABS_THRESH      87  // sin(5deg )*1000
#define LIS_8D_GRAV_THRESH_UPPER    1025
#define LIS_8D_GRAV_THRESH_LOWER    975 // Gravitational acce. +-2.5%
*/

// debugging (wider range)
#define LIS_8D_Z_ABS_THRESH_LOWER   350 // sin(30deg)*1000
#define LIS_8D_Z_ABS_THRESH_UPPER   793 // sin(40deg)*1000
#define LIS_8D_XY_ABS_THRESH_UPPER  936 // cos(30deg)*1000
#define LIS_8D_XY_ABS_THRESH_LOWER  500 // cos(40deg)*1000
#define LIS_8D_ZERO_ABS_THRESH      200  // sin(5deg )*1000
#define LIS_8D_GRAV_THRESH_UPPER    1100
#define LIS_8D_GRAV_THRESH_LOWER    900 // Gravitational acce. +-2.5%

// orientation of the octahedron
typedef enum {
  LIS_8D_NOT_MATCH = 0,
  LIS_8D_A    = 1,  // z+, x+, y0, led7
  LIS_8D_B    = 2,  // z+, x-, y0, led5
  LIS_8D_C    = 3,  // z+, x0, y+, led4
  LIS_8D_D    = 4,  // z+, x0, y-, led6
  LIS_8D_E    = 5,  // z-, x+, y0, led0
  LIS_8D_F    = 6,  // z-, x-, y0, led2
  LIS_8D_G    = 7,  // z-, x0, y+, led3
  LIS_8D_H    = 8,  // z-, x0, y-, led1
} lis_dice_8d_t;

typedef enum {
  INT_NONE         = 0,
  INT_FREE_FALL    = 1,
  INT_DTAP_X       = 2,
  INT_DTAP_Y       = 3,
  INT_DTAP_Z       = 4,
} lis_dice_int1_event_t;

int acc_init();
void acc_low_power();
lis_dice_8d_t acce_get_8d();
lis_dice_int1_event_t acce_get_int_event();
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif
