/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_W25Q80.c
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      W25Q80 SPI����
 *  @since      v1.0
 *  Sample usage:       W25Q80_Transfer()
 */
static inline void W25Q80_Transfer(uint8 *SPI_MO_Data,uint8 *SPI_MI_Data,uint32 SPI_Len)
{
  SPI_MOSI(SPI_SPI2,SPI_PCS0,&SPI_MO_Data[0],&SPI_MI_Data[0],SPI_Len);
}

/*
 *  @brief      W25Q80 SPI��������
 *  @since      v1.0
 *  Sample usage:       W25Q80_TransferCMD()
 */
static inline void W25Q80_TransferCMD(uint8 *SPI_MO_CMD,uint8 *SPI_MI_CMD,uint8 *SPI_MO_Data,uint8 *SPI_MI_Data,uint32 SPI_CMD_Len,uint32 SPI_Len)
{
  SPI_MOSI_CMD(SPI_SPI2,SPI_PCS0,&SPI_MO_CMD[0],&SPI_MI_CMD[0],&SPI_MO_Data[0],&SPI_MI_Data[0],SPI_CMD_Len,SPI_Len);
}

/*
 *  @brief      W25Q80 SPIдʹ��
 *  @since      v1.0
 *  Sample usage:       W25Q80_Write_Enable()
 */
static inline void W25Q80_Write_Enable(void)
{
  uint8 CMD=W25Q80_CMD_WRITE_ENABLE;
  
  W25Q80_Transfer(&CMD,NULL,1);
}

/*
 *  @brief      W25Q80���оƬBusy
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Check();//W25Q80���оƬBusy
 */
static inline void MAPS_Dock_W25Q80_Check(uint32 TimeOut,uint8 CMD)
{
  uint32 i=0;
  uint8 Status=0;
  
  W25Q80_Transfer(&CMD,NULL,1);
  
  for(i=0;i<TimeOut;i++)
  {
    W25Q80_Transfer(NULL,&Status,1);
    if((Status & STATUS_BUSY) == 0)
    {
      break;
    }
  }
}

/*
 *  @brief      W25Q80��ʼ��SPIƬѡ�ź�(��LCM����SPI2)
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Init();//W25Q80��ʼ��
 */
void MAPS_Dock_W25Q80_Init(void)
{
  SPI_Extra_PCS_Init(SPI_SPI2,SPI_PCS0);
  //SPI_Init(SPI_SPI2,SPI_PCS0,MASTER,10000000);
}

/*
 *  @brief      W25Q80��ȡоƬID
 *  @para       uint8   Vender_ID       ����ID��
 *  @para       uint8   Drive_ID[]      �豸ID��(2)
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Read_ID();//W25Q80��ȡоƬID
 */
void MAPS_Dock_W25Q80_Read_ID(uint8 *Vender_ID,uint8 *Drive_ID)
{
  uint8 Send[4]={W25Q80_CMD_DEVICE_ID,0,0,0};
  uint8 Receive[4]={0};
  
  W25Q80_TransferCMD(&Send[0],&Receive[0],NULL,NULL,4,1);
  
  *Vender_ID = Receive[1];
  *Drive_ID = Receive[2];
  *(Drive_ID+1) = Receive[3];
}

/*
 *  @brief      W25Q80оƬ����
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Erase_Chip();//W25Q80оƬ����
 */
void MAPS_Dock_W25Q80_Erase_Chip(void)
{
  uint8 CMD=W25Q80_CMD_CHIP_ERASE;
  
  W25Q80_Write_Enable();
  W25Q80_Transfer(&CMD,NULL,1);
  MAPS_Dock_W25Q80_Check(SPI_FLASH_TIMEOUT,W25Q80_CMD_READ_STATUS_REG);
  MAPS_Dock_W25Q80_Delay(SPI_FLASH_TIMEOUT);
}

/*
 *  @brief      W25Q80оƬ��������
 *  @para       uint32  Address        ƫ�Ƶ�ַ
 *  @para       uint8   Block_Size     ���������Ĵ�С
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Erase_Block();//W25Q80оƬ��������
 */
void MAPS_Dock_W25Q80_Erase_Block(uint32 Address,uint8 Block_Size)
{
  uint8 CMD[4]={0};
  
  ASSERT((Address % Block_Size) == 0);
  
  switch(Block_Size)
  {
    case ERASE_SECTOR_SIZE:
                            CMD[0] = W25Q80_CMD_SECTOR_ERASE;//��������4KB
                            break;
    case ERASE_CLUSTER_SIZE:
                            CMD[0] = W25Q80_CMD_CLUSTER_ERASE;//�ز���32KB
                            break;
    case ERASE_BLOCK_SIZE:
                            CMD[0] = W25Q80_CMD_BLOCK_ERASE;//�����64KB
                            break;
    default:
                            ASSERT(0);
                            break;
  }
  
  CMD[1] = (Address >> 16) & 0xff;
  CMD[2] = (Address >> 8) & 0xff;
  CMD[3] = (Address >> 0) & 0xff;
  
  W25Q80_Write_Enable();
  W25Q80_Transfer(&CMD[0],NULL,4);
  MAPS_Dock_W25Q80_Check(SPI_FLASH_TIMEOUT,W25Q80_CMD_READ_STATUS_REG);
  MAPS_Dock_W25Q80_Delay(SPI_FLASH_TIMEOUT);
}

/*
 *  @brief      W25Q80д��һҳ����
 *  @para       uint16  Page_Number     д���ҳ����ַ(0x0000~0x0FFF)
 *  @para       uint8   Byte_Offset     д��ĵ�ַƫ��(0x00~0xFF)
 *  @para       uint8   *Page_Buff      д�������
 *  @para       uint8   Page_Buff_Len   д�������ĳ���
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Write_Page();//W25Q80д��һҳ����
 */
void MAPS_Dock_W25Q80_Write_Page(uint16 Page_Number,uint8 Byte_Offset,uint8 *Page_Buff,uint8 Page_Buff_Len)
{
  uint8 Send[4]={W25Q80_CMD_PAGE_PROGRAM,(Page_Number>>8),(Page_Number&0xff),Byte_Offset};
  
  W25Q80_Write_Enable();
  W25Q80_TransferCMD(&Send[0],NULL,&Page_Buff[0],NULL,4,Page_Buff_Len);
  MAPS_Dock_W25Q80_Delay(SPI_FLASH_TIMEOUT);
}

/*
 *  @brief      W25Q80����һҳ����
 *  @para       uint16  Page_Number     д���ҳ����ַ(0x0000~0x0FFF)
 *  @para       uint8   Byte_Offset     д��ĵ�ַƫ��(0x00~0xFF)
 *  @para       uint8   *Page_Buff      д�������
 *  @para       uint8   Page_Buff_Len   д�������ĳ���
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Read_Page();//W25Q80����һҳ����
 */
void MAPS_Dock_W25Q80_Read_Page(uint16 Page_Number,uint8 Byte_Offset,uint8 *Page_Buff,uint8 Page_Buff_Len)
{
  uint8 Send[4]={W25Q80_CMD_READ_ARRAY_SLOW,(Page_Number>>8),(Page_Number&0xff),Byte_Offset};
  
  W25Q80_TransferCMD(&Send[0],NULL,NULL,&Page_Buff[0],4,Page_Buff_Len);
}
