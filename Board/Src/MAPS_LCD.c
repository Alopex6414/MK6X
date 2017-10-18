/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_LCD.c
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��(TFT:ILI9341)
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"
#include "MAPS_LCD_Font.h"
#include "MAPS_LCD_Pic.h"

static uint16 ForeColor = BLACKCOLOR;
static uint16 BackColor = BLACKCOLOR;

//BMPһ��ͼ��
uint8 BMP_Buffer[MAX_BMP_LINE_BYTE];

/*
 *  @brief      LCD��������
 *  @since      v1.0
 *  Sample usage:       LCDC_Send_CMD(0xCF);//LCD��������
 */
static inline void LCDC_Send_CMD(uint16 cmd)
{
  *(volatile uint16 *)LCDC_ADRESS_CMD = cmd;
}

/*
 *  @brief      LCD��������
 *  @since      v1.0
 *  Sample usage:       LCDC_Send_DATA(0xCF);//LCD��������
 */
static inline void LCDC_Send_DATA(uint16 data)
{
  *(volatile uint16 *)LCDC_ADRESS_DATA = data;
}

/*
 *  @brief      LCD�����ɫ
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_Fill_Color(0xCF);//LCD�����ɫ
 */
void MAPS_LCDC_Fill_Color(uint16 color)
{
  uint32 i=0;
  
  LCDC_Send_CMD(0x2A);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);
  
  LCDC_Send_CMD(0x2B);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);
  
  LCDC_Send_CMD(0x2C);
  
  for(i=0;i<(LCDC_SCREEN_PIXEL_X*LCDC_SCREEN_PIXEL_Y);i++)
  {
    LCDC_Send_DATA(color);
  }
  
}

/*
 *  @brief      LCD����
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_CLS();//LCD����
 */
void MAPS_LCDC_CLS(void)
{
  uint32 i=0;
  
  LCDC_Send_CMD(0x2A);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);
  
  LCDC_Send_CMD(0x2B);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);
  
  LCDC_Send_CMD(0x2C);
  
  for(i=0;i<(LCDC_SCREEN_PIXEL_X*LCDC_SCREEN_PIXEL_Y);i++)
  {
    LCDC_Send_DATA(0x00);
  }
}

/*
 *  @brief      MAPS_LCD_FlexBus��ʼ��
 *  @since      v1.0
 *  Sample usage:       MAPS_LCD_FlexBus_Init();//��ʼ��MAPS_LCD
 */
