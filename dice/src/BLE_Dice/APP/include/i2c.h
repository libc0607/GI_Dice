// From https://www.cnblogs.com/debugdabiaoge/p/15762304.html

#ifndef __I2C_SOFT2_H__
#define __I2C_SOFT2_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CH57x_common.h"
#include "dice_misc.h"

#ifndef UINT8
typedef unsigned char           u8;
#endif
#define I2C_Pin_SCL        PIN_I2C_SCL
#define I2C_Pin_SDA        PIN_I2C_SDA

#define SCL_H         GPIOB_SetBits( I2C_Pin_SCL )
#define SCL_L         GPIOB_ResetBits( I2C_Pin_SCL )
#define SDA_H         GPIOB_SetBits( I2C_Pin_SDA )
#define SDA_L         GPIOB_ResetBits( I2C_Pin_SDA )
#define SCL_read      GPIOB_ReadPortPin( I2C_Pin_SCL )
#define SDA_read      GPIOB_ReadPortPin( I2C_Pin_SDA )
#define SCL_out          GPIOB_ModeCfg(I2C_Pin_SCL, GPIO_ModeOut_PP_5mA)
#define SCL_in          GPIOB_ModeCfg(I2C_Pin_SCL, GPIO_ModeIN_PU)
#define SDA_out          GPIOB_ModeCfg(I2C_Pin_SDA, GPIO_ModeOut_PP_5mA)
#define SDA_in          GPIOB_ModeCfg(I2C_Pin_SDA, GPIO_ModeIN_PU)

void I2CInit(void);
void I2C_delay(void);
int I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
int I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte);
u8 I2C_ReadByte(void);

#ifdef __cplusplus
}
#endif

#endif
