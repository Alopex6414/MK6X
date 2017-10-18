/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_It.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**PIT计数器
*/
int PIT_Count=0;//PIT计数值
char PIT_Flag=0;//PIT标志

/*
**ADC转换
*/
uint16 ADC_Convert_Result[2]={0};

/*
 *  @brief      PORTC_PTC19_IRQHandler     PTC19外部中断服务函数
 *  @since      v1.0
 */
void PORTC_PTC19_IRQHandler(void)
{
  if(IRQ_MARK(C,19))
  {
    IRQ_CLEAR(C,19);
    disable_irq(PORTC_IRQn);
    
    //Put Your Code...
    
    IRQ_CLEAR(C,19);
    enable_irq(PORTC_IRQn);
  }
}

/*
 *  @brief      PORTD_PTD15_IRQHandler     PTD15外部中断服务函数
 *  @since      v1.0
 */
void PORTD_PTD15_IRQHandler(void)
{
  if(IRQ_MARK(D,15))
  {
    IRQ_CLEAR(D,15);
    disable_irq(PORTD_IRQn);
    
    //Put Your Code...
    
    IRQ_CLEAR(D,15);
    enable_irq(PORTD_IRQn);
  }
}

/*
 *  @brief      PIT0_IRQHandler     PIT0定时中断服务函数
 *  @since      v1.0
 */
void PIT0_IRQHandler(void)
{
  PIT_Flag_Clear(PIT0);
  disable_irq(PIT0_IRQn);
  
  //Put Your Code...
  
  PIT_Count++;
  
  if(PIT_Count > 1000)
  {
    PIT_Count = 1000;
  }
  
  if(PIT_Count == 1000)
  {
    PIT_Count = 0;
    
    PIT_Flag++;
    
    if(PIT_Flag > 3)
    {
      PIT_Flag = 0;
    }
    
    MAPS_Dock_LED_Turn();//LED翻转
    ADC_Convert_Result[0] = ADC_Once(ADC0_DP0,ADC_12Bit);//ADC转换
    ADC_Convert_Result[1] = ADC_Once(ADC0_DM0,ADC_12Bit);//ADC转换
  }
  
  PIT_Flag_Clear(PIT0);
  enable_irq(PIT0_IRQn);
}

