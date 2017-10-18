/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Drive_Oled.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __DRIVE_OLED_H__
#define __DRIVE_OLED_H__

#include "Common.h"

/*
**SPI�˿ڶ���
*/

/*
**CK:ʱ������ DI:�������� RST:��λ�ź� DC:����/����
*/
#define OLED_PORT_INIT_CK       GPIO_Init(PTB21,GPO,0)  //SPI��ʱ���ź�CK    //PTC16
#define OLED_PORT_INIT_DI       GPIO_Init(PTB23,GPO,0)  //SPI�������ź�DI    //PTC17
#define OLED_PORT_INIT_RST      GPIO_Init(PTB19,GPO,0)  //SPI�ĸ�λ�ź�RST   //PTC18
#define OLED_PORT_INIT_DC       GPIO_Init(PTB20,GPO,0)  //SPI�����������ź�DC//PTC19

/*
**�˿ڵ�ƽ��
*/
#define OLED_SET_CK_H           GPIO_SET(PTB21,1)       //SPI����CK�ߵ�ƽ    //PTC16
#define OLED_SET_CK_L           GPIO_SET(PTB21,0)       //SPI����CK�͵�ƽ    //PTC16
#define OLED_SET_DI_H           GPIO_SET(PTB23,1)       //SPI����DI�ߵ�ƽ    //PTC17
#define OLED_SET_DI_L           GPIO_SET(PTB23,0)       //SPI����DI�͵�ƽ    //PTC17
#define OLED_SET_RST_H          GPIO_SET(PTB19,1)       //SPI����RST�ߵ�ƽ   //PTC18
#define OLED_SET_RST_L          GPIO_SET(PTB19,0)       //SPI����RST�͵�ƽ   //PTC18
#define OLED_SET_DC_H           GPIO_SET(PTB20,1)       //SPI����DC�ߵ�ƽ    //PTC19
#define OLED_SET_DC_L           GPIO_SET(PTB20,0)       //SPI����DC�͵�ƽ    //PTC19

/*
**Oled���궨��
*/
#define OLED_XLevelL            0x00                            //OledX���λ
#define OLED_XLevelH	        0x10                            //OledX���λ
#define OLED_XLevel	        ((XLevelH&0x0F)*16+XLevelL)     //OledX������
#define OLED_Max_COL	        128                             //Oled�������
#define OLED_Max_ROW		64                              //Oled�������
#define	OLED_BRIGHTNESS	        0xCF                            //Oled����
#define OLED_X_WIDTH            128                             //OledX����
#define OLED_Y_WIDTH            64                              //OledY����

/*
**variate declaration
*/
extern const uint8 Oled_FontLib_6x8[][6];
extern const uint8 Oled_FontLib_8x16[];
extern const uint8 Oled_FontLib_12x24[];
extern const uint8 Oled_Picture_128x64_Star[][16];
extern const uint8 Oled_Picture_128x64_JBD_Logo[][16];

/*
**function declaration
*/
extern void Oled_WrDat(uint8 data);
extern void Oled_WrCmd(uint8 cmd);
extern void Oled_Set_Pos(uint8 x,uint8 y);
extern void Oled_Fill(uint8 data);
extern void Oled_Clean(void);
extern void Oled_Reset(void);
extern void Oled_Init(void);
extern void Oled_Put_Pixel(uint8 x,uint8 y);
extern void Oled_Put_Str_6x8(uint8 x,uint8 y,uint8 ch[]);
extern void Oled_Put_Str_8x16(uint8 x,uint8 y,uint8 ch[]);
extern void Oled_Put_Str_12x24(uint8 x,uint8 y,uint8 ch[]);
extern void Oled_Draw_Picture_128x64(const uint8 *Picture);
extern void Oled_Put_Para_6x8(uint8 x,uint8 y,uint8 ch[],int Value);
extern void Oled_Put_Para_Pot_6x8(uint8 x,uint8 y,uint8 ch[],float Value);
extern void Oled_Put_Para_8x16(uint8 x,uint8 y,uint8 ch[],int Value);
extern void Oled_Put_Para_Pot_8x16(uint8 x,uint8 y,uint8 ch[],float Value);

#endif