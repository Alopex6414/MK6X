/*
 *     COPYRIGHT NOTICE
 *     Copyright(c) 2016, Alopex
 *     All rights reserved.
 *
 * @file       MK6X_Vectors.h
 * @brief      MK66FX1M0VLQ18/MK66FN2M0VLQ18/MK64FX512VLQ12/MK64FN1M0VLQ12
 * @author     Alopex
 * @version    v1.0
 * @date       2016-09-24
 */

#ifndef __MK6X_VECTORS_H__
#define __MK6X_VECTORS_H__

#include "Common.h"

/*
**Address     Vector IRQ   Source module   Source description
*/
#define VECTOR_000      (vector_entry)__BOOT_STACK_ADDRESS	  //ARM core        Initial Stack Pointer
#define VECTOR_001      Reset_Handler	// 0x0000_0004 1 -          ARM core        Initial Program Counter
#define VECTOR_002      default_isr     // 0x0000_0008 2 -          ARM core        Non-maskable Interrupt (NMI)
#define VECTOR_003      default_isr     // 0x0000_000C 3 -          ARM core        Hard Fault
#define VECTOR_004      default_isr     // 0x0000_0010 4 -          ARM core        MemManage Fault
#define VECTOR_005      default_isr     // 0x0000_0014 5 -          ARM core        Bus Fault
#define VECTOR_006      default_isr     // 0x0000_0018 6 -          ARM core        Usage Fault
#define VECTOR_007      default_isr     // 0x0000_001C 7 -
#define VECTOR_008      default_isr     // 0x0000_0020 8 -
#define VECTOR_009      default_isr     // 0x0000_0024 9 -
#define VECTOR_010      default_isr     // 0x0000_0028 10 -
#define VECTOR_011      default_isr     // 0x0000_002C 11 -         ARM core         Supervisor call (SVCall)
#define VECTOR_012      default_isr     // 0x0000_0030 12 -         ARM core         Debug Monitor
#define VECTOR_013      default_isr     // 0x0000_0034 13 -
#define VECTOR_014      default_isr     // 0x0000_0038 14 -         ARM core         Pendable request for system service (PendableSrvReq)
#define VECTOR_015      default_isr     // 0x0000_003C 15 -         ARM core         System tick timer (SysTick)
#define VECTOR_016      default_isr     // 0x0000_0040 16     0     DMA              DMA Channel 0,16 transfer complete(MK66 DMA16 Channel)
#define VECTOR_017      default_isr     // 0x0000_0044 17     1     DMA              DMA Channel 1,17 transfer complete(MK66 DMA17 Channel)
#define VECTOR_018      default_isr     // 0x0000_0048 18     2     DMA              DMA Channel 2,18 transfer complete(MK66 DMA18 Channel)
#define VECTOR_019      default_isr     // 0x0000_004C 19     3     DMA              DMA Channel 3,19 transfer complete(MK66 DMA19 Channel)
#define VECTOR_020      default_isr     // 0x0000_0050 20     4     DMA              DMA Channel 4,20 transfer complete(MK66 DMA20 Channel)
#define VECTOR_021      default_isr     // 0x0000_0054 21     5     DMA              DMA Channel 5,21 transfer complete(MK66 DMA21 Channel)
#define VECTOR_022      default_isr     // 0x0000_0058 22     6     DMA              DMA Channel 6,22 transfer complete(MK66 DMA22 Channel)
#define VECTOR_023      default_isr     // 0x0000_005C 23     7     DMA              DMA Channel 7,23 transfer complete(MK66 DMA23 Channel)
#define VECTOR_024      default_isr     // 0x0000_0060 24     8     DMA              DMA Channel 8,24 transfer complete(MK66 DMA24 Channel)
#define VECTOR_025      default_isr     // 0x0000_0064 25     9     DMA              DMA Channel 9,25 transfer complete(MK66 DMA25 Channel)
#define VECTOR_026      default_isr     // 0x0000_0068 26    10     DMA              DMA Channel 10,26 transfer complete(MK66 DMA26 Channel)
#define VECTOR_027      default_isr     // 0x0000_006C 27    11     DMA              DMA Channel 11,27 transfer complete(MK66 DMA27 Channel)
#define VECTOR_028      default_isr     // 0x0000_0070 28    12     DMA              DMA Channel 12,28 transfer complete(MK66 DMA28 Channel)
#define VECTOR_029      default_isr     // 0x0000_0074 29    13     DMA              DMA Channel 13,29 transfer complete(MK66 DMA29 Channel)
#define VECTOR_030      default_isr     // 0x0000_0078 30    14     DMA              DMA Channel 14,30 transfer complete(MK66 DMA30 Channel)
#define VECTOR_031      default_isr     // 0x0000_007C 31    15     DMA              DMA Channel 15,31 transfer complete(MK66 DMA31 Channel)
#define VECTOR_032      default_isr     // 0x0000_0080 32    16     DMA              DMA Error Interrupt Channels 0-15,16-31(MK66 DMA16~DMA31 Channel)
#define VECTOR_033      default_isr     // 0x0000_0084 33    17     MCM              Normal interrupt
#define VECTOR_034      default_isr     // 0x0000_0088 34    18     FTFE             Command complete interrupt
#define VECTOR_035      default_isr     // 0x0000_008C 35    19     Read Collision Interrupt
#define VECTOR_036      default_isr     // 0x0000_0090 36    20     Low Voltage Detect, Low Voltage Warning
#define VECTOR_037      default_isr     // 0x0000_0094 37    21     LLWU             Low Leakage Wakeup Unit
#define VECTOR_038      default_isr     // 0x0000_0098 38    22     WDOG  or EWM
#define VECTOR_039      default_isr     // 0x0000_009C 39    23	    RNG
#define VECTOR_040      default_isr     // 0x0000_00A0 40    24     I2C0
#define VECTOR_041      default_isr     // 0x0000_00A4 41    25     I2C1
#define VECTOR_042      default_isr     // 0x0000_00A8 42    26     SPI0             Single interrupt vector for all sources
#define VECTOR_043      default_isr     // 0x0000_00AC 43    27     SPI1             Single interrupt vector for all sources
#define VECTOR_044      default_isr     // 0x0000_00B0 44    28     I2S0             Transmit
#define VECTOR_045      default_isr     // 0x0000_00B4 45    29     I2S0             Receive
#define VECTOR_046      default_isr     // 0x0000_00B8 46    30     --               ��
#define VECTOR_047      default_isr     // 0x0000_00BC 47    31     UART0             Single interrupt vector for UART status sources
#define VECTOR_048      default_isr     // 0x0000_00C0 48    32     UART0             Single interrupt vector for UART error sources
#define VECTOR_049      default_isr     // 0x0000_00C4 49    33     UART1             Single interrupt vector for UART status sources
#define VECTOR_050      default_isr     // 0x0000_00C8 50    34     UART1             Single interrupt vector for UART error sources
#define VECTOR_051      default_isr     // 0x0000_00CC 51    35     UART2             Single interrupt vector for UART status sources
#define VECTOR_052      default_isr     // 0x0000_00D0 52    36     UART2             Single interrupt vector for UART error sources
#define VECTOR_053      default_isr     // 0x0000_00D4 53    37     UART3             Single interrupt vector for UART status sources
#define VECTOR_054      default_isr     // 0x0000_00D8 54    38     UART3             Single interrupt vector for UART error sources
#define VECTOR_055      default_isr     // 0x0000_00DC 55    39     ADC0
#define VECTOR_056      default_isr     // 0x0000_00E0 56    40     CMP0
#define VECTOR_057      default_isr     // 0x0000_00E4 57    41     CMP1
#define VECTOR_058      default_isr     // 0x0000_00E8 58    42     FTM0             Single interrupt vector for all sources
#define VECTOR_059      default_isr     // 0x0000_00EC 59    43     FTM1             Single interrupt vector for all sources
#define VECTOR_060      default_isr     // 0x0000_00F0 60    44     FTM2             Single interrupt vector for all sources
#define VECTOR_061      default_isr     // 0x0000_00F4 61    45     CMT
#define VECTOR_062      default_isr     // 0x0000_00F8 62    46     RTC              Alarm interrupt
#define VECTOR_063      default_isr     // 0x0000_00FC 63    47     RTC              Seconds interrupt
#define VECTOR_064      default_isr     // 0x0000_0100 64    48     PIT              Channel 0
#define VECTOR_065      default_isr     // 0x0000_0104 65    49     PIT              Channel 1
#define VECTOR_066      default_isr     // 0x0000_0108 66    50     PIT              Channel 2
#define VECTOR_067      default_isr     // 0x0000_010C 67    51     PIT              Channel 3
#define VECTOR_068      default_isr     // 0x0000_0110 68    52     PDB
#define VECTOR_069      default_isr     // 0x0000_0114 69    53     USBFS OTG
#define VECTOR_070      default_isr     // 0x0000_0118 70    54     USBFS Charger Detect
#define VECTOR_071      default_isr     // 0x0000_011C 71    55     --               ��
#define VECTOR_072      default_isr     // 0x0000_0120 72    56     DAC0
#define VECTOR_073      default_isr     // 0x0000_0124 73    57     MCG
#define VECTOR_074      default_isr     // 0x0000_0128 74    58     Low Power Timer
#define VECTOR_075      default_isr     // 0x0000_012C 75    59     Port control module    Pin detect (Port A)
#define VECTOR_076      default_isr     // 0x0000_0130 76    60     Port control module    Pin detect (Port B)
#define VECTOR_077      default_isr     // 0x0000_0134 77    61     Port control module    Pin detect (Port C)
#define VECTOR_078      default_isr     // 0x0000_0138 78    62     Port control module    Pin detect (Port D)
#define VECTOR_079      default_isr     // 0x0000_013C 79    63     Port control module    Pin detect (Port E)
#define VECTOR_080      default_isr     // 0x0000_0140 80    64     Software 	           Software interrupt4
#define VECTOR_081      default_isr     // 0x0000_0144 81    65     SPI2                   Single interrupt vector for all sources
#define VECTOR_082      default_isr     // 0x0000_0148 82    66     UART4                  Single interrupt vector for UART status sources
#define VECTOR_083      default_isr     // 0x0000_014C 83    67     UART4                  Single interrupt vector for UART error source
#define VECTOR_084      default_isr     // 0x0000_0150 84    68     --(UART5)              (MK60 & MK64 Particular Vector)
#define VECTOR_085      default_isr     // 0x0000_0154 85    69     --(UART5)              (MK60 & MK64 Particular Vector)
#define VECTOR_086      default_isr     // 0x0000_0158 86    70     CMP2
#define VECTOR_087      default_isr     // 0x0000_015C 87    71     FTM3
#define VECTOR_088      default_isr     // 0x0000_0160 88    72     DAC1
#define VECTOR_089      default_isr     // 0x0000_0164 89    73     ADC1
#define VECTOR_090      default_isr     // 0x0000_0168 90    74     I2C2
#define VECTOR_091      default_isr     // 0x0000_016C 91    75	    CAN0	           OR'ed Message buffer (0-15)
#define VECTOR_092      default_isr     // 0x0000_0170 92    76	    CAN0	           Bus Off
#define VECTOR_093      default_isr     // 0x0000_0174 93    77     CAN0		   Error
#define VECTOR_094      default_isr     // 0x0000_0178 94    78	    CAN0	           Transmit Warning
#define VECTOR_095      default_isr     // 0x0000_017C 95    79     CAN0                   Receive Warning
#define VECTOR_096      default_isr     // 0x0000_0180 96    80     CAN0                   Wake Up
#define VECTOR_097      default_isr     // 0x0000_0184 97    81     SDHC
#define VECTOR_098      default_isr     // 0x0000_0188 98    82     Ethernet MAC           IEEE 1588 Timer Interrupt
#define VECTOR_099      default_isr     // 0x0000_018C 99    83     Ethernet MAC 	       Transmit interrupt
#define VECTOR_100      default_isr     // 0x0000_0190 100   84     Ethernet MAC           Receive interrupt
#define VECTOR_101      default_isr     // 0x0000_0194 101   85     Ethernet MAC           Error and miscellaneous interrupt//MK60 & MK64 Just Have Vectors Above
#define VECTOR_102      default_isr     // 0x0000_0198 102   86     LPUART0	               Status and error
#define VECTOR_103      default_isr     // 0x0000_019C 103   87     TSI0
#define VECTOR_104      default_isr     // 0x0000_01A0 104   88     TPM1
#define VECTOR_105      default_isr     // 0x0000_01A4 105   89     TPM2
#define VECTOR_106      default_isr     // 0x0000_01A8 106   90     USBHS DCD or USBHS Phy   USBHS DCD and USBHS Phy modules share this interrupt
#define VECTOR_107      default_isr     // 0x0000_01AC 107   91     I2C3
#define VECTOR_108      default_isr     // 0x0000_01B0 108   92     CMP3
#define VECTOR_109      default_isr     // 0x0000_01B4 109   93     USBHS OTG
#define VECTOR_110      default_isr     // 0x0000_01B8 110   94     CAN1                    OR'ed Message buffer (0-15)
#define VECTOR_111      default_isr     // 0x0000_01BC 111   95     CAN1                    Bus Off
#define VECTOR_112      default_isr     // 0x0000_01C0 112   96     CAN1                    Error
#define VECTOR_113      default_isr     // 0x0000_01C4 113   97     CAN1                    Transmit Warning
#define VECTOR_114      default_isr     // 0x0000_01C8 114   98     CAN1                    Receive Warning
#define VECTOR_115      default_isr     // 0x0000_01CC 115   99     CAN1                    Wake Up
#define VECTOR_116      default_isr     // 
#define VECTOR_117      default_isr     // 
#define VECTOR_118      default_isr     // 
#define VECTOR_119      default_isr     // 
#define VECTOR_120      default_isr     // 
#define VECTOR_121      default_isr     // 
#define VECTOR_122      default_isr     // 
#define VECTOR_123      default_isr     // 
#define VECTOR_124      default_isr     // 
#define VECTOR_125      default_isr     // 
#define VECTOR_126      default_isr     // 
#define VECTOR_127      default_isr     // 
#define VECTOR_128      default_isr     // 
#define VECTOR_129      default_isr     // 
#define VECTOR_130      default_isr     // 
#define VECTOR_131      default_isr     // 
#define VECTOR_132      default_isr     // 
#define VECTOR_133      default_isr     // 
#define VECTOR_134      default_isr     // 
#define VECTOR_135      default_isr     // 
#define VECTOR_136      default_isr     // 
#define VECTOR_137      default_isr     // 
#define VECTOR_138      default_isr     // 
#define VECTOR_139      default_isr     // 
#define VECTOR_140      default_isr     // 
#define VECTOR_141      default_isr     // 
#define VECTOR_142      default_isr     // 
#define VECTOR_143      default_isr     // 
#define VECTOR_144      default_isr     // 
#define VECTOR_145      default_isr     // 
#define VECTOR_146      default_isr     // 
#define VECTOR_147      default_isr     // 
#define VECTOR_148      default_isr     // 
#define VECTOR_149      default_isr     // 
#define VECTOR_150      default_isr     // 
#define VECTOR_151      default_isr     // 
#define VECTOR_152      default_isr     // 
#define VECTOR_153      default_isr     // 
#define VECTOR_154      default_isr     // 
#define VECTOR_155      default_isr     // 
#define VECTOR_156      default_isr     // 
#define VECTOR_157      default_isr     // 
#define VECTOR_158      default_isr     // 
#define VECTOR_159      default_isr     // 
#define VECTOR_160      default_isr     // 
#define VECTOR_161      default_isr     // 
#define VECTOR_162      default_isr     // 
#define VECTOR_163      default_isr     // 
#define VECTOR_164      default_isr     // 
#define VECTOR_165      default_isr     // 
#define VECTOR_166      default_isr     // 
#define VECTOR_167      default_isr     // 
#define VECTOR_168      default_isr     // 
#define VECTOR_169      default_isr     // 
#define VECTOR_170      default_isr     // 
#define VECTOR_171      default_isr     // 
#define VECTOR_172      default_isr     // 
#define VECTOR_173      default_isr     // 
#define VECTOR_174      default_isr     // 
#define VECTOR_175      default_isr     // 
#define VECTOR_176      default_isr     // 
#define VECTOR_177      default_isr     // 
#define VECTOR_178      default_isr     // 
#define VECTOR_179      default_isr     // 
#define VECTOR_180      default_isr     // 
#define VECTOR_181      default_isr     // 
#define VECTOR_182      default_isr     // 
#define VECTOR_183      default_isr     // 
#define VECTOR_184      default_isr     // 
#define VECTOR_185      default_isr     // 
#define VECTOR_186      default_isr     // 
#define VECTOR_187      default_isr     // 
#define VECTOR_188      default_isr     // 
#define VECTOR_189      default_isr     // 
#define VECTOR_190      default_isr     // 
#define VECTOR_191      default_isr     // 
#define VECTOR_192      default_isr     // 
#define VECTOR_193      default_isr     // 
#define VECTOR_194      default_isr     // 
#define VECTOR_195      default_isr     // 
#define VECTOR_196      default_isr     // 
#define VECTOR_197      default_isr     // 
#define VECTOR_198      default_isr     // 
#define VECTOR_199      default_isr     // 
#define VECTOR_200      default_isr     // 
#define VECTOR_201      default_isr     // 
#define VECTOR_202      default_isr     // 
#define VECTOR_203      default_isr     // 
#define VECTOR_204      default_isr     // 
#define VECTOR_205      default_isr     // 
#define VECTOR_206      default_isr     // 
#define VECTOR_207      default_isr     // 
#define VECTOR_208      default_isr     // 
#define VECTOR_209      default_isr     // 
#define VECTOR_210      default_isr     // 
#define VECTOR_211      default_isr     // 
#define VECTOR_212      default_isr     // 
#define VECTOR_213      default_isr     // 
#define VECTOR_214      default_isr     // 
#define VECTOR_215      default_isr     // 
#define VECTOR_216      default_isr     // 
#define VECTOR_217      default_isr     // 
#define VECTOR_218      default_isr     // 
#define VECTOR_219      default_isr     // 
#define VECTOR_220      default_isr     // 
#define VECTOR_221      default_isr     // 
#define VECTOR_222      default_isr     // 
#define VECTOR_223      default_isr     // 
#define VECTOR_224      default_isr     // 
#define VECTOR_225      default_isr     // 
#define VECTOR_226      default_isr     // 
#define VECTOR_227      default_isr     // 
#define VECTOR_228      default_isr     // 
#define VECTOR_229      default_isr     // 
#define VECTOR_230      default_isr     // 
#define VECTOR_231      default_isr     // 
#define VECTOR_232      default_isr     // 
#define VECTOR_233      default_isr     // 
#define VECTOR_234      default_isr     // 
#define VECTOR_235      default_isr     // 
#define VECTOR_236      default_isr     // 
#define VECTOR_237      default_isr     // 
#define VECTOR_238      default_isr     // 
#define VECTOR_239      default_isr     // 
#define VECTOR_240      default_isr     // 
#define VECTOR_241      default_isr     // 
#define VECTOR_242      default_isr     // 
#define VECTOR_243      default_isr     // 
#define VECTOR_244      default_isr     // 
#define VECTOR_245      default_isr     // 
#define VECTOR_246      default_isr     // 
#define VECTOR_247      default_isr     // 
#define VECTOR_248      default_isr     // 
#define VECTOR_249      default_isr     // 
#define VECTOR_250      default_isr     // 
#define VECTOR_251      default_isr     // 
#define VECTOR_252      default_isr     // 
#define VECTOR_253      default_isr     // 
#define VECTOR_254      default_isr     // 
#define VECTOR_255      default_isr     //

/* Flash configuration field values below */

/* Please be careful when modifying any of
 * the values below as it can secure the
 * flash (possibly permanently).
 */
#define CONFIG_1        (vector_entry)0xffffffff 
#define CONFIG_2	(vector_entry)0xffffffff 
#define CONFIG_3	(vector_entry)0xffffffff
#define CONFIG_4	(vector_entry)0xfffffffe

/*
**variate declaration
*/
typedef void (*vector_entry)(void);             //�����ж�������ĺ�������

/*
**function declaration
*/
extern unsigned long __BOOT_STACK_ADDRESS[];    //����ջ��ַ����linker�ļ�(*.icf )���
extern void Reset_Handler (void);               //������λ�������� .s �ļ��ﶨ��
extern void default_isr(void);                  //����Ĭ���жϷ�����



#endif