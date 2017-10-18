/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_LCM.c
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"
#include "MAPS_Dock_LCM_Lib.h"

/*
**LCM_Put_Para
*/
//LCM参数的5位
int LCM_TenThousand=0;
int LCM_Thousand=0;
int LCM_Hundred=0;
int LCM_Ten=0;
int LCM_Single=0;
int LCM_Pot_Ten=0;
int LCM_Pot_Hundred=0;

/*
 *  @brief      LCM写入命令
 *  @since      v1.0
 *  Sample usage:       LCM_Write_CMD();//LCM写入命令
 */
static inline void LCM_Write_CMD(uint8 cmd)
{ 
  LCM_SET_DC_L;//DC低电平,SPI写入命令
  
  SPI_Send(SPI_SPI2,SPI_PCS1,cmd);
}

/*
 *  @brief      LCM写入数据
 *  @since      v1.0
 *  Sample usage:       LCM_Write_DATA();//LCM写入数据
 */
static inline void LCM_Write_DATA(uint8 data)
{ 
  LCM_SET_DC_H;//DC高电平,SPI写入数据
  
  SPI_Send(SPI_SPI2,SPI_PCS1,data);
}

/*
 *  @brief      LCM填充一行
 *  @since      v1.0
 *  Sample usage:       LCM_Fill_Line();//LCM填充一行
 */
void MAPS_Dock_LCM_Fill_Line(uint8 Row,uint8 data)
{
  uint8 j=0;
  
  LCM_Write_CMD(0xB0|Row);    //写入页
  LCM_Write_CMD(0x10);        //高地址
  LCM_Write_CMD(0x00);        //低地址
  for(j=0;j<GUI_LCM_XMAX;j++)
  {
    LCM_Write_DATA(data);
  }
}

/*
 *  @brief      LCM填充
 *  @since      v1.0
 *  Sample usage:       LCM_Fill();//LCM填充
 */
void MAPS_Dock_LCM_Fill(uint8 data)
{
  uint8 i=0,j=0;
  
  for(i=0;i<GUI_LCM_PAGE;i++)
  {
    LCM_Write_CMD(0xB0|i);      //写入页
    LCM_Write_CMD(0x10);        //高地址
    LCM_Write_CMD(0x00);        //低地址
    for(j=0;j<GUI_LCM_XMAX;j++)
    {
      LCM_Write_DATA(data);
    }
  }
}

/*
 *  @brief      LCM清屏
 *  @since      v1.0
 *  Sample usage:       LCM_CLS();//LCM清屏
 */
void MAPS_Dock_LCM_CLS(void)
{
  uint8 i=0,j=0;
  
  for(i=0;i<GUI_LCM_PAGE;i++)
  {
    LCM_Write_CMD(0xB0|i);      //写入页
    LCM_Write_CMD(0x10);        //高地址
    LCM_Write_CMD(0x00);        //低地址
    for(j=0;j<GUI_LCM_XMAX;j++)
    {
      LCM_Write_DATA(0x00);
    }
  }
}

/*
 *  @brief      LCM复位
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Reset();
 */
void MAPS_Dock_LCM_Reset(void)
{
  DisableInterrupts;
  MAPS_Dock_LCM_Init();
  MAPS_Dock_LCM_CLS();
  EnableInterrupts;
}

/*
 *  @brief      MAPS_Dock_LCM初始化
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Init();//初始化MAPS_LCM
 */
