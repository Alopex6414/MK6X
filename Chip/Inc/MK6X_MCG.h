/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_MCG.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_MCG_H__
#define __MK6X_MCG_H__

#include "Common.h"

/*
**PLL锁相环(PLL频率)
*/
#if defined(MK66F18)//MK66F18 PLL //(EXTAL_50MHz)(MCGOUTCLK=(EXTAL_50MHz/(PRCIV+1)*(VDIV+16)/2))
typedef enum
{
  PLL75,
  PLL80,
  PLL85,
  PLL88,
  PLL90,
  PLL95,
  PLL100,
  PLL105,
  PLL110,
  PLL113,
  PLL115,
  PLL120,
  PLL125,
  PLL130,
  PLL135,
  PLL138,
  PLL140,
  PLL145,
  PLL150,
  PLL155,
  PLL160,
  PLL163,
  PLL165,
  PLL170,
  PLL175,
  PLL180,
  PLL185,
  PLL188,
  PLL190,
  PLL195,
  PLL200,
  PLL205,
  PLL210,
  PLL213,
  PLL215,
  PLL220,
  PLL225,
  PLL230,
  PLL235,
  PLL238,
  PLL250,
  PLL263,
  PLL275,
  PLL288,
  PLLMAX,
}PLLn;
#elif defined(MK64F12)//MK64F12 PLL //(EXTAL_50MHz)(MCGOUTCLK=(EXTAL_50MHz/(PRCIV+1)*(VDIV+24)))
typedef enum
{
  PLL48,
  PLL50,
  PLL52,
  PLL54,
  PLL56,
  PLL58,
  PLL60,
  PLL62,
  PLL64,
  PLL66,
  PLL68,
  PLL70,
  PLL72,
  PLL74,
  PLL76,
  PLL78,
  PLL80,
  PLL82,
  PLL84,
  PLL86,
  PLL88,
  PLL90,
  PLL92,
  PLL94,
  PLL96,
  PLL98,
  PLL100,
  PLL102,
  PLL104,
  PLL106,
  PLL108,
  PLL110,
  PLL115,
  PLL120,
  PLL125,
  PLL130,
  PLL135,
  PLL140,
  PLL150,
  PLL160,
  PLL170,
  PLL180,
  PLL200,
  PLLMAX,
}PLLn;
#endif

/*
**PLL分频因子结构体
*/
typedef struct
{
  uint16 PLL_CLK;
  uint8  PLL_PRDIV;
  uint8  PLL_VDIV;
}MCG_PLL_DIV;

/*
**SIM时钟分频因子结构体
*/
typedef struct
{
  uint8 SIM_CORE_DIV;
  uint8 SIM_BUS_DIV;
  uint8 SIM_FLEX_DIV;
  uint8 SIM_FLASH_DIV;
}MCG_SIM_DIV;

/*
**variate declaration
*/
extern MCG_PLL_DIV MCG_PLL[PLLMAX];
extern MCG_SIM_DIV MCG_DIV;

/*
**function declaration
*/
extern void MCG_DIV_Count(PLLn PLLx);
extern uint8 PLL_Init(PLLn PLLx);


#endif