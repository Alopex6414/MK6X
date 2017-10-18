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
#define FLASH_SECTOR_SIZE       (4*1024)        //������СΪ4KB�ֽ�
#define FLASH_SECTOR_NUM        (512)           //������512(512*4KB=2M)
#define FLASH_ALIGN_ADDR        (8)             //��ַ����������
#elif defined(MK66FX1M0)
#define FLASH_SECTOR_SIZE       (4*1024)        //������СΪ4KB�ֽ�
#define FLASH_SECTOR_NUM        (256)           //������256(256*4KB=1M)
#define FLASH_ALIGN_ADDR        (8)             //��ַ����������
#elif defined(MK64FN1M0)
#define FLASH_SECTOR_SIZE       (4*1024)        //������СΪ4KB�ֽ�
#define FLASH_SECTOR_NUM        (256)           //������256(256*4KB=1M)
#define FLASH_ALIGN_ADDR        (8)             //��ַ����������
#elif defined(MK64FX512)
#define FLASH_SECTOR_SIZE       (4*1024)        //������СΪ4KB�ֽ�
#define FLASH_SECTOR_NUM        (128)           //������128(128*4KB=512K)
#define FLASH_ALIGN_ADDR        (8)             //��ַ����������
#endif
typedef uint64  FLASH_WRITE_TYPE;               //Flash_Write ����д�� ����������

//�궨�� FCCOB Number
#define     FCMD        FTFE_FCCOB0         //FTFL ����
#define     FADDR2      FTFE_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFE_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFE_FCCOB3         //Flash address [7:0]
#define     FDATA0      FTFE_FCCOB4         //Data Byte 0       //ע��һ�㣬4�ֽ�����FDATA3�����λ��FDATA0�����λ
#define     FDATA1      FTFE_FCCOB5         //Data Byte 1
#define     FDATA2      FTFE_FCCOB6         //Data Byte 2
#define     FDATA3      FTFE_FCCOB7         //Data Byte 3
#define     FDATA4      FTFE_FCCOB8         //Data Byte 4
#define     FDATA5      FTFE_FCCOB9         //Data Byte 5
#define     FDATA6      FTFE_FCCOBA         //Data Byte 6
#define     FDATA7      FTFE_FCCOBB         //Data Byte 7

//FCMD ����
#define     RD1BLK    0x00   //������Flash
#define     RD1SEC    0x01   //����������
#define     PGMCHK    0x02   //д����
#define     RDRSRC    0x03   //��Ŀ������(8�ֽ�)
#define     PGM8      0x07   //д�볤��(8�ֽ�)
#define     ERSBLK    0x08   //��������Flash
#define     ERSSCR    0x09   //����Flash����
#define     PGMSEC    0x0B   //д������
#define     RD1ALL    0x40   //�����еĿ�
#define     RDONCE    0x41   //ֻ��һ��
#define     PGMONCE   0x43   //ֻдһ��
#define     ERSALL    0x44   //�������п�
#define     VFYKEY    0x45   //��֤���ŷ���Կ��
#define     PGMPART   0x80   //д�����
#define     SETRAM    0x81   //�趨FlexRAM����

/*
**Flash��ȡ����
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