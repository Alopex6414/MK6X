/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_Rocker.h
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_ROCKER_H__
#define __MAPS_DOCK_ROCKER_H__

#include "Common.h"
#include "MK6X_PORT.h"

/*
**摇杆按键结构体
*/
//摇杆按键枚举
typedef enum
{
  Rocker_Up,    //UP键
  Rocker_Donw,  //DOWN键
  Rocker_Left,  //LEFT键
  Rocker_Right, //RIGHT键
  Rocker_Select,//SELECT键
  Rocker_MAX,
}Rocker_Key_e;

//摇杆按键状态枚举
typedef enum
{
  Rocker_Key_On,
  Rocker_Key_Off,
}Rocker_Key_Status_e;

//摇杆按键消息结构体
typedef struct
{
  Rocker_Key_e  Key;//按键编号            
  Rocker_Key_Status_e   Key_Statu;//按键状态
}Rocker_Key_Message_s;

//摇杆按键宏
#define Rocker_Key_Delay(ms)    DELAY_MS(ms)

/*
**variate declaration
*/
extern PTXn Rocker_Key_PTXn[Rocker_MAX];

/*
**function declaration
*/
extern void MAPS_Dock_Rocker_Key_Init(void);
extern void MAPS_Dock_Rocker_Key_LCM_Control(void);

#endif