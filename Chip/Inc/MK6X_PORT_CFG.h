/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_PORT_CFG.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_PORT_CFG_H__
#define __MK6X_PORT_CFG_H__

#include "Common.h"
#include "MK6X_PORT.h"

/*
**PORT管脚复用配置
*/

/*
**UART
*/
//UART0
#define UART0_RX_PIN    PTA15   //PTA1,PTA15,PTB16,PTD6         //PTA1不要用(JTAG)
#define UART0_TX_PIN    PTA14   //PTA2,PTA14,PTB17,PTD7         //PTA2不要用(JTAG)

//UART1
#define UART1_RX_PIN    PTC3    //PTC3,PTE1                     //PTE1不要用(SDHC)    
#define UART1_TX_PIN    PTC4    //PTC4,PTE0                     //PTE0不要用(SDHC)

//UART2
#define UART2_RX_PIN    PTD2    //PTD2
#define UART2_TX_PIN    PTD3    //PTD3

//UART3
#define UART3_RX_PIN    PTC16   //PTB10,PTC16,PTE5              //PTE5不要用(SDHC)
#define UART3_TX_PIN    PTC17   //PTB11,PTC17,PTE4              //PTE4不要用(SDHC)

//UART4
#define UART4_RX_PIN    PTC14   //PTC14、PTE25
#define UART4_TX_PIN    PTC15   //PTC15、PTE24

//UART5
#ifdef MK64F12
#define UART5_RX_PIN    PTE9   //PTD8、PTE9
#define UART5_TX_PIN    PTE8   //PTD9、PTE8
#endif

/*
**FTM
*/
//FTM0
#define FTM0_CH0_PIN    PTC1    //PTC1,PTA3                     //PTA3不要用(JTAG)
#define FTM0_CH1_PIN    PTA4    //PTC2,PTA4
#define FTM0_CH2_PIN    PTA5    //PTC3,PTA5
#define FTM0_CH3_PIN    PTC4    //PTC4,PTA6
#define FTM0_CH4_PIN    PTA7    //PTD4,PTA7
#define FTM0_CH5_PIN    PTD5    //PTD5,PTA0                     //PTA0不要用(JTAG)
#define FTM0_CH6_PIN    PTD6    //PTD6,PTA1                     //PTA1不要用(JTAG)
#define FTM0_CH7_PIN    PTD7    //PTD7,PTA2                     //PTA2不要用(JTAG)

//FTM1
#define FTM1_CH0_PIN    PTA8    //PTA8,PTA12,PTB0
#define FTM1_CH1_PIN    PTA9    //PTA9,PTA13,PTB1

//FTM2
#define FTM2_CH0_PIN    PTB18   //PTA10,PTB18
#define FTM2_CH1_PIN    PTB19   //PTA11,PTB19

//FTM3
#define FTM3_CH0_PIN    PTD0    //PTE5,PTD0
#define FTM3_CH1_PIN    PTD1    //PTE6,PTD1
#define FTM3_CH2_PIN    PTE7    //PTE7,PTD2
#define FTM3_CH3_PIN    PTE8    //PTE8,PTD3
#define FTM3_CH4_PIN    PTE9    //PTE9,PTC8
#define FTM3_CH5_PIN    PTE10   //PTE10,PTC9
#define FTM3_CH6_PIN    PTE11   //PTE11,PTC10
#define FTM3_CH7_PIN    PTE12   //PTE12,PTC11

//FTM_QUAD
#define FTM1_QDPHA_PIN  PTA8    //PTA8,PTA12,PTB0
#define FTM1_QDPHB_PIN  PTA9    //PTA9,PTA13,PTB1

#define FTM2_QDPHA_PIN  PTA10   //PTA10,PTB18
#define FTM2_QDPHB_PIN  PTA11   //PTA11,PTB19

/*
**I2C
*/
//I2C0
#define I2C0_SCL_PIN    PTE24   //PTB0,PTB2,PTD8,PTE24
#define I2C0_SDA_PIN    PTE25   //PTB1,PTB3,PTD9,PTE25

//I2C1
#define I2C1_SCL_PIN    PTC10   //PTE1,PTC10                    //PTE1不要用(SDHC) 
#define I2C1_SDA_PIN    PTC11   //PTE0,PTC11                    //PTE0不要用(SDHC)

//I2C2
#define I2C2_SCL_PIN    PTA12   //PTA12,PTA14
#define I2C2_SDA_PIN    PTA11   //PTA11,PTA13

