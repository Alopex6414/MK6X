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
 *  @brief      LPTMR���������ʼ��
 *  @param      LPT0_ALTn       LPT0_ALTx       LPTMR��������ܽ�
 *  @param      LPT_CFG         LPT_CFG_x       LPTMR���������ʽ:�����ؼ������½��ؼ���
 *  @param      uint16          LPT_Count       LPTMR����Ƚ�ֵ
 *  @since      v1.0
 *  Sample usage:       LPTMR_Pluse_Init(LPT0_ALT1,LPT_Rising,0xFFFF);// LPTMR �������������0xFFFF�󴥷��ж�������Ҫ���жϲ�ִ���жϷ��������������ز�׽
 */
void LPTMR_Pluse_Init(LPT0_ALTn LPT0_ALTx,LPT_CFG LPT_CFG_x,uint16 LPT_Count)
{
  OSC_CR |= OSC_CR_ERCLKEN_MASK;//ʹ���ⲿ����ο�ʱ��
  
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMRʱ��ʹ��
  
  switch(LPT0_ALTx)//LPTMR����
  {
    case LPT0_ALT1:
                    PORT_Init(PTA19,ALT6);//PTA19����ALT6
                    break;
    case LPT0_ALT2:
                    PORT_Init(PTC5,ALT4);//PTC5����ALT4
                    break;
    default:
                    ASSERT(0);
                    break;
  }

  LPTMR0_CSR = 0;//��LPTMR0_CSR�Ĵ���
  
  LPTMR0_PSR = (0 
                | LPTMR_PSR_PCS(3)      //ʱ��Դѡ��OSC����ʱ��
                | LPTMR_PSR_PRESCALE(4) //Ԥ��Ƶ����2^(n+1)
                );
  
  LPTMR0_CMR = LPTMR_CMR_COMPARE(LPT_Count);//����LPTMR�����Ƚ�ֵ
  
  LPTMR0_CSR = (0
                | LPTMR_CSR_TPS(LPT0_ALTx)//LPTMR��������,ALT1,ALT2
                | LPTMR_CSR_TMS_MASK//ѡ���������ģʽ
                | (LPT_CFG_x == LPT_Falling ? LPTMR_CSR_TPP_MASK : 0)//ѡ�����������ʽ,�����ؼ���,�½��ؼ���
                | LPTMR_CSR_TEN_MASK//LPTMR��ʱ��ʹ��
                | LPTMR_CSR_TIE_MASK//LPTMR��ʱ���ж�ʹ��
                );

}

/*
 *  @brief      ��ȡLPTMR�������ֵ
 *  @return     �������ֵ
 *  @since      v1.0
 *  Sample usage:       uint16 data = LPTMR_Pluse_Get();//��ȡ�������ֵ
 */
uint16 LPTMR_Pluse_Get(void)
{
  uint16 LPTMR_Data=0;

  if(LPTMR0_CSR & LPTMR_CSR_TCF_MASK)//LPTMR���������
  {
    LPTMR_Data = ~0;
  }
  else
  {
    LPTMR0_CNR = LPTMR_CNR_COUNTER(0);
    LPTMR_Data = LPTMR0_CNR;//��ȡLPTMR�������ֵ
  }
  
  return LPTMR_Data;
}

/*
 *  @brief      ���LPTMR�������
 *  @since      v1.0
 *  Sample usage:       LPTMR_Count_Clean();//���LPTMR�������
 */
void LPTMR_Count_Clean(void)
{
  LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;//��ֹLPTMR������
  LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;//ʹ��LPTMR������
}

/*
 *  @brief      LPTMR��ʱ����(ms)
 *  @param      uint16          LPTMR_Delay      LPTMR��ʱʱ��(0~65535)
 *  @since      v1.0
 *  Sample usage:       LPTMR_Delay_ms(32);     //LPTMR��ʱ32ms
 */
void LPTMR_Delay_ms(uint16 LPTMR_Delay)
{
  //������ʱʱ�����0
  ASSERT(LPTMR_Delay > 0);

  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMRʱ��ʹ��
  
  LPTMR0_CSR = 0;//��LPTMR0_CSR�Ĵ���
  LPTMR0_CMR = LPTMR_Delay;//���ñȽ�ʱ��

  LPTMR0_PSR = (0
                | LPTMR_PSR_PCS(1)      //ѡ��LPO(1KHz)ʱ��Դ
                | LPTMR_PSR_PBYP_MASK   //��·Ԥ��Ƶ/�����˲���
                );
  
  LPTMR0_CSR = (0 | LPTMR_CSR_TEN_MASK);//ʹ��LPTMR��ʱ��
  
  while((LPTMR0_CSR & LPTMR_CSR_TCF_MASK) != LPTMR_CSR_TCF_MASK);
  LPTMR0_CSR &= ~LPTMR_CSR_TCF_MASK;//����Ƚϱ�־λ
  
}

