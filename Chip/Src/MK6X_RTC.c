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
 *  @brief      RTC初始化
 *  @since      v1.0
 *  Sample usage:       RTC_Init();    //RTC初始化
 */
void RTC_Init(void)
{
  volatile uint32 RTC_Delay=0;
  
  SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;//RTC时钟使能
  
  RTC_CR = RTC_CR_SWR_MASK;     //RTC寄存器复位
  RTC_CR &= ~RTC_CR_SWR_MASK;   //RTC软件复位清零
  
  RTC_CR =(0
           | RTC_CR_OSCE_MASK   //使能32.768KHz晶振
           | RTC_CR_SC16P_MASK  //使能16pF旁路电容
           | RTC_CR_CLKO_MASK   //32.768KHz波不输出到外部
           );
  
  //等待晶振稳定
  RTC_Delay = 0x600000;
  while(RTC_Delay--);
  
  //设置时间补偿
  RTC_TCR = (0
             | RTC_TCR_CIR(0)   //晶振补偿时间为0
             | RTC_TCR_TCR(0)   //32.768KHz晶振时间补偿(不补偿)
             );
  
  RTC_SR &= ~RTC_SR_TCE_MASK;   //禁用RTC计数器
  
  //时间和闹钟设置
  RTC_TSR = 0;                  //秒数计数器初值0
  RTC_TAR = 0;                  //闹钟计数器值0
  RTC_IER = 0;                  //关中断
  
  RTC_SR |= RTC_SR_TCE_MASK;    //使能RTC计数器
}

/*
 *  @brief      设置当前时间
 *  @since      v1.0
 */
void RTC_Set_Time(uint32 Seconds)
{
  RTC_SR &= ~RTC_SR_TCE_MASK;   //禁用RTC计数器
  RTC_TSR = Seconds;            //设置计数器初值时间
  RTC_SR |= RTC_SR_TCE_MASK;    //使能RTC计数器
}

/*
 *  @brief      获取当前时间
 *  @since      v1.0
 */
uint32 RTC_Get_Time(void)
{
  return RTC_TSR;               //计数开始后,RTC_TSR寄存器读取当前计数时间
}

/*
 *  @brief      设置RTC闹钟时间,使能闹钟中断
 *  @param      uint32  Alarm   闹钟时间
 *  @return     设置闹钟结果(0表示失败,1表示成功)
 *  @since      v1.0
 */
uint8 RTC_Set_Alarm(uint32 Alarm)
{
  //闹钟时间不能小于当前定时初值时间
  if(Alarm < RTC_TSR)
  {
    return 0;
  }
  
  RTC_SR &= ~RTC_SR_TCE_MASK;   //禁用RTC计数器
  RTC_TAR = Alarm;              //设置Alarm闹钟时间
  RTC_SR |= RTC_SR_TCE_MASK;    //使能RTC计数器
  
  RTC_IER |= RTC_IER_TAIE_MASK; //闹钟中断使能
  
  return 1;
}

/*
 *  @brief      关闭闹钟中断
 *  @since      v1.0
 */
void RTC_Close_Alarm(void)
{
  RTC_IER &= ~RTC_IER_TAIE_MASK;//禁止闹钟中断
}

/*
 *  @brief      RTC中断服务函数
 *  @since      v1.0
 *  @warning    此函数需要用户根据自己需求完成,这里仅仅是提供一个模版
 *  Sample usage:       Set_Vector_Handler(RTC_VECTORn , rtc_test_handler);    //把 rtc_test_handler 函数添加到中断向量表，不需要我们手动调用
 */
void RTC_Test_Handler(void)
{
  if(RTC_SR & RTC_SR_TIF_MASK)//无效设置
  {
    RTC_SR = 0;
    RTC_TSR = 0;
    
    //Put Your Code...
    
  }
  
  if(RTC_SR & RTC_SR_TOF_MASK)//计数溢出
  {
    RTC_SR = 0;
    RTC_TSR = 0;
    
    //Put Your Code...
    
  }
  
  if(RTC_SR & RTC_SR_TAF_MASK)//Alarm报警
  {
    RTC_TAR = 0;
    
    //Put Your Code...
  }
  
}