void MAPS_Dock_LCM_Init(void)
{
  
  //SPI初始化
  SPI_Init(SPI_SPI2,SPI_PCS1,MASTER,10000000);//初始化SPI2,SCLK:PTD12,MOSI:PTD13,MISO:PTD14,CS1:PTD15,波特率10Mbps
  LCM_PORT_INIT_DC;//初始化数据命令信号DC:PTD10
  
  //LCM初始化
  LCM_Write_CMD(0xAE);//关闭显示
  LCM_Delay(10);
  LCM_Write_CMD(0xE2);//LCM复位
  LCM_Delay(10);
  LCM_Write_CMD(0xA2);//Bias设置
  LCM_Delay(10);
  LCM_Write_CMD(0xA0);//显示设置,从左到右显示
  LCM_Delay(10);
  LCM_Write_CMD(0xC8);//显示设置,从上到下显示
  LCM_Delay(10);
  
  LCM_Write_CMD(0x2C);//电源升压设置
  LCM_Delay(50000);
  LCM_Write_CMD(0x2E);//电源校准设置
  LCM_Delay(50000);
  LCM_Write_CMD(0x2F);//电压跟随设置
  LCM_Delay(50000);
  
  LCM_Write_CMD(0x25);//设置电压寄存器
  LCM_Delay(10);
  LCM_Write_CMD(0x81);//设置电压模式
  LCM_Delay(10);
  LCM_Write_CMD(0x20);//设置电压寄存器
  LCM_Delay(10);
  LCM_Write_CMD(0xB0);//设置页地址
  LCM_Delay(10);
  LCM_Write_CMD(0x10);//设置列高位地址
  LCM_Delay(10);
  LCM_Write_CMD(0x00);//设置列低位地址
  LCM_Delay(10);
  LCM_Write_CMD(0xAF);//打开显示
  LCM_Delay(10);
  
  LCM_Write_CMD(0xA5);//打开显示所有
  LCM_Delay(10);
  LCM_Write_CMD(0xAE);//关闭显示
  LCM_Delay(10);
  LCM_Write_CMD(0xAF);//打开显示
  LCM_Delay(10);
  LCM_Write_CMD(0xA4);//正常模式
  LCM_Delay(10);
  MAPS_Dock_LCM_CLS();
}

/*
 *  @brief      LCM设置坐标点
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~7
 *  @since      v1.0
 *  Sample usage:       LCM_Set_Pos();//LCM设置坐标点
 */
static inline void MAPS_Dock_LCM_Set_Pos(uint8 x,uint8 y)
{
  LCM_Write_CMD(0xB0|y);                //写入页
  LCM_Write_CMD(0x10|((x&0xf0)>>4));    //高地址
  LCM_Write_CMD(0x00|(x&0x0f));         //低地址
}

/*
 *  @brief      LCM绘制一个坐标点
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~63
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Pixel(0,0);
 */
void MAPS_Dock_LCM_Put_Pixel(uint8 x,uint8 y)
{
  uint8 data;
  
  MAPS_Dock_LCM_Set_Pos(x,y);
  data = 0x01<<(y%8);
  LCM_Write_CMD(0xB0|(y>>3));           //写入页
  LCM_Write_CMD(0x10|((x&0xf0)>>4));    //高地址
  LCM_Write_CMD(0x00|(x&0x0f));         //低地址
  LCM_Write_DATA(data);                 //写入数据
}

/*
 *  @brief      LCM绘制6x8字符
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~7
 *  @param      uint8   *ch     ch数组
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Put_Str_6x8(0,0,"hello");
 */
void MAPS_Dock_LCM_Put_Str_6x8(uint8 x,uint8 y,uint8 *ch,LCM_Color_e LCM_Color_x)
{
  uint8 c=0,i=0,j=0;
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=6,j++)
    {
      c=*(ch+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(Oled_FontLib_6x8[c][i]);
      }
    }
  }
  else
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=6,j++)
    {
      c=*(ch+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_6x8[c][i]);
      }
    }
  }
  
}

/*
 *  @brief      LCM绘制8x16字符
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0,2,4,6
 *  @param      uint8   *ch     ch数组
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Put_Str_8x16(0,0,"hello");
 */
void MAPS_Dock_LCM_Put_Str_8x16(uint8 x,uint8 y,uint8 *ch,LCM_Color_e LCM_Color_x)
{
  uint8 c=0,i=0,j=0;
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=8,j++)
    {
      c=*(ch+j)-32;
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i+8]);
      }
    }
  }
  else
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=8,j++)
    {
      c=*(ch+j)-32;
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i+8]);
      }
    }
  }
}

/*
 *  @brief      LCM绘制12x24字符
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0,4
 *  @param      uint8   *ch     ch数组
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Put_Str_12x24(0,0,"hello");
 */
