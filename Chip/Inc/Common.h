/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       Common.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __COMMON_H__
#define __COMMON_H__

//芯片型号不同包含不同头文件(MK66 Or MK64)
#if defined(MK66F18)
#include "MK66F18.h"
#elif defined(MK64F12)
#include "MK64F12.h"
#endif
#include "stddef.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "arm_math.h"
#include "intrinsics.h"

/*
 * 数据类型声明
 */
typedef unsigned char       uint8;  /*  8 bits */
typedef unsigned short int  uint16; /* 16 bits */
typedef unsigned long int   uint32; /* 32 bits */
typedef unsigned long long  uint64; /* 64 bits */

typedef char                int8;   /*  8 bits */
typedef short int           int16;  /* 16 bits */
typedef long  int           int32;  /* 32 bits */
typedef long  long          int64;  /* 64 bits */

typedef volatile int8       vint8;  /*  8 bits */
typedef volatile int16      vint16; /* 16 bits */
typedef volatile int32      vint32; /* 32 bits */
typedef volatile int64      vint64; /* 64 bits */

typedef volatile uint8      vuint8;  /*  8 bits */
typedef volatile uint16     vuint16; /* 16 bits */
typedef volatile uint32     vuint32; /* 32 bits */
typedef volatile uint64     vuint64; /* 64 bits */

/*
 * 定义带位域的联合体类型
 */
typedef union
{
    uint32  DW;
    uint16  W[2];
    uint8   B[4];
    struct
    {
        uint32 b0: 1;
        uint32 b1: 1;
        uint32 b2: 1;
        uint32 b3: 1;
        uint32 b4: 1;
        uint32 b5: 1;
        uint32 b6: 1;
        uint32 b7: 1;
        uint32 b8: 1;
        uint32 b9: 1;
        uint32 b10: 1;
        uint32 b11: 1;
        uint32 b12: 1;
        uint32 b13: 1;
        uint32 b14: 1;
        uint32 b15: 1;
        uint32 b16: 1;
        uint32 b17: 1;
        uint32 b18: 1;
        uint32 b19: 1;
        uint32 b20: 1;
        uint32 b21: 1;
        uint32 b22: 1;
        uint32 b23: 1;
        uint32 b24: 1;
        uint32 b25: 1;
        uint32 b26: 1;
        uint32 b27: 1;
        uint32 b28: 1;
        uint32 b29: 1;
        uint32 b30: 1;
        uint32 b31: 1;
    };
}Dtype;
        
/*
**定义结构体坐标
*/
typedef struct
{
  uint16 x;
  uint16 y;
}Site_t;

/*
**定义矩形大小结构体
*/
typedef struct
{
  uint16 W;
  uint16 H;
}Size_t;

/*
 * 中断向量表编号声明
 */
