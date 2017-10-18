/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Drive_RTC_Count.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __DRIVE_RTC_COUNT_H__
#define __DRIVE_RTC_COUNT_H__

#include "Common.h"

#define DAYSEC  (60*60*24)//定义每天的总秒数

/*
**RTC时间结构体
*/
typedef struct
{
  uint16 Year;  //年
  uint8 Mon;    //月
  uint8 Day;    //日
  uint8 Hour;   //时
  uint8 Min;    //分
  uint8 Sec;    //秒
  uint8 Invalid;//无效
}RTC_Time_s;

/*
**function declaration
*/
extern uint8 IsLeapYear(uint32 Year);
extern uint32 Year_To_Day(uint32 Year);
extern uint32 Time_To_Sec(RTC_Time_s Time);
extern void Sec_To_Time(uint32 Sec,RTC_Time_s *Time);

#endif