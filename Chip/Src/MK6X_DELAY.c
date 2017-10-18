/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_DELAY.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      微秒级别延时(us)
 *  @param      uint32  Delay_Time
 *  @since      v1.0
 *  Sample usage:       DELAY_us(1);//延时1us
 */
void DELAY_us(uint32 Delay_Time)
{
  uint32 i=0;
  uint32 j=0;
  uint32 DELAY_Clk=MK6X_Core_MHz;//延时参考时钟
  
  for(i=0;i<Delay_Time;i++)
  {
    for(j=0;j<DELAY_Clk;j++)
    {
      asm("nop");
    }
  }
  
}

/*
 *  @brief      毫秒级别延时(ms)
 *  @param      uint32  Delay_Time
 *  @since      v1.0
 *  Sample usage:       DELAY_ms(1);//延时1ms
 */
void DELAY_ms(uint32 Delay_Time)
{
  uint32 i=0;
  uint32 j=0;
  uint32 DELAY_Clk=MK6X_Core_KHz;//延时参考时钟
  
  for(i=0;i<Delay_Time;i++)
  {
    for(j=0;j<DELAY_Clk;j++)
    {
      asm("nop");
    }
  }
  
}