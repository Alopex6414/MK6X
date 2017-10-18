/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_ADC.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**ADC��ַָ��
*/
ADC_MemMapPtr ADCN[ADC_ADC_MAX]=
{
  ADC0_BASE_PTR,
  ADC1_BASE_PTR,
};

/*
 *  @brief      ADC��ʼ��
 *  @param      ADCn_CHn        ADCn_CHx         ADCͨ��
 *  @since      v1.0
 *  @note       �˳�ʼ����֧���������������ÿ��ͨ����֧��ADC ���������
                ����˵���� ADCn_CHn ��ע��˵��
 *  Sample usage:       ADC_Init(ADC0_SE10);    //��ʼ�� ADC0_SE10,ʹ�� PTA7 �ܽ�
 */
void ADC_Init(ADCn_CHn ADCn_CHx)
{
  switch(ADCn(ADCn_CHx))//ѡ��ADCģ��
  {
    case ADC_ADC0://ADC0
                  SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;//ADC0ʱ��ʹ��
                  SIM_SOPT7 &= ~(SIM_SOPT7_ADC0ALTTRGEN_MASK | SIM_SOPT7_ADC0PRETRGSEL_MASK);//ADC0ѡ��PDB����
                  SIM_SOPT7 |= SIM_SOPT7_ADC0TRGSEL(0);//ADC0PDB����
                  break;
    case ADC_ADC1://ADC1
                  SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;//ADC1ʱ��ʹ��
                  SIM_SOPT7 &= ~(SIM_SOPT7_ADC1ALTTRGEN_MASK | SIM_SOPT7_ADC1PRETRGSEL_MASK);//ADC1ѡ��PDB����
                  SIM_SOPT7 |= SIM_SOPT7_ADC1TRGSEL(0);//ADC1PDB����
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  switch(ADCn_CHx)//ѡ��ADCͨ��
  {
    /*
    **ADC0
    */
    case ADC0_SE8://PTB0
                  PORT_Init(PTB0, ALT0);
                  break;
    case ADC0_SE9://PTB1
                  PORT_Init(PTB1, ALT0);
                  break;
    case ADC0_SE10://PTA7
                  PORT_Init(PTA7, ALT0);
                  break;
    case ADC0_SE11://PTA8
                  PORT_Init(PTA8, ALT0);
                  break;
    case ADC0_SE12://PTB2
                  PORT_Init(PTB2, ALT0);
                  break;
    case ADC0_SE13://PTB3
                  PORT_Init(PTB3, ALT0);
                  break;
    case ADC0_SE14://PTC0
                  PORT_Init(PTC0, ALT0);
                  break;
    case ADC0_SE15://PTC1
                  PORT_Init(PTC1, ALT0);
                  break;
    case ADC0_SE17://PTE24
                  PORT_Init(PTE24,ALT0);
                  break;
    case ADC0_SE18://PTE25
                  PORT_Init(PTE25,ALT0);
                  break;
    
    /*
    **ADC0����Ҫ���ø��ùܽ�
    */
    case ADC0_DP0:
    case ADC0_DP1:
    case ADC0_DP3:
    case ADC0_DM0:              // ADC0_DM0
    case ADC0_DM1:              // ADC0_DM1
    case ADC0_SE16:             // ADC0_SE16
    case Temp0_Sensor:          // Temperature Sensor,�ڲ��¶Ȳ���������ADC����
    case VREFH0:                // �ο��ߵ�ѹ,����ADC���� ,�����Ϊ 2^n-1
    case VREFL0:                // �ο��͵�ѹ,����ADC���� ,�����Ϊ 0
                  break;
    
    /*
    **ADC1
    */
    case ADC1_SE4a://PTE0
                  PORT_Init(PTE0,ALT0);
                  break;
    case ADC1_SE5a://PTE1
                  PORT_Init(PTE1,ALT0);
                  break;
    case ADC1_SE6a://PTE2
                  PORT_Init(PTE2,ALT0);
                  break;
    case ADC1_SE7a://PTE3
                  PORT_Init(PTE3,ALT0);
                  break;              
    case ADC1_SE8://PTB0
                  PORT_Init(PTB0,ALT0);
                  break;
    case ADC1_SE9://PTB1
                  PORT_Init(PTB1,ALT0);
                  break;
    case ADC1_SE10://PTB4
                  PORT_Init(PTB4,ALT0);
                  break;
    case ADC1_SE11://PTB5
                  PORT_Init(PTB5,ALT0);
                  break;
    case ADC1_SE12://PTB6
                  PORT_Init(PTB6,ALT0);
                  break;
    case ADC1_SE13://PTB7
                  PORT_Init(PTB7,ALT0);
                  break;
    case ADC1_SE14://PTB10
                  PORT_Init(PTB10,ALT0);
                  break;
    case ADC1_SE15://PTB11
                  PORT_Init(PTB11,ALT0);
                  break;
    case ADC1_SE17://PTA17
                  PORT_Init(PTA17,ALT0);
                  break;
                  
    /*
    **ADC1����Ҫ���ø��ùܽ�
    */              
    case ADC1_DP0:
    case ADC1_DP1:
    case ADC1_DP3:
    case ADC1_SE16:             // ADC1_SE16
    case VREF_OUTPUT:           // VREF Output
    case ADC1_DM0:              // ADC1_DM0
    case ADC1_DM1:              // ADC1_DM1
    case Temp1_Sensor:          // Temperature Sensor,�ڲ��¶Ȳ���������ADC����
    case VREFH1:                // �ο��ߵ�ѹ,����ADC���� ,�����Ϊ 2^n-1
    case VREFL1:                // �ο��͵�ѹ,����ADC���� ,�����Ϊ 0
                  break;
    
    default:
                  ASSERT(0);
                  break;                
  }
  
}

/*
 *  @brief      ����ADC�������(��֧��Bͨ��)
 *  @param      ADCn_CHn        ADCn_CHx        ADCͨ��
 *  @param      ADC_nBit        ADC_xbit        ADC����(ADC_8Bit,ADC_10Bit,ADC_12Bit,ADC_16Bit)
 *  @since      v5.0
 *  @note       �˺����ڲ����ã������󼴿ɵȴ����ݲɼ����
 *  Sample usage:       ADC_Start(ADC0_SE10, ADC_8Bit);
 */
static void ADC_Start(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit)
{
  //ADC���üĴ���1
  ADC_CFG1_REG(ADCN[ADCn(ADCn_CHx)]) = (0
                                         | ADC_CFG1_ADIV(2)             //ADCʱ��4��Ƶ,2^n,n=0~3
                                         | ADC_CFG1_ADLSMP_MASK         //ADC������ʱ��,0:�̲���ʱ��,1:������ʱ��
                                         | ADC_CFG1_MODE(ADC_xBit)      //ADCת������ѡ��
                                         | ADC_CFG1_ADICLK(0)           //ADCʱ�Ӳ�������ʱ��,00:Bus,01:Bus/2,10:ALTCLK,11:ADACK
                                         );
  
  //ADC���üĴ���2
  ADC_CFG2_REG(ADCN[ADCn(ADCn_CHx)]) = (0
                                         | ADC_CFG2_ADHSC_MASK          //���ٲ���ת������
                                         | ADC_CFG2_ADLSTS(0)           //Ĭ�������ʱ��,24��ADCK
                                         );
  
  
  //ADC״̬���ƼĴ���(Aͨ��)
  ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) = (0
                                                      | ADC_SC1_AIEN_MASK                  //ת������ж�ʹ��
                                                      | ADC_SC1_ADCH(ADC_CHn(ADCn_CHx))    //ѡ��ADCת��ͨ��
                                                      );
  
}

