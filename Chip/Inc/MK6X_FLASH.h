/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_FLASH.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_FLASH_H__
#define __MK6X_FLASH_H__

#include "Common.h"

#if defined(MK66FN2M0)
#define FLASH_SECTOR_SIZE       (4*1024)        //扇区大小为4KB字节
#define FLASH_SECTOR_NUM        (512)           //扇区数512(512*4KB=2M)
#define FLASH_ALIGN_ADDR        (8)             //地址对齐整数倍
#elif defined(MK66FX1M0)
#define FLASH_SECTOR_SIZE       (4*1024)        //扇区大小为4KB字节
#define FLASH_SECTOR_NUM        (256)           //扇区数256(256*4KB=1M)
#define FLASH_ALIGN_ADDR        (8)             //地址对齐整数倍
#elif defined(MK64FN1M0)
#define FLASH_SECTOR_SIZE       (4*1024)        //扇区大小为4KB字节
#define FLASH_SECTOR_NUM        (256)           //扇区数256(256*4KB=1M)
#define FLASH_ALIGN_ADDR        (8)             //地址对齐整数倍
#elif defined(MK64FX512)
#define FLASH_SECTOR_SIZE       (4*1024)        //扇区大小为4KB字节
#define FLASH_SECTOR_NUM        (128)           //扇区数128(128*4KB=512K)
#define FLASH_ALIGN_ADDR        (8)             //地址对齐整数倍
#endif
typedef uint64  FLASH_WRITE_TYPE;               //Flash_Write 函数写入 的数据类型

//宏定义 FCCOB Number
#define     FCMD        FTFE_FCCOB0         //FTFL 命令
#define     FADDR2      FTFE_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFE_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFE_FCCOB3         //Flash address [7:0]
#define     FDATA0      FTFE_FCCOB4         //Data Byte 0       //注意一点，4字节排序，FDATA3是最低位，FDATA0是最高位
#define     FDATA1      FTFE_FCCOB5         //Data Byte 1
#define     FDATA2      FTFE_FCCOB6         //Data Byte 2
#define     FDATA3      FTFE_FCCOB7         //Data Byte 3
#define     FDATA4      FTFE_FCCOB8         //Data Byte 4
#define     FDATA5      FTFE_FCCOB9         //Data Byte 5
#define     FDATA6      FTFE_FCCOBA         //Data Byte 6
#define     FDATA7      FTFE_FCCOBB         //Data Byte 7

//FCMD 命令
#define     RD1BLK    0x00   //读整块Flash
#define     RD1SEC    0x01   //读整个扇区
#define     PGMCHK    0x02   //写入检查
#define     RDRSRC    0x03   //读目标数据(8字节)
#define     PGM8      0x07   //写入长字(8字节)
#define     ERSBLK    0x08   //擦除整块Flash
#define     ERSSCR    0x09   //擦除Flash扇区
#define     PGMSEC    0x0B   //写入扇区
#define     RD1ALL    0x40   //读所有的块
#define     RDONCE    0x41   //只读一次
#define     PGMONCE   0x43   //只写一次
#define     ERSALL    0x44   //擦除所有块
#define     VFYKEY    0x45   //验证后门访问钥匙
#define     PGMPART   0x80   //写入分区
#define     SETRAM    0x81   //设定FlexRAM功能

/*
**Flash读取扇区
*/
#define Flash_Read(SectorNo,Offset,Type)        (*(Type*)((uint32)((SectorNo)*FLASH_SECTOR_SIZE+Offset)))

/*
**function declaration
*/
__RAMFUNC uint8 Flash_CMD(void);
__RAMFUNC void Flash_Init(void);
__RAMFUNC uint8 Flash_Erase_Sector(uint16 sector_num);
__RAMFUNC uint8 Flash_Write(uint16 sector_num, uint16 offset, FLASH_WRITE_TYPE data);
__RAMFUNC uint8 Flash_Write_Buff(uint16 sector_num, uint16 offset, uint16 cnt, uint8 *buf);

#endif