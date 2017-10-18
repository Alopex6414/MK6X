/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_LED.c
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

PTXn MAPS_LED[MAPS_Dock_LED_MAX]={PTB7,PTB6,PTB5,PTB4};

/*
 *  @brief      MAPS_Dock_LED单个LED初始化
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LEDx_Init();//初始化MAPS_Dock_LED
 */
void MAPS_Dock_LEDx_Init(MAPS_Dock_LEDn MAPS_Dock_LEDx,LED_Status LED_Status_x)
{
  GPIO_Init(MAPS_LED[MAPS_Dock_LEDx],GPO,LED_Status_x);
}

/*
 *  @brief      MAPS_Dock_LED单个LED反转
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LEDx_Turn();//初始化MAPS_Dock_LED
 */
void MAPS_Dock_LEDx_Turn(MAPS_Dock_LEDn MAPS_Dock_LEDx)
{
  GPIO_Turn(MAPS_LED[MAPS_Dock_LEDx]);
}

/*
 *  @brief      MAPS_Dock_LED初始化
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LED_Init();//初始化MAPS_Dock_LED
 */
void MAPS_Dock_LED_Init(void)
{
  MAPS_Dock_LED1_Off;    //LED1亮
  MAPS_Dock_LED2_On;     //LED2灭
  MAPS_Dock_LED3_Off;    //LED3亮
  MAPS_Dock_LED4_On;     //LED4灭
}

/*
 *  @brief      MAPS_Dock_LED反转
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LED_Turn();//初始化MAPS_Dock_LED
 */
void MAPS_Dock_LED_Turn(void)
{
  MAPS_Dock_LED1_Turn;  //LED1反转
  MAPS_Dock_LED2_Turn;  //LED2反转
  MAPS_Dock_LED3_Turn;  //LED3反转
  MAPS_Dock_LED4_Turn;  //LED4反转
}