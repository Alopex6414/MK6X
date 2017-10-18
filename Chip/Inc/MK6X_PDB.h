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
**PDB触发源枚举
*/
typedef enum
{
  PDB_External_Trigger,         //外部触发源
  PDB_CMP0_Trigger,             //外部触发CMP0
  PDB_CMP1_Trigger,             //外部触发CMP1
  PDB_CMP2_Trigger,             //外部触发CMP2
  PDB_PIT0_Trigger,             //外部触发PIT0
  PDB_PIT1_Trigger,             //外部触发PIT1
  PDB_PIT2_Trigger,             //外部触发PIT2
  PDB_PIT3_Trigger,             //外部触发PIT3
  PDB_FTM0_Trigger,             //外部触发FTM0
  PDB_FTM1_Trigger,             //外部触发FTM1
  PDB_FTM2_Trigger,             //外部触发FTM2
  PDB_FTM3_Trigger,             //外部触发FTM3
  PDB_RTC_Alarm_Trigger,        //外部触发RTC_Alarm
  PDB_RTC_Seconds_Trigger,      //外部触发RTC_Seconds
  PDB_LPTMR_Trigger,            //外部触发LMPTR
  PDB_Software_Trigger,         //软件触发
}PDB_Trigger_Source;





#endif