void MAPS_Dock_LCM_Put_Str_12x24(uint8 x,uint8 y,uint8 *ch,LCM_Color_e LCM_Color_x)
{
  uint8 c=0,i=0,j=0;
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=12,j++)
    {
      c=*(ch+j)-32;
      
      if(x>115)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<12;i++)
      {
        LCM_Write_DATA(Oled_FontLib_12x24[c*36+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<12;i++)
      {
        LCM_Write_DATA(Oled_FontLib_12x24[c*36+i+12]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+2);
      
      for(i=0;i<12;i++)
      {
        LCM_Write_DATA(Oled_FontLib_12x24[c*36+i+24]);
      }
    }
  }
  else
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=12,j++)
    {
      c=*(ch+j)-32;
      
      if(x>115)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<12;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_12x24[c*36+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<12;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_12x24[c*36+i+12]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+2);
      
      for(i=0;i<12;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_12x24[c*36+i+24]);
      }
    }
  }
}

/*
 *  @brief      LCM绘制128x64静态图片
 *  @param      uint8   Picture[]    Picture数组
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Draw_Picture_128x64(&Oled_Picture_128x64_Star[0][0]);
 */
void MAPS_Dock_LCM_Draw_Picture_128x64(const uint8 *Picture,LCM_Color_e LCM_Color_x)
{
  int i=0,j=0,k=0;
  uint32 Pixel=0;
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(i=0;i<8;i++)
    {
      MAPS_Dock_LCM_Set_Pos(0,i);
      
      for(j=0;j<16;j++)
      {
        for(k=7;k>=0;k--)
        {
          Pixel=(((*(Picture+(i*8+0)*16+j))&(0x01<<k))>>k)*(1<<0)
                +(((*(Picture+(i*8+1)*16+j))&(0x01<<k))>>k)*(1<<1)
                  +(((*(Picture+(i*8+2)*16+j))&(0x01<<k))>>k)*(1<<2)
                    +(((*(Picture+(i*8+3)*16+j))&(0x01<<k))>>k)*(1<<3)
                      +(((*(Picture+(i*8+4)*16+j))&(0x01<<k))>>k)*(1<<4)
                        +(((*(Picture+(i*8+5)*16+j))&(0x01<<k))>>k)*(1<<5)
                          +(((*(Picture+(i*8+6)*16+j))&(0x01<<k))>>k)*(1<<6)
                            +(((*(Picture+(i*8+7)*16+j))&(0x01<<k))>>k)*(1<<7);
          LCM_Write_DATA(Pixel);
        }
      }
    }
  }
  else
  {
    for(i=0;i<8;i++)
    {
      MAPS_Dock_LCM_Set_Pos(0,i);
      
      for(j=0;j<16;j++)
      {
        for(k=7;k>=0;k--)
        {
          Pixel=(((*(Picture+(i*8+0)*16+j))&(0x01<<k))>>k)*(1<<0)
                +(((*(Picture+(i*8+1)*16+j))&(0x01<<k))>>k)*(1<<1)
                  +(((*(Picture+(i*8+2)*16+j))&(0x01<<k))>>k)*(1<<2)
                    +(((*(Picture+(i*8+3)*16+j))&(0x01<<k))>>k)*(1<<3)
                      +(((*(Picture+(i*8+4)*16+j))&(0x01<<k))>>k)*(1<<4)
                        +(((*(Picture+(i*8+5)*16+j))&(0x01<<k))>>k)*(1<<5)
                          +(((*(Picture+(i*8+6)*16+j))&(0x01<<k))>>k)*(1<<6)
                            +(((*(Picture+(i*8+7)*16+j))&(0x01<<k))>>k)*(1<<7);
          LCM_Write_DATA(~Pixel);
        }
      }
    }
  }
}

/*
 *  @brief      LCM绘制6x8正整参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~7
 *  @param      uint8   *ch     ch数组,参数名显示
 *  @param      int     Value   Value整型参数(Value是正数)
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Put_Para_6x8(0,0,"hello:",Value);
 */
