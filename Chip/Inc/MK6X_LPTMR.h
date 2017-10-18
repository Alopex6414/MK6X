/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_LPTMR.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_LPTMR_H__
#define __MK6X_LPTMR_H__

#include "Common.h"

/*
**LPTMR枚举
*/
typedef enum
{
  LPT0_ALT1=1,//PTA19
  LPT0_ALT2=2,//PTC5
}LPT0_ALTn;

/*
**LPTMR脉冲计数触发方式
*/
typedef enum
{
  LPT_Rising, //上升沿触发
  LPT_Falling,//下降沿触发
}LPT_CFG;

/*
**LPTMR宏
*/
#define LPTMR_Flag_Clear        (LPTMR0_CSR |= LPTMR_CSR_TCF_MASK)//清除LPT比较位


/*
**function declaration
*/
extern void LPTMR_Pluse_Init(LPT0_ALTn LPT0_ALTx,LPT_CFG LPT_CFG_x,uint16 LPT_Count);
extern uint16 LPTMR_Pluse_Get(void);
extern void LPTMR_Count_Clean(void);
extern void LPTMR_Delay_ms(uint16 LPTMR_Delay);
extern void LPTMR_Timing_ms(uint16 LPTMR_Delay);
extern void LPTMR_Delay_us(uint16 LPTMR_Delay);
extern void LPTMR_Timing_us(uint16 LPTMR_Delay);

#endif