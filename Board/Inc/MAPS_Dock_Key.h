/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_Key.h
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_KEY_H__
#define __MAPS_DOCK_KEY_H__

#include "Common.h"
#include "MK6X_PORT.h"

/*
**��������ö��
*/
typedef enum
{
  MAPS_Dock_KEY0,       //��������KEY0
  MAPS_Dock_KEY1,       //��������KEY1
  MAPS_Dock_KEY2,       //��������KEY2
  MAPS_Dock_KEY3,       //��������KEY3
  MAPS_Dock_KEY_MAX,
}MAPS_Dock_KEYn;

/*
**��������״̬ö��
*/
typedef enum
{
  MAPS_Dock_KEY_On,     //������������
  MAPS_Dock_KEY_Off,    //������������
}MAPS_Dock_KEY_Status;

//����������
#define MAPS_Dock_KEY_Delay(ms) DELAY_MS(ms)    //������ʱms

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