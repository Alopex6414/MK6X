/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_Rocker.c
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

//ҡ�˰�������LCM
int Rocker_Key_Switch_Page=1;           //��ǰѡ��ҳ��
int Rocker_Key_Switch_Row=1;            //��ǰѡ����
int Rocker_Key_Switch_Row_Old=1;        //��һ��ѡ����
int Rocker_Key_Switch_Choice_Stauts=0;  //����ѡ��״̬
int Rocker_Key_Switch_Choice_Flag=0;    //����������־

/*
**ҡ�˰����˿�
*/
PTXn Rocker_Key_PTXn[Rocker_MAX]={PTA27,PTA26,PTA25,PTA24,PTA4};//PTA4(NMI)

/*
 *  @brief      Rocker_Key��ʼ��
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_Rocker_Key_Init();//��ʼ��ҡ�˰���
 */
void MAPS_Dock_Rocker_Key_Init(void)
{
  GPIO_Init(Rocker_Key_PTXn[Rocker_Up],GPI,0);//Rocker_Up����ʼ��
  GPIO_Init(Rocker_Key_PTXn[Rocker_Donw],GPI,0);//Rocker_Donw����ʼ��
  GPIO_Init(Rocker_Key_PTXn[Rocker_Left],GPI,0);//Rocker_Left����ʼ��
  GPIO_Init(Rocker_Key_PTXn[Rocker_Right],GPI,0);//Rocker_Right����ʼ��
  GPIO_Init(Rocker_Key_PTXn[Rocker_Select],GPI,0);//Rocker_Select����ʼ��
}

/*
 *  @brief      Rocker_Keyҡ�˰�������LCM
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_Rocker_Key_LCM_Control();//ҡ�˰�������LCM
 */
void MAPS_Dock_Rocker_Key_LCM_Control(void)
{
  //�������
  if(Rocker_Key_Switch_Choice_Stauts == 0)
  {
    //ֻ�а���Select�����ܽ����������
    if(GPIO_GET(Rocker_Key_PTXn[Rocker_Select]) == Rocker_Key_On)
    {
      Rocker_Key_Switch_Choice_Stauts = 1;
      MAPS_Dock_LCM_CLS();//����
      Rocker_Key_Delay(500);//������ʱ
    }
  }
  //������ҳѡ�����
  else if(Rocker_Key_Switch_Choice_Stauts == 1)
  {
    //����ҡ�����
    if(GPIO_GET(Rocker_Key_PTXn[Rocker_Left]) == Rocker_Key_On)
    {
      Rocker_Key_Switch_Page--;//ҳ����һ
      if(Rocker_Key_Switch_Page < 1)//ҳ��С��1
      {
        Rocker_Key_Switch_Page = LCM_PAGES;//ҳ���������ҳ��
      }
      Rocker_Key_Switch_Row = 1;
      Rocker_Key_Switch_Row_Old = 1;
      Rocker_Key_Switch_Choice_Flag = 0;
      Rocker_Key_Switch_Choice_Stauts = 1;
      MAPS_Dock_LCM_CLS();//����
      Rocker_Key_Delay(500);//������ʱ
    }
    //����ҡ���Ҽ�
    else if(GPIO_GET(Rocker_Key_PTXn[Rocker_Right]) == Rocker_Key_On)
    {
      Rocker_Key_Switch_Page++;//ҳ����һ
      if(Rocker_Key_Switch_Page > LCM_PAGES)//ҳ���������ҳ��
      {
        Rocker_Key_Switch_Page = 1;//ҳ������1
      }
      Rocker_Key_Switch_Row = 1;
      Rocker_Key_Switch_Row_Old = 1;
      Rocker_Key_Switch_Choice_Flag = 0;
      Rocker_Key_Switch_Choice_Stauts = 1;
      MAPS_Dock_LCM_CLS();//����
      Rocker_Key_Delay(500);//������ʱ
    }
    //����ҡ���ϼ�
    else if(GPIO_GET(Rocker_Key_PTXn[Rocker_Up]) == Rocker_Key_On)
    {
      Rocker_Key_Delay(500);//������ʱ 
    }
    //����ҡ���¼�
    else if(GPIO_GET(Rocker_Key_PTXn[Rocker_Donw]) == Rocker_Key_On)
    {
      Rocker_Key_Delay(500);//������ʱ
    }
  }
  
  
  //LCM������ʾ
  if(Rocker_Key_Switch_Choice_Stauts == 0)
  {
    MAPS_Dock_LCM_DrawBMP(&LCM_Freescale_logo[0],LCM_Invert_Color);
  }
  else
  {
    switch(Rocker_Key_Switch_Page)
    {
      case 1:
              MAPS_Dock_LCM_Put_Str_6x8(37,0,"MAPS_MK64",LCM_Pure_Color);
              MAPS_Dock_LCM_Put_Str_6x8(49,1,"List1",LCM_Pure_Color);
              MAPS_Dock_LCM_Put_Para_6x8(0,2,"PIT_Count:",PIT_Count,LCM_Pure_Color);
              MAPS_Dock_LCM_Put_Para_6x8(0,3,"ADC0_DP0:",ADC_Convert_Result[0],LCM_Pure_Color);
              MAPS_Dock_LCM_Put_Para_6x8(0,4,"ADC0_DM0:",ADC_Convert_Result[1],LCM_Pure_Color);
              break;
      case 2:
              MAPS_Dock_LCM_Put_Str_6x8(37,0,"MAPS_MK64",LCM_Pure_Color);
              MAPS_Dock_LCM_Put_Str_6x8(49,1,"List2",LCM_Pure_Color);
              break;
      case 3:
              MAPS_Dock_LCM_Put_Str_6x8(37,0,"MAPS_MK64",LCM_Pure_Color);
              MAPS_Dock_LCM_Put_Str_6x8(49,1,"List3",LCM_Pure_Color);
              break;
      case 4:
              MAPS_Dock_LCM_Put_Str_6x8(37,0,"MAPS_MK64",LCM_Pure_Color);
              MAPS_Dock_LCM_Put_Str_6x8(49,1,"List4",LCM_Pure_Color);
              break;
      case 5:
              MAPS_Dock_LCM_Put_Str_6x8(37,0,"MAPS_MK64",LCM_Pure_Color);
              MAPS_Dock_LCM_Put_Str_6x8(49,1,"List5",LCM_Pure_Color);
              break;
      default:
              break;
    }
  }
  
}