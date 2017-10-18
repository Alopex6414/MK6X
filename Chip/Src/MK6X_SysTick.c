/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_SysTick.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      SysTick延时函数
 *  @param      uint32  SysTick_Time
 *  @since      v1.0
 *  Sample usage:       SysTick_Delay(32);     // systick 延时32 个系统周期
 */
void SysTick_Delay(uint32 SysTick_Time)
{
  ASSERT(SysTick_Time > 0 && SysTick_Time <= SysTick_LOAD_RELOAD_Msk);
  
  ((SysTick_Type*)SysTick_BASE)->CTRL = 0;
  ((SysTick_Type*)SysTick_BASE)->LOAD = SysTick_Time;
  ((SysTick_Type*)SysTick_BASE)->VAL = 0;
  
  ((SysTick_Type*)SysTick_BASE)->CTRL = (0 | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk);
  
  while(!(((SysTick_Type*)SysTick_BASE)->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
  
}

/*
 *  @brief      SysTick延时函数
 *  @param      uint32  SysTick_Time_ms
 *  @since      v1.0
 *  Sample usage:       SysTick_Delay(32);     // systick 延时32 ms
 */
void SysTick_Delay_ms(uint32 SysTick_Time_ms)
{
  while(SysTick_Time_ms--)
  {
    SysTick_Delay(SYSTICK_CLK_KHZ);
  }
}

/*
 *  @brief      SysTick定时函数
 *  @param      uint32  SysTick_Time
 *  @since      v1.0
 *  Sample usage:       SysTick_Timing(32);     // systick 延时32 系统周期
 */
void SysTick_Timing(uint32 SysTick_Time)
{
  ASSERT(SysTick_Time > 0 && SysTick_Time <= SysTick_LOAD_RELOAD_Msk);
  
  ((SysTick_Type*)SysTick_BASE)->LOAD = SysTick_Time;
  
  NVIC_SetPriority(SysTick_IRQn,(1 << __NVIC_PRIO_BITS) - 1);
  
  ((SysTick_Type*)SysTick_BASE)->VAL = 0;
  
  ((SysTick_Type*)SysTick_BASE)->CTRL = (0 | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk);
}