/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_Key.c
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
**���������˿�
*/
PTXn MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY_MAX]={PTB21,PTB22,PTB23,PTB20};

/*
 *  @brief      MAPS_Dock_KEY��ʼ�����а���
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_KEY_ALL_Init();//MAPS_Dock_KEY��ʼ�����а���
 */
void MAPS_Dock_KEY_ALL_Init(void)
{
  GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY0],GPI,0);
  GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY1],GPI,0);
  GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY2],GPI,0);
  GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY3],GPI,0);
}

/*
 *  @brief      MAPS_Dock_KEY��ʼ����������
 *  @para       MAPS_Dock_KEYn  MAPS_Dock_KEYx  ��������
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_KEY_KEYn_Init();//MAPS_Dock_KEY��ʼ����������
 */
void MAPS_Dock_KEY_KEYn_Init(MAPS_Dock_KEYn MAPS_Dock_KEYx)
{
  switch(MAPS_Dock_KEYx)
  {
    case MAPS_Dock_KEY0://KEY0
                        GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY0],GPI,0);
                        break;
    case MAPS_Dock_KEY1://KEY1
                        GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY1],GPI,0);
                        break;
    case MAPS_Dock_KEY2://KEY2
                        GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY2],GPI,0);
                        break;
    case MAPS_Dock_KEY3://KEY3
                        GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY3],GPI,0);
                        break;
    case MAPS_Dock_KEY_MAX://KEYALL
                        GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY0],GPI,0);
                        GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY1],GPI,0);
                        GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY2],GPI,0);
                        GPIO_Init(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY3],GPI,0);
                        break;
    default:
                        ASSERT(0);
                        break;
  }
}

/*
 *  @brief      MAPS_Dock_KEY��ȡ��������״̬
 *  @para       MAPS_Dock_KEYn  MAPS_Dock_KEYx  ��������
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_KEY_KEYn_Get();//MAPS_Dock_KEY��ȡ��������״̬
 */
uint8 MAPS_Dock_KEY_KEYn_Get(MAPS_Dock_KEYn MAPS_Dock_KEYx)
{
  uint8 KEY_Status=0;
  
  switch(MAPS_Dock_KEYx)
  {
    case MAPS_Dock_KEY0:
                        KEY_Status = GPIO_GET(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY0]);
                        break;
    case MAPS_Dock_KEY1:
                        KEY_Status = GPIO_GET(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY1]);
                        break;
    case MAPS_Dock_KEY2:
                        KEY_Status = GPIO_GET(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY2]);
                        break;
    case MAPS_Dock_KEY3:
                        KEY_Status = GPIO_GET(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEY3]);
                        break;
    default:
                        ASSERT(0);
                        break;
  }
  
  return KEY_Status;
}

/*
 *  @brief      MAPS_Dock_KEY����������ѹ���
 *  @para       MAPS_Dock_KEYn  MAPS_Dock_KEYx  ��������
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_KEY_KEYn_Check();//MAPS_Dock_KEY����������ѹ���
 */
MAPS_Dock_KEY_Status MAPS_Dock_KEY_KEYn_Check(MAPS_Dock_KEYn MAPS_Dock_KEYx)
{
  if(GPIO_GET(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEYx]) == MAPS_Dock_KEY_On)
  {
    MAPS_Dock_KEY_Delay(10);//��ʱ����10ms
    if(GPIO_GET(MAPS_Dock_KEY_PTXn[MAPS_Dock_KEYx]) == MAPS_Dock_KEY_On)
    {
      return MAPS_Dock_KEY_On;
    }
  }
  
  return MAPS_Dock_KEY_Off;
}

/*
 *  @brief      MAPS_Dock_KEYɨ�����а���
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_KEY_Incident();//MAPS_Dock_KEYɨ�����а���
 */
void MAPS_Dock_KEY_Incident(void)
{
  //KEY0����
  if(MAPS_Dock_KEY_KEYn_Check(MAPS_Dock_KEY0) == MAPS_Dock_KEY_On)
  {
    //Put Your Code...
    UART_PutStr(UART_UART4,"KEY0 ");
    MAPS_Dock_KEY_Delay(500);//������ʱ500ms
  }
  else if(MAPS_Dock_KEY_KEYn_Check(MAPS_Dock_KEY1) == MAPS_Dock_KEY_On)
  {
    //Put Your Code...
    UART_PutStr(UART_UART4,"KEY1 ");
    MAPS_Dock_KEY_Delay(500);//������ʱ500ms
  }
  else if(MAPS_Dock_KEY_KEYn_Check(MAPS_Dock_KEY2) == MAPS_Dock_KEY_On)
  {
    //Put Your Code...
    UART_PutStr(UART_UART4,"KEY2 ");
    MAPS_Dock_KEY_Delay(500);//������ʱ500ms
  }
  else if(MAPS_Dock_KEY_KEYn_Check(MAPS_Dock_KEY3) == MAPS_Dock_KEY_On)
  {
    //Put Your Code...
    UART_PutStr(UART_UART4,"KEY3 ");
    MAPS_Dock_KEY_Delay(500);//������ʱ500ms
  }
}