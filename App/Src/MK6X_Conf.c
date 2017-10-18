/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_Conf.c
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#include "Common.h"
#include "Include.h"

/*
 *  @brief      断言失败所执行的函数
 *  @param      file    文件路径地址
 *  @param      line    行数
 *  @since      v1.0
 *  Sample usage:       assert_failed(__FILE__, __LINE__);
 */
void assert_failed(char *file, int line)
{
  while(1)
  {
    ;
  }
}

/*
 *  @brief      默认中断服务函数
 *  @since      v1.0
 *  @note       此函数写入中断向量表里，不需要用户执行
 */
void default_isr(void)
{
  #ifdef  DEBUG
  #define VECTORNUM     (*(volatile uint8_t*)(0xE000ED04))
  uint8 vtr = VECTORNUM;
  
  MAPS_Dock_LCM_Init();
  MAPS_Dock_LCM_Put_Str_6x8(0,0,Vector_Str[vtr],LCM_Pure_Color);
  
  MAPS_Dock_LEDx_Init(MAPS_Dock_LED1,LED_ON);
  MAPS_Dock_LEDx_Init(MAPS_Dock_LED2,LED_ON);
  MAPS_Dock_LEDx_Init(MAPS_Dock_LED3,LED_ON);
  MAPS_Dock_LEDx_Init(MAPS_Dock_LED4,LED_ON);
  
  while(1)
  {
    MAPS_Dock_LEDx_Turn(MAPS_Dock_LED1);
    MAPS_Dock_LEDx_Turn(MAPS_Dock_LED2);
    MAPS_Dock_LEDx_Turn(MAPS_Dock_LED3);
    MAPS_Dock_LEDx_Turn(MAPS_Dock_LED4);
    DELAY_MS(100);
  }
  #else
  return;
  #endif
}

