/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_GPIO.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**GPIO��ַָ��
*/
GPIO_MemMapPtr GPIOX[PORT_PTX_MAX]=
{
  PTA_BASE_PTR,//PTA��ַָ��
  PTB_BASE_PTR,//PTB��ַָ��
  PTC_BASE_PTR,//PTC��ַָ��
  PTD_BASE_PTR,//PTD��ַָ��
  PTE_BASE_PTR,//PTE��ַָ��
};

/*
 *  @brief      ��ʼ��GPIO
 *  @param      PTXn            PTXx    �˿�
 *  @param      GPIO_CFG        CFG     ���ŷ���,0=����,1=���
 *  @param      uint8           DATA    �����ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ(��������Ч)
 *  @since      v1.0
 *  Sample usage:       GPIO_Init(PTA8, GPI,0);    //��ʼ�� PTA8 �ܽ�Ϊ����
 */
void GPIO_Init(PTXn PTXx,GPIO_CFG CFG,uint8 DATA)
{
  PORT_Init(PTXx,ALT1);//��ʼ��ΪGPIO
  
  if(CFG == GPI)//GPIO Input
  {
    GPIO_PDDR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));// GPIO PDDR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿ڷ�������
  }
  else//GPIO Output
  {
    GPIO_PDDR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));// GPIO PDDR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿ڷ������
    
    if(DATA == 0)//�͵�ƽ
    {
      GPIO_PDOR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));// GPIO PDOR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿�����͵�ƽ
    }
    else//�ߵ�ƽ
    {
      GPIO_PDOR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));// GPIO PDOR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿�����ߵ�ƽ
    }
    
  }
  
}

/*
 *  @brief      �����������ݷ���
 *  @param      PTXn            PTXx    �˿�
 *  @param      GPIO_CFG        CFG     ���ŷ���,0=����,1=���
 *  @since      v1.0
 *  Sample usage:       GPIO_DDR(PTA8, GPI);    //���� PTA8 �ܽ�Ϊ����
 */
void GPIO_DDR(PTXn PTXx,GPIO_CFG CFG)
{
  if(CFG == GPI)
  {
    GPIO_PDDR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));// GPIO PDDR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿ڷ�������
  }
  else
  {
    GPIO_PDDR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));// GPIO PDDR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿ڷ������
  }
}

/*
 *  @brief      ��������״̬
 *  @param      PTXn     PTXx    �˿�
 *  @param      uint8    DATA    �����ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ(��������Ч)
 *  @since      v1.0
 *  @warning    ��ر�֤���ݷ���Ϊ���(DEBUGģʽ��,�ж��Խ��м��)
 *  Sample usage:       GPIO_Set(PTA8, 1);    // PTA8 �ܽ� ��� 1
 */
void GPIO_Set(PTXn PTXx,uint8 DATA)
{
  ASSERT(BIT_GET(GPIO_PDDR_REG(GPIOX_BASE(PTXx)),PORT_PTn(PTXx)) == GPO);
  
  if(DATA == 0)//�͵�ƽ
  {
    GPIO_PDOR_REG(GPIOX_BASE(PTXx)) &= ~(1 << PORT_PTn(PTXx));// GPIO PDOR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿�����͵�ƽ
  }
  else//�ߵ�ƽ
  {
    GPIO_PDOR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));// GPIO PDOR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿�����ߵ�ƽ
  }
}

/*
 *  @brief      ��ת����״̬
 *  @param      PTXn    PTXx    �˿�
 *  @since      v1.0
 *  @warning    ��ر�֤���ݷ���Ϊ���(DEBUGģʽ��,�ж��Խ��м��)
 *  Sample usage:       GPIO_Turn(PTA8);    // PTA8 �ܽ� ��� ��ת
 */
void GPIO_Turn(PTXn PTXx)
{
  ASSERT(BIT_GET(GPIO_PDDR_REG(GPIOX_BASE(PTXx)),PORT_PTn(PTXx)) == GPO);
  
  GPIO_PTOR_REG(GPIOX_BASE(PTXx)) |= (1 << PORT_PTn(PTXx));//�ܽ�����Ϊ�˿������ת

}

/*
 *  @brief      ��ȡ��������״̬
 *  @param      PTXn    PTXx    �˿�
 *  @return     �ܽŵ�״̬,1Ϊ�ߵ�ƽ,0Ϊ�͵�ƽ
 *  @since      v1.0
 *  @warning    ��ر�֤���ݷ���Ϊ����(DEBUGģʽ�£��ж��Խ��м��)
 *  Sample usage:       uint8 GPIO_DATA = GPIO_Get(PTA8);    // ��ȡ PTA8 �ܽ� �����ƽ
 */
uint8 GPIO_Get(PTXn PTXx)
{
  uint8 GPIO_Data=0;
  
  ASSERT(BIT_GET(GPIO_PDDR_REG(GPIOX_BASE(PTXx)),PORT_PTn(PTXx)) == GPI);
  
  GPIO_Data = (GPIO_PDIR_REG(GPIOX_BASE(PTXx)) >> PORT_PTn(PTXx)) & 0x01;
  
  return GPIO_Data;
}