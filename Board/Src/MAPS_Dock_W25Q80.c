/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_W25Q80.c
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      W25Q80 SPI传输
 *  @since      v1.0
 *  Sample usage:       W25Q80_Transfer()
 */
static inline void W25Q80_Transfer(uint8 *SPI_MO_Data,uint8 *SPI_MI_Data,uint32 SPI_Len)
{
  SPI_MOSI(SPI_SPI2,SPI_PCS0,&SPI_MO_Data[0],&SPI_MI_Data[0],SPI_Len);
}

/*
 *  @brief      W25Q80 SPI传输命令
 *  @since      v1.0
 *  Sample usage:       W25Q80_TransferCMD()
 */
static inline void W25Q80_TransferCMD(uint8 *SPI_MO_CMD,uint8 *SPI_MI_CMD,uint8 *SPI_MO_Data,uint8 *SPI_MI_Data,uint32 SPI_CMD_Len,uint32 SPI_Len)
{
  SPI_MOSI_CMD(SPI_SPI2,SPI_PCS0,&SPI_MO_CMD[0],&SPI_MI_CMD[0],&SPI_MO_Data[0],&SPI_MI_Data[0],SPI_CMD_Len,SPI_Len);
}

/*
 *  @brief      W25Q80 SPI写使能
 *  @since      v1.0
 *  Sample usage:       W25Q80_Write_Enable()
 */
static inline void W25Q80_Write_Enable(void)
{
  uint8 CMD=W25Q80_CMD_WRITE_ENABLE;
  
  W25Q80_Transfer(&CMD,NULL,1);
}

/*
 *  @brief      W25Q80检查芯片Busy
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Check();//W25Q80检查芯片Busy
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
 *  @brief      W25Q80初始化SPI片选信号(与LCM公用SPI2)
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Init();//W25Q80初始化
 */
void MAPS_Dock_W25Q80_Init(void)
{
  SPI_Extra_PCS_Init(SPI_SPI2,SPI_PCS0);
  //SPI_Init(SPI_SPI2,SPI_PCS0,MASTER,10000000);
}

/*
 *  @brief      W25Q80读取芯片ID
 *  @para       uint8   Vender_ID       制造ID号
 *  @para       uint8   Drive_ID[]      设备ID号(2)
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Read_ID();//W25Q80读取芯片ID
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
 *  @brief      W25Q80芯片擦除
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Erase_Chip();//W25Q80芯片擦除
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
 *  @brief      W25Q80芯片扇区擦除
 *  @para       uint32  Address        偏移地址
 *  @para       uint8   Block_Size     擦除扇区的大小
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Erase_Block();//W25Q80芯片扇区擦除
 */
void MAPS_Dock_W25Q80_Erase_Block(uint32 Address,uint8 Block_Size)
{
  uint8 CMD[4]={0};
  
  ASSERT((Address % Block_Size) == 0);
  
  switch(Block_Size)
  {
    case ERASE_SECTOR_SIZE:
                            CMD[0] = W25Q80_CMD_SECTOR_ERASE;//扇区擦除4KB
                            break;
    case ERASE_CLUSTER_SIZE:
                            CMD[0] = W25Q80_CMD_CLUSTER_ERASE;//簇擦除32KB
                            break;
    case ERASE_BLOCK_SIZE:
                            CMD[0] = W25Q80_CMD_BLOCK_ERASE;//块擦除64KB
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
 *  @brief      W25Q80写入一页数据
 *  @para       uint16  Page_Number     写入的页数地址(0x0000~0x0FFF)
 *  @para       uint8   Byte_Offset     写入的地址偏移(0x00~0xFF)
 *  @para       uint8   *Page_Buff      写入的数组
 *  @para       uint8   Page_Buff_Len   写入的数组的长度
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Write_Page();//W25Q80写入一页数据
 */
void MAPS_Dock_W25Q80_Write_Page(uint16 Page_Number,uint8 Byte_Offset,uint8 *Page_Buff,uint8 Page_Buff_Len)
{
  uint8 Send[4]={W25Q80_CMD_PAGE_PROGRAM,(Page_Number>>8),(Page_Number&0xff),Byte_Offset};
  
  W25Q80_Write_Enable();
  W25Q80_TransferCMD(&Send[0],NULL,&Page_Buff[0],NULL,4,Page_Buff_Len);
  MAPS_Dock_W25Q80_Delay(SPI_FLASH_TIMEOUT);
}

/*
 *  @brief      W25Q80读入一页数据
 *  @para       uint16  Page_Number     写入的页数地址(0x0000~0x0FFF)
 *  @para       uint8   Byte_Offset     写入的地址偏移(0x00~0xFF)
 *  @para       uint8   *Page_Buff      写入的数组
 *  @para       uint8   Page_Buff_Len   写入的数组的长度
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_W25Q80_Read_Page();//W25Q80读入一页数据
 */
void MAPS_Dock_W25Q80_Read_Page(uint16 Page_Number,uint8 Byte_Offset,uint8 *Page_Buff,uint8 Page_Buff_Len)
{
  uint8 Send[4]={W25Q80_CMD_READ_ARRAY_SLOW,(Page_Number>>8),(Page_Number&0xff),Byte_Offset};
  
  W25Q80_TransferCMD(&Send[0],NULL,NULL,&Page_Buff[0],4,Page_Buff_Len);
}