static void MAPS_LCD_FlexBus_Init(void)
{
  //FlexBusʱ�ӳ�ʼ��
  SIM_SOPT2 |= SIM_SOPT2_FBSL(3);             //FlexBus��ȫˮƽ:����ָ������ݷ���
  SIM_SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;        //ʹ��ʱ��
  
  //MAPS_LCD�˿����ü�FlexBus��ʼ��
  //FlexBus
  PORT_Init(FB_AD0 ,ALT5 | SSR);//PTD6
  PORT_Init(FB_AD1 ,ALT5 | SSR);//PTD5
  PORT_Init(FB_AD2 ,ALT5 | SSR);//PTD4
  PORT_Init(FB_AD3 ,ALT5 | SSR);//PTD3
  PORT_Init(FB_AD4 ,ALT5 | SSR);//PTD2
  PORT_Init(FB_AD5 ,ALT5 | SSR);//PTC10
  PORT_Init(FB_AD6 ,ALT5 | SSR);//PTC9
  PORT_Init(FB_AD7 ,ALT5 | SSR);//PTC8
  PORT_Init(FB_AD8 ,ALT5 | SSR);//PTC7
  PORT_Init(FB_AD9 ,ALT5 | SSR);//PTC6
  PORT_Init(FB_AD10 ,ALT5 | SSR);//PTC5
  PORT_Init(FB_AD11 ,ALT5 | SSR);//PTC4
  PORT_Init(FB_AD12 ,ALT5 | SSR);//PTC2
  PORT_Init(FB_AD13 ,ALT5 | SSR);//PTC1
  PORT_Init(FB_AD14 ,ALT5 | SSR);//PTC0
  PORT_Init(FB_AD15 ,ALT5 | SSR);//PTB18
  PORT_Init(FB_AD16 ,ALT5 | SSR);//PTB17
  PORT_Init(FB_AD17 ,ALT5 | SSR);//PTB16
  PORT_Init(FB_AD18 ,ALT5 | SSR);//PTB11
  PORT_Init(FB_AD19 ,ALT5 | SSR);//PTB10
  PORT_Init(FB_AD20 ,ALT5 | SSR);//PTB9
  //LCD PORT
  PORT_Init(MAPS_LCD_RD ,ALT5 | SSR);//PTB19
  PORT_Init(MAPS_LCD_RW ,ALT5 | SSR);//PTC11
  PORT_Init(MAPS_LCD_CLK ,ALT5 | SSR);//PTC3
  PORT_Init(MAPS_LCD_ALE ,ALT5 | SSR);//PTD0
  PORT_Init(MAPS_LCD_CS0 ,ALT5 | SSR);//PTD1
  PORT_Init(MAPS_LCD_CS2 ,ALT5 | SSR);//PTC18
  PORT_Init(MAPS_LCD_BE31_24 ,ALT5 | SSR);//PTC17
  PORT_Init(MAPS_LCD_BE23_16 ,ALT5 | SSR);//PTC16
  
  //FlexBus����
  FB_CSMR0 = (0
              | FB_CSMR_BAM(FLEX_ADRESS_MASK)   //д��FlexBus��ַ����
              | FB_CSMR_V_MASK                  //Ƭѡ�źſ���
              );
  
  FB_CSAR0 = (0 | FB_CSAR_BA(FLEX_BASE_ADDRESS));//д��FlexBus��ַ
  
  FB_CSCR0 = (0
              | FB_CSCR_BLS_MASK                //Bate-Lane Shift(�Ҷ���ģʽ)
              | FB_CSCR_AA_MASK                 //�Զ�Ӧ��ACK
              | FB_CSCR_PS(2)                   //16Bit���ݴ���
              | FB_CSCR_ASET(3)                 //��4�����������õ�ַ
              | FB_CSCR_WS(3)                   //�ȴ�λWS=3,�ȴ�3����
              | FB_CSCR_RDAH(3)                 //�����ߵȴ�4����
              );
  
  //SRAM����
  FB_CSMR2 = (0
              | FB_CSMR_BAM(SRAM_ADRESS_MASK)   //д��SRAM��ַ����
              | FB_CSMR_V_MASK                  //Ƭѡ�źſ���
              );
  
  FB_CSAR2 = (0 | FB_CSAR_BA(SRAM_BASE_ADDRESS));//д��SRAM��ַ
  
  FB_CSCR2 = (0
              | FB_CSCR_BLS_MASK                //Bate-Lane Shift(�Ҷ���ģʽ)
              | FB_CSCR_AA_MASK                 //�Զ�Ӧ��ACK
              | FB_CSCR_PS(2)                   //16Bit���ݴ���
              | FB_CSCR_ASET(1)                 //��2�����������õ�ַ
              | FB_CSCR_WS(2)                   //�ȴ�λWS=2,�ȴ�2����
              | FB_CSCR_RDAH(1)                 //�����ߵȴ�2����
              | FB_CSCR_WRAH(1)                 //д���ߵȴ�2����
              | FB_CSCR_BEM_MASK                //λʹ��ģʽ
              );
  
  FB_CSPMCR = (0
               | FB_CSPMCR_GROUP2(2)            //ѡ��FB_BE_31_24
               | FB_CSPMCR_GROUP3(2)            //ѡ��FB_BE_23_16
               | FB_CSPMCR_GROUP4(1)            //ѡ��FB_CS2
               );
  
}

/*
 *  @brief      MAPS_LCD��ʼ��
 *  @since      v1.0
 *  Sample usage:       MAPS_LCD_Init();//��ʼ��MAPS_LCD
 */