/*
 *  @brief      ֹͣADC�������
 *  @param      ADC_ADCn        ADC_ADCx        ADCͨ��
 *  @since      v1.0
 *  Sample usage:       ADC_Stop(ADC_ADC0);
 */
void ADC_Stop(ADC_ADCn ADC_ADCx)
{
  //����ADCģ���ADC_ADC0,ADC_ADC1
  ASSERT(ADC_ADCx <= ADC_ADC1);
  
  ADC_SC1_REG(ADCN[ADC_ADCx],ADC_Channel_A) = (0
                                               | ADC_SC1_AIEN_MASK              //ADCת������ж�ʹ��
                                               | ADC_SC1_ADCH(Module0_Dis)     //ADCģ���ֹ
                                               );
  
}

/*
 *  @brief      ��ȡADC����ֵ(��֧��Bͨ��)
 *  @param      ADCn_CHn        ADCn_CHx        ADCͨ��
 *  @param      ADC_nBit        ADC_xbit        ADC����(ADC_8Bit,ADC_10Bit,ADC_12Bit,ADC_16Bit)
 *  @return     ����ֵ
 *  @since      v1.0
 *  Sample usage:       uint16 var = ADC_Once(ADC0_SE10,ADC_8Bit);
 */
uint16 ADC_Once(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit)
{
  uint16 ADC_Result=0;
  
  ADC_Start(ADCn_CHx,ADC_xBit);//����ADCת��
  
  while((ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);
  
  ADC_Result = ADC_R_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A);//��ȡADCת�����
  
  ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) &= ~ADC_SC1_COCO_MASK;//ADCת����ɱ�־λ����
  
  return ADC_Result;
}

