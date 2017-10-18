/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_LPTMR.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      LPTMR脉冲计数初始化
 *  @param      LPT0_ALTn       LPT0_ALTx       LPTMR脉冲计数管脚
 *  @param      LPT_CFG         LPT_CFG_x       LPTMR脉冲计数方式:上升沿计数或下降沿计数
 *  @param      uint16          LPT_Count       LPTMR脉冲比较值
 *  @since      v1.0
 *  Sample usage:       LPTMR_Pluse_Init(LPT0_ALT1,LPT_Rising,0xFFFF);// LPTMR 脉冲计数，计数0xFFFF后触发中断请求（需要开中断才执行中断服务函数），上升沿捕捉
 */
void LPTMR_Pluse_Init(LPT0_ALTn LPT0_ALTx,LPT_CFG LPT_CFG_x,uint16 LPT_Count)
{
  OSC_CR |= OSC_CR_ERCLKEN_MASK;//使能外部晶振参考时钟
  
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMR时钟使能
  
  switch(LPT0_ALTx)//LPTMR复用
  {
    case LPT0_ALT1:
                    PORT_Init(PTA19,ALT6);//PTA19复用ALT6
                    break;
    case LPT0_ALT2:
                    PORT_Init(PTC5,ALT4);//PTC5复用ALT4
                    break;
    default:
                    ASSERT(0);
                    break;
  }

  LPTMR0_CSR = 0;//清LPTMR0_CSR寄存器
  
  LPTMR0_PSR = (0 
                | LPTMR_PSR_PCS(3)      //时钟源选择OSC晶振时钟
                | LPTMR_PSR_PRESCALE(4) //预分频设置2^(n+1)
                );
  
  LPTMR0_CMR = LPTMR_CMR_COMPARE(LPT_Count);//设置LPTMR计数比较值
  
  LPTMR0_CSR = (0
                | LPTMR_CSR_TPS(LPT0_ALTx)//LPTMR脉冲输入,ALT1,ALT2
                | LPTMR_CSR_TMS_MASK//选择脉冲计数模式
                | (LPT_CFG_x == LPT_Falling ? LPTMR_CSR_TPP_MASK : 0)//选择脉冲计数方式,上升沿计数,下降沿计数
                | LPTMR_CSR_TEN_MASK//LPTMR定时器使能
                | LPTMR_CSR_TIE_MASK//LPTMR定时器中断使能
                );

}

/*
 *  @brief      获取LPTMR脉冲计数值
 *  @return     脉冲计数值
 *  @since      v1.0
 *  Sample usage:       uint16 data = LPTMR_Pluse_Get();//获取脉冲计数值
 */
uint16 LPTMR_Pluse_Get(void)
{
  uint16 LPTMR_Data=0;

  if(LPTMR0_CSR & LPTMR_CSR_TCF_MASK)//LPTMR计数器溢出
  {
    LPTMR_Data = ~0;
  }
  else
  {
    LPTMR0_CNR = LPTMR_CNR_COUNTER(0);
    LPTMR_Data = LPTMR0_CNR;//读取LPTMR脉冲计数值
  }
  
  return LPTMR_Data;
}

/*
 *  @brief      清空LPTMR脉冲计数
 *  @since      v1.0
 *  Sample usage:       LPTMR_Count_Clean();//清空LPTMR脉冲计数
 */
void LPTMR_Count_Clean(void)
{
  LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;//禁止LPTMR计数器
  LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;//使能LPTMR计数器
}

/*
 *  @brief      LPTMR延时函数(ms)
 *  @param      uint16          LPTMR_Delay      LPTMR延时时间(0~65535)
 *  @since      v1.0
 *  Sample usage:       LPTMR_Delay_ms(32);     //LPTMR延时32ms
 */
void LPTMR_Delay_ms(uint16 LPTMR_Delay)
{
  //断言延时时间大于0
  ASSERT(LPTMR_Delay > 0);

  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMR时钟使能
  
  LPTMR0_CSR = 0;//清LPTMR0_CSR寄存器
  LPTMR0_CMR = LPTMR_Delay;//设置比较时间

  LPTMR0_PSR = (0
                | LPTMR_PSR_PCS(1)      //选择LPO(1KHz)时钟源
                | LPTMR_PSR_PBYP_MASK   //旁路预分频/干扰滤波器
                );
  
  LPTMR0_CSR = (0 | LPTMR_CSR_TEN_MASK);//使能LPTMR定时器
  
  while((LPTMR0_CSR & LPTMR_CSR_TCF_MASK) != LPTMR_CSR_TCF_MASK);
  LPTMR0_CSR &= ~LPTMR_CSR_TCF_MASK;//清除比较标志位
  
}

