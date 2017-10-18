/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Drive_Oled.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

//SSD1306
/*
**Oled_Put_Para
*/
//Oled参数的5位
int Oled_TenThousand=0;
int Oled_Thousand=0;
int Oled_Hundred=0;
int Oled_Ten=0;
int Oled_Single=0;
int Oled_Pot_Ten=0;
int Oled_Pot_Hundred=0;

/*
 *  @brief      Oled写入数据
 *  @param      uint8   data
 *  @since      v1.0
 *  Sample usage:       Oled_WrDat(0xAA);
 */
void Oled_WrDat(uint8 data)
{
  uint8 i=0;
  
  OLED_SET_DC_H;//Oled写入数据
  
  for(i=0;i<8;i++,data<<=1)//从高到低写入8Bit
  {
    OLED_SET_CK_L;//时钟线低电平
    
    if(data&0x80)
    {
      OLED_SET_DI_H;//数据线高电平
    }
    else
    {
      OLED_SET_DI_L;//数据线低电平
    }
    
    OLED_SET_CK_H;//时钟线高电平
  }
}

/*
 *  @brief      Oled写入命令
 *  @param      uint8   cmd
 *  @since      v1.0
 *  Sample usage:       Oled_WrCmd(0xAA);
 */
void Oled_WrCmd(uint8 cmd)
{
  uint8 i=0;
  
  OLED_SET_DC_L;//Oled写入命令
  
  for(i=0;i<8;i++,cmd<<=1)//从高到低写入8Bit
  {
    OLED_SET_CK_L;//时钟线低电平
    
    if(cmd&0x80)
    {
      OLED_SET_DI_H;//数据线高电平
    }
    else
    {
      OLED_SET_DI_L;//数据线低电平
    }
    
    OLED_SET_CK_H;//时钟线高电平
  }
}

/*
 *  @brief      Oled设置坐标点
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~63
 *  @since      v1.0
 *  Sample usage:       Oled_Set_Pos(64,32);
 */
void Oled_Set_Pos(uint8 x,uint8 y)
{
  Oled_WrCmd(0xb0+y);
  Oled_WrCmd(((x&0xf0)>>4)|0x10);
  Oled_WrCmd((x&0x0f)|0x01);
}

/*
 *  @brief      Oled全屏显示
 *  @param      uint8   data
 *  @since      v1.0
 *  Sample usage:       Oled_Fill(0xff);
 */
void Oled_Fill(uint8 data)
{
  uint8 i,j;
  
  for(j=0;j<8;j++)
  {
    Oled_WrCmd(0xb0+j);
    Oled_WrCmd(0x01);
    Oled_WrCmd(0x10);
    for(i=0;i<OLED_X_WIDTH;i++)
    {
      Oled_WrDat(data);
    }
  }
}

/*
 *  @brief      Oled清屏
 *  @since      v1.0
 *  Sample usage:       Oled_Clean();
 */
void Oled_Clean(void)
{
  uint8 i,j;
  
  for(j=0;j<8;j++)
  {
    Oled_WrCmd(0xb0+j);
    Oled_WrCmd(0x01);
    Oled_WrCmd(0x10);
    for(i=0;i<OLED_X_WIDTH;i++)
    {
      Oled_WrDat(0);
    }
  }
}

/*
 *  @brief      Oled复位
 *  @since      v1.0
 *  Sample usage:       Oled_Reset();
 */
void Oled_Reset(void)
{
  DisableInterrupts;
  Oled_Init();
  Oled_Clean();
  EnableInterrupts;
}

/*
 *  @brief      Oled初始化
 *  @since      v1.0
 *  Sample usage:       Oled_Init();
 */
