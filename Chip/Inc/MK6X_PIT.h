/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PIT.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_PIT_H__
#define __MK6X_PIT_H__

#include "Common.h"

/*
**PIT模块枚举
*/
typedef enum
{
  PIT0,
  PIT1,
  PIT2,
  PIT3,
  PIT_MAX,
}PITn;

/*
**PIT宏
*/
#define PIT_Flag_Clear(PITx)    (PIT_TFLG(PITx) |= PIT_TFLG_TIF_MASK)    

/*
**PIT中断
*/
#define PIT_Init_ms(PITx,PIT_Count)     PIT_Init(PITx,PIT_Count*MK6X_Bus_KHz)
#define PIT_Init_us(PITx,PIT_Count)     PIT_Init(PITx,PIT_Count*MK6X_Bus_KHz/1000)
#define PIT_Init_ns(PITx,PIT_Count)     PIT_Init(PITx,PIT_Count*MK6X_Bus_KHz/1000000)

/*
**PIT延时(不需要初始化)
*/
#define PIT_Delay_ms(PITx,PIT_Count)    PIT_Delay(PITx,PIT_Count*MK6X_Bus_KHz)
#define PIT_Delay_us(PITx,PIT_Count)    PIT_Delay(PITx,PIT_Count*MK6X_Bus_KHz/1000)
#define PIT_Delay_ns(PITx,PIT_Count)    PIT_Delay(PITx,PIT_Count*MK6X_Bus_KHz/1000000)

/*
**PIT计时
*/
#define PIT_Time_Get_ms(PITx)           (PIT_Time_Get(PITx)/MK6X_Bus_KHz)
#define PIT_Time_Get_us(PITx)           (PIT_Time_Get(PITx)/(MK6X_Bus_KHz/1000))

/*
**PIT中断相关向量及IRQ
*/
//PIT0_VECTORn,PIT0中断向量,PIT0_IRQn
//PIT1_VECTORn,PIT0中断向量,PIT1_IRQn
//PIT2_VECTORn,PIT0中断向量,PIT2_IRQn
//PIT3_VECTORn,PIT0中断向量,PIT3_IRQn

/*
**function declaration
*/
extern void PIT_Init(PITn PITx,uint32 PIT_Count);
extern void PIT_Delay(PITn PITx,uint32 PIT_Count);
extern void PIT_Time_Start(PITn PITx);
extern uint32 PIT_Time_Get(PITn PITx);
extern void PIT_Close(PITn PITx);


#endif