/*
 *  @brief      LPTMR定时函数(ms)
 *  @param      uint16          LPTMR_Delay      LPTMR延时时间(0~65535)
 *  @since      v1.0
 *  Sample usage:
                    LPTMR_Timing_ms(32);                                // LPTMR 定时 32ms
                    Set_Vector_Handler(LPTimer_VECTORn,lptmr_hander);   // 设置中断服务函数到中断向量表里
                    enable_irq(LPTimer_IRQn);                           // 使能LPTMR中断
 */
void LPTMR_Timing_ms(uint16 LPTMR_Delay)
{
  //断言延时时间大于0
  ASSERT(LPTMR_Delay > 0);
  
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMR时钟使能
  
  LPTMR0_CSR = 0;//清LPTMR0_CSR寄存器
  LPTMR0_CMR = LPTMR_Delay;//设置比较时间
  
  LPTMR0_PSR = (0
                | LPTMR_PSR_PCS(1)      //选择LPO(1KHz)时钟源
                | LPTMR_PSR_PBYP_MASK   //旁路预分频/干扰滤波器
                );
  
  LPTMR0_CSR = (0 | LPTMR_CSR_TEN_MASK | LPTMR_CSR_TIE_MASK);//使能LPTMR定时器,使能LPTMR定时器中断
  
}

/*
 *  @brief      LPTMR延时函数(us)
 *  @param      uint16          LPTMR_Delay      LPTMR延时时间(0~41942)
 *  @since      v1.0
 *  Sample usage:       LPTMR_Delay_us(32);     //LPTMR延时32us
 */
void LPTMR_Delay_us(uint16 LPTMR_Delay)
{
  //断言定时时长,确保寄存器不会溢出
  ASSERT((((EXTAL_IN_MHz * LPTMR_Delay + 16) / 32) < 0xffff) && (LPTMR_Delay > 0));
  
  OSC_CR |= OSC_CR_ERCLKEN_MASK;//使能外部晶振参考时钟
  
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMR时钟使能
  
  LPTMR0_CSR = 0;//清LPTMR0_CSR寄存器
  
  LPTMR0_CMR = (EXTAL_IN_MHz * LPTMR_Delay + 16) / 32;//设置比较时间
  
  LPTMR0_PSR = (0
                | LPTMR_PSR_PCS(3)      //时钟源选择OSC晶振时钟
                | LPTMR_PSR_PRESCALE(4) //预分频设置2^(n+1)
                );
  
  LPTMR0_CSR = (0 | LPTMR_CSR_TEN_MASK);//LPTMR时钟使能
  
  while((LPTMR0_CSR & LPTMR_CSR_TCF_MASK) != LPTMR_CSR_TCF_MASK);
  LPTMR0_CSR &= ~LPTMR_CSR_TCF_MASK;//清除比较标志位
  
}

/*
 *  @brief      LPTMR定时函数(us)
 *  @param      uint16          LPTMR_Delay      LPTMR延时时间(0~41942)
 *  @since      v1.0
 *  Sample usage:
                    LPTMR_Timing_us(32);                                // LPTMR 定时32us
                    Set_Vector_Handler(LPTimer_VECTORn,lptmr_hander);   // 设置中断服务函数到中断向量表里
                    enable_irq(LPTimer_IRQn);                           // 使能LPTMR中断
 */
void LPTMR_Timing_us(uint16 LPTMR_Delay)
{
  //断言定时时长,确保寄存器不会溢出
  ASSERT((((EXTAL_IN_MHz * LPTMR_Delay + 16) / 32) < 0xffff) && (LPTMR_Delay > 0));
  
  OSC_CR |= OSC_CR_ERCLKEN_MASK;//使能外部晶振参考时钟
  
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMR时钟使能
  
  LPTMR0_CSR = 0;//清LPTMR0_CSR寄存器
  
  LPTMR0_CMR = (EXTAL_IN_MHz * LPTMR_Delay + 16) / 32;//设置比较时间
  
  LPTMR0_PSR = (0
                | LPTMR_PSR_PCS(3)      //时钟源选择OSC晶振时钟
                | LPTMR_PSR_PRESCALE(4) //预分频设置2^(n+1)
                );
  
  LPTMR0_CSR = (0 | LPTMR_CSR_TEN_MASK | LPTMR_CSR_TIE_MASK);//LPTMR时钟使能,LPTMR中断使能
  
}