//I2C3
#define I2C3_SCL_PIN    PTE11    //PTA2,PTE11                   //PTA2不要用(JTAG)
#define I2C3_SDA_PIN    PTE10    //PTA1,PTE10                   //PTA1不要用(JTAG)

/*
**SPI
*/
//SPI0
#define SPI0_SCK_PIN    PTA15   //PTA15,PTC5,PTD1
#define SPI0_SOUT_PIN   PTA16   //PTA16,PTC6,PTD2
#define SPI0_SIN_PIN    PTA17   //PTA17,PTC7,PTD3 
#define SPI0_PCS0_PIN   PTA14   //PTA14,PTC4,PTD0
#define SPI0_PCS1_PIN   PTC3    //PTC3,PTD4          
#define SPI0_PCS2_PIN   PTC2    //PTC2,PTD5               
#define SPI0_PCS3_PIN   PTC1    //PTC1,PTD6   
#define SPI0_PCS4_PIN   PTC0    //PTC0
#define SPI0_PCS5_PIN   PTB23   //PTB23

//SPI1
#define SPI1_SCK_PIN    PTB11   //PTE2,PTB11
#define SPI1_SOUT_PIN   PTB16   //PTE1,PTB16
#define SPI1_SIN_PIN    PTB17   //PTE3,PTB17
#define SPI1_PCS0_PIN   PTB10   //PTE4,PTB10
#define SPI1_PCS1_PIN   PTB9    //PTE0,PTB9
#define SPI1_PCS2_PIN   PTE5    //PTE5
#define SPI1_PCS3_PIN   PTE6    //PTE6

//SPI2
#define SPI2_SCK_PIN    PTD12   //PTB21,PTD12
#define SPI2_SOUT_PIN   PTD13   //PTB22,PTD13
#define SPI2_SIN_PIN    PTD14   //PTB23,PTD14
#define SPI2_PCS0_PIN   PTD11   //PTB20,PTD11
#define SPI2_PCS1_PIN   PTD15   //PTD15

/*
**CAN
*/
//CAN0
#define CAN0_TX_PIN     PTA12   //PTA12,PTB18
#define CAN0_RX_PIN     PTA13   //PTA13,PTB19

//CAN1
#define CAN1_TX_PIN     PTE24   //PTE24,PTC17
#define CAN1_RX_PIN     PTE25   //PTE25,PTC16

/*
**FLEXBUS
*/
#define FB_AD0          PTD6    //PTD6
#define FB_AD1          PTD5    //PTD5
#define FB_AD2          PTD4    //PTD4
#define FB_AD3          PTD3    //PTD3
#define FB_AD4          PTD2    //PTD2
#define FB_AD5          PTC10   //PTC10
#define FB_AD6          PTC9    //PTC9
#define FB_AD7          PTC8    //PTC8
#define FB_AD8          PTC7    //PTC7
#define FB_AD9          PTC6    //PTC6
#define FB_AD10         PTC5    //PTC5
#define FB_AD11         PTC4    //PTC4
#define FB_AD12         PTC2    //PTC2
#define FB_AD13         PTC1    //PTC1
#define FB_AD14         PTC0    //PTC0
#define FB_AD15         PTB18   //PTB18
#define FB_AD16         PTB17   //PTB17
#define FB_AD17         PTB16   //PTB16
#define FB_AD18         PTB11   //PTB11
#define FB_AD19         PTB10   //PTB10
#define FB_AD20         PTB9    //PTB9
#define FB_AD21         PTB8    //PTB8
#define FB_AD22         PTB7    //PTB7
#define FB_AD23         PTB6    //PTB6

/*
**LPUART
*/
#define LPUART0_TX_PIN  PTE8    //PTE8
#define LPUART0_RX_PIN  PTE9    //PTE9
#define LPUART0_CTS_PIN PTE10   //PTE10
#define LPUART0_RTS_PIN PTE11   //PTE11

/*
**I2S
*/
#define I2S0_MCLK       PTE6    //PTE6
#define I2S0_RXD0       PTE7    //PTE7
#define I2S0_RX_FS      PTE8    //PTE8
#define I2S0_RX_BCLK    PTE9    //PTE9
#define I2S0_TXD0       PTE10   //PTE10
#define I2S0_TX_FS      PTE11   //PTE11
#define I2S0_TX_BCLK    PTE12   //PTE12



#endif