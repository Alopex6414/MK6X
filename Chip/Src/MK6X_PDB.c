/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PDB.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      PDB初始化
 *  @since      v1.0
 *  Sample usage:       PDB_Init();//初始化 PDB0
 */
void PDB_Init(void)
{
  SIM_SCGC6 |= SIM_SCGC6_PDB_MASK;//PDB模块时钟使能
  
  //PDB状态控制寄存器
  PDB_SC_REG(PDB0_BASE_PTR) = (0
                               | PDB_SC_CONT_MASK       //PDB连续模式
                               | PDB_SC_TRGSEL(15)      //PDB软件触发
                               | PDB_SC_PDBEN_MASK      //PDB模块使能
                               );
  
}