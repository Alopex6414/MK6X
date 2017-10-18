/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_DAC.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**DAC��ַָ��
*/
DAC_MemMapPtr DACN[DAC_DAC_MAX]=
{
  DAC0_BASE_PTR,//DAC0��ַָ��
  DAC1_BASE_PTR,//DAC1��ַָ��
};

/*
 *  @brief      DAC��ʼ��
 *  @param      DAC_DACn        DAC_DACx        DACģ���
 *  @since      v1.0
 *  Sample usage:       DAC_Init(DAC1);//��ʼ�� DAC1
 */
void DAC_Init(DAC_DACn DAC_DACx)
{
  ASSERT(DAC_DACx <= DAC_DAC1);
  
  switch(DAC_DACx)
  {
    case DAC_DAC0:
                  SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK;//DAC0ʱ��ʹ��
                  break;
    case DAC_DAC1:
                  SIM_SCGC2 |= SIM_SCGC2_DAC1_MASK;//DAC1ʱ��ʹ��
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  /*
  **DAC_C0�Ĵ�������
  */
  DAC_C0_REG(DACN[DAC_DACx]) = (0
                                | DAC_C0_DACTRGSEL_MASK         //DAC�������
                                | DAC_C0_DACRFS_MASK            //DAC�ο�ԴVDD(3.3V)
                                | DAC_C0_DACEN_MASK             //DACϵͳʹ��
                                );
  
  /*
  **DAC_C1�Ĵ�������
  */
  DAC_C1_REG(DACN[DAC_DACx]) = (0);
  
  /*
  **DAC_C2�Ĵ�������
  */
  DAC_C2_REG(DACN[DAC_DACx]) = (0 | DAC_C2_DACBFRP(0));
  
  //�����͵�ѹ
  DAC_DATH_REG(DACN[DAC_DACx],0) = 0;
  DAC_DATL_REG(DACN[DAC_DACx],0) = 0;
    
}

/*
 *  @brief      DAC���
 *  @param      DAC_DACn        DAC_DACx        DACģ���
 *  @param      uint16          DAC_Value       ���ģ��������Ӧ��������(12bit)
 *  @since      v1.0
 *  Sample usage:       DAC_Out (DAC1 ,0x100);    //��ʼ�� DAC1 ��� 0x100 ��������Ӧ��ģ����
 */
void DAC_Out(DAC_DACn DAC_DACx,uint16 DAC_Value)
{
  //����DAC���ֵΪ12Bit
  ASSERT(DAC_Value < 0x1000);
  
  DAC_DATH_REG(DACN[DAC_DACx],0) = (DAC_Value >> 8);    //DAC�����λ�Ĵ���
  DAC_DATL_REG(DACN[DAC_DACx],0) = (DAC_Value & 0xff);  //DAC�����λ�Ĵ���
  
}