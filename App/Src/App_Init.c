/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       App_Init.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      Interrupt_Init     中断初始化
 *  @since      v1.0
 */
void Interrupt_Init(void)
{
  /*PORT_Init_Exit(PTC19,IRQ_EITHER);//PTC19外部中断,跳变沿触发
  set_irq_priority(PORTC_IRQn,0);//中断优先级0
  enable_irq(PORTC_IRQn);//使能中断
  
  PORT_Init_Exit(PTD15,IRQ_EITHER);//PTD15外部中断,跳变沿触发
  set_irq_priority(PORTD_IRQn,1);//中断优先级1
  enable_irq(PORTD_IRQn);//使能中断*/
  
  PIT_Init_ms(PIT0,1);//PIT0定时中断,定时周期1ms
  set_irq_priority(PIT0_IRQn,2);//中断优先级2
  enable_irq(PIT0_IRQn);//使能中断
  
}

/*
 *  @brief      AllInit     应用初始化
 *  @since      v1.0
 */
void AllInit(void)
{
  DisableInterrupts;//关总中断
  /*
  **MAPS_Dock
  */
  MAPS_Dock_LED_Init();//LED初始化
  MAPS_Dock_LCM_Init();//LCM初始化
  MAPS_Dock_KEY_ALL_Init();//KEY独立按键初始化
  MAPS_Dock_Rocker_Key_Init();//Rocker摇杆按键初始化
  //MAPS_Dock_W25Q80_Init();//W25Q80初始化
  
  /*
  **MAPS
  */
  MAPS_LCD_Init();//LCDC初始化
  
  /*
  **MK6X
  */
  ADC_Init(ADC0_DP0);//ADC0_DP0通道初始化
  ADC_Init(ADC0_DM0);//ADC0_DM0通道初始化
  I2C_Init(I2C_I2C0,400000);//初始化I2C0,波特率400Kbps
  UART_Init(UART_UART4,115200);//初始化UART4,波特率115200Bps
  //DAC_Init(DAC_DAC1);//DAC_DAC1初始化
  
  Interrupt_Init();//中断初始化
  
  EnableInterrupts;
}