void Oled_Init(void)
{
  OLED_PORT_INIT_CK;    //SPI的CK
  OLED_PORT_INIT_DI;    //SPI的DI
  OLED_PORT_INIT_RST;   //SPI的RST
  OLED_PORT_INIT_DC;    //SPI的DC
  
  OLED_SET_CK_H;        //时钟线拉低
  OLED_SET_RST_L;       //Oled复位
  DELAY_us(50);
  OLED_SET_RST_H;
  
  Oled_WrCmd(0xae);     //--turn off oled panel
  Oled_WrCmd(0x00);     //---set low column address
  Oled_WrCmd(0x10);     //---set high column address
  Oled_WrCmd(0x40);     //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  Oled_WrCmd(0x81);     //--set contrast control register
  Oled_WrCmd(0xcf);     // Set SEG Output Current Brightness 0xcf
  Oled_WrCmd(0xa1);     //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  Oled_WrCmd(0xc8);     //Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  Oled_WrCmd(0xa6);     //--set normal display
  Oled_WrCmd(0xa8);     //--set multiplex ratio(1 to 64)
  Oled_WrCmd(0x3f);     //--1/64 duty
  Oled_WrCmd(0xd3);     //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  Oled_WrCmd(0x00);     //-not offset
  Oled_WrCmd(0xd5);     //--set display clock divide ratio/oscillator frequency
  Oled_WrCmd(0x80);     //--set divide ratio, Set Clock as 100 Frames/Sec
  Oled_WrCmd(0xd9);     //--set pre-charge period
  Oled_WrCmd(0xf1);     //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  Oled_WrCmd(0xda);     //--set com pins hardware configuration
  Oled_WrCmd(0x12);     //
  Oled_WrCmd(0xdb);     //--set vcomh
  Oled_WrCmd(0x40);     //Set VCOM Deselect Level
  Oled_WrCmd(0x20);     //-Set Page Addressing Mode (0x00/0x01/0x02)
  Oled_WrCmd(0x02);     //
  Oled_WrCmd(0x8d);     //--set Charge Pump enable/disable
  Oled_WrCmd(0x14);     //--set(0x10) disable
  Oled_WrCmd(0xa4);     // Disable Entire Display On (0xa4/0xa5)
  Oled_WrCmd(0xa6);     // Disable Inverse Display On (0xa6/a7) 
  Oled_WrCmd(0xaf);     //--turn on oled panel
  Oled_Clean();
  Oled_Set_Pos(0,0);
}

/*
 *  @brief      Oled绘制一个坐标点
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~63
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Pixel(0,0);
 */
void Oled_Put_Pixel(uint8 x,uint8 y)
{
  uint8 data;
  
  Oled_Set_Pos(x,y);
  
  data = 0x01<<(y%8); 	
  Oled_WrCmd(0xb0+(y>>3));
  Oled_WrCmd(((x&0xf0)>>4)|0x10);
  Oled_WrCmd((x&0x0f)|0x00);
  Oled_WrDat(data);
}

/*
 *  @brief      Oled绘制6x8字符
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~7
 *  @param      uint8   ch[]    ch数组
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Str_6x8(0,0,"hello");
 */
void Oled_Put_Str_6x8(uint8 x,uint8 y,uint8 ch[])
{
  uint8 c=0,i=0,j=0;
  
  for(c=0,i=0,j=0;ch[j]!='\0';x+=6,j++)
  {
    c=ch[j]-32;
    
    if(x>121)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<6;i++)
    {
      Oled_WrDat(Oled_FontLib_6x8[c][i]);
    }
  }
}

/*
 *  @brief      Oled绘制8x16字符
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0,2,4,6
 *  @param      uint8   ch[]    ch数组
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Str_8x16(0,0,"hello");
 */
void Oled_Put_Str_8x16(uint8 x,uint8 y,uint8 ch[])
{
  uint8 c=0,i=0,j=0;
  
  while(ch[j]!='\0')
  {
    c=ch[j]-32;
    
    if(x>119)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i]);
    }
    
    Oled_Set_Pos(x,y+1);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i+8]);
    }
    
    x+=8;
    j++;
  }
  
}

/*
 *  @brief      Oled绘制12x24字符
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0,4
 *  @param      uint8   ch[]    ch数组
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Str_12x24(0,0,"hello");
 */