typedef enum
{
    /******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
    NonMaskableInt_VECTORn          = 2 ,       /*!< 2 Non Maskable Interrupt                                                                                    */
    HardFault_VECTORn               = 3 ,       /*!< 3 Hard Fault                                                                                */
    MemoryManagement_VECTORn        = 4 ,       /*!< 4 Cortex-M4 Memory Management Interrupt                                                     */
    BusFault_VECTORn                = 5 ,       /*!< 5 Cortex-M4 Bus Fault Interrupt                                                                     */
    UsageFault_VECTORn              = 6 ,       /*!< 6 Cortex-M4 Usage Fault Interrupt
    */
    SVCall_VECTORn                  = 11,       /*!< 11 Cortex-M4 SV Call Interrupt                                                                      */
    DebugMonitor_VECTORn            = 12,       /*!< 12 Cortex-M4 Debug Monitor Interrupt
    */
    PendSV_VECTORn                  = 14,       /*!< 14 Cortex-M4 Pend SV Interrupt                                                                      */
    SysTick_VECTORn                 = 15,       /*!< 15 Cortex-M4 System Tick Interrupt                                                              */
    /******  Kinetis 6X specific Interrupt Numbers **********************************************************************/
    DMA0_VECTORn                    = 16,       // DMA Channel 0,16 Transfer Complete
    DMA1_VECTORn                    = 17,       // DMA Channel 1,17 Transfer Complete
    DMA2_VECTORn                    = 18,       // DMA Channel 2,18 Transfer Complete
    DMA3_VECTORn                    = 19,       // DMA Channel 3,19 Transfer Complete
    DMA4_VECTORn                    = 20,       // DMA Channel 4,20 Transfer Complete
    DMA5_VECTORn                    = 21,       // DMA Channel 5,21 Transfer Complete
    DMA6_VECTORn                    = 22,       // DMA Channel 6,22 Transfer Complete
    DMA7_VECTORn                    = 23,       // DMA Channel 7,23 Transfer Complete
    DMA8_VECTORn                    = 24,       // DMA Channel 8,24 Transfer Complete
    DMA9_VECTORn                    = 25,       // DMA Channel 9,25 Transfer Complete
    DMA10_VECTORn                   = 26,       // DMA Channel 10,26 Transfer Complete
    DMA11_VECTORn                   = 27,       // DMA Channel 11,27 Transfer Complete
    DMA12_VECTORn                   = 28,       // DMA Channel 12,28 Transfer Complete
    DMA13_VECTORn                   = 29,       // DMA Channel 13,29 Transfer Complete
    DMA14_VECTORn                   = 30,       // DMA Channel 14,30 Transfer Complete
    DMA15_VECTORn                   = 31,       // DMA Channel 15,31 Transfer Complete
    DMA_Error_VECTORn               = 32,       // DMA Error Interrupt
    MCM_VECTORn                     = 33,       // Normal Interrupt
    FTFE_VECTORn                    = 34,       // FTFE Interrupt
    Read_Collision_VECTORn          = 35,       // Read Collision Interrupt
    LVD_LVW_VECTORn                 = 36,       // Low Voltage Detect, Low Voltage Warning
    LLW_VECTORn                     = 37,       // Low Leakage Wakeup
    Watchdog_VECTORn                = 38,       // WDOG Interrupt
    RNG_VECTORn                     = 39,       // RNGB Interrupt
    I2C0_VECTORn                    = 40,       // I2C0 interrupt
    I2C1_VECTORn                    = 41,       // I2C1 interrupt
    SPI0_VECTORn                    = 42,       // SPI0 Interrupt
    SPI1_VECTORn                    = 43,       // SPI1 Interrupt
    I2S0_Tx_VECTORn                 = 44,       // I2S0 Interrupt(Transmit)
    I2S0_Rx_VECTORn                 = 45,       // I2S0 Interrupt(Receive)
    Reserved46_VECTORn              = 46,       // Reserved interrupt
    UART0_RX_TX_VECTORn             = 47,       // UART0 Receive/Transmit interrupt
    UART0_ERR_VECTORn               = 48,       // UART0 Error interrupt
    UART1_RX_TX_VECTORn             = 49,       // UART1 Receive/Transmit interrupt
    UART1_ERR_VECTORn               = 50,       // UART1 Error interrupt
    UART2_RX_TX_VECTORn             = 51,       // UART2 Receive/Transmit interrupt
    UART2_ERR_VECTORn               = 52,       // UART2 Error interrupt
    UART3_RX_TX_VECTORn             = 53,       // UART3 Receive/Transmit interrupt
    UART3_ERR_VECTORn               = 54,       // UART3 Error interrupt
    ADC0_VECTORn                    = 55,       // ADC0 interrupt
    CMP0_VECTORn                    = 56,       // CMP0 interrupt
    CMP1_VECTORn                    = 57,       // CMP1 interrupt
    FTM0_VECTORn                    = 58,       // FTM0 fault, overflow and channels interrupt
    FTM1_VECTORn                    = 59,       // FTM1 fault, overflow and channels interrupt
    FTM2_VECTORn                    = 60,       // FTM2 fault, overflow and channels interrupt
    CMT_VECTORn                     = 61,       // CMT interrupt
    RTC_VECTORn                     = 62,       // RTC interrupt
    RTC_Seconds_VECTORn             = 63,       // RTC seconds interrupt
    PIT0_VECTORn                    = 64,       // PIT timer channel 0 interrupt
    PIT1_VECTORn                    = 65,       // PIT timer channel 1 interrupt
    PIT2_VECTORn                    = 66,       // PIT timer channel 2 interrupt
    PIT3_VECTORn                    = 67,       // PIT timer channel 3 interrupt
    PDB0_VECTORn                    = 68,       // PDB0 Interrupt
    USB0_VECTORn                    = 69,       // USB0 interrupt
    USBDCD_VECTORn                  = 70,       // USBDCD Interrupt
    Reserved71_VECTORn              = 71,       // Reserved interrupt 71
    DAC0_VECTORn                    = 72,       // DAC0 interrupt
    MCG_VECTORn                     = 73,       // MCG Interrupt
    LPTMR_VECTORn                   = 74,       // LPTimer interrupt
    PORTA_VECTORn                   = 75,       // Port A interrupt
    PORTB_VECTORn                   = 76,       // Port B interrupt
    PORTC_VECTORn                   = 77,       // Port C interrupt
    PORTD_VECTORn                   = 78,       // Port D interrupt
    PORTE_VECTORn                   = 79,       // Port E interrupt
    SWI_VECTORn                     = 80,       // Software interrupt
    SPI2_VECTORn                    = 81,       // SPI2 Interrupt
    UART4_RX_TX_VECTORn             = 82,       // UART4 Receive/Transmit interrupt
    UART4_ERR_VECTORn               = 83,       // UART4 Error interrupt
    #if defined(MK66F18)
    Reserved84_VECTORn              = 84,       // Reserved interrupt 84
    Reserved85_VECTORn              = 85,       // Reserved interrupt 85
    #elif defined(MK64F12)
    UART5_RX_TX_VECTORn             = 84,       // UART5 Receive/Transmit interrupt
    UART5_ERR_VECTORn               = 85,       // UART5 Error interrupt
    #endif
    CMP2_VECTORn                    = 86,       // CMP2 interrupt
    FTM3_VECTORn                    = 87,       // FTM3 fault, overflow and channels interrupt
    DAC1_VECTORn                    = 88,       // DAC1 interrupt
    ADC1_VECTORn                    = 89,       // ADC1 interrupt
    I2C2_VECTORn                    = 90,       // I2C2 interrupt
    CAN0_ORed_MB_VECTORn            = 91,       // CAN0 OR'd Message Buffers Interrupt
    CAN0_Bus_Off_VECTORn            = 92,       // CAN0 Bus Off Interrupt
    CAN0_Error_VECTORn              = 93,       // CAN0 Error Interrupt
    CAN0_Tx_Warning_VECTORn         = 94,       // CAN0 Tx Warning Interrupt
    CAN0_Rx_Warning_VECTORn         = 95,       // CAN0 Rx Warning Interrupt
    CAN0_Wake_Up_VECTORn            = 96,       // CAN0 Wake Up Interrupt
    SDHC_VECTORn                    = 97,       // SDHC Interrupt
    ENET_1588_Timer_VECTORn         = 98,       // Ethernet MAC IEEE 1588 Timer Interrupt
    ENET_Transmit_VECTORn           = 99,       // Ethernet MAC Transmit Interrupt
    ENET_Receive_VECTORn            = 100,      // Ethernet MAC Receive Interrupt
    ENET_Error_VECTORn              = 101,      // Ethernet MAC Error and miscelaneous Interrupt
    #if defined(MK66F18)
    LPUART0_VECTORn                 = 102,      // LPUART0 status/error interrupt
    TSI0_VECTORn                    = 103,      // TSI0 Interrupt
    TPM1_VECTORn                    = 104,      // TPM1 fault, overflow and channels interrupt
    TPM2_VECTORn                    = 105,      // TPM2 fault, overflow and channels interrupt
    USBHSDCD_VECTORn                = 106,      // USBHSDCD, USBHS Phy Interrupt
    I2C3_VECTORn                    = 107,      // I2C3 interrupt
    CMP3_VECTORn                    = 108,      // CMP3 interrupt  
    USBHS_VECTORn                   = 109,      // USB high speed OTG interrupt
    CAN1_ORed_MB_VECTORn            = 110,      // CAN1 OR'd Message Buffers Interrupt
    CAN1_Bus_Off_VECTORn            = 111,      // CAN1 Bus Off Interrupt
    CAN1_Error_VECTORn              = 112,      // CAN1 Error Interrupt
    CAN1_Tx_Warning_VECTORn         = 113,      // CAN1 Tx Warning Interrupt
    CAN1_Rx_Warning_VECTORn         = 114,      // CAN1 Rx Warning Interrupt
    CAN1_Wake_Up_VECTORn            = 115,      // CAN1 Wake Up Interrupt
    #elif defined(MK64F12)
    Reserved102_VECTORn             = 102,       // Reserved interrupt 102
    Reserved103_VECTORn             = 103,       // Reserved interrupt 103
    Reserved104_VECTORn             = 104,       // Reserved interrupt 104
    Reserved105_VECTORn             = 105,       // Reserved interrupt 105
    Reserved106_VECTORn             = 106,       // Reserved interrupt 106
    Reserved107_VECTORn             = 107,       // Reserved interrupt 107
    Reserved108_VECTORn             = 108,       // Reserved interrupt 108
    Reserved109_VECTORn             = 109,       // Reserved interrupt 109
    Reserved110_VECTORn             = 110,       // Reserved interrupt 110
    Reserved111_VECTORn             = 111,       // Reserved interrupt 111
    Reserved112_VECTORn             = 112,       // Reserved interrupt 112
    Reserved113_VECTORn             = 113,       // Reserved interrupt 113
    Reserved114_VECTORn             = 114,       // Reserved interrupt 114
    Reserved115_VECTORn             = 115,       // Reserved interrupt 115
    #endif
} VECTORn_t;

