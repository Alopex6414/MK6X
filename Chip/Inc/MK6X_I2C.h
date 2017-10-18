/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_I2C.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_I2C_H__
#define __MK6X_I2C_H__

#include "Common.h"

/*
**I2C模块枚举
*/
typedef enum
{
  I2C_I2C0,
  I2C_I2C1,
  I2C_I2C2,
  #ifdef MK66F18
  I2C_I2C3,
  #endif
  I2C_I2C_MAX,
}I2C_I2Cn;

/*
**I2C模式枚举
*/
typedef enum
{
  MWSR=0x00,//主机读模式
  MRSW=0x01,//主机写模式
}I2C_Mode;

/*
**I2C宏
*/
//启动信号
#define I2C_Start(I2Cn)     I2C_C1_REG(I2CN[I2Cn]) |= (I2C_C1_MST_MASK | I2C_C1_TX_MASK)
//停止信号
#define I2C_Stop(I2Cn)      I2C_C1_REG(I2CN[I2Cn]) &= ~(I2C_C1_MST_MASK | I2C_C1_TX_MASK)
//重复启动
#define I2C_ReStart(I2Cn)   I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_RSTA_MASK
//接收模式应答
#define I2C_EnterRx(I2Cn)   I2C_C1_REG(I2CN[I2Cn]) &= ~(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK)
//接收模式不应答
#define I2C_PutInRx(I2Cn)   I2C_C1_REG(I2CN[I2Cn]) &= ~I2C_C1_TX_MASK;I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_TXAK_MASK
//禁用应答
#define I2C_DisableAck(I2Cn) I2C_C1_REG(I2CN[I2Cn]) |= I2C_C1_TXAK_MASK;
//等待I2C_S
#define I2C_Wait(I2Cn)      while((I2C_S_REG(I2CN[I2Cn]) & I2C_S_IICIF_MASK) == 0);I2C_S_REG(I2CN[I2Cn]) |= I2C_S_IICIF_MASK
//I2C写入一个字节
#define I2C_Write_Byte(I2Cn,I2C_Data)       I2C_D_REG(I2CN[I2Cn]) = I2C_Data;I2C_Wait(I2Cn)

/*
**variate declaration
*/
extern I2C_MemMapPtr I2CN[I2C_I2C_MAX];

/*
**function declaration
*/
extern uint32 I2C_Init(I2C_I2Cn I2C_I2Cx,uint32 I2C_Baud);
extern void I2C_Delay(uint16 n);
extern uint8 I2C_Read_Reg(I2C_I2Cn I2C_I2Cx,uint8 I2C_SlaveID,uint8 I2C_Reg);
extern void I2C_Write_Reg(I2C_I2Cn I2C_I2Cx,uint8 I2C_SlaveID,uint8 I2C_Reg,uint8 I2C_Data);

#endif