void Oled_Put_Str_12x24(uint8 x,uint8 y,uint8 ch[])
{
  uint8 c=0,i=0,j=0;
  
  while(ch[j]!='\0')
  {
    c=ch[j]-32;
    
    if(x>115)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<12;i++)
    {
      Oled_WrDat(Oled_FontLib_12x24[c*36+i]);
    }
    
    Oled_Set_Pos(x,y+1);
    
    for(i=0;i<12;i++)
    {
      Oled_WrDat(Oled_FontLib_12x24[c*36+i+12]);
    }
    
    Oled_Set_Pos(x,y+2);
    
    for(i=0;i<12;i++)
    {
      Oled_WrDat(Oled_FontLib_12x24[c*36+i+24]);
    }

    x+=12;
    j++;
  }
}

/*
 *  @brief      Oled绘制128x64静态图片
 *  @param      uint8   Picture[]    Picture数组
 *  @since      v1.0
 *  Sample usage:       Oled_Draw_Picture_128x64(&Oled_Picture_128x64_Star[0][0]);
 */
void Oled_Draw_Picture_128x64(const uint8 *Picture)
{
  int i=0,j=0,k=0;
  uint32 Pixel=0;
  
  for(i=0;i<8;i++)
  {
    Oled_Set_Pos(0,i);
    
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
        Oled_WrDat(Pixel);
      }
    }
  }
}

/*
 *  @brief      Oled绘制6x8正整参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~7
 *  @param      uint8   ch[]    ch数组,参数名显示
 *  @param      int     Value   Value整型参数(Value是正数)
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Para_6x8(0,0,"hello:",Value);
 */
void Oled_Put_Para_6x8(uint8 x,uint8 y,uint8 ch[],int Value)
{
  uint8 c=0,i=0,j=0;
  int Oled_Num[5]={0};
  
  Oled_TenThousand = Value / 10000;
  Oled_Thousand = (Value % 10000) / 1000;
  Oled_Hundred = (Value % 1000) / 100;
  Oled_Ten = (Value % 100) / 10;
  Oled_Single = Value % 10;
    
  if(Oled_TenThousand != 0)
  {
    Oled_Num[0] = Oled_TenThousand + 16;
    Oled_Num[1] = Oled_Thousand + 16;
    Oled_Num[2] = Oled_Hundred + 16;
    Oled_Num[3] = Oled_Ten + 16;
    Oled_Num[4] = Oled_Single + 16;
  }
  else if(Oled_Thousand != 0)
  {
    Oled_Num[0] = Oled_Thousand + 16;
    Oled_Num[1] = Oled_Hundred + 16;
    Oled_Num[2] = Oled_Ten + 16;
    Oled_Num[3] = Oled_Single + 16;
    Oled_Num[4] = 0;
  }
  else if(Oled_Hundred != 0)
  {
    Oled_Num[0] = Oled_Hundred + 16;
    Oled_Num[1] = Oled_Ten + 16;
    Oled_Num[2] = Oled_Single + 16;
    Oled_Num[3] = 0;
    Oled_Num[4] = 0;
  }
  else if(Oled_Ten != 0)
  {
    Oled_Num[0] = Oled_Ten + 16;
    Oled_Num[1] = Oled_Single + 16;
    Oled_Num[2] = 0;
    Oled_Num[3] = 0;
    Oled_Num[4] = 0;
  }
  else if(Oled_Single != 0)
  {
    Oled_Num[0] = Oled_Single + 16;
    Oled_Num[1] = 0;
    Oled_Num[2] = 0;
    Oled_Num[3] = 0;
    Oled_Num[4] = 0;
  }
  else
  {
    Oled_Num[0] = 16;
    Oled_Num[1] = 0;
    Oled_Num[2] = 0;
    Oled_Num[3] = 0;
    Oled_Num[4] = 0;
  }
  
  for(c=0,i=0,j=0;ch[j]!='\0';x+=6,j++)
  {
    c=ch[j]-32;
    
    if(x>121)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<6;i++)
    {
      Oled_WrDat(Oled_FontLib_6x8[c][i]);
    }
  }
  
  for(c=0,i=0,j=0;j<5;x+=6,j++)
  {
    c=Oled_Num[j];
    
    if(x>121)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<6;i++)
    {
      Oled_WrDat(Oled_FontLib_6x8[c][i]);
    }
  }
  
}

