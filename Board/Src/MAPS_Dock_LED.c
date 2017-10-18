/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_LED.c
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

PTXn MAPS_LED[MAPS_Dock_LED_MAX]={PTB7,PTB6,PTB5,PTB4};

/*
 *  @brief      MAPS_Dock_LED����LED��ʼ��
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LEDx_Init();//��ʼ��MAPS_Dock_LED
 */
void MAPS_Dock_LEDx_Init(MAPS_Dock_LEDn MAPS_Dock_LEDx,LED_Status LED_Status_x)
{
  GPIO_Init(MAPS_LED[MAPS_Dock_LEDx],GPO,LED_Status_x);
}

/*
 *  @brief      MAPS_Dock_LED����LED��ת
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LEDx_Turn();//��ʼ��MAPS_Dock_LED
 */
void MAPS_Dock_LEDx_Turn(MAPS_Dock_LEDn MAPS_Dock_LEDx)
{
  GPIO_Turn(MAPS_LED[MAPS_Dock_LEDx]);
}

/*
 *  @brief      MAPS_Dock_LED��ʼ��
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LED_Init();//��ʼ��MAPS_Dock_LED
 */
void MAPS_Dock_LED_Init(void)
{
  MAPS_Dock_LED1_Off;    //LED1��
  MAPS_Dock_LED2_On;     //LED2��
  MAPS_Dock_LED3_Off;    //LED3��
  MAPS_Dock_LED4_On;     //LED4��
}

/*
 *  @brief      MAPS_Dock_LED��ת
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LED_Turn();//��ʼ��MAPS_Dock_LED
 */
void MAPS_Dock_LED_Turn(void)
{
  MAPS_Dock_LED1_Turn;  //LED1��ת
  MAPS_Dock_LED2_Turn;  //LED2��ת
  MAPS_Dock_LED3_Turn;  //LED3��ת
  MAPS_Dock_LED4_Turn;  //LED4��ת
}