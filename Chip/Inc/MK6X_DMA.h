/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_DMA.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_DMA_H__
#define __MK6X_DMA_H__

#include "Common.h"
#include "MK6X_PORT.h"

/*
**DMA通道枚举
*/
typedef enum
{
  /*
  **禁用通道
  */
  Channel_Disabled = 0,
  
  /*
  **UART
  */
  DMA_UART0_Rx = 2,
  DMA_UART0_Tx = 3,
  DMA_UART1_Rx = 4,
  DMA_UART1_Tx = 5,
  DMA_UART2_Rx = 6,
  DMA_UART2_Tx = 7,
  DMA_UART3_Rx = 8,
  DMA_UART3_Tx = 9,
  DMA_UART4_Rx_Or_Tx = 10,
  
  /*
  **I2S
  */
  DMA_I2S0_Rx = 12,
  DMA_I2S0_Tx = 13,
  
  /*
  **SPI
  */
  DMA_SPI0_Rx = 14,
  DMA_SPI0_Tx = 15,
  DMA_SPI1_Rx = 16,
  DMA_SPI1_Tx = 17,
  
  /*
  **I2C
  */
  DMA_I2C0_Or_I2C3 = 18,
  DMA_I2C1_Or_I2C2 = 19,
  
  /*
  **FTM
  */
  DMA_FTM0_CH0 = 20,
  DMA_FTM0_CH1 = 21,
  DMA_FTM0_CH2 = 22,
  DMA_FTM0_CH3 = 23,
  DMA_FTM0_CH4 = 24,
  DMA_FTM0_CH5 = 25,
  DMA_FTM0_CH6 = 26,
  DMA_FTM0_CH7 = 27,
  DMA_FTM1_Or_TMP1_CH0 = 28,
  DMA_FTM1_Or_TMP1_CH1 = 29,
  DMA_FTM2_Or_TMP2_CH0 = 30,
  DMA_FTM2_Or_TMP2_CH1 = 31,
  DMA_FTM3_CH0 = 32,
  DMA_FTM3_CH1 = 33,
  DMA_FTM3_CH2 = 34,
  DMA_FTM3_CH3 = 35,
  DMA_FTM3_CH4 = 36,
  DMA_FTM3_CH5 = 37,
  DMA_FTM3_CH6_Or_SPI2_Rx = 38,
  DMA_FTM3_CH7_Or_SPI2_Tx = 39,
  
  /*
  **ADC&DAC
  */
  DMA_ADC0 = 40,
  DMA_ADC1 = 41,
  DMA_CMP0 = 42,
  DMA_CMP1 = 43,
  DMA_CMP2_Or_CMP3 = 44,
  DMA_DAC0 = 45,
  DMA_DAC1 = 46,
  DMA_CMT = 47,
  DMA_PDB = 48,
  
  /*
  **PORT
  */
  DMA_PORTA = 49,
  DMA_PORTB = 50,
  DMA_PORTC = 51,
  DMA_PORTD = 52,
  DMA_PORTE = 53,
  
  /*
  **IEEE
  */
  DMA_IEEE_TIM0 = 54,
  DMA_IEEE_TIM1_Or_TPM1 = 55,
  DMA_IEEE_TIM2_Or_TPM2 = 56,
  DMA_IEEE_TIM3 = 57,
  
  /*
  **LPUART
  */
  DMA_LPUART0_Rx = 58,
  DMA_LPUART0_Tx = 59,
  
  /*
  **DMA_MUX
  */
  DMA_Always_EN1 = 60,
  DMA_Always_EN2 = 61,
  DMA_Always_EN3 = 62,
  DMA_Always_EN4 = 63,
  
}DMA_Sources;

/*
**DMA配置
*/
typedef enum
{
  DADDR_RECOVER,//恢复目的地址
  DADDR_KEEPON, //目的地址保持不变
}DMA_CFG;

/*
**DMA每次传输字节数
*/
typedef enum
{
  DMA_BYTE1 = 0,
  DMA_BYTE2 = 1,
  DMA_BYTE4 = 2,
  DMA_BYTE16 = 4,
}DMA_BYTEn;

/*
**DMA传输通道
*/
typedef enum
{
  DMA_CH0,
  DMA_CH1,
  DMA_CH2,
  DMA_CH3,
  DMA_CH4,
  DMA_CH5,
  DMA_CH6,
  DMA_CH7,
  DMA_CH8,
  DMA_CH9,
  DMA_CH10,
  DMA_CH11,
  DMA_CH12,
  DMA_CH13,
  DMA_CH14,
  DMA_CH15,
  #ifdef MK66F18
  DMA_CH16,
  DMA_CH17,
  DMA_CH18,
  DMA_CH19,
  DMA_CH20,
  DMA_CH21,
  DMA_CH22,
  DMA_CH23,
  DMA_CH24,
  DMA_CH25,
  DMA_CH26,
  DMA_CH27,
  DMA_CH28,
  DMA_CH29,
  DMA_CH30,
  DMA_CH31,
  #endif
}DMA_CHn;

/*
**DMA中断相关宏
*/
#define  DMA_EN(DMA_CHn)        DMA_ERQ |= (DMA_ERQ_ERQ0_MASK<<(DMA_CHn))                       //使能通道硬件DMA请求
#define  DMA_DIS(DMA_CHn)       DMA_ERQ &=~(DMA_ERQ_ERQ0_MASK<<(DMA_CHn))                       //禁止通道硬件DMA请求

#if defined(MK66F18)
#define  DMA_IRQ_EN(DMA_CHn)    enable_irq((IRQn_Type)((IRQn_Type)DMA_CHn + DMA0_DMA16_IRQn))   //允许DMA通道传输完成中断
#define  DMA_IRQ_DIS(DMA_CHn)   disable_irq((IRQn_Type)((IRQn_Type)DMA_CHn + DMA0_DMA16_IRQn))  //禁止DMA通道传输完成中断
#elif defined(MK64F12)
#define  DMA_IRQ_EN(DMA_CHn)    enable_irq((IRQn_Type)((IRQn_Type)DMA_CHn + DMA0_IRQn))   //允许DMA通道传输完成中断
#define  DMA_IRQ_DIS(DMA_CHn)   disable_irq((IRQn_Type)((IRQn_Type)DMA_CHn + DMA0_IRQn))  //禁止DMA通道传输完成中断
#endif
#define  DMA_IRQ_CLEAN(DMA_CHn) DMA_INT|=(DMA_INT_INT0_MASK<<DMA_CHn)                           //清除通道传输中断标志位

#define  DMA_CHn_DIS(DMA_CHn)   DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,DMA_CHn) &= ~DMAMUX_CHCFG_SOURCE(Channel_Disabled)  //禁用通道

/*
**DMA计数相关宏
*/
#define DMA_COUNTSADDR      0x4004000C      //DMA计数源地址
#define DMA_COUNTDADDR      0x4004000C      //DMA计数目的地址

/*
**variate declaration
*/
extern uint32 DMA_Count_Array[32];

/*
**function declaration
*/
extern void DMA_PORTX_To_Buff_Init(DMA_CHn DMA_CHx,void *SADDR,void *DADDR,PTXn PTXx,DMA_BYTEn DMA_BYTEx,uint32 Count,DMA_CFG CFG);
extern void DMA_Count_Init(DMA_CHn DMA_CHx,PTXn PTXx,uint32 DMA_Count,PORT_CFG DMA_cfg);
extern uint32 DMA_Count_Get(DMA_CHn DMA_CHx);
extern void DMA_Count_Reset(DMA_CHn DMA_CHx);


#endif