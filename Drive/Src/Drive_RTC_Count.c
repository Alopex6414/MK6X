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
**ƽ���������·�����
*/
//ƽ��
const uint8 CommonYearMon[12] =
{
  31,28,31,30,31,30,31,31,30,31,30,31
};
//����
const uint8 LeapYearMon[12] =
{
  31,29,31,30,31,30,31,31,30,31,30,31
};

//ƽ��������
const uint16 CommonYearMonOff[] =
{
  0,31,59,90,120,151,181,212,243,273,304,334,365
};
//����������
const uint16 LeapYearMonOff[] = 
{
  0,31,60,91,121,152,182,213,244,274,305,335,366
};

/*
 *  @brief      ����Ƿ�Ϊ����
 *  @param      uint32  Year    ���
 *  @return     �Ƿ�Ϊ����(0��ʾƽ�꣬1��ʾ����)
 *  @since      v1.0
 */
uint8 IsLeapYear(uint32 Year)
{
  if(Year % 4 == 0)
  {
    if((Year % 100 != 0) || (Year % 400 == 0))
    {
      return 1;//����
    }
  }
  
  //ƽ��
  return 0;
}

/*
 *  @brief      ����ݵ�����
 *  @param      uint32  Year    ���
 *  @return     ָ����ݵ�����
 *  @since      v1.0
 */
uint32 Year_To_Day(uint32 Year)
{
  return (365 + (IsLeapYear(Year)));
}

/*
 *  @brief      ��1970-01-01 0:0:0 �� ָ��ʱ���������ʱ�����ʽתΪ������
 *  @param      Time    ʱ��ṹ��
 *  @return     ��1970-01-01 0:0:0 �� ָ��ʱ���������
 *  @since      v1.0
 *  Sample usage:       RTC_Time_s Time = {2013,9,1,0,0,0};  //ʱ��Ϊ 2013-09-01 0:0:0
 */
uint32 Time_To_Sec(RTC_Time_s Time)
{
  //�ο� Linux�ں˴��� Include/Linux/time.h ��ĺ��� mktime()
  //���ݸ�˹�㷨����year/mon/day/hour/min/sec(��1980��12��31 23��59��59)
  //��ʽ��ʾ��ʱ��ת��Ϊ�����1970��01��01 00��00��00
  //���UNIXʱ���׼�������������

  //ע��һ�㣬����Ķ��·���29�죬��������Ϊ28��
  //����һ�򣬰��겻���İ�������
  
  //���ʱ�����ȷ
  ASSERT((Time.Year >= 1970) && (Time.Year < 2100) && (Time.Mon <= 12));
  ASSERT(((IsLeapYear(Time.Year) == 0) && (Time.Day <= CommonYearMon[Time.Mon - 1]))      //ƽ������
         || ((IsLeapYear(Time.Year) == 1) && (Time.Day <= LeapYearMon[Time.Mon - 1])));   //��������
  
  //һ�¶��·����·����,��3,4,5,...11,12,1,2
  if((int8)(Time.Mon -= 2) <= 0)
  {
    Time.Mon += 12;
    Time.Year -= 1;
  }
  
  return (((((uint32)(Time.Year/4 - Time.Year/100 + Time.Year/400 + (367*Time.Mon)/12 + Time.Day) + Time.Year*365 - 719499)*24 + Time.Hour)*60 + Time.Min)*60 + Time.Sec);
}

/*
 *  @brief      ��1970-01-01 Ϊ��׼�������� תΪ������ʱ�����ʽ
 *  @param      Sec     ������
 *  @param      Time    ʱ��ṹ��
 *  @since      v1.0
 *  Sample usage:       RTC_Time_s Time;
                        Sec_To_Time(1000,&time);   //��1000���Ӧ��ʱ��
 */
void Sec_To_Time(uint32 Sec,RTC_Time_s *Time)
{
  //�ο� Linux�ں˴��� Include/Linux/time.h ��ĺ��� mktime()
  //���ݸ�˹�㷨����year/mon/day/hour/min/sec(��1980��12��31 23��59��59)
  //��ʽ��ʾ��ʱ��ת��Ϊ�����1970��01��01 00��00��00
  //���UNIXʱ���׼�������������

  //ע��һ�㣬����Ķ��·���29�죬��������Ϊ28��
  //����һ�򣬰��겻���İ�������
  
  uint8 const* MonOff;
  uint16 const* DayOff;
  uint32 Hms,Day,Tmp;
  
  //��ʱʱ�䳬��2099-12-31 23:59:59,��1970-1-1 0:0:0��ʼ��ʱ
  if(Sec > 0xF48656FF)
  {
    Sec -= 0xF48656FF;
  }
  
  //�����������������ʣ������
  Day = Sec / DAYSEC;
  Hms = Sec % DAYSEC;
  
  Time->Hour = (uint8)(Hms / (60 * 60));
  Hms %= (60 * 60);
  Time->Min = (uint8)(Hms / 60);
  Time->Sec = (uint8)(Hms % 60);
  
  //����������
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