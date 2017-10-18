/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Drive_RTC_Count.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**平年和闰年的月份数组
*/
//平年
const uint8 CommonYearMon[12] =
{
  31,28,31,30,31,30,31,31,30,31,30,31
};
//闰年
const uint8 LeapYearMon[12] =
{
  31,29,31,30,31,30,31,31,30,31,30,31
};

//平年月天数
const uint16 CommonYearMonOff[] =
{
  0,31,59,90,120,151,181,212,243,273,304,334,365
};
//闰年月天数
const uint16 LeapYearMonOff[] = 
{
  0,31,60,91,121,152,182,213,244,274,305,335,366
};

/*
 *  @brief      检测是否为闰年
 *  @param      uint32  Year    年份
 *  @return     是否为闰年(0表示平年，1表示闰年)
 *  @since      v1.0
 */
uint8 IsLeapYear(uint32 Year)
{
  if(Year % 4 == 0)
  {
    if((Year % 100 != 0) || (Year % 400 == 0))
    {
      return 1;//闰年
    }
  }
  
  //平年
  return 0;
}

/*
 *  @brief      求年份的天数
 *  @param      uint32  Year    年份
 *  @return     指定年份的天数
 *  @since      v1.0
 */
uint32 Year_To_Day(uint32 Year)
{
  return (365 + (IsLeapYear(Year)));
}

/*
 *  @brief      从1970-01-01 0:0:0 至 指定时间的年月日时分秒格式转为总秒数
 *  @param      Time    时间结构体
 *  @return     从1970-01-01 0:0:0 至 指定时间的总秒数
 *  @since      v1.0
 *  Sample usage:       RTC_Time_s Time = {2013,9,1,0,0,0};  //时间为 2013-09-01 0:0:0
 */
uint32 Time_To_Sec(RTC_Time_s Time)
{
  //参考 Linux内核代码 Include/Linux/time.h 里的函数 mktime()
  //根据高斯算法将以year/mon/day/hour/min/sec(如1980－12－31 23：59：59)
  //格式表示的时间转换为相对于1970－01－01 00：00：00
  //这个UNIX时间基准以来的相对秒数

  //注意一点，闰年的二月份是29天，非闰年则为28天
  //四年一闰，百年不闰，四百年再闰
  
  //检测时间的正确
  ASSERT((Time.Year >= 1970) && (Time.Year < 2100) && (Time.Mon <= 12));
  ASSERT(((IsLeapYear(Time.Year) == 0) && (Time.Day <= CommonYearMon[Time.Mon - 1]))      //平年天数
         || ((IsLeapYear(Time.Year) == 1) && (Time.Day <= LeapYearMon[Time.Mon - 1])));   //闰年天数
  
  //一月二月放在月份最后,即3,4,5,...11,12,1,2
  if((int8)(Time.Mon -= 2) <= 0)
  {
    Time.Mon += 12;
    Time.Year -= 1;
  }
  
  return (((((uint32)(Time.Year/4 - Time.Year/100 + Time.Year/400 + (367*Time.Mon)/12 + Time.Day) + Time.Year*365 - 719499)*24 + Time.Hour)*60 + Time.Min)*60 + Time.Sec);
}

/*
 *  @brief      以1970-01-01 为基准的总秒数 转为年月日时分秒格式
 *  @param      Sec     总秒数
 *  @param      Time    时间结构体
 *  @since      v1.0
 *  Sample usage:       RTC_Time_s Time;
                        Sec_To_Time(1000,&time);   //求1000秒对应的时间
 */
void Sec_To_Time(uint32 Sec,RTC_Time_s *Time)
{
  //参考 Linux内核代码 Include/Linux/time.h 里的函数 mktime()
  //根据高斯算法将以year/mon/day/hour/min/sec(如1980－12－31 23：59：59)
  //格式表示的时间转换为相对于1970－01－01 00：00：00
  //这个UNIX时间基准以来的相对秒数

  //注意一点，闰年的二月份是29天，非闰年则为28天
  //四年一闰，百年不闰，四百年再闰
  
  uint8 const* MonOff;
  uint16 const* DayOff;
  uint32 Hms,Day,Tmp;
  
  //计时时间超过2099-12-31 23:59:59,从1970-1-1 0:0:0开始计时
  if(Sec > 0xF48656FF)
  {
    Sec -= 0xF48656FF;
  }
  
  //求出秒数共有天数和剩下天数
  Day = Sec / DAYSEC;
  Hms = Sec % DAYSEC;
  
  Time->Hour = (uint8)(Hms / (60 * 60));
  Hms %= (60 * 60);
  Time->Min = (uint8)(Hms / 60);
  Time->Sec = (uint8)(Hms % 60);
  
  //算出当年年份
  Time->Year = (uint16)(Day / 366);
  Day = Day - 365*(Time->Year) - ((Time->Year + 1)/4);
  Time->Year += 1970;
  
  Tmp = 365 + IsLeapYear(Time->Year);
  if(Day > Tmp)
  {
    Time->Year++;
    Day -= Tmp;
  }
  
  Time->Mon = (uint8)(Day/31+1);
  Tmp = IsLeapYear(Time->Year);
  
  DayOff = Tmp?LeapYearMonOff:CommonYearMonOff;
  MonOff = Tmp?LeapYearMon:CommonYearMon;
  
  Time->Day = (uint8)(Day + 1 - DayOff[Time->Mon - 1]);
  
  if(Time->Day > MonOff[Time->Mon - 1])
  {
    Time->Mon++;
    Time->Day = (uint8)(Day + 1 - DayOff[Time->Mon - 1]);
  }
  
}