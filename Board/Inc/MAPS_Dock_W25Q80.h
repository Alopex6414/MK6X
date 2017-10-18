/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_W25Q80.h
 * @brief      MAPSËÄÉ«°åMAPS_DockÍâ²¿À©Õ¹°å
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MAPS_DOCK_W25Q80_H__
#define __MAPS_DOCK_W25Q80_H__

#include "Common.h"

/*
**SPI¶ÁÐ´W25Q80Flash
*/
#define SPI_FLASH_WINBOND_VENDER_ID     0xEF            //WINBOND Vendor Id: 0xEF
#define SPI_FLASH_WINBOND_ID_LEN        0x03            //WINBOND Vendor Id Length

#define SPI_FLASH_PAGESIZE              (256)           //256B Page Size
#define SPI_FLASH_SECTOR_SIZE           (256 * 16)      //4K Sector Size
#define SPI_FLASH_TOTAL_SIZE            (1024 * 1024)   //1M Sector Size

#define SPI_FLASH_TIMEOUT		(2000)

//Flash×´Ì¬
#define STATUS_BUSY		        (0x01)

#define ERASE_SECTOR_SIZE               (4096)
#define ERASE_CLUSTER_SIZE              (32768)
#define ERASE_BLOCK_SIZE                (65536)

//SPI¶ÁÐ´W25Q80ÃüÁî
#define W25Q80_CMD_DEVICE_ID            0x9F
#define W25Q80_CMD_WRITE_ENABLE         0x06
#define W25Q80_CMD_WRITE_DISABLE        0x04
#define W25Q80_CMD_READ_STATUS_REG      0x05
#define W25Q80_CMD_WRITE_STATUS_REG     0x01
#define W25Q80_CMD_READ_ARRAY_SLOW      0x03
#define W25Q80_CMD_READ_ARRAY_FAST      0x0B
#define W25Q80_CMD_PAGE_PROGRAM         0x02
#define W25Q80_CMD_SECTOR_ERASE         0x20    //ÉÈÇø²Á³ý:4KB
#define W25Q80_CMD_CLUSTER_ERASE        0x52    //´Ø²Á³ý:32KB
#define W25Q80_CMD_BLOCK_ERASE          0xD8    //¿é²Á³ý:64KB
#define W25Q80_CMD_CHIP_ERASE           0xC7    //Ð¾Æ¬²Á³ý:1MB
#define W25Q80_CMD_POWER_DOWN           0xB9
#define W25Q80_CMD_RELEASE_POWER_DOWN   0xAB

/*
**SPI FlashÑÓÊ±
*/
#define MAPS_Dock_W25Q80_Delay(ms) DELAY_MS(ms) //W25Q80ÑÓÊ±ms

/*
**SPI_Flash½á¹¹Ìå
*/
typedef struct
{
  uint32 Size;
  uint32 Page_Size;
  uint32 Sector_Size;
}SPI_Flash;


/*
**function declaration
*/
extern void MAPS_Dock_W25Q80_Init(void);
extern void MAPS_Dock_W25Q80_Read_ID(uint8 *Vender_ID,uint8 *Drive_ID);
extern void MAPS_Dock_W25Q80_Erase_Chip(void);
extern void MAPS_Dock_W25Q80_Erase_Block(uint32 Address,uint8 Block_Size);
extern void MAPS_Dock_W25Q80_Write_Page(uint16 Page_Number,uint8 Byte_Offset,uint8 *Page_Buff,uint8 Page_Buff_Len);
extern void MAPS_Dock_W25Q80_Read_Page(uint16 Page_Number,uint8 Byte_Offset,uint8 *Page_Buff,uint8 Page_Buff_Len);

#endif