void MAPS_LCD_Init(void)
{
  MAPS_LCD_FlexBus_Init();//FlexBus��ʼ��
  
  LCDC_Send_CMD(0xCF);  //Power control B
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0xC1);
  LCDC_Send_DATA(0x30);
  
  LCDC_Send_CMD(0xED);  //Power on sequence control
  LCDC_Send_DATA(0x64);
  LCDC_Send_DATA(0x03);
  LCDC_Send_DATA(0x12);
  LCDC_Send_DATA(0x81);
  
  LCDC_Send_CMD(0xE8);  //Driver timing control A
  LCDC_Send_DATA(0x85); 
  LCDC_Send_DATA(0x10); 
  LCDC_Send_DATA(0x7A);
  
  LCDC_Send_CMD(0xCB);  //Power control A
  LCDC_Send_DATA(0x39); 
  LCDC_Send_DATA(0x2C); 
  LCDC_Send_DATA(0x00); 
  LCDC_Send_DATA(0x34); 
  LCDC_Send_DATA(0x02);
  
  LCDC_Send_CMD(0xF7);  //Pump ratio control
  LCDC_Send_DATA(0x20);
  
  LCDC_Send_CMD(0xEA);  //Driver timing control B
  LCDC_Send_DATA(0x00); 
  LCDC_Send_DATA(0x00);
  
  LCDC_Send_CMD(0xC0);  //Power control 
  LCDC_Send_DATA(0x1B); //VRH[5:0]  1B
    
  LCDC_Send_CMD(0xC1);  //Power control 
  LCDC_Send_DATA(0x01); //SAP[2:0];BT[3:0] 
    
  LCDC_Send_CMD(0xC5);  //VCM control 
  LCDC_Send_DATA(0x45); //3F
  LCDC_Send_DATA(0x25); //3C
    
  LCDC_Send_CMD(0xC7);  //VCM control2 
  LCDC_Send_DATA(0xB7); //b7
  
  LCDC_Send_CMD(0x36);  //Memory Access Control 
  LCDC_Send_DATA(0x28); 
    
  LCDC_Send_CMD(0x3A);  //Pixel Format Set
  LCDC_Send_DATA(0x55); 
    
  LCDC_Send_CMD(0xB1);  //Frame Rate Control
  LCDC_Send_DATA(0x00);   
  LCDC_Send_DATA(0x1A); 
    
  LCDC_Send_CMD(0xB6);  //Display Function Control 
  LCDC_Send_DATA(0x0A); 
  LCDC_Send_DATA(0x82); 
    
  LCDC_Send_CMD(0xF2);  //3Gamma Function Disable 
  LCDC_Send_DATA(0x00); 
    
  LCDC_Send_CMD(0x26);  //Gamma curve selected 
  LCDC_Send_DATA(0x01);
  
  LCDC_Send_CMD(0xE0);  //Set Gamma 
  LCDC_Send_DATA(0x0F); 
  LCDC_Send_DATA(0x2A); 
  LCDC_Send_DATA(0x28); 
  LCDC_Send_DATA(0x08); 
  LCDC_Send_DATA(0x0E); 
  LCDC_Send_DATA(0x08); 
  LCDC_Send_DATA(0x54); 
  LCDC_Send_DATA(0xA9); 
  LCDC_Send_DATA(0x43); 
  LCDC_Send_DATA(0x0A); 
  LCDC_Send_DATA(0x0F); 
  LCDC_Send_DATA(0x00); 
  LCDC_Send_DATA(0x00); 
  LCDC_Send_DATA(0x00); 
  LCDC_Send_DATA(0x00); 
    
  LCDC_Send_CMD(0xE1);  //Set Gamma 
  LCDC_Send_DATA(0x00); 
  LCDC_Send_DATA(0x15); 
  LCDC_Send_DATA(0x17); 
  LCDC_Send_DATA(0x07); 
  LCDC_Send_DATA(0x11); 
  LCDC_Send_DATA(0x06); 
  LCDC_Send_DATA(0x2B); 
  LCDC_Send_DATA(0x56); 
  LCDC_Send_DATA(0x3C); 
  LCDC_Send_DATA(0x05); 
  LCDC_Send_DATA(0x10); 
  LCDC_Send_DATA(0x0F); 
  LCDC_Send_DATA(0x3F); 
  LCDC_Send_DATA(0x3F); 
  LCDC_Send_DATA(0x0F); 
    
  LCDC_Send_CMD(0x2A);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x01);
  LCDC_Send_DATA(0x3F);	
    
  LCDC_Send_CMD(0x2B);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0xEF);
  
  LCDC_Send_CMD(0x11);   //Exit Sleep
  LCDC_DELAY(10);
  LCDC_Send_CMD(0x29);   //display on
  LCDC_DELAY(10);
  LCDC_Send_CMD(0x2C);
  MAPS_LCDC_Fill_Color(BLACKCOLOR);//��ʼ������
  LCDC_DELAY(100);
  MAPS_LCDC_Fill_Color(BackColor);//����ɫ����Ϊ��ɫ
  
}