/*
 *  @brief      Oled绘制6x8浮点参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0~7
 *  @param      uint8   ch[]    ch数组,参数名显示
 *  @param      float   Value   Value浮点参数(Value是正数)
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Para_Pot_6x8(0,0,"hello:",Value);
 */
void Oled_Put_Para_Pot_6x8(uint8 x,uint8 y,uint8 ch[],float Value)
{
  uint8 c=0,i=0,j=0;
  int Oled_Num[5]={0};
  
  Oled_Ten = ((int)Value % 100) / 10;
  Oled_Single = (int)Value % 10;
  Oled_Pot_Ten = (int)(Value * 10) % 10;
  Oled_Pot_Hundred = (int)(Value * 100) % 10;
    
  if(Oled_Ten != 0)
  {
    Oled_Num[0] = Oled_Ten + 16;
    Oled_Num[1] = Oled_Single + 16;
    Oled_Num[2] = 14;
    Oled_Num[3] = Oled_Pot_Ten + 16;
    Oled_Num[4] = Oled_Pot_Hundred + 16;
  }
  else if(Oled_Single != 0)
  {
    Oled_Num[0] = Oled_Single + 16;
    Oled_Num[1] = 14;
    Oled_Num[2] = Oled_Pot_Ten + 16;
    Oled_Num[3] = Oled_Pot_Hundred + 16;
    Oled_Num[4] = 0;
  }
  else
  {
    Oled_Num[0] = 16;
    Oled_Num[1] = 14;
    Oled_Num[2] = Oled_Pot_Ten + 16;
    Oled_Num[3] = Oled_Pot_Hundred + 16;
    Oled_Num[4] = 0;
  }
  
  for(c=0,i=0,j=0;ch[j]!='\0';x+=6,j++)
  {
    c=ch[j]-32;
    
    if(x>121)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<6;i++)
    {
      Oled_WrDat(Oled_FontLib_6x8[c][i]);
    }
  }
  
  for(c=0,i=0,j=0;j<5;x+=6,j++)
  {
    c=Oled_Num[j];
    
    if(x>121)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<6;i++)
    {
      Oled_WrDat(Oled_FontLib_6x8[c][i]);
    }
  }
  
}

/*
 *  @brief      Oled绘制8x16正整参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0,2,4,6
 *  @param      uint8   ch[]    ch数组,参数名显示
 *  @param      int     Value   Value整型参数(Value是正数)
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Para_8x16(0,0,"hello:",Value);
 */
