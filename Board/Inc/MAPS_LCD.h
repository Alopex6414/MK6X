/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_LCD.h
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��(TFT:ILI9341)
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_LCD_H__
#define __MAPS_LCD_H__

#include "Common.h"

/*
**MAPS_LCD��ض˿ں�
*/
#define MAPS_LCD_RD             PTB19
#define MAPS_LCD_RW             PTC11
#define MAPS_LCD_CLK            PTC3
#define MAPS_LCD_ALE            PTD0
#define MAPS_LCD_CS0            PTD1
#define MAPS_LCD_CS2            PTC18
#define MAPS_LCD_BE31_24        PTC17
#define MAPS_LCD_BE23_16        PTC16

#define MAPS_LCD_BLC            PTD9
#define MAPS_LCD_DC             PTD10

/*
**FLEXBUS��غ�
*/
#define FLEX_BASE_ADDRESS       0x6000
#define SRAM_BASE_ADDRESS       0x8000
#define FLEX_ADRESS_MASK        0x000f
#define SRAM_ADRESS_MASK        0x001f
#define SRAM_CHIP_SELECTION     2
#define LCD_CHIP_SELECTION      0

/*
**MAPS_LCD�������
*/

#define LCDC_ADRESS_CMD         0x60000000      //LCD�����ַ
#define LCDC_ADRESS_DATA        0x60000002      //LCD���ݵ�ַ

#define LCDC_SCREEN_PIXEL_X     320             //LCD��ĻX����������
#define LCDC_SCREEN_PIXEL_Y     240             //LCD��ĻY����������

//������ɫ
#define BLACKCOLOR              0x0000          //��ɫ
#define WHITECOLOR              0xffff          //��ɫ
#define REDCOLOR                0xf800          //��ɫ
#define YELLOWCOLOR             0xffe0          //��ɫ
#define BLUECOLOR               0x001f          //��ɫ
#define GREENCOLOR              0x07e0          //��ɫ
#define CELESTECOLOR            0x07ff          //����ɫ
#define PURPLECOLOR             0xf81f          //��ɫ

//��ȡRGB��ԭɫ,RGB565��16Bit����
#define RGB565_RED(rgb565)      (uint8)(((uint16)(rgb565)>>11)&0x1f)
#define RGB565_GREEN(rgb565)    (uint8)(((uint16)(rgb565)>>5)&0x3f)
#define RGB565_BLUE(rgb565)     (uint8)((uint16)(rgb565)&0x1f)

//�Ҷ�ͼ��RGB565ͼ��ת��
#define GRAY_TO_RGB565(gray)    ((uint16)((((uint8)(gray)>>3)<<11)|(((uint8)(gray)>>2)<<5)|((uint8)(gray)>>3)))
#define RGB565_TO_GRAY(rgb565)  ((uint8)(((RGB565_RED(rgb565)*235+RGB565_GREEN(rgb565)*613+RGB565_BLUE(rgb565)*625)+1)>>8))

#define RGB565_H(rgb565)                ((uint8)(((uint16)(rgb565))>>8))
#define RGB565_L(rgb565)                (uint8)(rgb565))

#define RGB24_RGB565(R,G,B)             ((uint16)((((uint8)(R)>>3)<<11)|(((uint8)(G)>>2)<<5)|((uint8)(B)>>3)))
#define RGB555_RGB565(rgb555)           (((((uint16)(rgb555)) & (uint16)(~0x1F)) << 1) |  (((uint16)(rgb555)) & 0x1F))
#define BGR555_RGB565(bgr555)           ((((uint16)(bgr555)<<11) & (uint16)(0x1F<<11)) | (((uint16)(bgr555)) & (uint16)(0x1F<<5)) | (((uint16)(bgr555)>>10) & (uint16)(0x1F)))

//LCDC��ʱ��
#define LCDC_DELAY(us)          DELAY_US(us)

/*
**BMPͼ����Ϣ
*/
#define MAX_BMP_H               240         //BMP ֧����߸߶�
#define MAX_BMP_W               320         //BMP ֧����߿��
#define MAX_BMP_BIT             24          //BMP ֧�����λ��

//ͼ��ѹ��ö��
typedef enum
{
  BI_RGB,               //��ѹ��
  BI_RLE8,              //ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��
  BI_RLE4,              //ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
  BI_BITFIELDS,         //ÿ�����صı�����ָ�������������
}biCompression_e;

