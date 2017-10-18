/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PIT.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      PITn定时中断
 *  @param      PITn    PITx    模块号(PIT0~PIT3)
 *  @param      uint32  PIT_Count       定时中断时间(单位为bus时钟周期)
 *  @since      v1.0
 *  Sample usage:
                PIT_Init(PIT0,1000);                           //定时 1000 个bus时钟 后中断
                Set_Vector_Handler(PIT0_VECTORn,pit_hander);   //设置中断服务函数到中断向量表里
                enable_irq(PIT0_IRQn);                         //使能PIT中断
 */
void PIT_Init(PITn PITx,uint32 PIT_Count)
{
  //断言PIT模块号,PIT定时值大于0
  ASSERT((PITx <= PIT3) && (PIT_Count > 0));
  
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;//PIT时钟使能
  
  PIT_MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);//调试模式下PIT运行,PIT使能
  PIT_LDVAL(PITx) = PIT_Count - 1;//加载PIT定时器初值(减计数器)
  
  PIT_Flag_Clear(PITx);//清中断标志
  
  PIT_TCTRL(PITx) = (0 | PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);//定时器中断使能,定时器使能,不使用计数器级联
  
}

/*
 *  @brief      PITn延时
 *  @param      PITn    PITx    模块号(PIT0~PIT3)
 *  @param      uint32  PIT_Count       延时时间(单位为bus时钟周期)
 *  @since      v1.0
 *  Sample usage:       PIT_Delay(PIT0, 1000);  //延时 1000 个bus时钟
 */
void PIT_Delay(PITn PITx,uint32 PIT_Count)
{
  //断言PIT模块号,PIT定时值大于0
  ASSERT((PITx <= PIT3) && (PIT_Count > 0));
  
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;//PIT时钟使能
  
  PIT_MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);//调试模式下PIT运行,PIT使能
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//禁止PIT中断
  PIT_LDVAL(PITx) = PIT_Count - 1;//加载PIT定时器初值(减计数器)
  
  PIT_Flag_Clear(PITx);//清中断标志
  
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//禁止PIT中断
  
  
  PIT_TCTRL(PITx) = (0 | PIT_TCTRL_TEN_MASK);//定时器使能,不使用计数器级联
  
  while((PIT_TFLG(PITx) & PIT_TFLG_TIF_MASK) != PIT_TFLG_TIF_MASK);
  
  PIT_Flag_Clear(PITx);//清中断标志
  
}

/*
 *  @brief      PITn计时开始
 *  @param      PITn    PITx    模块号(PIT0~PIT3)
 *  @since      v1.0
 *  Sample usage:       PIT_Time_Start(PIT0);//PIT0计时开始
 */
void PIT_Time_Start(PITn PITx)
{
  //断言PIT模块号
  ASSERT(PITx <= PIT3);
  
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;//PIT时钟使能
  
  PIT_MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);//调试模式下PIT运行,PIT使能
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//禁止PIT中断
  PIT_LDVAL(PITx) = ~0;//加载PIT定时器初值(减计数器)
  
  PIT_Flag_Clear(PITx);//清中断标志
  
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//禁止PIT中断
  PIT_TCTRL(PITx) = (0 | PIT_TCTRL_TEN_MASK);//定时器使能,不使用计数器级联
  
}

/*
 *  @brief      获取 PITn计时时间(超时时会关闭定时器)
 *  @param      PITn    PITx    模块号(PIT0~PIT3)
 *  @since      v1.0
 *  Sample usage:       uint32 time = PIT_Time_Get(PIT0);       //获取 PITn计时时间
 */
uint32 PIT_Time_Get(PITn PITx)
{
  uint32 PIT_Value=0;
  
  //断言PIT模块号
  ASSERT(PITx <= PIT3);
  
  PIT_Value = ~0 - PIT_CVAL(PITx);//计数时间值=计数初值0~-当前计数值PIT_CVAL
  
  if(PIT_TFLG(PITx) & PIT_TFLG_TIF_MASK)//是否超出计数时间
  {
    PIT_Flag_Clear(PITx);//溢出标志清零
    PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//禁止PIT中断
    return ~0;
  }
  
  if(PIT_Value == ~0)
  {
    PIT_Value = 0xffffffff - 0x1;
  }
  
  return PIT_Value;
  
}

/*
 *  @brief      关闭PIT
 *  @param      PITn    PITx    模块号(PIT0~PIT3)
 *  @since      v1.0
 *  Sample usage:        PIT_Close(PIT0);       //关闭PIT
 */
void PIT_Close(PITn PITx)
{
  //断言PIT模块号
  ASSERT(PITx <= PIT3);
  
  PIT_Flag_Clear(PITx);//溢出标志清零
  PIT_TCTRL(PITx) &= ~PIT_TCTRL_TEN_MASK;//禁止PIT中断
  
}