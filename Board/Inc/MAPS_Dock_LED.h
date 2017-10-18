/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_LED.h
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_LED_H__
#define __MAPS_DOCK_LED_H__

#include "Common.h"

/*
**MAPS_Dock_LEDö��
*/
typedef enum
{
  MAPS_Dock_LED1,
  MAPS_Dock_LED2,
  MAPS_Dock_LED3,
  MAPS_Dock_LED4,
  MAPS_Dock_LED_MAX,
}MAPS_Dock_LEDn;

/*
**MAPS_Dock_LED״̬
*/
typedef enum
{
  LED_ON,
  LED_OFF,
}LED_Status;

/*
**MAPS��ɫ���ϵ�LED
*/
//LED1(LD3)
#define MAPS_Dock_LED1_On       GPIO_Init(PTB7,GPO,0)   //LED1��
#define MAPS_Dock_LED1_Off      GPIO_Init(PTB7,GPO,1)   //LED1��
#define MAPS_Dock_LED1_Turn     GPIO_Turn(PTB7)         //LED1��ת

//LED2(LD4)
#define MAPS_Dock_LED2_On       GPIO_Init(PTB6,GPO,0)   //LED2��
#define MAPS_Dock_LED2_Off      GPIO_Init(PTB6,GPO,1)   //LED2��
#define MAPS_Dock_LED2_Turn     GPIO_Turn(PTB6)         //LED2��ת

//LED3(LD5)
#define MAPS_Dock_LED3_On       GPIO_Init(PTB5,GPO,0)   //LED3��
#define MAPS_Dock_LED3_Off      GPIO_Init(PTB5,GPO,1)   //LED3��
#define MAPS_Dock_LED3_Turn     GPIO_Turn(PTB5)         //LED3��ת

//LED4(LD6)
#define MAPS_Dock_LED4_On       GPIO_Init(PTB4,GPO,0)   //LED4��
#define MAPS_Dock_LED4_Off      GPIO_Init(PTB4,GPO,1)   //LED4��
#define MAPS_Dock_LED4_Turn     GPIO_Turn(PTB4)         //LED4��ת

/*
**function declaration
*/
extern void MAPS_Dock_LEDx_Init(MAPS_Dock_LEDn MAPS_Dock_LEDx,LED_Status LED_Status_x);
extern void MAPS_Dock_LEDx_Turn(MAPS_Dock_LEDn MAPS_Dock_LEDx);
extern void MAPS_Dock_LED_Init(void);
extern void MAPS_Dock_LED_Turn(void);

#endif