//ͼ����Ϣ�ṹ
#pragma pack(2)

typedef struct          //����˫�ֽڶ���(���ߵ��ֽڶ���)
{
  //BMPλͼ�ļ�ͷ
  uint16 bfType;         //ƫ��:0x00,�ļ���־.'BM',����ʶ��BMPλͼ����
  uint32 bfSize;         //ƫ��:0x02,�ļ���С
  uint16 bfReserved1;    //ƫ��:0x06,����
  uint16 bfReserved2;    //ƫ��:0x08,����
  uint32 bfOffBits;      //ƫ��:0x0A,���ļ���ʼ��λͼ����(bitmap data)��ʼ֮��ĵ�ƫ����

  //BMPλͼ��Ϣͷ
  uint32 biSize;         //ƫ��:0x0E,λͼ��Ϣͷ�ֽ�������
  int32  biWidth;        //ƫ��:0x12,ͼ����
  int32  biHeight;       //ƫ��:0x16,ͼ��߶ȣ������һ��������˵��ͼ�������Ǵ�ͼ�����½ǿ�ʼɨ�裬����������Ͻ�
  uint16 biPlanes;       //ƫ��:0x1A,ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1
  uint16 biBitCount;     //ƫ��:0x1C,˵��������/���أ���ֵΪ1��4��8��16��24����32
  uint32 biCompression;  //ƫ��:0x1E,˵��ͼ������ѹ�������͡���ֵ����Ϊ biCompression_e
  uint32 biSizeImage;    //ƫ��:0x22,˵��ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0
  uint32 biXPelsPerMeter;//ƫ��:0x26,˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ,�з�������
  uint32 biYPelsPerMeter;//ƫ��:0x2A,˵����ֱ�ֱ��ʣ�������/�ױ�ʾ,�з�������
  uint32 biClrUsed;      //ƫ��:0x2E,˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
  uint32 biClrImportant; //ƫ��:0x32,˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��
}BMP_FILEHEADER;

//��ɫ����ɫ�ṹ��
typedef struct tagRGBQUAD
{
  uint8 rgbBlue;
  uint8 rgbGreen;
  uint8 rgbRed;
  uint8 rgbReserved;
}RGBQUAD;

//ͼ����غ�
#define BMP_SIZE(W,H)           ((((W)*4+3)/4)*(H))
#define BMP_BYTECNT(W,H,BIT)    (BMP_SIZE(W,H)*BIT/8)

#define MAX_BMP_SIZE            BMP_SIZE(MAX_BMP_W,MAX_BMP_H)
#define MAX_BMP_BYTECNT         BMP_BYTECNT(MAX_BMP_W,MAX_BMP_H,MAX_BMP_BIT)

#define BMP_LINE_BYTE(W,BIT)    ((((W)*(BIT)+31)/32)*4)
#define MAX_BMP_LINE_BYTE       BMP_LINE_BYTE(MAX_BMP_W,MAX_BMP_BIT)

/*
**variate declaration
*/
extern const uint8 Font_6x8_h[];
extern const uint8 Font_8x16_h[256*16];
extern const uint8 LCDC_Freescale_Logo[153600];

/*
**function declaration
*/
extern void MAPS_LCD_Init(void);
extern void MAPS_LCDC_CLS(void);
extern void MAPS_LCDC_Fill_Color(uint16 color);
extern void MAPS_LCDC_Set_Window(uint16 x,uint16 y,uint16 w,uint16 h);
extern void MAPS_LCDC_DrawPixel(uint16 x,uint16 y,uint16 color);
extern void MAPS_LCDC_DrawChar_6x8(uint16 x,uint16 y,uint8 bc,uint8 c);
extern void MAPS_LCDC_DrawChar_8x16(uint16 x,uint16 y,uint8 bc,uint8 c);
extern void MAPS_LCDC_DisplayChar(uint16 x,uint16 y,uint8 font,uint8 bc,char c);
extern void MAPS_LCDC_DisplayString(uint16 x,uint16 y,uint8 font,uint8 bc,char *String);
extern void MAPS_LCDC_Show(uint16 *Color);
extern void MAPS_LCDC_BMP(uint16 x,uint16 y,uint16 w,uint16 h,uint16 *BMP_PTemp);
extern uint8 MAPS_LCDC_BMP_From_SD(char *file,Site_t Site);

#endif