/*
**定义运行到RAM的函数
*/
#if defined(__ICCARM__)//IAR 用 __ramfunc 来声明
#define __RAMFUNC       __ramfunc
#else
#define __RAMFUN
#endif

/*
**变量的位清0和置1
*/
#define BIT_CLEAN(var,n)        (var) &= ~(1<<(n))   //变量var 的n位(即第n+1位)清0
#define BIT_SET(var,n)          (var) |=  (1<<(n))   //变量var 的n位(即第n+1位)置1
#define BIT_GET(var,n)          (((var)>>(n))&0x01)  //读取变量var 的n位(即第n+1位)

/*
**布尔类型
*/
#define TRUE    1
#define FALSE   0

/*
**求最大值和最小值
*/
#define MAX(x,y)        (((x)>(y))?(x):(y))
#define MIN(x,y)        (((x)<(y))?(x):(y))

/*
**数组元素个数和长度
*/
#define ARRAY_SIZE(x)   (sizeof((x))/sizeof(((x)[0])))

/*
**绝对值函数宏
*/
#define ABS(x)          (((x)>0)?(x):(-(x)))

/*
**交换32位数据4字节顺序
*/
#define SWAP32(data)    __REV(data)

/*
**交换16位数据2字节顺序
*/
#define SWAP16(data)    __REVSH(data)

