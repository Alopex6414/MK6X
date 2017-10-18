/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_SDCard.c
 * @brief      MAPS四色板MAPS_Dock外部扩展板
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      加载SD卡文件
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_SDCard_LoadFile();//加载SD卡文件
 */
/*void MAPS_Dock_SDCard_LoadFile(void)
{
  FIL     fdst;   //文件
  FATFS   fs;     //文件系统
  DIR     dir;    //文件扇区
  FILINFO finfo;  //文件信息
  FRESULT res;    //文件系统返回值
  
  res = f_mount(0, &fs);//挂载文件系统
  if(res != FR_OK)
  {
    MAPS_Dock_LCM_Put_Str_6x8(37,3,"No SDCard");
  }
  
}*/