/*
 *  @brief      LPTMR��ʱ����(ms)
 *  @param      uint16          LPTMR_Delay      LPTMR��ʱʱ��(0~65535)
 *  @since      v1.0
 *  Sample usage:
                    LPTMR_Timing_ms(32);                                // LPTMR ��ʱ 32ms
                    Set_Vector_Handler(LPTimer_VECTORn,lptmr_hander);   // �����жϷ��������ж���������
                    enable_irq(LPTimer_IRQn);                           // ʹ��LPTMR�ж�
 */
void LPTMR_Timing_ms(uint16 LPTMR_Delay)
{
  //������ʱʱ�����0
  ASSERT(LPTMR_Delay > 0);
  
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMRʱ��ʹ��
  
  LPTMR0_CSR = 0;//��LPTMR0_CSR�Ĵ���
  LPTMR0_CMR = LPTMR_Delay;//���ñȽ�ʱ��
  
  LPTMR0_PSR = (0
                | LPTMR_PSR_PCS(1)      //ѡ��LPO(1KHz)ʱ��Դ
                | LPTMR_PSR_PBYP_MASK   //��·Ԥ��Ƶ/�����˲���
                );
  
  LPTMR0_CSR = (0 | LPTMR_CSR_TEN_MASK | LPTMR_CSR_TIE_MASK);//ʹ��LPTMR��ʱ��,ʹ��LPTMR��ʱ���ж�
  
}

/*
 *  @brief      LPTMR��ʱ����(us)
 *  @param      uint16          LPTMR_Delay      LPTMR��ʱʱ��(0~41942)
 *  @since      v1.0
 *  Sample usage:       LPTMR_Delay_us(32);     //LPTMR��ʱ32us
 */
void LPTMR_Delay_us(uint16 LPTMR_Delay)
{
  //���Զ�ʱʱ��,ȷ���Ĵ����������
  ASSERT((((EXTAL_IN_MHz * LPTMR_Delay + 16) / 32) < 0xffff) && (LPTMR_Delay > 0));
  
  OSC_CR |= OSC_CR_ERCLKEN_MASK;//ʹ���ⲿ����ο�ʱ��
  
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMRʱ��ʹ��
  
  LPTMR0_CSR = 0;//��LPTMR0_CSR�Ĵ���
  
  LPTMR0_CMR = (EXTAL_IN_MHz * LPTMR_Delay + 16) / 32;//���ñȽ�ʱ��
  
  LPTMR0_PSR = (0
                | LPTMR_PSR_PCS(3)      //ʱ��Դѡ��OSC����ʱ��
                | LPTMR_PSR_PRESCALE(4) //Ԥ��Ƶ����2^(n+1)
                );
  
  LPTMR0_CSR = (0 | LPTMR_CSR_TEN_MASK);//LPTMRʱ��ʹ��
  
  while((LPTMR0_CSR & LPTMR_CSR_TCF_MASK) != LPTMR_CSR_TCF_MASK);
  LPTMR0_CSR &= ~LPTMR_CSR_TCF_MASK;//����Ƚϱ�־λ
  
}

/*
 *  @brief      LPTMR��ʱ����(us)
 *  @param      uint16          LPTMR_Delay      LPTMR��ʱʱ��(0~41942)
 *  @since      v1.0
 *  Sample usage:
                    LPTMR_Timing_us(32);                                // LPTMR ��ʱ32us
                    Set_Vector_Handler(LPTimer_VECTORn,lptmr_hander);   // �����жϷ��������ж���������
                    enable_irq(LPTimer_IRQn);                           // ʹ��LPTMR�ж�
 */
void LPTMR_Timing_us(uint16 LPTMR_Delay)
{
  //���Զ�ʱʱ��,ȷ���Ĵ����������
  ASSERT((((EXTAL_IN_MHz * LPTMR_Delay + 16) / 32) < 0xffff) && (LPTMR_Delay > 0));
  
  OSC_CR |= OSC_CR_ERCLKEN_MASK;//ʹ���ⲿ����ο�ʱ��
  
  SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//LPTMRʱ��ʹ��
  
  LPTMR0_CSR = 0;//��LPTMR0_CSR�Ĵ���
  
  LPTMR0_CMR = (EXTAL_IN_MHz * LPTMR_Delay + 16) / 32;//���ñȽ�ʱ��
  
  LPTMR0_PSR = (0
                | LPTMR_PSR_PCS(3)      //ʱ��Դѡ��OSC����ʱ��
                | LPTMR_PSR_PRESCALE(4) //Ԥ��Ƶ����2^(n+1)
                );
  
  LPTMR0_CSR = (0 | LPTMR_CSR_TEN_MASK | LPTMR_CSR_TIE_MASK);//LPTMRʱ��ʹ��,LPTMR�ж�ʹ��
  
}