/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_LCD.h
 * @brief      MAPS四色板MAPS_Dock外部扩展板(TFT:ILI9341)
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_LCD_H__
#define __MAPS_LCD_H__

#include "Common.h"

/*
**MAPS_LCD相关端口宏
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
**FLEXBUS相关宏
*/
#define FLEX_BASE_ADDRESS       0x6000
#define SRAM_BASE_ADDRESS       0x8000
#define FLEX_ADRESS_MASK        0x000f
#define SRAM_ADRESS_MASK        0x001f
#define SRAM_CHIP_SELECTION     2
#define LCD_CHIP_SELECTION      0

/*
**MAPS_LCD相关设置
*/

#define LCDC_ADRESS_CMD         0x60000000      //LCD命令地址
#define LCDC_ADRESS_DATA        0x60000002      //LCD数据地址

#define LCDC_SCREEN_PIXEL_X     320             //LCD屏幕X轴像素坐标
#define LCDC_SCREEN_PIXEL_Y     240             //LCD屏幕Y轴像素坐标

//常用颜色
#define BLACKCOLOR              0x0000          //黑色
#define WHITECOLOR              0xffff          //白色
#define REDCOLOR                0xf800          //红色
#define YELLOWCOLOR             0xffe0          //黄色
#define BLUECOLOR               0x001f          //蓝色
#define GREENCOLOR              0x07e0          //绿色
#define CELESTECOLOR            0x07ff          //天蓝色
#define PURPLECOLOR             0xf81f          //紫色

//提取RGB三原色,RGB565是16Bit数据
#define RGB565_RED(rgb565)      (uint8)(((uint16)(rgb565)>>11)&0x1f)
#define RGB565_GREEN(rgb565)    (uint8)(((uint16)(rgb565)>>5)&0x3f)
#define RGB565_BLUE(rgb565)     (uint8)((uint16)(rgb565)&0x1f)

//灰度图和RGB565图像转换
#define GRAY_TO_RGB565(gray)    ((uint16)((((uint8)(gray)>>3)<<11)|(((uint8)(gray)>>2)<<5)|((uint8)(gray)>>3)))
#define RGB565_TO_GRAY(rgb565)  ((uint8)(((RGB565_RED(rgb565)*235+RGB565_GREEN(rgb565)*613+RGB565_BLUE(rgb565)*625)+1)>>8))

#define RGB565_H(rgb565)                ((uint8)(((uint16)(rgb565))>>8))
#define RGB565_L(rgb565)                (uint8)(rgb565))

#define RGB24_RGB565(R,G,B)             ((uint16)((((uint8)(R)>>3)<<11)|(((uint8)(G)>>2)<<5)|((uint8)(B)>>3)))
#define RGB555_RGB565(rgb555)           (((((uint16)(rgb555)) & (uint16)(~0x1F)) << 1) |  (((uint16)(rgb555)) & 0x1F))
#define BGR555_RGB565(bgr555)           ((((uint16)(bgr555)<<11) & (uint16)(0x1F<<11)) | (((uint16)(bgr555)) & (uint16)(0x1F<<5)) | (((uint16)(bgr555)>>10) & (uint16)(0x1F)))

//LCDC延时宏
#define LCDC_DELAY(us)          DELAY_US(us)

/*
**BMP图像信息
*/
#define MAX_BMP_H               240         //BMP 支持最高高度
#define MAX_BMP_W               320         //BMP 支持最高宽度
#define MAX_BMP_BIT             24          //BMP 支持最高位数

//图像压缩枚举
typedef enum
{
  BI_RGB,               //无压缩
  BI_RLE8,              //每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)；
  BI_RLE4,              //每个象素4比特的RLE压缩编码，压缩格式由2字节组成
  BI_BITFIELDS,         //每个象素的比特由指定的掩码决定。
}biCompression_e;

//图像信息结构
#pragma pack(2)

typedef struct          //必须双字节对齐(或者单字节对齐)
{
  //BMP位图文件头
  uint16 bfType;         //偏移:0x00,文件标志.'BM',用来识别BMP位图类型
  uint32 bfSize;         //偏移:0x02,文件大小
  uint16 bfReserved1;    //偏移:0x06,保留
  uint16 bfReserved2;    //偏移:0x08,保留
  uint32 bfOffBits;      //偏移:0x0A,从文件开始到位图数据(bitmap data)开始之间的的偏移量

  //BMP位图信息头
  uint32 biSize;         //偏移:0x0E,位图信息头字节数量。
  int32  biWidth;        //偏移:0x12,图象宽度
  int32  biHeight;       //偏移:0x16,图象高度，如果是一个正数，说明图像数据是从图像左下角开始扫描，负数则从左上角
  uint16 biPlanes;       //偏移:0x1A,为目标设备说明位面数，其值将总是被设为1
  uint16 biBitCount;     //偏移:0x1C,说明比特数/象素，其值为1、4、8、16、24、或32
  uint32 biCompression;  //偏移:0x1E,说明图象数据压缩的类型。其值类型为 biCompression_e
  uint32 biSizeImage;    //偏移:0x22,说明图象的大小，以字节为单位。当用BI_RGB格式时，可设置为0
  uint32 biXPelsPerMeter;//偏移:0x26,说明水平分辨率，用象素/米表示,有符号整数
  uint32 biYPelsPerMeter;//偏移:0x2A,说明垂直分辨率，用象素/米表示,有符号整数
  uint32 biClrUsed;      //偏移:0x2E,说明位图实际使用的彩色表中的颜色索引数
  uint32 biClrImportant; //偏移:0x32,说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。
}BMP_FILEHEADER;

//调色板颜色结构体
typedef struct tagRGBQUAD
{
  uint8 rgbBlue;
  uint8 rgbGreen;
  uint8 rgbRed;
  uint8 rgbReserved;
}RGBQUAD;

//图像相关宏
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