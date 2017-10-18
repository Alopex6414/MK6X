/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Include.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

/*
**App
*/
#include "App_Init.h"
#include "Main.h"
#include "MK6X_Conf.h"
#include "MK6X_It.h"

/*
**Board
*/
#include "MAPS_Dock_I2C.h"
#include "MAPS_Dock_Key.h"
#include "MAPS_Dock_LCM.h"
#include "MAPS_Dock_LED.h"
#include "MAPS_Dock_Rocker.h"
#include "MAPS_Dock_SDCard.h"
#include "MAPS_Dock_W25Q80.h"
#include "MAPS_LCD.h"

/*
**Chip
*/
#include "MK6X_ADC.h"
#include "MK6X_CAN.h"
#include "MK6X_DAC.h"
#include "MK6X_DELAY.h"
#include "MK6X_DMA.h"
#include "MK6X_DWT.h"
#include "MK6X_FLASH.h"
#include "MK6X_FLEXBUS.h"
#include "MK6X_FTM.h"
#include "MK6X_GPIO.h"
#include "MK6X_GPIO_CFG.h"
#include "MK6X_I2C.h"
#include "MK6X_I2S.h"
#include "MK6X_LPTMR.h"
#include "MK6X_MCG.h"
#include "MK6X_PDB.h"
#include "MK6X_PIT.h"
#include "MK6X_PORT.h"
#include "MK6X_PORT_CFG.h"
#include "MK6X_RTC.h"
#include "MK6X_SDHC.h"
#include "MK6X_SPI.h"
#include "MK6X_SysTick.h"
#include "MK6X_UART.h"
#include "MK6X_USB.h"
#include "MK6X_WDOG.h"

/*
**Drive
*/
#include "Drive_Camera.h"
#include "Drive_CCD.h"
#include "Drive_MPU6050.h"
#include "Drive_Oled.h"
#include "Drive_RTC_Count.h"

/*
**File
*/

/*
**Lib
*/
//FATFS
#include "diskio.h"
#include "ff.h"
#include "integer.h"
#include "ffconf.h"
//USB
#include "USB.h"

/*
**Start
*/
#include "MK6X_Misc.h"
#include "MK6X_SystemInit.h"
#include "MK6X_Vectors.h"



#endif