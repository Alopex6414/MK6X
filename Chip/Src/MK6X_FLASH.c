/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_FLASH.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      Flash命令
 *  @return     命令执行结果(1成功，0失败)
 *  @since      v1.0
 */
__RAMFUNC uint8 Flash_CMD(void)
{
  FTFE_FSTAT = (0
                | FTFE_FSTAT_CCIF_MASK        //指令完成标志(写1清0)
                | FTFE_FSTAT_RDCOLERR_MASK    //读冲突错误标志(写1清0)
                | FTFE_FSTAT_ACCERR_MASK      //访问错误标志位(写1清0)
                | FTFE_FSTAT_FPVIOL_MASK      //非法访问保护标志位(写1清0)
                );
  while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)); //等待命令完成
  
  if(FTFE_FSTAT & (FTFE_FSTAT_ACCERR_MASK | FTFE_FSTAT_RDCOLERR_MASK | FTFE_FSTAT_FPVIOL_MASK | FTFE_FSTAT_MGSTAT0_MASK))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/*
 *  @brief      初始化flash
 *  @since      v1.0
 */
__RAMFUNC void Flash_Init(void)
{
  // 清除Flash预读取缓冲区
  #if defined(MK66F18)
  FMC_PFB01CR |= FMC_PFB01CR_S_B_INV_MASK;
  #elif defined(MK64F12)
  FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;
  #endif
  
  while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK));
  
  FTFE_FSTAT = (0
                | FTFE_FSTAT_CCIF_MASK        //指令完成标志(写1清0)
                | FTFE_FSTAT_RDCOLERR_MASK    //读冲突错误标志(写1清0)
                | FTFE_FSTAT_ACCERR_MASK      //访问错误标志位(写1清0)
                | FTFE_FSTAT_FPVIOL_MASK      //非法访问保护标志位(写1清0)
                );
  DELAY_MS(10);
}

/*
 *  @brief      擦除指定flash扇区
 *  @param      sector_num    扇区号(MK66FN2M0实际使用0~511,MK66FX1M0实际使用0~255)
 *  @return     执行结果(1成功，0失败)
 *  @since      v1.0
 *  Sample usage:       Flash_Erase_Sector(512-1);        //擦除扇区512-1
 */
__RAMFUNC uint8 Flash_Erase_Sector(uint16 sector_num)
{
  uint32 addr = sector_num * FLASH_SECTOR_SIZE;
  
  //设置擦除命令
  FCMD = ERSSCR;

  //设置目标地址
  FADDR2 = ((Dtype *)&addr)->B[2];
  FADDR1 = ((Dtype *)&addr)->B[1];
  FADDR0 = ((Dtype *)&addr)->B[0];
  
  if(Flash_CMD() == 0)//Flash_CMD命令是否完成
  {
    return 0;
  }
  
  if(sector_num == 0)//扇区号不要为0
  {
    return Flash_Write(sector_num,0x000408,0xFFFFFFFFFFFFFFFF);
  }
  
  return 1;
}

/*
 *  @brief      写入长字节数据到 flash指定地址
 *  @param      sector_num      扇区号(MK66FN2M0实际使用0~511,MK66FX1M0实际使用0~255)
 *  @param      offset          写入扇区内部偏移地址(0~4095 中 8的倍数)
 *  @param      data            需要写入的数据
 *  @return     执行结果(1成功，0失败)
 *  @since      v1.0
 *  Sample usage:       Flash_Write(511,0,0xAABBCCDDEEFF0011);        //扇区127,偏移地址为0,写入数据:0xFFFFFFFE
 */
__RAMFUNC uint8 Flash_Write(uint16 sector_num, uint16 offset, FLASH_WRITE_TYPE data)
{
  uint32 addr = sector_num * FLASH_SECTOR_SIZE + offset;
  uint32 tmpdata;
  
  //偏移地址不是FLASH_ALIGN_ADDR的倍数或偏移地址大于扇区大小执行失败
  if(offset % FLASH_ALIGN_ADDR != 0 || offset > FLASH_SECTOR_SIZE)
  {
    return 0;
  }
  
  //设置目标地址
  FADDR2 = ((Dtype *)&addr)->B[2];
  FADDR1 = ((Dtype *)&addr)->B[1];
  FADDR0 = ((Dtype *)&addr)->B[0];
  
  //设置低32位数据
  tmpdata = (uint32)data;
  FDATA0 = ((Dtype *)&tmpdata)->B[3];                    // 设置写入数据
  FDATA1 = ((Dtype *)&tmpdata)->B[2];
  FDATA2 = ((Dtype *)&tmpdata)->B[1];
  FDATA3 = ((Dtype *)&tmpdata)->B[0];
  
  FCMD = PGM8;
  
  tmpdata = (uint32)(data>>32);

  FDATA4 = ((Dtype *)&tmpdata)->B[3];                 // 设置写入数据
  FDATA5 = ((Dtype *)&tmpdata)->B[2];
  FDATA6 = ((Dtype *)&tmpdata)->B[1];
  FDATA7 = ((Dtype *)&tmpdata)->B[0];
  
  if(Flash_CMD() == 0)
  {
    return 0;
  }
  
  return 1;
}

/*
 *  @brief      写入数据缓冲区到 flash指定地址
 *  @param      sector_num      扇区号(MK66FN2M0实际使用0~511,MK66FX1M0实际使用0~255)
 *  @param      offset          写入扇区内部偏移地址(0~4095 中 8的倍数)
 *  @param      buf             需要写入的数据缓冲区首地址
 *  @return     执行结果(1成功，0失败)
 *  @since      v1.0
 *  Sample usage:           uint32 buff[10];
                            Flash_Write_Buff(127,0,sizeof(buff),buff);        //扇区127,偏移地址为0,写入数据源地址:buff,数目sizeof(buff)
 */
__RAMFUNC uint8 Flash_Write_Buff(uint16 sector_num, uint16 offset, uint16 cnt, uint8 *buf)
{
  uint32  size;
  uint32  addr;
  uint32  data;
  
  //偏移地址不是FLASH_ALIGN_ADDR的倍数或偏移地址大于扇区大小执行失败
  if(offset % FLASH_ALIGN_ADDR != 0 || offset > FLASH_SECTOR_SIZE)
  {
    return 0;
  }
  
  addr = sector_num * FLASH_SECTOR_SIZE + offset;
  
  FCMD = PGM8;
  
  for(size = 0; size < cnt; size += FLASH_ALIGN_ADDR)
  {
    //设置目标地址
    FADDR2 = ((Dtype *)&addr)->B[2];
    FADDR1 = ((Dtype *)&addr)->B[1];
    FADDR0 = ((Dtype *)&addr)->B[0];
    
    //设置低32位数据
    data =  *(uint32 *)buf;
    
    FDATA0 = ((Dtype *)&data)->B[3];                    // 设置写入数据
    FDATA1 = ((Dtype *)&data)->B[2];
    FDATA2 = ((Dtype *)&data)->B[1];
    FDATA3 = ((Dtype *)&data)->B[0];
    
    //设置高32位数据
    data = *(uint32 *)(buf+4);

    FDATA4 = ((Dtype *)&data)->B[3];                    // 设置写入数据
    FDATA5 = ((Dtype *)&data)->B[2];
    FDATA6 = ((Dtype *)&data)->B[1];
    FDATA7 = ((Dtype *)&data)->B[0];
    
    if(Flash_CMD() == 0)
    {
      return 0;
    }
    
    addr += FLASH_ALIGN_ADDR;
    buf += FLASH_ALIGN_ADDR;
  }
  
  return 1;
}