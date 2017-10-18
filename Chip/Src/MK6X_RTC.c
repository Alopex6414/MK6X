/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_RTC.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      RTC��ʼ��
 *  @since      v1.0
 *  Sample usage:       RTC_Init();    //RTC��ʼ��
 */
void RTC_Init(void)
{
  volatile uint32 RTC_Delay=0;
  
  SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;//RTCʱ��ʹ��
  
  RTC_CR = RTC_CR_SWR_MASK;     //RTC�Ĵ�����λ
  RTC_CR &= ~RTC_CR_SWR_MASK;   //RTC�����λ����
  
  RTC_CR =(0
           | RTC_CR_OSCE_MASK   //ʹ��32.768KHz����
           | RTC_CR_SC16P_MASK  //ʹ��16pF��·����
           | RTC_CR_CLKO_MASK   //32.768KHz����������ⲿ
           );
  
  //�ȴ������ȶ�
  RTC_Delay = 0x600000;
  while(RTC_Delay--);
  
  //����ʱ�䲹��
  RTC_TCR = (0
             | RTC_TCR_CIR(0)   //���񲹳�ʱ��Ϊ0
             | RTC_TCR_TCR(0)   //32.768KHz����ʱ�䲹��(������)
             );
  
  RTC_SR &= ~RTC_SR_TCE_MASK;   //����RTC������
  
  //ʱ�����������
  RTC_TSR = 0;                  //������������ֵ0
  RTC_TAR = 0;                  //���Ӽ�����ֵ0
  RTC_IER = 0;                  //���ж�
  
  RTC_SR |= RTC_SR_TCE_MASK;    //ʹ��RTC������
}

/*
 *  @brief      ���õ�ǰʱ��
 *  @since      v1.0
 */
void RTC_Set_Time(uint32 Seconds)
{
  RTC_SR &= ~RTC_SR_TCE_MASK;   //����RTC������
  RTC_TSR = Seconds;            //���ü�������ֵʱ��
  RTC_SR |= RTC_SR_TCE_MASK;    //ʹ��RTC������
}

/*
 *  @brief      ��ȡ��ǰʱ��
 *  @since      v1.0
 */
uint32 RTC_Get_Time(void)
{
  return RTC_TSR;               //������ʼ��,RTC_TSR�Ĵ�����ȡ��ǰ����ʱ��
}

/*
 *  @brief      ����RTC����ʱ��,ʹ�������ж�
 *  @param      uint32  Alarm   ����ʱ��
 *  @return     �������ӽ��(0��ʾʧ��,1��ʾ�ɹ�)
 *  @since      v1.0
 */
uint8 RTC_Set_Alarm(uint32 Alarm)
{
  //����ʱ�䲻��С�ڵ�ǰ��ʱ��ֵʱ��
  if(Alarm < RTC_TSR)
  {
    return 0;
  }
  
  RTC_SR &= ~RTC_SR_TCE_MASK;   //����RTC������
  RTC_TAR = Alarm;              //����Alarm����ʱ��
  RTC_SR |= RTC_SR_TCE_MASK;    //ʹ��RTC������
  
  RTC_IER |= RTC_IER_TAIE_MASK; //�����ж�ʹ��
  
  return 1;
}

/*
 *  @brief      �ر������ж�
 *  @since      v1.0
 */
void RTC_Close_Alarm(void)
{
  RTC_IER &= ~RTC_IER_TAIE_MASK;//��ֹ�����ж�
}

/*
 *  @brief      RTC�жϷ�����
 *  @since      v1.0
 *  @warning    �˺�����Ҫ�û������Լ��������,����������ṩһ��ģ��
 *  Sample usage:       Set_Vector_Handler(RTC_VECTORn , rtc_test_handler);    //�� rtc_test_handler ������ӵ��ж�����������Ҫ�����ֶ�����
 */
void RTC_Test_Handler(void)
{
  if(RTC_SR & RTC_SR_TIF_MASK)//��Ч����
  {
    RTC_SR = 0;
    RTC_TSR = 0;
    
    //Put Your Code...
    
  }
  
  if(RTC_SR & RTC_SR_TOF_MASK)//�������
  {
    RTC_SR = 0;
    RTC_TSR = 0;
    
    //Put Your Code...
    
  }
  
  if(RTC_SR & RTC_SR_TAF_MASK)//Alarm����
  {
    RTC_TAR = 0;
    
    //Put Your Code...
  }
  
}