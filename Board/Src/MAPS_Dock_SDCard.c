/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MAPS_Dock_SDCard.c
 * @brief      MAPS��ɫ��MAPS_Dock�ⲿ��չ��
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      ����SD���ļ�
 *  @since      v1.0
 *  Sample usage:       MAPS_Dock_SDCard_LoadFile();//����SD���ļ�
 */
/*void MAPS_Dock_SDCard_LoadFile(void)
{
  FIL     fdst;   //�ļ�
  FATFS   fs;     //�ļ�ϵͳ
  DIR     dir;    //�ļ�����
  FILINFO finfo;  //�ļ���Ϣ
  FRESULT res;    //�ļ�ϵͳ����ֵ
  
  res = f_mount(0, &fs);//�����ļ�ϵͳ
  if(res != FR_OK)
  {
    MAPS_Dock_LCM_Put_Str_6x8(37,3,"No SDCard");
  }
  
}*/