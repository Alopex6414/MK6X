/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PORT.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**PTX�˿ڻ�ַָ��
*/
PORT_MemMapPtr PORTX[PORT_PTX_MAX]=
{
  PORTA_BASE_PTR,//PTA��ַָ��
  PORTB_BASE_PTR,//PTB��ַָ��
  PORTC_BASE_PTR,//PTC��ַָ��
  PORTD_BASE_PTR,//PTD��ַָ��
  PORTE_BASE_PTR,//PTE��ַָ��
};

/*
 *  @brief      PORT��ʼ��
 *  @param      PTXn    PTXx    �˿�
 *  @param      uint32  CFG     �˿��������ã��紥��ѡ�����������ѡ��
 *  @since      v1.0
 *  @note       ��PORT_Init_NoALT��ͬ���ǣ��˺�����Ҫ���� MUX ���ù��ܣ�
                ���� MUX = ALT0
 *  Sample usage:       PORT_Init(PTA8, IRQ_RISING | PF | ALT1 | PULLUP );    //��ʼ�� PTA8 �ܽţ������ش����жϣ�����Դ�˲��������ù���ΪGPIO ����������
 */
void PORT_Init(PTXn PTXx,uint32 CFG)
{
  switch(PORT_PTX(PTXx))//ѡ��Enableʱ��
  {
    case PORT_PTA:
                  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
                  break;
    case PORT_PTB:
                  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
                  break;
    case PORT_PTC:
                  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
                  break;
    case PORT_PTD:
                  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
                  break;
    case PORT_PTE:
                  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  PORT_ISFR_REG(PORTX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));//���жϱ�־
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) &= ~PORT_PCR_MUX_MASK;//���ԭMUX�Ĵ���ֵ
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) |= (0 | CFG);//MUX�ܽŹ��ܸ���
  
}

/*
 *  @brief      PORT��ʼ��
 *  @param      PTXn    PTXx    �˿�
 *  @param      uint32  CFG     �˿��������ã��紥��ѡ�����������ѡ��
 *  @since      v1.0
 *  @note       ��PORT_Init��ͬ���ǣ��˺�������Ҫ���� MUX ���ù��ܣ���ʹ������Ҳ����Ч����
                MUX ���� Ϊԭ�ȼĴ������õ�ֵ
 *  Sample usage:       PORT_Init_NoALT (PTA8, IRQ_RISING | PF | PULLUP );    //��ʼ�� PTA8 �ܽţ������ش����жϣ�����Դ�˲���������ԭ�ȸ��ù��ܣ���������
 */
void PORT_Init_NoALT(PTXn PTXx,uint32 CFG)
{
  switch(PORT_PTX(PTXx))//ѡ��Enableʱ��
  {
    case PORT_PTA:
                  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
                  break;
    case PORT_PTB:
                  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
                  break;
    case PORT_PTC:
                  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
                  break;
    case PORT_PTD:
                  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
                  break;
    case PORT_PTE:
                  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  PORT_ISFR_REG(PORTX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));//���жϱ�־
  CFG &= ~PORT_PCR_MUX_MASK;//�������MUX
  CFG |= (PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) & PORT_PCR_MUX_MASK);//��ȡԭ��MUX����
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) |= (0 | CFG);//MUX�ܽŹ��ܸ���
  
}

/*
 *  @brief      PORT��ʼ��EXIT�ⲿ�ж�
 *  @param      PTXn    PTXx    �˿�
 *  @param      uint32  CFG     �˿��������ã��紥��ѡ�����������ѡ��
 *  @since      v1.0
 *  @note       
 *  Sample usage:       PORT_Init_Exit(PTA13,IRQ_RISING)//PTA13,�����ش����ⲿ�ж�
 */
void PORT_Init_Exit(PTXn PTXx,uint32 CFG)
{
  switch(PORT_PTX(PTXx))//ѡ��Enableʱ��
  {
    case PORT_PTA:
                  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
                  break;
    case PORT_PTB:
                  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
                  break;
    case PORT_PTC:
                  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
                  break;
    case PORT_PTD:
                  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
                  break;
    case PORT_PTE:
                  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
                  break;
    default:
                  ASSERT(0);
                  break;
  }
  
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) &= ~PORT_PCR_MUX_MASK;//���ԭMUX�Ĵ���ֵ
  PORT_PCR_REG(PORTX_BASE(PTXx),PORT_PTn(PTXx)) |= (0 | ALT1 | CFG);//MUX�ܽŹ��ܸ���
  GPIO_PDDR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));//�ܽ�����Ϊ����ģʽ
  PORT_ISFR_REG(PORTX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));//���жϱ�־
  
}