#ifdef DEBUG
uint8 Vector_Str[][15] = 
{
  /******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
    "",                         //0
    "",
    "NonMaskable"               , /*!< 2 Non Maskable Interrupt                              */
    "HardFault"                 , /*!< 3 Hard Fault                                          */
    "MemManagement"             , /*!< 4 Cortex-M4 Memory Management Interrupt               */
    "BusFault"                  , /*!< 5 Cortex-M4 Bus Fault Interrupt                       */
    "UsageFault"                , /*!< 6 Cortex-M4 Usage Fault Interrupt                     */
    "",                         //7
    "",
    "",                         //9
    "",
    "SVCall"                    , /*!< 11 Cortex-M4 SV Call Interrupt                        */
    "DebugMonitor"              , /*!< 12 Cortex-M4 Debug Monitor Interrupt                  */
    "",
    "PendSV"                    , /*!< 14 Cortex-M4 Pend SV Interrupt                        */
    "SysTick"                   , /*!< 15 Cortex-M4 System Tick Interrupt                    */
    /******  Kinetis 60 specific Interrupt Numbers **********************************************************************/
    "DMA0"                      , // DMA Channel 0 Transfer Complete
    "DMA1"                      , // DMA Channel 1 Transfer Complete
    "DMA2"                      , // DMA Channel 2 Transfer Complete
    "DMA3"                      , // DMA Channel 3 Transfer Complete
    "DMA4"                      , // DMA Channel 4 Transfer Complete
    "DMA5"                      , // DMA Channel 5 Transfer Complete
    "DMA6"                      , // DMA Channel 6 Transfer Complete
    "DMA7"                      , // DMA Channel 7 Transfer Complete
    "DMA8"                      , // DMA Channel 8 Transfer Complete
    "DMA9"                      , // DMA Channel 9 Transfer Complete
    "DMA10"                     , // DMA Channel 10 Transfer Complete
    "DMA11"                     , // DMA Channel 11 Transfer Complete
    "DMA12"                     , // DMA Channel 12 Transfer Complete
    "DMA13"                     , // DMA Channel 13 Transfer Complete
    "DMA14"                     , // DMA Channel 14 Transfer Complete
    "DMA15"                     , // DMA Channel 15 Transfer Complete
    "DMA_Error"                 , // DMA Error Interrupt
    "MCM"                       , // Normal Interrupt
    "FTFL"                      , // FTFL Interrupt
    "Read_Collision"            , // Read Collision Interrupt
    "LVD_LVW"                   , // Low Voltage Detect, Low Voltage Warning
    "LLW"                       , // Low Leakage Wakeup
    "Watchdog"                  , // WDOG Interrupt
    "RNG"                       , // RNGB Interrupt
    "I2C0"                      , // I2C0 interrupt
    "I2C1"                      , // I2C1 interrupt
    "SPI0"                      , // SPI0 Interrupt
    "SPI1"                      , // SPI1 Interrupt
    "I2S0_Tx"                   , // I2S0_Tx Interrupt
    "I2S0_Rx"                   , // I2S0_Rx Interrupt
    "Reserved46"                , // 保留 interrupt 46
    "UART0_RX_TX"               , // UART0 Receive/Transmit interrupt
    "UART0_ERR"                 , // UART0 Error interrupt
    "UART1_RX_TX"               , // UART1 Receive/Transmit interrupt
    "UART1_ERR"                 , // UART1 Error interrupt
    "UART2_RX_TX"               , // UART2 Receive/Transmit interrupt
    "UART2_ERR"                 , // UART2 Error interrupt
    "UART3_RX_TX"               , // UART3 Receive/Transmit interrupt
    "UART3_ERR"                 , // UART3 Error interrupt
    "ADC0"                      , // ADC0 interrupt
    "CMP0"                      , // CMP0 interrupt
    "CMP1"                      , // CMP1 interrupt
    "FTM0"                      , // FTM0 fault, overflow and channels interrupt
    "FTM1"                      , // FTM1 fault, overflow and channels interrupt
    "FTM2"                      , // FTM2 fault, overflow and channels interrupt
    "CMT"                       , // CMT interrupt
    "RTC"                       , // RTC interrupt
    "RTC_Sec"                   , // RTC_Sec interrupt
    "PIT0"                      , // PIT timer channel 0 interrupt
    "PIT1"                      , // PIT timer channel 1 interrupt
    "PIT2"                      , // PIT timer channel 2 interrupt
    "PIT3"                      , // PIT timer channel 3 interrupt
    "PDB0"                      , // PDB0 Interrupt
    "USB0"                      , // USB0 interrupt
    "USBDCD"                    , // USBDCD Interrupt
    "Reserved71"                , // 保留 interrupt 71
    "DAC0"                      , // DAC0 interrupt
    "MCG"                       , // MCG Interrupt
    "LPTimer"                   , // LPTimer interrupt
    "PORTA"                     , // Port A interrupt
    "PORTB"                     , // Port B interrupt
    "PORTC"                     , // Port C interrupt
    "PORTD"                     , // Port D interrupt
    "PORTE"                     , // Port E interrupt
    "SWI"                       , // SWI interrupt
    "SPI2"                      , // SPI2 Interrupt
    "UART4_RX_TX"               , // UART4 Receive/Transmit interrupt
    "UART4_ERR"                 , // UART4 Error interrupt
    #if defined(MK66F18)
    "Reserved84"                , // 保留 interrupt 84
    "Reserved85"                , // 保留 interrupt 85
    #elif defined(MK64F12)
    "UART5_RX_TX"               , // UART5 Receive/Transmit interrupt
    "UART5_ERR"                 , // UART5 Error interrupt
    #endif
    "CMP2"                      , // CMP2 interrupt
    "FTM3"                      , // FTM3 fault, overflow and channels interrupt
    "DAC1"                      , // DAC1 interrupt
    "ADC1"                      , // ADC1 interrupt
    "I2C2"                      , // I2C2 interrupt
    "CAN0_OR_MB_buf"            , // CAN0 OR'd Message Buffers Interrupt
    "CAN0_Bus_Off"              , // CAN0 Bus Off Interrupt
    "CAN0_Error"                , // CAN0 Error Interrupt
    "CAN0_Tx_Warning"           , // CAN0 Tx Warning Interrupt
    "CAN0_Rx_Warning"           , // CAN0 Rx Warning Interrupt
    "CAN0_Wake_Up"              , // CAN0 Wake Up Interrupt
    "SDHC"                      , // SDHC Interrupt
    "ENET_1588_Timer"           , // Ethernet MAC IEEE 1588 Timer Interrupt
    "ENET_Transmit"             , // Ethernet MAC Transmit Interrupt
    "ENET_Receive"              , // Ethernet MAC Receive Interrupt
    "ENET_Error"                , // Ethernet MAC Error and miscelaneous Interrupt
    #if defined(MK66F18)
    "LPUART0"                   , // LPUART0 interrupt
    "TSI0"                      , // TSI0 Interrupt
    "TPM1"                      , // TPM1 fault, overflow and channels interrupt
    "TPM2"                      , // TPM2 fault, overflow and channels interrupt
    "USBHSDCD"                  , // USBHSDCD, USBHS Phy Interrupt
    "I2C3"                      , // I2C3 interrupt
    "CMP3"                      , // CMP3 interrupt
    "USBHS"                     , // USB high speed OTG interrupt
    "CAN1_OR_MB_buf"            , // CAN1 OR'd Message Buffers Interrupt
    "CAN1_Bus_Off"              , // CAN1 Bus Off Interrupt
    "CAN1_Error"                , // CAN1 Error Interrupt
    "CAN1_Tx_Warning"           , // CAN1 Tx Warning Interrupt
    "CAN1_Rx_Warning"           , // CAN1 Rx Warning Interrupt
    "CAN1_Wake_Up"              , // CAN1 Wake Up Interrupt
    #elif defined(MK64F12)
    "Reserved102"               , // 保留 interrupt 102
    "Reserved103"               , // 保留 interrupt 103
    "Reserved104"               , // 保留 interrupt 104
    "Reserved105"               , // 保留 interrupt 105
    "Reserved106"               , // 保留 interrupt 106
    "Reserved107"               , // 保留 interrupt 107
    "Reserved108"               , // 保留 interrupt 108
    "Reserved109"               , // 保留 interrupt 109
    "Reserved110"               , // 保留 interrupt 110
    "Reserved111"               , // 保留 interrupt 111
    "Reserved112"               , // 保留 interrupt 112
    "Reserved113"               , // 保留 interrupt 113
    "Reserved114"               , // 保留 interrupt 114
    "Reserved115"               , // 保留 interrupt 115
    #endif
};
#endif