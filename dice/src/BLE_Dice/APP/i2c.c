/*
 * Since CH573F does not support hardware I2C, we simulate it here
 * if u r using CH582F, u can change it to hardware i2c
 * this file is from https://www.cnblogs.com/debugdabiaoge/p/15762304.html
 */

#include "i2c.h"

inline void I2CInit(void)
{
    SCL_out;
    SDA_out;
}

inline void I2C_delay(void)
{
   DelayUs(2);
}

inline int I2C_Start(void)
{
    SDA_H;
    SDA_out;
    SCL_H;
    I2C_delay();
    if (!SDA_read)
        return 0;
    SDA_L;
    I2C_delay();
    if (SDA_read)
        return 0;
    SDA_L;
    I2C_delay();
    return 1;
}

inline void I2C_Stop(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    SDA_out;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_H;
    I2C_delay();
}

inline void I2C_Ack(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    SDA_out;
    I2C_delay();
    SCL_H;
    I2C_delay();
    I2C_delay();
    SCL_L;
    I2C_delay();
}

inline void I2C_NoAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    SDA_out;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

// ret: 1 - ACK, 0 - no ACK
inline int I2C_WaitAck(void)
{
    SCL_L;
    I2C_delay();
    I2C_delay();
    SCL_H;
    SDA_in;
    I2C_delay();
    I2C_delay();
    if(SDA_read) {
        SCL_L;
        return 0;
    }
    SCL_L;
    return 1;
}

// MSB First
inline void I2C_SendByte(u8 SendByte)
{
    u8 i=8;
    SDA_out;
    while(i--) {
        SCL_L;
        I2C_delay();
        if (SendByte&0x80)
            SDA_H;
        else
            SDA_L;
        SendByte<<=1;
        I2C_delay();
        SCL_H;
        I2C_delay();
        I2C_delay();
    }
    SCL_L;
}

// MSB First
inline u8 I2C_ReadByte(void)
{
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;
    SDA_out;
    while(i--) {
        ReceiveByte <<= 1;
        SCL_L;
        I2C_delay();
        I2C_delay();
        SCL_H;
        SDA_in;
        I2C_delay();
        I2C_delay();
        if (SDA_read)
            ReceiveByte |= 0x01;
    }
    SCL_L;
    return ReceiveByte;
}