void MAPS_Dock_LCM_Put_Para_6x8(uint8 x,uint8 y,uint8 *ch,int Value,LCM_Color_e LCM_Color_x)
{
  uint8 c=0,i=0,j=0;
  int LCM_Num[5]={0};
  
  LCM_TenThousand = Value / 10000;
  LCM_Thousand = (Value % 10000) / 1000;
  LCM_Hundred = (Value % 1000) / 100;
  LCM_Ten = (Value % 100) / 10;
  LCM_Single = Value % 10;
  
  if(LCM_TenThousand != 0)
  {
    LCM_Num[0] = LCM_TenThousand + 16;
    LCM_Num[1] = LCM_Thousand + 16;
    LCM_Num[2] = LCM_Hundred + 16;
    LCM_Num[3] = LCM_Ten + 16;
    LCM_Num[4] = LCM_Single + 16;
  }
  else if(LCM_Thousand != 0)
  {
    LCM_Num[0] = LCM_Thousand + 16;
    LCM_Num[1] = LCM_Hundred + 16;
    LCM_Num[2] = LCM_Ten + 16;
    LCM_Num[3] = LCM_Single + 16;
    LCM_Num[4] = 0;
  }
  else if(LCM_Hundred != 0)
  {
    LCM_Num[0] = LCM_Hundred + 16;
    LCM_Num[1] = LCM_Ten + 16;
    LCM_Num[2] = LCM_Single + 16;
    LCM_Num[3] = 0;
    LCM_Num[4] = 0;
  }
  else if(LCM_Ten != 0)
  {
    LCM_Num[0] = LCM_Ten + 16;
    LCM_Num[1] = LCM_Single + 16;
    LCM_Num[2] = 0;
    LCM_Num[3] = 0;
    LCM_Num[4] = 0;
  }
  else if(LCM_Single != 0)
  {
    LCM_Num[0] = LCM_Single + 16;
    LCM_Num[1] = 0;
    LCM_Num[2] = 0;
    LCM_Num[3] = 0;
    LCM_Num[4] = 0;
  }
  else
  {
    LCM_Num[0] = 16;
    LCM_Num[1] = 0;
    LCM_Num[2] = 0;
    LCM_Num[3] = 0;
    LCM_Num[4] = 0;
  }
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=6,j++)
    {
      c=*(ch+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(Oled_FontLib_6x8[c][i]);
      }
    }
    
    for(c=0,i=0,j=0;j<5;x+=6,j++)
    {
      c=LCM_Num[j];
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(Oled_FontLib_6x8[c][i]);
      }
    }
  }
  else
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=6,j++)
    {
      c=*(ch+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_6x8[c][i]);
      }
    }
    
    for(c=0,i=0,j=0;j<5;x+=6,j++)
    {
      c=LCM_Num[j];
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_6x8[c][i]);
      }
    }
  }
  
}

/*
 *  @brief      LCM绘制6x8浮点参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~7
 *  @param      uint8   *ch     ch数组,参数名显示
 *  @param      float   Value   Value浮点参数(Value是正数)
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Put_Para_Pot_6x8(0,0,"hello:",Value);
 */
void MAPS_Dock_LCM_Put_Para_Pot_6x8(uint8 x,uint8 y,uint8 *ch,float Value,LCM_Color_e LCM_Color_x)
{
  uint8 c=0,i=0,j=0;
  int LCM_Num[5]={0};
  
  LCM_Ten = ((int)Value % 100) / 10;
  LCM_Single = (int)Value % 10;
  LCM_Pot_Ten = (int)(Value * 10) % 10;
  LCM_Pot_Hundred = (int)(Value * 100) % 10;
  
  if(LCM_Ten != 0)
  {
    LCM_Num[0] = LCM_Ten + 16;
    LCM_Num[1] = LCM_Single + 16;
    LCM_Num[2] = 14;
    LCM_Num[3] = LCM_Pot_Ten + 16;
    LCM_Num[4] = LCM_Pot_Hundred + 16;
  }
  else if(LCM_Single != 0)
  {
    LCM_Num[0] = LCM_Single + 16;
    LCM_Num[1] = 14;
    LCM_Num[2] = LCM_Pot_Ten + 16;
    LCM_Num[3] = LCM_Pot_Hundred + 16;
    LCM_Num[4] = 0;
  }
  else
  {
    LCM_Num[0] = 16;
    LCM_Num[1] = 14;
    LCM_Num[2] = LCM_Pot_Ten + 16;
    LCM_Num[3] = LCM_Pot_Hundred + 16;
    LCM_Num[4] = 0;
  }
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=6,j++)
    {
      c=*(ch+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(Oled_FontLib_6x8[c][i]);
      }
    }
    
    for(c=0,i=0,j=0;j<5;x+=6,j++)
    {
      c=LCM_Num[j];
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(Oled_FontLib_6x8[c][i]);
      }
    }
  }
  else
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=6,j++)
    {
      c=*(ch+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_6x8[c][i]);
      }
    }
    
    for(c=0,i=0,j=0;j<5;x+=6,j++)
    {
      c=LCM_Num[j];
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_6x8[c][i]);
      }
    }
  }
  
}