/*
 *  @brief      MAPS_LCDC�����Ӵ�����
 *  @param      uint16    x
 *  @param      uint16    y
 *  @param      uint16    w
 *  @param      uint16    h
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_Set_Window();//MAPS_LCD���ô���
 */
void MAPS_LCDC_Set_Window(uint16 x,uint16 y,uint16 w,uint16 h)
{
  LCDC_Send_CMD(0x2A);
  LCDC_Send_DATA(x>>8);
  LCDC_Send_DATA(x&0xFF);
  LCDC_Send_DATA((x+w-1)>>8);
  LCDC_Send_DATA((x+w-1)&0xFF);	
    
  LCDC_Send_CMD(0x2B);
  LCDC_Send_DATA(y>>8);
  LCDC_Send_DATA(y&0xFF);
  LCDC_Send_DATA((y+h-1)>>8);
  LCDC_Send_DATA((y+h-1)&0xFF);
}

/*
 *  @brief      MAPS_LCDCдһ������
 *  @param      uint16    x
 *  @param      uint16    y
 *  @param      uint16    color
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_DrawPixel();//MAPS_LCDдһ������
 */
void MAPS_LCDC_DrawPixel(uint16 x,uint16 y,uint16 color)
{
  LCDC_Send_CMD(0x2A);
  LCDC_Send_DATA(x>>8);
  LCDC_Send_DATA(x&0xFF);
  LCDC_Send_CMD(0x2B);
  LCDC_Send_DATA(y>>8);
  LCDC_Send_DATA(y&0xFF);
  LCDC_Send_CMD(0x2C);
  LCDC_Send_DATA(color);
}

/*
 *  @brief      MAPS_LCDCдһ��6x8�ַ�
 *  @param      uint16    x
 *  @param      uint16    y
 *  @param      uint8     bc
 *  @param      uint8     c
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_DrawChar_6x8();//MAPS_LCDдһ��6x8�ַ�
 */
void MAPS_LCDC_DrawChar_6x8(uint16 x,uint16 y,uint8 bc,uint8 c)
{
  int i=0,j=0,k=0;
  
  if(c>0x1f && c<0x90)
  {
    k = (c - 0x20) * 8;
    for(i=0;i<8;i++)
    {
      for(j=0;j<6;j++)
      {
        if(Font_6x8_h[k+i] & (0x01<<(7-j)))
        {
          MAPS_LCDC_DrawPixel(x+j,y+i,ForeColor);
        }
        else
        {
          if(bc)
          {
            MAPS_LCDC_DrawPixel(x+j,y+i,BackColor);
          }
        }
      }
    }
  }
}

/*
 *  @brief      MAPS_LCDCдһ��8x16�ַ�
 *  @param      uint16    x
 *  @param      uint16    y
 *  @param      uint8     bc
 *  @param      uint8     c
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_DrawChar_8x16();//MAPS_LCDдһ��8x16�ַ�
 */