void Oled_Put_Para_8x16(uint8 x,uint8 y,uint8 ch[],int Value)
{
  uint8 c=0,i=0,j=0;
  int Oled_Num[5]={0};
  
  Oled_TenThousand = Value / 10000;
  Oled_Thousand = (Value % 10000) / 1000;
  Oled_Hundred = (Value % 1000) / 100;
  Oled_Ten = (Value % 100) / 10;
  Oled_Single = Value % 10;
    
  if(Oled_TenThousand != 0)
  {
    Oled_Num[0] = Oled_TenThousand + 16;
    Oled_Num[1] = Oled_Thousand + 16;
    Oled_Num[2] = Oled_Hundred + 16;
    Oled_Num[3] = Oled_Ten + 16;
    Oled_Num[4] = Oled_Single + 16;
  }
  else if(Oled_Thousand != 0)
  {
    Oled_Num[0] = Oled_Thousand + 16;
    Oled_Num[1] = Oled_Hundred + 16;
    Oled_Num[2] = Oled_Ten + 16;
    Oled_Num[3] = Oled_Single + 16;
    Oled_Num[4] = 0;
  }
  else if(Oled_Hundred != 0)
  {
    Oled_Num[0] = Oled_Hundred + 16;
    Oled_Num[1] = Oled_Ten + 16;
    Oled_Num[2] = Oled_Single + 16;
    Oled_Num[3] = 0;
    Oled_Num[4] = 0;
  }
  else if(Oled_Ten != 0)
  {
    Oled_Num[0] = Oled_Ten + 16;
    Oled_Num[1] = Oled_Single + 16;
    Oled_Num[2] = 0;
    Oled_Num[3] = 0;
    Oled_Num[4] = 0;
  }
  else if(Oled_Single != 0)
  {
    Oled_Num[0] = Oled_Single + 16;
    Oled_Num[1] = 0;
    Oled_Num[2] = 0;
    Oled_Num[3] = 0;
    Oled_Num[4] = 0;
  }
  else
  {
    Oled_Num[0] = 16;
    Oled_Num[1] = 0;
    Oled_Num[2] = 0;
    Oled_Num[3] = 0;
    Oled_Num[4] = 0;
  }
  
  for(c=0,i=0,j=0;ch[j]!='\0';x+=8,j++)
  {
    c=ch[j]-32;
    
    if(x>119)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i]);
    }
    
    Oled_Set_Pos(x,y+1);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i+8]);
    }
  }
  
  for(c=0,i=0,j=0;j<5;x+=8,j++)
  {
    c=Oled_Num[j];
    
    if(x>119)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i]);
    }
    
    Oled_Set_Pos(x,y+1);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i+8]);
    }
  }
  
}

/*
 *  @brief      Oled绘制8x16浮点参数
 *  @param      uint8   x       x范围为0~127
 *  @param      uint8   y       y范围为0,2,4,6
 *  @param      uint8   ch[]    ch数组,参数名显示
 *  @param      float   Value   Value浮点参数(Value是正数)
 *  @since      v1.0
 *  Sample usage:       Oled_Put_Para_Pot_8x16(0,0,"hello:",Value);
 */
void Oled_Put_Para_Pot_8x16(uint8 x,uint8 y,uint8 ch[],float Value)
{
  uint8 c=0,i=0,j=0;
  int Oled_Num[5]={0};
  
  Oled_Ten = ((int)Value % 100) / 10;
  Oled_Single = (int)Value % 10;
  Oled_Pot_Ten = (int)(Value * 10) % 10;
  Oled_Pot_Hundred = (int)(Value * 100) % 10;
    
  if(Oled_Ten != 0)
  {
    Oled_Num[0] = Oled_Ten + 16;
    Oled_Num[1] = Oled_Single + 16;
    Oled_Num[2] = 14;
    Oled_Num[3] = Oled_Pot_Ten + 16;
    Oled_Num[4] = Oled_Pot_Hundred + 16;
  }
  else if(Oled_Single != 0)
  {
    Oled_Num[0] = Oled_Single + 16;
    Oled_Num[1] = 14;
    Oled_Num[2] = Oled_Pot_Ten + 16;
    Oled_Num[3] = Oled_Pot_Hundred + 16;
    Oled_Num[4] = 0;
  }
  else
  {
    Oled_Num[0] = 16;
    Oled_Num[1] = 14;
    Oled_Num[2] = Oled_Pot_Ten + 16;
    Oled_Num[3] = Oled_Pot_Hundred + 16;
    Oled_Num[4] = 0;
  }
  
  for(c=0,i=0,j=0;ch[j]!='\0';x+=8,j++)
  {
    c=ch[j]-32;
    
    if(x>119)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i]);
    }
    
    Oled_Set_Pos(x,y+1);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i+8]);
    }
  }
  
  for(c=0,i=0,j=0;j<5;x+=8,j++)
  {
    c=Oled_Num[j];
    
    if(x>119)
    {
      x=0;
      y++;
    }
    
    Oled_Set_Pos(x,y);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i]);
    }
    
    Oled_Set_Pos(x,y+1);
    
    for(i=0;i<8;i++)
    {
      Oled_WrDat(Oled_FontLib_8x16[c*16+i+8]);
    }
  }
}