/*
 *  @brief      LCM绘制8x16正整参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0,2,4,6
 *  @param      uint8   *ch     ch数组,参数名显示
 *  @param      int     Value   Value整型参数(Value是正数)
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Put_Para_8x16(0,0,"hello:",Value);
 */
void MAPS_Dock_LCM_Put_Para_8x16(uint8 x,uint8 y,uint8 *ch,int Value,LCM_Color_e LCM_Color_x)
{
  uint8 c=0,i=0,j=0;
  int LCM_Num[5]={0};
  
  LCM_TenThousand = Value / 10000;
  LCM_Thousand = (Value % 10000) / 1000;
  LCM_Hundred = (Value % 1000) / 100;
  LCM_Ten = (Value % 100) / 10;
  LCM_Single = Value % 10;
  
  if(LCM_TenThousand != 0)
  {
    LCM_Num[0] = LCM_TenThousand + 16;
    LCM_Num[1] = LCM_Thousand + 16;
    LCM_Num[2] = LCM_Hundred + 16;
    LCM_Num[3] = LCM_Ten + 16;
    LCM_Num[4] = LCM_Single + 16;
  }
  else if(LCM_Thousand != 0)
  {
    LCM_Num[0] = LCM_Thousand + 16;
    LCM_Num[1] = LCM_Hundred + 16;
    LCM_Num[2] = LCM_Ten + 16;
    LCM_Num[3] = LCM_Single + 16;
    LCM_Num[4] = 0;
  }
  else if(LCM_Hundred != 0)
  {
    LCM_Num[0] = LCM_Hundred + 16;
    LCM_Num[1] = LCM_Ten + 16;
    LCM_Num[2] = LCM_Single + 16;
    LCM_Num[3] = 0;
    LCM_Num[4] = 0;
  }
  else if(LCM_Ten != 0)
  {
    LCM_Num[0] = LCM_Ten + 16;
    LCM_Num[1] = LCM_Single + 16;
    LCM_Num[2] = 0;
    LCM_Num[3] = 0;
    LCM_Num[4] = 0;
  }
  else if(LCM_Single != 0)
  {
    LCM_Num[0] = LCM_Single + 16;
    LCM_Num[1] = 0;
    LCM_Num[2] = 0;
    LCM_Num[3] = 0;
    LCM_Num[4] = 0;
  }
  else
  {
    LCM_Num[0] = 16;
    LCM_Num[1] = 0;
    LCM_Num[2] = 0;
    LCM_Num[3] = 0;
    LCM_Num[4] = 0;
  }
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=8,j++)
    {
      c=*(ch+j)-32;
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i+8]);
      }
    }
    
    for(c=0,i=0,j=0;j<5;x+=8,j++)
    {
      c=LCM_Num[j];
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i+8]);
      }
    }    
  }
  else
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=8,j++)
    {
      c=*(ch+j)-32;
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i+8]);
      }
    }
    
    for(c=0,i=0,j=0;j<5;x+=8,j++)
    {
      c=LCM_Num[j];
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i+8]);
      }
    }
  }
  
}

/*
 *  @brief      LCM绘制8x16浮点参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0,2,4,6
 *  @param      uint8   *ch     ch数组,参数名显示
 *  @param      float   Value   Value浮点参数(Value是正数)
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Put_Para_Pot_8x16(0,0,"hello:",Value);
 */