void MAPS_LCDC_DrawChar_8x16(uint16 x,uint16 y,uint8 bc,uint8 c)
{
  int i=0,j=0,k=0;
  
  if(c>0x1f && c<0x90)
  {
    k = c * 16;
    for(i=0;i<16;i++)
    {
      for(j=0;j<8;j++)
      {
        if(Font_8x16_h[k+i] & (0x01<<(7-j)))
        {
          MAPS_LCDC_DrawPixel(x+j,y+i,ForeColor);
        }
        else
        {
          if(bc)
          {
            MAPS_LCDC_DrawPixel(x+j,y+i,BackColor);
          }
        }
      }
    }
  }
}

/*
 *  @brief      MAPS_LCDC��ʾ�ַ�
 *  @param      uint16    x
 *  @param      uint16    y
 *  @param      uint8     font
 *  @param      uint8     bc
 *  @param      char      c
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_DisplayChar();//MAPS_LCD��ʾ�ַ�
 */
void MAPS_LCDC_DisplayChar(uint16 x,uint16 y,uint8 font,uint8 bc,char c)
{
  if(c & 0x80)
  {
    return;
  }
  switch(font)
  {
    case 0:
            MAPS_LCDC_DrawChar_6x8(x,y,bc,c);
            break;
    case 1:
            MAPS_LCDC_DrawChar_8x16(x,y,bc,c);
            break;
    default:
            MAPS_LCDC_DrawChar_8x16(x,y,bc,c);
            break;
  }
}

/*
 *  @brief      MAPS_LCDC��ʾ�ַ���
 *  @param      uint16    x
 *  @param      uint16    y
 *  @param      uint8     font
 *  @param      uint8     bc
 *  @param      char      *String
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_DisplayString();//MAPS_LCD��ʾ�ַ���
 */
void MAPS_LCDC_DisplayString(uint16 x,uint16 y,uint8 font,uint8 bc,char *String)
{
  while(*String)
  {
    switch(font)
    {
      case 0:
              MAPS_LCDC_DisplayChar(x,y,font,bc,*String++);
              x += 6;
              break;
      case 1:
              MAPS_LCDC_DisplayChar(x,y,font,bc,*String++);
              x += 8;
              break;
      default:
              MAPS_LCDC_DisplayChar(x,y,font,bc,*String++);
              x += 8;
              break;
    }
  }
}

/*
 *  @brief      MAPS_LCDC����
 *  @param      uint16  *Color
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_Show();//MAPS_LCD����
 */
void MAPS_LCDC_Show(uint16 *Color)
{
  uint32 i=0;
  
  LCDC_Send_CMD(0x2A);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);;	
    
  LCDC_Send_CMD(0x2B);
  LCDC_Send_DATA(0x00);
  LCDC_Send_DATA(0x00);
    
  LCDC_Send_CMD(0x2C);
  for(i=0;i<(LCDC_SCREEN_PIXEL_X*LCDC_SCREEN_PIXEL_Y);i++)
  {
    LCDC_Send_DATA(*Color++);
  }
}

/*
 *  @brief      MAPS_LCDC��ʾͼ��
 *  @param      uint16    x
 *  @param      uint16    y
 *  @param      uint16    w
 *  @param      uint16    h
 *  @param      uint16   *BMP_PTemp
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_BMP();//MAPS_LCD��ʾͼ��
 */
void MAPS_LCDC_BMP(uint16 x,uint16 y,uint16 w,uint16 h,uint16 *BMP_PTemp)
{
  uint32 i=0,j=0;
  uint16 *BMP_DATA_PTR=(uint16*)BMP_PTemp;
  uint16 *BMP_SRAM_PTR=(uint16*)(SRAM_BASE_ADDRESS<<16);
  
  for(i=0,j=0;i<(w*h);i++,j++)
  {
    *BMP_SRAM_PTR++ = *((uint16*)(BMP_DATA_PTR++));
  }
  
  MAPS_LCDC_Set_Window(x,y,w,h);
  
  LCDC_Send_CMD(0x2C);
  
  BMP_SRAM_PTR=(uint16*)(SRAM_BASE_ADDRESS<<16);
    
  for(i=0;i<(w*h);i++)
  {
    LCDC_Send_DATA(*BMP_SRAM_PTR++);
  }
    
}

