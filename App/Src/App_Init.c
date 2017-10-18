/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       App_Init.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      Interrupt_Init     �жϳ�ʼ��
 *  @since      v1.0
 */
void Interrupt_Init(void)
{
  /*PORT_Init_Exit(PTC19,IRQ_EITHER);//PTC19�ⲿ�ж�,�����ش���
  set_irq_priority(PORTC_IRQn,0);//�ж����ȼ�0
  enable_irq(PORTC_IRQn);//ʹ���ж�
  
  PORT_Init_Exit(PTD15,IRQ_EITHER);//PTD15�ⲿ�ж�,�����ش���
  set_irq_priority(PORTD_IRQn,1);//�ж����ȼ�1
  enable_irq(PORTD_IRQn);//ʹ���ж�*/
  
  PIT_Init_ms(PIT0,1);//PIT0��ʱ�ж�,��ʱ����1ms
  set_irq_priority(PIT0_IRQn,2);//�ж����ȼ�2
  enable_irq(PIT0_IRQn);//ʹ���ж�
  
}

/*
 *  @brief      AllInit     Ӧ�ó�ʼ��
 *  @since      v1.0
 */
void AllInit(void)
{
  DisableInterrupts;//�����ж�
  /*
  **MAPS_Dock
  */
  MAPS_Dock_LED_Init();//LED��ʼ��
  MAPS_Dock_LCM_Init();//LCM��ʼ��
  MAPS_Dock_KEY_ALL_Init();//KEY����������ʼ��
  MAPS_Dock_Rocker_Key_Init();//Rockerҡ�˰�����ʼ��
  //MAPS_Dock_W25Q80_Init();//W25Q80��ʼ��
  
  /*
  **MAPS
  */
  MAPS_LCD_Init();//LCDC��ʼ��
  
  /*
  **MK6X
  */
  ADC_Init(ADC0_DP0);//ADC0_DP0ͨ����ʼ��
  ADC_Init(ADC0_DM0);//ADC0_DM0ͨ����ʼ��
  I2C_Init(I2C_I2C0,400000);//��ʼ��I2C0,������400Kbps
  UART_Init(UART_UART4,115200);//��ʼ��UART4,������115200Bps
  //DAC_Init(DAC_DAC1);//DAC_DAC1��ʼ��
  
  Interrupt_Init();//�жϳ�ʼ��
  
  EnableInterrupts;
}