/*
 *  @brief      ADC����N�β�����ֵֵ(��֧��Bͨ��)
 *  @param      ADCn_CHn        ADCn_CHx        ADCͨ��
 *  @param      ADC_nBit        ADC_xbit        ADC����(ADC_8Bit,ADC_10Bit,ADC_12Bit,ADC_16Bit)
 *  @param      uint8           ADC_Samp_Num
 *  @return     ����ֵ
 *  @since      v1.0
 *  Sample usage:       uint16 var = ADC_Average(ADC0_SE10,ADC_8Bit,20);
 */
uint16 ADC_Average(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit,uint8 ADC_Samp_Num)
{
  uint8 i=0;
  uint16 ADC_Samp_Ave=0;
  uint32 ADC_Samp_Temp=0;
  
  for(i=0;i<ADC_Samp_Num;i++)
  {
    ADC_Start(ADCn_CHx,ADC_xBit);//����ADCת��
    
    while((ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);
    
    ADC_Samp_Temp += ADC_R_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A);//��ȡADCת�����
    
    ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) &= ~ADC_SC1_COCO_MASK;//ADCת����ɱ�־λ����
  }
  
  ADC_Samp_Ave = ADC_Samp_Temp / ADC_Samp_Num;
  
  return ADC_Samp_Ave;
}

/*
 *  @brief      ADC����N�δ洢������(��֧��Bͨ��)
 *  @param      ADCn_CHn        ADCn_CHx        ADCͨ��
 *  @param      ADC_nBit        ADC_xbit        ADC����(ADC_8Bit,ADC_10Bit,ADC_12Bit,ADC_16Bit)
 *  @param      uint16          ADC_Array[]     ADC����
 *  @return     ����ֵ
 *  @since      v1.0
 *  Sample usage:               ADC_Samp_Array(ADC0_SE10,ADC_12Bit,&ADC_Array[0])
 */
void ADC_Samp_Array(ADCn_CHn ADCn_CHx,ADC_nBit ADC_xBit,uint16 *ADC_Array)
{
  uint8 i=0;
  uint8 ADC_Array_Size=0;
  
  ADC_Array_Size = (sizeof(ADC_Array) / sizeof(uint16));
  
  for(i=0;i<ADC_Array_Size;i++)
  {
    ADC_Start(ADCn_CHx,ADC_xBit);//����ADCת��
    
    while((ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);
    
    *ADC_Array++ = ADC_R_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A);//��ȡADCת�����
    
    ADC_SC1_REG(ADCN[ADCn(ADCn_CHx)],ADC_Channel_A) &= ~ADC_SC1_COCO_MASK;//ADCת����ɱ�־λ����
  }
  
}