/*
**交换x,y的值
*/
#define SWAP(x,y)       do{x^=y;y^=x;x^=y;}while(0)

/*
**获取结构体某成员偏移
*/
#define OFFSET(type,member)    (uint32)(&(((type *)0)->member))

/*
**确保x的范围为 min~max
*/
#define RANGE(x,max,min)        ((uint8)((x)<(min)?(min):((x)>(max)?(max):(x))))

/*
**仿二进制赋值
*/
#define HEX__(n)        0x##n##UL
#define B8__(x)         ((x & 0x0000000FUL) ? 1:0)\
                        +((x & 0x000000F0UL) ? 2:0)\
                        +((x & 0x00000F00UL) ? 4:0)\
                        +((x & 0x0000F000UL) ? 8:0)\
                        +((x & 0x000F0000UL) ? 16:0)\
                        +((x & 0x00F00000UL) ? 32:0)\
                        +((x & 0x0F000000UL) ? 64:0)\
                        +((x & 0xF0000000UL) ? 128:0)
#define  B8(x)                          ((unsigned char)B8__(HEX__(x)))
#define  B16(x_msb,x_lsb)               (((unsigned int)B8(x_msb)<<8) + B8(x_lsb))
#define  B32(x_msb,x_2,x_3,x_lsb)       (((unsigned long)B8(x_msb)<<24) + ((unsigned long)B8(x_2)<<16) + ((unsigned long)B8(x_3)<<8) + B8(x_lsb))
                          
#endif