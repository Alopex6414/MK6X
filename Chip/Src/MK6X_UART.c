/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_UART.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**UART基址指针
*/
UART_MemMapPtr UARTN[UART_UART_MAX]=
{
  UART0_BASE_PTR,//UART0基址指针
  UART1_BASE_PTR,//UART1基址指针
  UART2_BASE_PTR,//UART2基址指针
  UART3_BASE_PTR,//UART3基址指针
  UART4_BASE_PTR,//UART4基址指针
  #ifdef MK64F12
  UART5_BASE_PTR,//UART5基址指针
  #endif
};

/*
 *  @brief      初始化串口UART,设置波特率
 *  @param      UART_UARTn      UART_UARTx      模块号(UART0~UART4)
 *  @param      uint32          UART_Baud       波特率,如9600、19200、56000、115200等
 *  @since      v1.0
 *  Sample usage:       UART_Init(UART3,115200);        //初始化串口,波特率为115200
 */
void UART_Init(UART_UARTn UART_UARTx,uint32 UART_Baud)
{
  uint8 UART_Temp=0;
  uint32 UART_SysClk=0;
  register uint16 UART_Sbr=0;
  register uint16 UART_Brfa=0;
  
  //UART管脚复用
  switch(UART_UARTx)
  {
    case UART_UART0:
                    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;//UART0时钟使能
                    if(UART0_RX_PIN == PTA1)
                    {
                      PORT_Init(UART0_RX_PIN,ALT2);
                    }
                    else if((UART0_RX_PIN == PTA15) || (UART0_RX_PIN == PTB16) || (UART0_RX_PIN == PTD6))
                    {
                      PORT_Init(UART0_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if(UART0_TX_PIN == PTA2)
                    {
                      PORT_Init(UART0_TX_PIN,ALT2);
                    }
                    else if((UART0_TX_PIN == PTA14) || (UART0_TX_PIN == PTB17) || (UART0_TX_PIN == PTD7))
                    {
                      PORT_Init(UART0_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    case UART_UART1:
                    SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;//UART1时钟使能
                    if((UART1_RX_PIN == PTC3) || (UART1_RX_PIN == PTE1))
                    {
                      PORT_Init(UART1_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if((UART1_TX_PIN == PTC4) || (UART1_TX_PIN == PTE0))
                    {
                      PORT_Init(UART1_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    case UART_UART2:
                    SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;//UART2时钟使能
                    if(UART2_RX_PIN == PTD2)
                    {
                      PORT_Init(UART2_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if(UART2_TX_PIN == PTD3)
                    {
                      PORT_Init(UART2_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    case UART_UART3:
                    SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;//UART3时钟使能
                    if((UART3_RX_PIN == PTB10)|| (UART3_RX_PIN == PTC16) || (UART3_RX_PIN == PTE5))
                    {
                      PORT_Init(UART3_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if((UART3_TX_PIN == PTB11) || (UART3_TX_PIN == PTC17) || (UART3_TX_PIN == PTE4))
                    {
                      PORT_Init(UART3_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    case UART_UART4:
                    SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;//UART4时钟使能
                    if((UART4_RX_PIN == PTC14) || (UART4_RX_PIN == PTE25))
                    {
                      PORT_Init(UART4_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if((UART4_TX_PIN == PTC15) || (UART4_TX_PIN == PTE24))
                    {
                      PORT_Init(UART4_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    #ifdef MK64F12
    case UART_UART5:
                    SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
                    if((UART5_RX_PIN == PTD8) || (UART5_RX_PIN == PTE9))
                    {
                      PORT_Init(UART5_RX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    
                    if((UART5_TX_PIN == PTD9) ||(UART5_TX_PIN == PTE8))
                    {
                      PORT_Init(UART5_TX_PIN,ALT3);
                    }
                    else
                    {
                      ASSERT(0);
                    }
                    break;
    #endif                
    default:
                    ASSERT(0);
                    break;
  }
  
  //UART寄存器配置
  UART_C2_REG(UARTN[UART_UARTx]) &= ~(0 | UART_C2_RE_MASK | UART_C2_TE_MASK);//禁止接受发送
  UART_C1_REG(UARTN[UART_UARTx]) = 0;
  
  //UART时钟设置
  if(UART_UARTx == UART_UART0 || UART_UARTx == UART_UART1)//UART0,UART1
  {
    UART_SysClk = MK6X_Core_KHz * 1000;//Core时钟
  }
  else
  {
    UART_SysClk = MK6X_Bus_KHz * 1000;//Bus时钟
  }
  
  //UART波特率计算 UART_Baud = UART_SysClk / (16 * (SBR + BRFD))
  UART_Sbr = (uint16)(UART_SysClk / (UART_Baud * 16));
  
  if(UART_Sbr > 0x1FFF)
  {
    UART_Sbr = 0x1FFF;
  }
  
  //BRFA波特率调整值
  UART_Brfa = (UART_SysClk / UART_Baud) - (UART_Sbr * 16);
  ASSERT(UART_Brfa <= 0x1F);
  
  //UART配置
  UART_Temp = UART_BDH_REG(UARTN[UART_UARTx]) & (~UART_BDH_SBR_MASK);//保存BDH寄存器其他设置
  UART_BDH_REG(UARTN[UART_UARTx]) = UART_Temp | UART_BDH_SBR(UART_Sbr >> 8);//BDH波特率高位写入
  UART_BDL_REG(UARTN[UART_UARTx]) = UART_BDL_SBR(UART_Sbr & 0xff);//BDL波特率低位写入
  
  UART_Temp = UART_C4_REG(UARTN[UART_UARTx]) & (~UART_C4_BRFA_MASK);//保存C4寄存器其他设置
  UART_C4_REG(UARTN[UART_UARTx]) = UART_Temp | UART_C4_BRFA(UART_Brfa);//C4写入BRFA波特率调整值
  
  //UART设置FIFO
  UART_PFIFO_REG(UARTN[UART_UARTx]) = (0 | UART_PFIFO_RXFE_MASK | UART_PFIFO_TXFE_MASK);
  
  //允许发送接收
  UART_C2_REG(UARTN[UART_UARTx]) |= (0 | UART_C2_RE_MASK | UART_C2_TE_MASK);//允许发送接收
  
}

/*
 *  @brief      UART接受1个字节
 *  @param      UART_UARTn      UART_UARTx      模块号(UART0~UART4)
 *  @param      char            ch              UART接受字节
 *  @since      v1.0
 *  Sample usage:
                        UART_GetChar(UART3,&ch);   //等待接受1个字节,保存到ch里
 */
void UART_GetChar(UART_UARTn UART_UARTx,char *ch)
{
  while(!(UART_S1_REG(UARTN[UART_UARTx]) & UART_S1_RDRF_MASK));//等待数据接收
  
  *ch = UART_D_REG(UARTN[UART_UARTx]);//读取缓冲寄存器接收值
}

/*
 *  @brief      UART发送一个字节
 *  @param      UART_UARTn      UART_UARTx      模块号(UART0~UART4)
 *  @param      char            ch              UART发送字节
 *  @since      v1.0
 *  Sample usage:       UART_PutChar(UART3,'A');  //发送字节'A'
 */
void UART_PutChar(UART_UARTn UART_UARTx,char ch)
{
  while(!(UART_S1_REG(UARTN[UART_UARTx]) & UART_S1_TDRE_MASK));//等待发送缓冲
  
  UART_D_REG(UARTN[UART_UARTx]) = (uint8)ch;//发送一个字节数据
}

/*
 *  @brief      UART发送字符串(遇NULL停止发送)
 *  @param      UART_UARTn      UART_UARTx      模块号(UART0~UART4)
 *  @param      str             字符串地址
 *  @since      v1.0
 *  Sample usage:       UART_PutStr(UART3,"1234567");//实际发送了7个字节
 */
void UART_PutStr(UART_UARTn UART_UARTx,const uint8 *str)
{
  for(;*str!='\0';str++)
  {
    while(!(UART_S1_REG(UARTN[UART_UARTx]) & UART_S1_TDRE_MASK));//等待发送缓冲
  
    UART_D_REG(UARTN[UART_UARTx]) = (uint8)(*str);//发送一个字节数据
  }
}

/*
 *  @brief      开UART接收中断
 *  @param      UART_UARTn      UART_UARTx      模块号(UART0~UART4)
 *  @since      v1.0
 *  Sample usage:       UART_Rx_IRQ_En(UART3);         //开串口3接收中断
 */
void UART_Rx_IRQ_En(UART_UARTn UART_UARTx)
{
  UART_C2_REG(UARTN[UART_UARTx]) |= UART_C2_RIE_MASK;//UART接受中断使能
  if(UART_UARTx == UART_UART4)
  {
    enable_irq(UART4_RX_TX_IRQn);//IRQ中断
  }
  else
  {
    enable_irq((IRQn_Type)((UART_UARTx<<1) + UART0_RX_TX_IRQn));//IRQ中断
  }
}

/*
 *  @brief      开UART发送中断
 *  @param      UART_UARTn      UART_UARTx      模块号(UART0~UART4)
 *  @since      v1.0
 *  Sample usage:       UART_Tx_IRQ_En(UART3);         //开串口3接收中断
 */
void UART_Tx_IRQ_En(UART_UARTn UART_UARTx)
{
  UART_C2_REG(UARTN[UART_UARTx]) |= UART_C2_TIE_MASK;//UART发送中断使能
  if(UART_UARTx == UART_UART4)
  {
    enable_irq(UART4_RX_TX_IRQn);//IRQ中断
  }
  else
  {
    enable_irq((IRQn_Type)((UART_UARTx<<1) + UART0_RX_TX_IRQn));//IRQ中断
  }
}

/*
 *  @brief      关UART接收中断
 *  @param      UART_UARTn      UART_UARTx      模块号(UART0~UART4)
 *  @since      v1.0
 *  Sample usage:       UART_Rx_IRQ_Dis(UART3);         //关串口3接收中断
 */
void UART_Rx_IRQ_Dis(UART_UARTn UART_UARTx)
{
  UART_C2_REG(UARTN[UART_UARTx]) &= ~UART_C2_RIE_MASK;//UART接受中断关闭
  
  if(!(UART_C2_REG(UARTN[UART_UARTx]) & (UART_C2_TIE_MASK | UART_C2_TCIE_MASK)))
  {
    if(UART_UARTx == UART_UART4)
    {
      disable_irq(UART4_RX_TX_IRQn);//关闭中断
    }
    else
    {
      disable_irq((IRQn_Type)((UART_UARTx<<1) + UART0_RX_TX_IRQn));//关闭中断
    }
  }
}

/*
 *  @brief      关UART发送中断
 *  @param      UART_UARTn      UART_UARTx      模块号(UART0~UART4)
 *  @since      v1.0
 *  Sample usage:       UART_Tx_IRQ_Dis(UART3);         //关串口3发送中断
 */
void UART_Tx_IRQ_Dis(UART_UARTn UART_UARTx)
{
  UART_C2_REG(UARTN[UART_UARTx]) &= ~UART_C2_TIE_MASK;//UART发送中断关闭
  
  if(!(UART_C2_REG(UARTN[UART_UARTx]) & UART_C2_RIE_MASK))
  {
    if(UART_UARTx == UART_UART4)
    {
      disable_irq(UART4_RX_TX_IRQn);//关闭中断
    }
    else
    {
      disable_irq((IRQn_Type)((UART_UARTx<<1) + UART0_RX_TX_IRQn));//关闭中断
    }
  }
}