void MAPS_Dock_LCM_Put_Para_Pot_8x16(uint8 x,uint8 y,uint8 *ch,float Value,LCM_Color_e LCM_Color_x)
{
  uint8 c=0,i=0,j=0;
  int LCM_Num[5]={0};
  
  LCM_Ten = ((int)Value % 100) / 10;
  LCM_Single = (int)Value % 10;
  LCM_Pot_Ten = (int)(Value * 10) % 10;
  LCM_Pot_Hundred = (int)(Value * 100) % 10;
  
  if(LCM_Ten != 0)
  {
    LCM_Num[0] = LCM_Ten + 16;
    LCM_Num[1] = LCM_Single + 16;
    LCM_Num[2] = 14;
    LCM_Num[3] = LCM_Pot_Ten + 16;
    LCM_Num[4] = LCM_Pot_Hundred + 16;
  }
  else if(LCM_Single != 0)
  {
    LCM_Num[0] = LCM_Single + 16;
    LCM_Num[1] = 14;
    LCM_Num[2] = LCM_Pot_Ten + 16;
    LCM_Num[3] = LCM_Pot_Hundred + 16;
    LCM_Num[4] = 0;
  }
  else
  {
    LCM_Num[0] = 16;
    LCM_Num[1] = 14;
    LCM_Num[2] = LCM_Pot_Ten + 16;
    LCM_Num[3] = LCM_Pot_Hundred + 16;
    LCM_Num[4] = 0;
  }
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=8,j++)
    {
      c=*(ch+j)-32;
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i+8]);
      }
    }
    
    for(c=0,i=0,j=0;j<5;x+=8,j++)
    {
      c=LCM_Num[j];
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(Oled_FontLib_8x16[c*16+i+8]);
      }
    }
  }
  else
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=8,j++)
    {
      c=*(ch+j)-32;
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i+8]);
      }
    }
    
    for(c=0,i=0,j=0;j<5;x+=8,j++)
    {
      c=LCM_Num[j];
      
      if(x>119)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i]);
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y+1);
      
      for(i=0;i<8;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_8x16[c*16+i+8]);
      }
    }
  }
  
}

/*
 *  @brief      LCM绘制6x8字符数组参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~7
 *  @param      uint8   *ch     ch数组,参数名显示
 *  @param      uint8   *buff   buff数组
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_Put_Para_Char_6x8(0,0,"hello:",Value);
 */
void MAPS_Dock_LCM_Put_Para_Buff_6x8(uint8 x,uint8 y,uint8 *ch,uint8 *buff,LCM_Color_e LCM_Color_x)
{
  uint8 c=0,i=0,j=0;
  
  if(LCM_Color_x == LCM_Pure_Color)
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=6,j++)
    {
      c=*(ch+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(Oled_FontLib_6x8[c][i]);
      }
    }
    
    for(c=0,i=0,j=0;*(buff+j)!='\0';x+=6,j++)
    {
      c=*(buff+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(Oled_FontLib_6x8[c][i]);
      }
    }
  }
  else
  {
    for(c=0,i=0,j=0;*(ch+j)!='\0';x+=6,j++)
    {
      c=*(ch+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_6x8[c][i]);
      }
    }
    
    for(c=0,i=0,j=0;*(buff+j)!='\0';x+=6,j++)
    {
      c=*(buff+j)-32;
      
      if(x>121)
      {
        x=0;
        y++;
      }
      
      MAPS_Dock_LCM_Set_Pos(x,y);
      
      for(i=0;i<6;i++)
      {
        LCM_Write_DATA(~Oled_FontLib_6x8[c][i]);
      }
    }
  }
}

/*
 *  @brief      LCM绘制BMP图像(8*128数组)
 *  @para       uint8   *Buff
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_LCM_DrawBMP();//LCM绘制BMP图像
 */
void MAPS_Dock_LCM_DrawBMP(const uint8 *Buff,LCM_Color_e LCM_Color_x)
{
  uint8 i=0,j=0;
  
  if(LCM_Color_x == LCM_Pure_Color)//正色
  {
    for(i=0;i<GUI_LCM_PAGE;i++)
    {
      MAPS_Dock_LCM_Set_Pos(0,i);
      
      for(j=0;j<GUI_LCM_XMAX;j++)
      {
        LCM_Write_DATA(*Buff++);
      }
    }
  }
  else//反色
  {
    for(i=0;i<GUI_LCM_PAGE;i++)
    {
      MAPS_Dock_LCM_Set_Pos(0,i);
      
      for(j=0;j<GUI_LCM_XMAX;j++)
      {
        LCM_Write_DATA(~*Buff++);
      }
    }
  }
}