/*
 *  @brief      MAPS_LCDC��SD���ж�ȡһ��ͼ��
 *  @param      char*           file
 *  @param      Site_t          Site
 *  @since      v1.0
 *  Sample usage:       MAPS_LCDC_BMP_From_SD();//MAPS_LCD��SD���ж�ȡһ��ͼ��
 */
uint8 MAPS_LCDC_BMP_From_SD(char *file,Site_t Site)
{
  FIL fdst;     //�ļ�
  FATFS fs;     //�ļ�ϵͳ
  FRESULT res;  //�ļ�ϵͳ����ֵ
  BMP_FILEHEADER BMP_FileHead;//BMPͼ���ļ�
  uint32 Br;
  
  int Width,Height;
  uint32 OffBits,Bitcnt;
  
  uint8 r,g,b;
  uint16 rgb;

  Size_t size;
  Site_t site;

  int x=0,y=0,BytesPerLine,Step;

  uint8 *pColor;

  
  res = f_mount(0, &fs);//�����ļ�ϵͳ
  res = f_open(&fdst, file, FA_OPEN_EXISTING | FA_READ);//���ļ�,ֻ��
  if(res)//������ļ�ʧ��
  {
    goto BMP_EXIT_FALSE;//��ת���˳�����
  }
  
  res = f_read(&fdst, &BMP_FileHead, sizeof(BMP_FileHead), &Br);//��ȡ�ļ����ݵ�BMP_FileHead����
  if(res)//�����ȡ�ļ�ʧ��
  {
    goto BMP_EXIT_FALSE;//��ת���˳�����
  }
  
  Width = BMP_FileHead.biWidth;         //ͼ����
  Height = BMP_FileHead.biHeight;       //ͼ��߶�
  OffBits = BMP_FileHead.bfOffBits;     //���ļ���ʼ��λͼ���ݿ�ʼ֮��ĵ�ƫ����
  Bitcnt = BMP_FileHead.biBitCount;     //˵��������/����,��ֵΪ1��4��8��16��24��32
  
  if((BMP_FileHead.bfType != 0x4d42) || (BMP_FileHead.biCompression))//����BMPλͼ���ͻ�ûѹ��
  {
    goto BMP_EXIT_FALSE;//��ת���˳�����
  }
  
  if(Width > MAX_BMP_W)//��ȳ���LCD�����ʾ���
  {
    goto BMP_EXIT_FALSE;//��ת���˳�����
  }
  
  if(Height > 0)//����߶�������,�����½����϶�����
  {
    y = Height - 1 + (LCDC_SCREEN_PIXEL_Y - Height)/2;
    Step = -1;
  }
  else if(Height < 0)//����߶��Ǹ���,�����Ͻ����¶�����
  {
    Height = -Height;
    y = (LCDC_SCREEN_PIXEL_Y - Height)/2;
    Step = 1;
  }
  else
  {
    goto BMP_EXIT_FALSE;//��ת���˳�����
  }
  
  size.H= 1;
  size.W = Width;
  site.x = Site.x;
  BytesPerLine = BMP_LINE_BYTE(Width,Bitcnt);
  
  switch(Bitcnt)
  {
    case 24://24λ���ɫ:RGB24
            res = f_lseek(&fdst,OffBits);//�ҵ�BMP��ɫ������ʼλ��
            for(;(y>=((LCDC_SCREEN_PIXEL_Y-Height)/2))&&(y<(Height+(LCDC_SCREEN_PIXEL_Y-Height)/2));y+=Step)
            {
              res = f_read(&fdst, BMP_Buffer, BytesPerLine, &Br);//��ȡһ��ͼ����Ϣ
              if(res)//�����ȡ�ļ�ʧ��
              {
                goto BMP_EXIT_FALSE;//��ת���˳�����
              }
              pColor = BMP_Buffer;//BMP_Buffer��ַ
              
              site.y = Site.y + y;
              MAPS_LCDC_Set_Window(site.x,site.y,size.W,size.H);//���ô���
              LCDC_Send_CMD(0x2C);//дģʽ
              
              for(x=0;x<Width;x++)
              {
                b = *pColor++;
                g = *pColor++;
                r = *pColor++;
                
                rgb = RGB24_RGB565(r,g,b);
                LCDC_Send_DATA(rgb);
              }
              
            }
            break;
    case 16://16λλͼ
            res = f_lseek(&fdst,OffBits);//�ҵ�BMP��ɫ������ʼλ��
            for(;(y>=((LCDC_SCREEN_PIXEL_Y-Height)/2))&&(y<(Height+(LCDC_SCREEN_PIXEL_Y-Height)/2));y+=Step)
            {
              res = f_read(&fdst, BMP_Buffer, BytesPerLine, &Br);//��ȡһ��ͼ����Ϣ
              if(res)//�����ȡ�ļ�ʧ��
              {
                goto BMP_EXIT_FALSE;//��ת���˳�����
              }
              pColor = BMP_Buffer;//BMP_Buffer��ַ
              
              site.y = Site.y + y;
              MAPS_LCDC_Set_Window(site.x,site.y,size.W,size.H);//���ô���
              LCDC_Send_CMD(0x2C);//дģʽ
              
              for(x=0;x<Width;x++)
              {
                rgb = *(uint16 *)pColor;
                rgb = RGB555_RGB565(rgb);
                LCDC_Send_DATA(rgb);
                pColor += 2;
              }
              
            }
            break;
    case 1://��ɫBMP
            res = f_read(&fdst, BMP_Buffer, 2*sizeof(RGBQUAD), &Br);
            uint16 color[2];
            color[0] = RGB24_RGB565(BMP_Buffer[2],BMP_Buffer[1],BMP_Buffer[0]);
            color[1] = RGB24_RGB565(BMP_Buffer[6],BMP_Buffer[5],BMP_Buffer[4]);
            
            res = f_lseek(&fdst,OffBits);//�ҵ�BMP��ɫ������ʼλ��
            
            Width = (Width+7)/8;//8������һ����(+7�ǽ�1)
            for(;(y>=((LCDC_SCREEN_PIXEL_Y-Height)/2))&&(y<(Height+(LCDC_SCREEN_PIXEL_Y-Height)/2));y+=Step)
            {
              res = f_read(&fdst, BMP_Buffer, BytesPerLine, &Br);//��ȡһ��ͼ����Ϣ
              if(res)//�����ȡ�ļ�ʧ��
              {
                goto BMP_EXIT_FALSE;//��ת���˳�����
              }
              pColor = BMP_Buffer;//BMP_Buffer��ַ
              
              site.y = Site.y + y;
              MAPS_LCDC_Set_Window(site.x,site.y,size.W,size.H);//���ô���
              LCDC_Send_CMD(0x2C);//дģʽ
              
              for(x=0;x<Width;x++)
              {
                rgb = color[(*pColor >> 7)&0x01];
                LCDC_Send_DATA(rgb);
                rgb = color[(*pColor >> 6)&0x01];
                LCDC_Send_DATA(rgb);
                rgb = color[(*pColor >> 5)&0x01];
                LCDC_Send_DATA(rgb);
                rgb = color[(*pColor >> 4)&0x01];
                LCDC_Send_DATA(rgb);
                rgb = color[(*pColor >> 3)&0x01];
                LCDC_Send_DATA(rgb);
                rgb = color[(*pColor >> 2)&0x01];
                LCDC_Send_DATA(rgb);
                rgb = color[(*pColor >> 1)&0x01];
                LCDC_Send_DATA(rgb);
                rgb = color[(*pColor >> 0)&0x01];
                LCDC_Send_DATA(rgb);
                
                pColor += 1;
              }
              
            }
            break;
    default:
            goto BMP_EXIT_FALSE;//��ת���˳�����
            break;
  }
  res = f_close(&fdst);
  res = f_mount(0,NULL);
  return TRUE;
  
 BMP_EXIT_FALSE://�˳�����
  res = f_close(&fdst);
  res = f_mount(0,NULL);
  return FALSE;
}