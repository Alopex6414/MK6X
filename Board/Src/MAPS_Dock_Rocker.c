/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_Rocker.c
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

//摇杆按键控制LCM
int Rocker_Key_Switch_Page=1;           //当前选择页数
int Rocker_Key_Switch_Row=1;            //当前选择行
int Rocker_Key_Switch_Row_Old=1;        //上一次选择行
int Rocker_Key_Switch_Choice_Stauts=0;  //参数选择状态
int Rocker_Key_Switch_Choice_Flag=0;    //按键动作标志

/*
**摇杆按键端口
*/
PTXn Rocker_Key_PTXn[Rocker_MAX]={PTA27,PTA26,PTA25,PTA24,PTA4};//PTA4(NMI)

/*
 *  @brief      Rocker_Key初始化
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_Rocker_Key_Init();//初始化摇杆按键
 */
void MAPS_Dock_Rocker_Key_Init(void)
{
  GPIO_Init(Rocker_Key_PTXn[Rocker_Up],GPI,0);//Rocker_Up键初始化
  GPIO_Init(Rocker_Key_PTXn[Rocker_Donw],GPI,0);//Rocker_Donw键初始化
  GPIO_Init(Rocker_Key_PTXn[Rocker_Left],GPI,0);//Rocker_Left键初始化
  GPIO_Init(Rocker_Key_PTXn[Rocker_Right],GPI,0);//Rocker_Right键初始化
  GPIO_Init(Rocker_Key_PTXn[Rocker_Select],GPI,0);//Rocker_Select键初始化
}

/*
 *  @brief      Rocker_Key摇杆按键控制LCM
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_Rocker_Key_LCM_Control();//摇杆按键控制LCM
 */
void MAPS_Dock_Rocker_Key_LCM_Control(void)
{
  //进入界面
  if(Rocker_Key_Switch_Choice_Stauts == 0)
  {
    //只有按下Select键才能进入参数界面
    if(GPIO_GET(Rocker_Key_PTXn[Rocker_Select]) == Rocker_Key_On)
    {
      Rocker_Key_Switch_Choice_Stauts = 1;
      MAPS_Dock_LCM_CLS();//清屏
      Rocker_Key_Delay(500);//按键延时
    }
  }
  //按键翻页选择界面
  else if(Rocker_Key_Switch_Choice_Stauts == 1)
  {
    //按下摇杆左键
    if(GPIO_GET(Rocker_Key_PTXn[Rocker_Left]) == Rocker_Key_On)
    {
      Rocker_Key_Switch_Page--;//页数减一
      if(Rocker_Key_Switch_Page < 1)//页数小于1
      {
        Rocker_Key_Switch_Page = LCM_PAGES;//页数等于最大页数
      }
      Rocker_Key_Switch_Row = 1;
      Rocker_Key_Switch_Row_Old = 1;
      Rocker_Key_Switch_Choice_Flag = 0;
      Rocker_Key_Switch_Choice_Stauts = 1;
      MAPS_Dock_LCM_CLS();//清屏
      Rocker_Key_Delay(500);//按键延时
    }
    //按下摇杆右键
    else if(GPIO_GET(Rocker_Key_PTXn[Rocker_Right]) == Rocker_Key_On)
    {
      Rocker_Key_Switch_Page++;//页数加一
      if(Rocker_Key_Switch_Page > LCM_PAGES)//页数大于最大页数
      {
        Rocker_Key_Switch_Page = 1;//页数等于1
      }
      Rocker_Key_Switch_Row = 1;
      Rocker_Key_Switch_Row_Old = 1;
      Rocker_Key_Switch_Choice_Flag = 0;
      Rocker_Key_Switch_Choice_Stauts = 1;
      MAPS_Dock_LCM_CLS();//清屏
      Rocker_Key_Delay(500);//按键延时
    }
    //按下摇杆上键
    else if(GPIO_GET(Rocker_Key_PTXn[Rocker_Up]) == Rocker_Key_On)
    {
      Rocker_Key_Delay(500);//按键延时 
    }
    //按下摇杆下键
    else if(GPIO_GET(Rocker_Key_PTXn[Rocker_Donw]) == Rocker_Key_On)
    {
      Rocker_Key_Delay(500);//按键延时
    }
  }
  
  
  //LCM参数显示
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