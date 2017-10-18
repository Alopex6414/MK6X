/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_Rocker.h
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_ROCKER_H__
#define __MAPS_DOCK_ROCKER_H__

#include "Common.h"
#include "MK6X_PORT.h"

/*
**ҡ�˰����ṹ��
*/
//ҡ�˰���ö��
typedef enum
{
  Rocker_Up,    //UP��
  Rocker_Donw,  //DOWN��
  Rocker_Left,  //LEFT��
  Rocker_Right, //RIGHT��
  Rocker_Select,//SELECT��
  Rocker_MAX,
}Rocker_Key_e;

//ҡ�˰���״̬ö��
typedef enum
{
  Rocker_Key_On,
  Rocker_Key_Off,
}Rocker_Key_Status_e;

//ҡ�˰�����Ϣ�ṹ��
typedef struct
{
  Rocker_Key_e  Key;//�������            
  Rocker_Key_Status_e   Key_Statu;//����״̬
}Rocker_Key_Message_s;

//ҡ�˰�����
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