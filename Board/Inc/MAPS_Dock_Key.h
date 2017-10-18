/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_Key.h
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_KEY_H__
#define __MAPS_DOCK_KEY_H__

#include "Common.h"
#include "MK6X_PORT.h"

/*
**独立按键枚举
*/
typedef enum
{
  MAPS_Dock_KEY0,       //独立按键KEY0
  MAPS_Dock_KEY1,       //独立按键KEY1
  MAPS_Dock_KEY2,       //独立按键KEY2
  MAPS_Dock_KEY3,       //独立按键KEY3
  MAPS_Dock_KEY_MAX,
}MAPS_Dock_KEYn;

/*
**独立按键状态枚举
*/
typedef enum
{
  MAPS_Dock_KEY_On,     //独立按键按下
  MAPS_Dock_KEY_Off,    //独立按键弹起
}MAPS_Dock_KEY_Status;

//独立按键宏
#define MAPS_Dock_KEY_Delay(ms) DELAY_MS(ms)    //按键延时ms

/*
**variate declaration
*/
extern PTXn MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY_MAX];

/*
**function declaration
*/
extern void MAPS_Dock_KEY_ALL_Init(void);
extern void MAPS_Dock_KEY_KEYn_Init(MAPS_Dock_KEYn MAPS_Dock_KEYx);
extern uint8 MAPS_Dock_KEY_KEYn_Get(MAPS_Dock_KEYn MAPS_Dock_KEYx);
extern MAPS_Dock_KEY_Status MAPS_Dock_KEY_KEYn_Check(MAPS_Dock_KEYn MAPS_Dock_KEYx);
extern void MAPS_Dock_KEY_Incident(void);

#endif