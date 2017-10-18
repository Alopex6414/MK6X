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
**ADC�˿�ö��(ADC0,ADC1)
*/
typedef enum
{
  /*
  **ADC0
  */
  ADC0_DP0,
  ADC0_DP1,
  PGA0_DP,        //��֧��ADC����Ҫ���� ADC PGA register ���÷Ŵ�����
  ADC0_DP3,
  
  ADC0_SE4b,      // PTC2     ��֧�����ADC
  ADC0_SE5b,      // PTD1     ��֧�����ADC
  ADC0_SE6b,      // PTD5     ��֧�����ADC
  ADC0_SE7b,      // PTD6     ��֧�����ADC
  
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
  ADC0_SE21,      // ����
  ADC0_SE22,      // ����
  DAC0_OUT,       // DAC0��� ��֧��ADC
  RES2,           // ����
  RES3,           // ����
  Temp0_Sensor,   // Temperature Sensor,�ڲ��¶Ȳ���������ADC����
  Bandgap0,       // �¶Ȳ����ṹ��϶��׼Դ   ��֧��ADC
  RES4,           // ����
  VREFH0,         // �ο��ߵ�ѹ,����ADC���� ,�����Ϊ 2^n-1
  VREFL0,         // �ο��͵�ѹ,����ADC���� ,�����Ϊ 0
  Module0_Dis,    // ��֧�� ADC
  
  /*
  **ADC1
  */
  ADC1_DP0,
  ADC1_DP1,
  PGA1_DP,        // ��֧�� ADC
  ADC1_DP3,
  ADC1_SE4a,      // PTE0
  ADC1_SE5a,      // PTE1
  ADC1_SE6a,      // PTE2
  ADC1_SE7a,      // PTE3
  
  ADC1_SE4b = ADC1_SE4a,  // PTC8    Bͨ�� ��֧�����ADC ,���� ADC1_SE4b �����ADC������ᵱ�� ADC1_SE4a ����
  ADC1_SE5b = ADC1_SE5a,  // PTC9    Bͨ�� ��֧�����ADC
  ADC1_SE6b = ADC1_SE6a,  // PTC10   Bͨ�� ��֧�����ADC
  ADC1_SE7b = ADC1_SE7a,  // PTC11   Bͨ�� ��֧�����ADC
  
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
  RES5,           // ����
  RES6,           // ����
  DAC1_OUT,       // DAC1��� ��֧��ADC
  RES7,           // ����
  RES8,           // ����
  Temp1_Sensor,   // Temperature Sensor,�ڲ��¶Ȳ���������ADC����
  Bandgap1,       // �¶Ȳ����ṹ��϶��׼Դ   ��֧��ADC
  RES9,           // ����
  VREFH1,         // �ο��ߵ�ѹ,����ADC���� ,�����Ϊ 2^n-1
  VREFL1,         // �ο��͵�ѹ,����ADC���� ,�����Ϊ 0
  Module1_Dis,    // ��֧�� ADC 
}ADCn_CHn;

/*
**ADCģ��ö��
*/
typedef enum
{
  ADC_ADC0,
  ADC_ADC1,
  ADC_ADC_MAX,
}ADC_ADCn;

/*
**ADC����λ��
*/
typedef enum
{
  ADC_8Bit=0x00,
  ADC_10Bit=0x02,
  ADC_12Bit=0x01,
  ADC_16Bit=0x03,
}ADC_nBit;

/*
**ADCͨ��ö��(Aͨ��,Bͨ��)
*/
typedef enum
{
  ADC_Channel_A,
  ADC_Channel_B,
}ADC_Channel_n;

/*
**ADCģ��ź�
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