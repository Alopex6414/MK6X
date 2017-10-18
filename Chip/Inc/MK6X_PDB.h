/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PDB.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_PDB_H__
#define __MK6X_PDB_H__

#include "Common.h"

/*
**PDB����Դö��
*/
typedef enum
{
  PDB_External_Trigger,         //�ⲿ����Դ
  PDB_CMP0_Trigger,             //�ⲿ����CMP0
  PDB_CMP1_Trigger,             //�ⲿ����CMP1
  PDB_CMP2_Trigger,             //�ⲿ����CMP2
  PDB_PIT0_Trigger,             //�ⲿ����PIT0
  PDB_PIT1_Trigger,             //�ⲿ����PIT1
  PDB_PIT2_Trigger,             //�ⲿ����PIT2
  PDB_PIT3_Trigger,             //�ⲿ����PIT3
  PDB_FTM0_Trigger,             //�ⲿ����FTM0
  PDB_FTM1_Trigger,             //�ⲿ����FTM1
  PDB_FTM2_Trigger,             //�ⲿ����FTM2
  PDB_FTM3_Trigger,             //�ⲿ����FTM3
  PDB_RTC_Alarm_Trigger,        //�ⲿ����RTC_Alarm
  PDB_RTC_Seconds_Trigger,      //�ⲿ����RTC_Seconds
  PDB_LPTMR_Trigger,            //�ⲿ����LMPTR
  PDB_Software_Trigger,         //�������
}PDB_Trigger_Source;





#endif