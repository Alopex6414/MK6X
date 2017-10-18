/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_RTC.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_RTC_H__
#define __MK6X_RTC_H__

#include "Common.h"

/*
**RTC��
*/
#define RTC_ALARM_IRQ_EN()      RTC_IER |= RTC_IER_TAIE_MASK      //ʹ�������ж�
#define RTC_ALARM_IRQ_DIS()     RTC_IER &= ~RTC_IER_TAIE_MASK     //��ֹ�����ж�

#define RTC_OVERFLOW_IRQ_EN()   RTC_IER |= RTC_IER_TOIE_MASK      //ʹ������ж�
#define RTC_OVERFLOW_IRQ_DIS()  RTC_IER &= ~RTC_IER_TOIE_MASK     //��ֹ����ж�

#define RTC_INVALID_IRQ_EN()    RTC_IER |= RTC_IER_TIIE_MASK      //ʹ����Ч�����ж�
#define RTC_INVALID_IRQ_DIS()   RTC_IER &= ~RTC_IER_TIIE_MASK     //��ֹ��Ч�����ж�

/*
**function declaration
*/
extern void RTC_Init(void);
extern void RTC_Set_Time(uint32 Seconds);
extern uint32 RTC_Get_Time(void);
extern uint8 RTC_Set_Alarm(uint32 Alarm);
extern void RTC_Close_Alarm(void);
extern void RTC_Test_Handler(void);

#endif