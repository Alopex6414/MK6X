/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_DWT.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      DWT��ʱ(us)
 *  @param      uint32  DWT_us      ��ʱʱ��
 *  @since      v1.0
 */
void DWT_Delay_us(uint32 DWT_us)
{
  uint32 DWT_St=0;
  uint32 DWT_Et=0;
  uint32 DWT_Ts=0;
  
  ((CoreDebug_Type*)CoreDebug_BASE)->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;//����ʱ��Enable
  ((DWT_Type*)DWT_BASE)->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  
  DWT_St = ((DWT_Type*)DWT_BASE)->CYCCNT;
  DWT_Ts = DWT_us * (DWT_CLK_KHZ / 1000);
  DWT_Et = DWT_St + DWT_Ts;
  
  if(DWT_Et < DWT_St)
  {
    while((((DWT_Type*)DWT_BASE)->CYCCNT) > DWT_Et);
  }
  
  while((((DWT_Type*)DWT_BASE)->CYCCNT) < DWT_Et);
  
}

/*
 *  @brief      DWT��ʱ(ms)
 *  @param      uint32  DWT_ms      ��ʱʱ��
 *  @since      v1.0
 */
void DWT_Delay_ms(uint32 DWT_ms)
{
  while(DWT_ms--)
  {
    DWT_Delay_us(1000);
  }
}