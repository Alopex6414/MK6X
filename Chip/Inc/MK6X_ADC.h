/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_ADC.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_ADC_H__
#define __MK6X_ADC_H__

#include "Common.h"

/*
**ADC端口枚举(ADC0,ADC1)
*/
typedef enum
{
  /*
  **ADC0
  */
  ADC0_DP0,
  ADC0_DP1,
  PGA0_DP,        //不支持ADC，需要配置 ADC PGA register 设置放大增益
  ADC0_DP3,
  
  ADC0_SE4b,      // PTC2     不支持软件ADC
  ADC0_SE5b,      // PTD1     不支持软件ADC
  ADC0_SE6b,      // PTD5     不支持软件ADC
  ADC0_SE7b,      // PTD6     不支持软件ADC
  
  ADC0_SE8,       // PTB0
  ADC0_SE9,       // PTB1
  ADC0_SE10,      // PTA7
  ADC0_SE11,      // PTA8
  ADC0_SE12,      // PTB2
  ADC0_SE13,      // PTB3
  ADC0_SE14,      // PTC0
  ADC0_SE15,      // PTC1
  ADC0_SE16,      // ADC0_SE16
  ADC0_SE17,      // PTE24
  ADC0_SE18,      // PTE25
  ADC0_DM0,       // ADC0_DM0
  ADC0_DM1,       // ADC0_DM1
  ADC0_SE21,      // 保留
  ADC0_SE22,      // 保留
  DAC0_OUT,       // DAC0输出 不支持ADC
  RES2,           // 保留
  RES3,           // 保留
  Temp0_Sensor,   // Temperature Sensor,内部温度测量，可用ADC函数
  Bandgap0,       // 温度补偿结构带隙基准源   不支持ADC
  RES4,           // 保留
  VREFH0,         // 参考高电压,可用ADC函数 ,结果恒为 2^n-1
  VREFL0,         // 参考低电压,可用ADC函数 ,结果恒为 0
  Module0_Dis,    // 不支持 ADC
  
  /*
  **ADC1
  */
  ADC1_DP0,
  ADC1_DP1,
  PGA1_DP,        // 不支持 ADC
  ADC1_DP3,
  ADC1_SE4a,      // PTE0
  ADC1_SE5a,      // PTE1
  ADC1_SE6a,      // PTE2
  ADC1_SE7a,      // PTE3
  
  ADC1_SE4b = ADC1_SE4a,  // PTC8    B通道 不支持软件ADC ,传递 ADC1_SE4b 到软件ADC函数里，会当作 ADC1_SE4a 处理。
  ADC1_SE5b = ADC1_SE5a,  // PTC9    B通道 不支持软件ADC
  ADC1_SE6b = ADC1_SE6a,  // PTC10   B通道 不支持软件ADC
  ADC1_SE7b = ADC1_SE7a,  // PTC11   B通道 不支持软件ADC
  
  ADC1_SE8,       // PTB0
  ADC1_SE9,       // PTB1
  ADC1_SE10,      // PTB4
  ADC1_SE11,      // PTB5
  ADC1_SE12,      // PTB6
  ADC1_SE13,      // PTB7
  ADC1_SE14,      // PTB10
  ADC1_SE15,      // PTB11
  ADC1_SE16,      // ADC1_SE16
  ADC1_SE17,      // PTA17
  VREF_OUTPUT,    // VREF Output
  ADC1_DM0,       // ADC1_DM0
  ADC1_DM1,       // ADC1_DM1
  RES5,           // 保留
  RES6,           // 保留
  DAC1_OUT,       // DAC1输出 不支持ADC
  RES7,           // 保留
  RES8,           // 保留
  Temp1_Sensor,   // Temperature Sensor,内部温度测量，可用ADC函数
  Bandgap1,       // 温度补偿结构带隙基准源   不支持ADC
  RES9,           // 保留
  VREFH1,         // 参考高电压,可用ADC函数 ,结果恒为 2^n-1
  VREFL1,         // 参考低电压,可用ADC函数 ,结果恒为 0
  Module1_Dis,    // 不支持 ADC 
}ADCn_CHn;

/*
**ADC模块枚举
*/
typedef enum
{
  ADC_ADC0,
  ADC_ADC1,
  ADC_ADC_MAX,
}ADC_ADCn;

/*
**ADC精度位数
*/
typedef enum
{
  ADC_8Bit=0x00,
  ADC_10Bit=0x02,
  ADC_12Bit=0x01,
  ADC_16Bit=0x03,
}ADC_nBit;

/*
**ADC通道枚举(A通道,B通道)
*/
typedef enum
{
  ADC_Channel_A,
  ADC_Channel_B,
}ADC_Channel_n;

/*
**ADC模块号宏
*/
#define ADCn(ADCn_CHx)          ((ADCn_CHx)>>5)  //ADCn=ADC_CHx/32
#define ADC_CHn(ADCn_CHx)       ((ADCn_CHx)&0x1f)//ADC_CHn=ADC_CHx%31

/*
**variate declaration
*/
extern ADC_MemMapPtr ADCN[ADC_ADC_MAX];

/*
**function declaration
*/
extern void ADC_Init(ADCn_CHn ADCn_CHx);
//extern void ADC_Start(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit);
extern void ADC_Stop(ADC_ADCn ADC_ADCx);
extern uint16 ADC_Once(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit);
extern uint16 ADC_Average(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit,uint8 ADC_Samp_Num);
extern void ADC_Samp_Array(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit,uint16 *ADC_Array);


#endif