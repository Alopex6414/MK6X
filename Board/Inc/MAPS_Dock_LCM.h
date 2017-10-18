/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_LCM.h
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_LCM_H__
#define __MAPS_DOCK_LCM_H__

#include "Common.h"

/*
**LCD is Manley's ZYMG12864 and driver IC is ST7565R
*/

//LCM打印颜色枚举
typedef enum
{
  LCM_Pure_Color,       //正色
  LCM_Invert_Color,     //反色
}LCM_Color_e;

//LCM端口设置宏(GPIO模拟SPI需要用到,DSPI只需要DC管脚设置CMD/DATA)
#define LCM_PORT_INIT_DC        GPIO_Init(PTD10,GPO,0)  //LCM的数据命令信号DC
#define LCM_PORT_INIT_CS        GPIO_Init(PTD15,GPO,0)  //LCM的数据命令信号CS

#define LCM_SET_DC_H            GPIO_SET(PTD10,1)       //LCM的DC端口高电平
#define LCM_SET_DC_L            GPIO_SET(PTD10,0)       //LCM的DC端口低电平
#define LCM_SET_CS_H            GPIO_SET(PTD15,1)       //LCM的CS端口高电平
#define LCM_SET_CS_L            GPIO_SET(PTD15,0)       //LCM的CS端口低电平

//LCM上电和复位延时
#define LCM_Delay(us)           DELAY_US(us)            //延时


//define the arrtibute of ZYMG12864(LCM)
#define GUI_LCM_XMAX            128             //defined the lcd's line-number is 128
#define GUI_LCM_YMAX 		64		//defined the lcd's column-number is 64
#define GUI_LCM_PAGE		8		//defined the lcd's page-number is 8(GUI_LCM_YMAX/8)

//LCM页数
#define LCM_PAGES               5

/*
**variate declaration
*/
extern const uint8 FONTTYPE8_8[][8];
extern const uint8 LCM_Freescale_logo[];

/*
**function declaration
*/
extern void MAPS_Dock_LCM_Fill_Line(uint8 Row,uint8 data);
extern void MAPS_Dock_LCM_Fill(uint8 data);
extern void MAPS_Dock_LCM_CLS(void);
extern void MAPS_Dock_LCM_Reset(void);
extern void MAPS_Dock_LCM_Init(void);
extern void MAPS_Dock_LCM_Put_Pixel(uint8 x,uint8 y);
extern void MAPS_Dock_LCM_Put_Str_6x8(uint8 x,uint8 y,uint8 *ch,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_Put_Str_8x16(uint8 x,uint8 y,uint8 *ch,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_Put_Str_12x24(uint8 x,uint8 y,uint8 *ch,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_Draw_Picture_128x64(const uint8 *Picture,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_Put_Para_6x8(uint8 x,uint8 y,uint8 *ch,int Value,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_Put_Para_Pot_6x8(uint8 x,uint8 y,uint8 *ch,float Value,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_Put_Para_8x16(uint8 x,uint8 y,uint8 *ch,int Value,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_Put_Para_Pot_8x16(uint8 x,uint8 y,uint8 *ch,float Value,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_Put_Para_Buff_6x8(uint8 x,uint8 y,uint8 *ch,uint8 *buff,LCM_Color_e LCM_Color_x);
extern void MAPS_Dock_LCM_DrawBMP(const uint8 *Buff,LCM_Color_e LCM_Color_x);

#endif