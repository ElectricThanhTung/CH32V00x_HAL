
#ifndef __CH32V00x_H
#define __CH32V00x_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define __MPU_PRESENT                           0               /* Other CH32 devices does not provide an MPU */
#define __Vendor_SysTickConfig                  0               /* Set to 1 if different SysTick Config is used */

/**
 * @brief Internal High Speed oscillator (HSI) value.
 *        This value is used by the RCC HAL module to compute the system frequency
 *        (when HSI is used as system clock source, directly or through the PLL).
 */
#define HSI_VALUE                               (24000000UL)    /*!< Value of the Internal oscillator in Hz*/

/**
 * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
 *        This value is used by the RCC HAL module to compute the system frequency
 *        (when HSE is used as system clock source, directly or through the PLL).
 */
#ifndef HSE_VALUE
#define HSE_VALUE                               (24000000UL)    /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

/**
 * @brief External High Speed oscillator (HSE) Startup Timeout value.
 */
#ifndef HSE_STARTUP_TIMEOUT
#define HSE_STARTUP_TIMEOUT                     (0x2000U)       /* Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */

/* Interrupt Number Definition, according to the selected device */
typedef enum IRQn {
    /******  RISC-V Processor Exceptions Numbers ****************************************************/
    NonMaskableInt_IRQn = 2U,                   /* 2 Non Maskable Interrupt                         */
    EXC_IRQn            = 3U,                   /* 3 Exception Interrupt                            */
    SysTicK_IRQn        = 12U,                  /* 12 System timer Interrupt                        */
    Software_IRQn       = 14U,                  /* 14 software Interrupt                            */

    /******  RISC-V specific Interrupt Numbers ******************************************************/
    WWDG_IRQn           = 16U,                  /* Window WatchDog Interrupt                        */
    PVD_IRQn            = 17U,                  /* PVD through EXTI Line detection Interrupt        */
    FLASH_IRQn          = 18U,                  /* FLASH global Interrupt                           */
    RCC_IRQn            = 19U,                  /* RCC global Interrupt                             */
    EXTI7_0_IRQn        = 20U,                  /* External Line[7:0] Interrupts                    */
    AWU_IRQn            = 21U,                  /* AWU global Interrupt                             */
    DMA1_Channel1_IRQn  = 22U,                  /* DMA1 Channel 1 global Interrupt                  */
    DMA1_Channel2_IRQn  = 23U,                  /* DMA1 Channel 2 global Interrupt                  */
    DMA1_Channel3_IRQn  = 24U,                  /* DMA1 Channel 3 global Interrupt                  */
    DMA1_Channel4_IRQn  = 25U,                  /* DMA1 Channel 4 global Interrupt                  */
    DMA1_Channel5_IRQn  = 26U,                  /* DMA1 Channel 5 global Interrupt                  */
    DMA1_Channel6_IRQn  = 27U,                  /* DMA1 Channel 6 global Interrupt                  */
    DMA1_Channel7_IRQn  = 28U,                  /* DMA1 Channel 7 global Interrupt                  */
    ADC_IRQn            = 29U,                  /* ADC global Interrupt                             */
    I2C1_EV_IRQn        = 30U,                  /* I2C1 Event Interrupt                             */
    I2C1_ER_IRQn        = 31U,                  /* I2C1 Error Interrupt                             */
    USART1_IRQn         = 32U,                  /* USART1 global Interrupt                          */
    SPI1_IRQn           = 33U,                  /* SPI1 global Interrupt                            */
    TIM1_BRK_IRQn       = 34U,                  /* TIM1 Break Interrupt                             */
    TIM1_UP_IRQn        = 35U,                  /* TIM1 Update Interrupt                            */
    TIM1_TRG_COM_IRQn   = 36U,                  /* TIM1 Trigger and Commutation Interrupt           */
    TIM1_CC_IRQn        = 37U,                  /* TIM1 Capture Compare Interrupt                   */
    TIM2_IRQn           = 38U,                  /* TIM2 global Interrupt                            */
} IRQn_Type;

#define HardFault_IRQn    EXC_IRQn

#include "core_riscv.h"

/* Peripheral memory map */
#define FLASH_BASE                              ((uint32_t)0x08000000) /* FLASH base address in the alias region */
#define SRAM_BASE                               ((uint32_t)0x20000000) /* SRAM base address in the alias region */
#define PERIPH_BASE                             ((uint32_t)0x40000000) /* Peripheral base address in the alias region */

#define APB1PERIPH_BASE                         (PERIPH_BASE)
#define APB2PERIPH_BASE                         (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE                          (PERIPH_BASE + 0x20000)

#define TIM2_BASE                               (APB1PERIPH_BASE + 0x0000)
#define WWDG_BASE                               (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE                               (APB1PERIPH_BASE + 0x3000)
#define I2C1_BASE                               (APB1PERIPH_BASE + 0x5400)
#define PWR_BASE                                (APB1PERIPH_BASE + 0x7000)

#define AFIO_BASE                               (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE                               (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE                              (APB2PERIPH_BASE + 0x0800)
#define GPIOC_BASE                              (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE                              (APB2PERIPH_BASE + 0x1400)
#define ADC1_BASE                               (APB2PERIPH_BASE + 0x2400)
#define TIM1_BASE                               (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE                               (APB2PERIPH_BASE + 0x3000)
#define USART1_BASE                             (APB2PERIPH_BASE + 0x3800)

#define DMA1_BASE                               (AHBPERIPH_BASE + 0x0000)
#define DMA1_Channel1_BASE                      (AHBPERIPH_BASE + 0x0008)
#define DMA1_Channel2_BASE                      (AHBPERIPH_BASE + 0x001C)
#define DMA1_Channel3_BASE                      (AHBPERIPH_BASE + 0x0030)
#define DMA1_Channel4_BASE                      (AHBPERIPH_BASE + 0x0044)
#define DMA1_Channel5_BASE                      (AHBPERIPH_BASE + 0x0058)
#define DMA1_Channel6_BASE                      (AHBPERIPH_BASE + 0x006C)
#define DMA1_Channel7_BASE                      (AHBPERIPH_BASE + 0x0080)
#define RCC_BASE                                (AHBPERIPH_BASE + 0x1000)

#define FLASH_R_BASE                            (AHBPERIPH_BASE + 0x2000) /* Flash registers base address */
#define UOB_BASE                                ((uint32_t)0x1FFFF800)    /* Flash Option Bytes base address */
#define EXTEND_BASE                             ((uint32_t)0x40023800)

/******************************************************************************/
/*                    Peripheral Registers Bits Definition                    */
/******************************************************************************/
/******************************************************************************/
/*                        Analog to Digital Converter                         */
/******************************************************************************/
/******************  Bit definition for ADC_STATR register  *******************/
#define ADC_STATR_AWD_Pos                       (0U)
#define ADC_STATR_AWD_Msk                       (0x01UL << ADC_STATR_AWD_Pos)
#define ADC_STATR_AWD                           ADC_STATR_AWD_Msk
#define ADC_STATR_EOC_Pos                       (1U)
#define ADC_STATR_EOC_Msk                       (0x01UL << ADC_STATR_EOC_Pos)
#define ADC_STATR_EOC                           ADC_STATR_EOC_Msk
#define ADC_STATR_JEOC_Pos                      (2U)
#define ADC_STATR_JEOC_Msk                      (0x01UL << ADC_STATR_JEOC_Pos)
#define ADC_STATR_JEOC                          ADC_STATR_JEOC_Msk
#define ADC_STATR_JSTRT_Pos                     (3U)
#define ADC_STATR_JSTRT_Msk                     (0x01UL << ADC_STATR_JSTRT_Pos)
#define ADC_STATR_JSTRT                         ADC_STATR_JSTRT_Msk
#define ADC_STATR_STRT_Pos                      (4U)
#define ADC_STATR_STRT_Msk                      (0x01UL << ADC_STATR_STRT_Pos)
#define ADC_STATR_STRT                          ADC_STATR_STRT_Msk

/******************  Bit definition for ADC_CTLR1 register  *******************/
#define ADC_CTLR1_AWDCH_Pos                     (0U)
#define ADC_CTLR1_AWDCH_Msk                     (0x1FUL << ADC_CTLR1_AWDCH_Pos)
#define ADC_CTLR1_AWDCH                         ADC_CTLR1_AWDCH_Msk
#define ADC_CTLR1_EOCIE_Pos                     (5U)
#define ADC_CTLR1_EOCIE_Msk                     (0x01UL << ADC_CTLR1_EOCIE_Pos)
#define ADC_CTLR1_EOCIE                         ADC_CTLR1_EOCIE_Msk
#define ADC_CTLR1_AWDIE_Pos                     (6U)
#define ADC_CTLR1_AWDIE_Msk                     (0x01UL << ADC_CTLR1_AWDIE_Pos)
#define ADC_CTLR1_AWDIE                         ADC_CTLR1_AWDIE_Msk
#define ADC_CTLR1_JEOCIE_Pos                    (7U)
#define ADC_CTLR1_JEOCIE_Msk                    (0x01UL << ADC_CTLR1_JEOCIE_Pos)
#define ADC_CTLR1_JEOCIE                        ADC_CTLR1_JEOCIE_Msk
#define ADC_CTLR1_SCAN_Pos                      (8U)
#define ADC_CTLR1_SCAN_Msk                      (0x01UL << ADC_CTLR1_SCAN_Pos)
#define ADC_CTLR1_SCAN                          ADC_CTLR1_SCAN_Msk
#define ADC_CTLR1_AWDSGL_Pos                    (9U)
#define ADC_CTLR1_AWDSGL_Msk                    (0x01UL << ADC_CTLR1_AWDSGL_Pos)
#define ADC_CTLR1_AWDSGL                        ADC_CTLR1_AWDSGL_Msk
#define ADC_CTLR1_JAUTO_Pos                     (10U)
#define ADC_CTLR1_JAUTO_Msk                     (0x01UL << ADC_CTLR1_JAUTO_Pos)
#define ADC_CTLR1_JAUTO                         ADC_CTLR1_JAUTO_Msk
#define ADC_CTLR1_DISCEN_Pos                    (11U)
#define ADC_CTLR1_DISCEN_Msk                    (0x01UL << ADC_CTLR1_DISCEN_Pos)
#define ADC_CTLR1_DISCEN                        ADC_CTLR1_DISCEN_Msk
#define ADC_CTLR1_JDISCEN_Pos                   (12U)
#define ADC_CTLR1_JDISCEN_Msk                   (0x01UL << ADC_CTLR1_JDISCEN_Pos)
#define ADC_CTLR1_JDISCEN                       ADC_CTLR1_JDISCEN_Msk
#define ADC_CTLR1_DISCNUM_Pos                   (13U)
#define ADC_CTLR1_DISCNUM_Msk                   (0x07UL << ADC_CTLR1_DISCNUM_Pos)
#define ADC_CTLR1_DISCNUM                       ADC_CTLR1_DISCNUM_Msk
#define ADC_CTLR1_JAWDEN_Pos                    (22U)
#define ADC_CTLR1_JAWDEN_Msk                    (0x01UL << ADC_CTLR1_JAWDEN_Pos)
#define ADC_CTLR1_JAWDEN                        ADC_CTLR1_JAWDEN_Msk
#define ADC_CTLR1_AWDEN_Pos                     (23U)
#define ADC_CTLR1_AWDEN_Msk                     (0x01UL << ADC_CTLR1_AWDEN_Pos)
#define ADC_CTLR1_AWDEN                         ADC_CTLR1_AWDEN_Msk
#define ADC_CTLR1_CALVOL_Pos                    (25U)
#define ADC_CTLR1_CALVOL_Msk                    (0x03 << ADC_CTLR1_CALVOL_Pos)
#define ADC_CTLR1_CALVOL                        ADC_CTLR1_CALVOL_Msk

/******************  Bit definition for ADC_CTLR2 register  *******************/
#define ADC_CTLR2_ADON_Pos                      (0U)
#define ADC_CTLR2_ADON_Msk                      (0x01UL << ADC_CTLR2_ADON_Pos)
#define ADC_CTLR2_ADON                          ADC_CTLR2_ADON_Msk
#define ADC_CTLR2_CONT_Pos                      (1U)
#define ADC_CTLR2_CONT_Msk                      (0x01UL << ADC_CTLR2_CONT_Pos)
#define ADC_CTLR2_CONT                          ADC_CTLR2_CONT_Msk
#define ADC_CTLR2_CAL_Pos                       (2U)
#define ADC_CTLR2_CAL_Msk                       (0x01UL << ADC_CTLR2_CAL_Pos)
#define ADC_CTLR2_CAL                           ADC_CTLR2_CAL_Msk
#define ADC_CTLR2_RSTCAL_Pos                    (3U)
#define ADC_CTLR2_RSTCAL_Msk                    (0x01UL << ADC_CTLR2_RSTCAL_Pos)
#define ADC_CTLR2_RSTCAL                        ADC_CTLR2_RSTCAL_Msk
#define ADC_CTLR2_DMA_Pos                       (8U)
#define ADC_CTLR2_DMA_Msk                       (0x01UL << ADC_CTLR2_DMA_Pos)
#define ADC_CTLR2_DMA                           ADC_CTLR2_DMA_Msk
#define ADC_CTLR2_ALIGN_Pos                     (11U)
#define ADC_CTLR2_ALIGN_Msk                     (0x01UL << ADC_CTLR2_ALIGN_Pos)
#define ADC_CTLR2_ALIGN                         ADC_CTLR2_ALIGN_Msk
#define ADC_CTLR2_JEXTSEL_Pos                   (12U)
#define ADC_CTLR2_JEXTSEL_Msk                   (0x07UL << ADC_CTLR2_JEXTSEL_Pos)
#define ADC_CTLR2_JEXTSEL                       ADC_CTLR2_JEXTSEL_Msk
#define ADC_CTLR2_JEXTTRIG_Pos                  (15U)
#define ADC_CTLR2_JEXTTRIG_Msk                  (0x01UL << ADC_CTLR2_JEXTTRIG_Pos)
#define ADC_CTLR2_JEXTTRIG                      ADC_CTLR2_JEXTTRIG_Msk
#define ADC_CTLR2_EXTSEL_Pos                    (17U)
#define ADC_CTLR2_EXTSEL_Msk                    (0x07UL << ADC_CTLR2_EXTSEL_Pos)
#define ADC_CTLR2_EXTSEL                        ADC_CTLR2_EXTSEL_Msk
#define ADC_CTLR2_EXTTRIG_Pos                   (20U)
#define ADC_CTLR2_EXTTRIG_Msk                   (0x01UL << ADC_CTLR2_EXTTRIG_Pos)
#define ADC_CTLR2_EXTTRIG                       ADC_CTLR2_EXTTRIG_Msk
#define ADC_CTLR2_JSWSTART_Pos                  (21U)
#define ADC_CTLR2_JSWSTART_Msk                  (0x01UL << ADC_CTLR2_JSWSTART_Pos)
#define ADC_CTLR2_JSWSTART                      ADC_CTLR2_JSWSTART_Msk
#define ADC_CTLR2_SWSTART_Pos                   (22U)
#define ADC_CTLR2_SWSTART_Msk                   (0x01UL << ADC_CTLR2_SWSTART_Pos)
#define ADC_CTLR2_SWSTART                       ADC_CTLR2_SWSTART_Msk

/******************  Bit definition for ADC_SAMPTR1 register  *****************/
#define ADC_SAMPTR1_SMP10_Pos                   (0U)
#define ADC_SAMPTR1_SMP10_Msk                   (0x07UL << ADC_SAMPTR1_SMP10_Pos)
#define ADC_SAMPTR1_SMP10                       ADC_SAMPTR1_SMP10_Msk
#define ADC_SAMPTR1_SMP11_Pos                   (3U)
#define ADC_SAMPTR1_SMP11_Msk                   (0x07UL << ADC_SAMPTR1_SMP11_Pos)
#define ADC_SAMPTR1_SMP11                       ADC_SAMPTR1_SMP11_Msk
#define ADC_SAMPTR1_SMP12_Pos                   (6U)
#define ADC_SAMPTR1_SMP12_Msk                   (0x07UL << ADC_SAMPTR1_SMP12_Pos)
#define ADC_SAMPTR1_SMP12                       ADC_SAMPTR1_SMP12_Msk
#define ADC_SAMPTR1_SMP13_Pos                   (9U)
#define ADC_SAMPTR1_SMP13_Msk                   (0x07UL << ADC_SAMPTR1_SMP13_Pos)
#define ADC_SAMPTR1_SMP13                       ADC_SAMPTR1_SMP13_Msk
#define ADC_SAMPTR1_SMP14_Pos                   (12U)
#define ADC_SAMPTR1_SMP14_Msk                   (0x07UL << ADC_SAMPTR1_SMP14_Pos)
#define ADC_SAMPTR1_SMP14                       ADC_SAMPTR1_SMP14_Msk
#define ADC_SAMPTR1_SMP15_Pos                   (15U)
#define ADC_SAMPTR1_SMP15_Msk                   (0x07UL << ADC_SAMPTR1_SMP15_Pos)
#define ADC_SAMPTR1_SMP15                       ADC_SAMPTR1_SMP15_Msk

/******************  Bit definition for ADC_SAMPTR2 register  *****************/
#define ADC_SAMPTR2_SMP0_Pos                    (0U)
#define ADC_SAMPTR2_SMP0_Msk                    (0x07UL << ADC_SAMPTR2_SMP0_Pos)
#define ADC_SAMPTR2_SMP0                        ADC_SAMPTR2_SMP0_Msk
#define ADC_SAMPTR2_SMP1_Pos                    (3U)
#define ADC_SAMPTR2_SMP1_Msk                    (0x07UL << ADC_SAMPTR2_SMP1_Pos)
#define ADC_SAMPTR2_SMP1                        ADC_SAMPTR2_SMP1_Msk
#define ADC_SAMPTR2_SMP2_Pos                    (6U)
#define ADC_SAMPTR2_SMP2_Msk                    (0x07UL << ADC_SAMPTR2_SMP2_Pos)
#define ADC_SAMPTR2_SMP2                        ADC_SAMPTR2_SMP2_Msk
#define ADC_SAMPTR2_SMP3_Pos                    (9U)
#define ADC_SAMPTR2_SMP3_Msk                    (0x07UL << ADC_SAMPTR2_SMP3_Pos)
#define ADC_SAMPTR2_SMP3                        ADC_SAMPTR2_SMP3_Msk
#define ADC_SAMPTR2_SMP4_Pos                    (12U)
#define ADC_SAMPTR2_SMP4_Msk                    (0x07UL << ADC_SAMPTR2_SMP4_Pos)
#define ADC_SAMPTR2_SMP4                        ADC_SAMPTR2_SMP4_Msk
#define ADC_SAMPTR2_SMP5_Pos                    (15U)
#define ADC_SAMPTR2_SMP5_Msk                    (0x07UL << ADC_SAMPTR2_SMP5_Pos)
#define ADC_SAMPTR2_SMP5                        ADC_SAMPTR2_SMP5_Msk
#define ADC_SAMPTR2_SMP6_Pos                    (18U)
#define ADC_SAMPTR2_SMP6_Msk                    (0x07UL << ADC_SAMPTR2_SMP6_Pos)
#define ADC_SAMPTR2_SMP6                        ADC_SAMPTR2_SMP6_Msk
#define ADC_SAMPTR2_SMP7_Pos                    (21U)
#define ADC_SAMPTR2_SMP7_Msk                    (0x07UL << ADC_SAMPTR2_SMP7_Pos)
#define ADC_SAMPTR2_SMP7                        ADC_SAMPTR2_SMP7_Msk
#define ADC_SAMPTR2_SMP8_Pos                    (24U)
#define ADC_SAMPTR2_SMP8_Msk                    (0x07UL << ADC_SAMPTR2_SMP8_Pos)
#define ADC_SAMPTR2_SMP8                        ADC_SAMPTR2_SMP8_Msk
#define ADC_SAMPTR2_SMP9_Pos                    (27U)
#define ADC_SAMPTR2_SMP9_Msk                    (0x07UL << ADC_SAMPTR2_SMP9_Pos)
#define ADC_SAMPTR2_SMP9                        ADC_SAMPTR2_SMP9_Msk

/******************  Bit definition for ADC_IOFR1 register  *******************/
#define ADC_IOFR1_JOFFSET1_Pos                  (0U)
#define ADC_IOFR1_JOFFSET1_Msk                  (0x03FFUL << ADC_IOFR1_JOFFSET1_Pos)
#define ADC_IOFR1_JOFFSET1                      ADC_IOFR1_JOFFSET1_Msk

/******************  Bit definition for ADC_IOFR2 register  *******************/
#define ADC_IOFR2_JOFFSET2_Pos                  (0U)
#define ADC_IOFR2_JOFFSET2_Msk                  (0x03FFUL << ADC_IOFR2_JOFFSET2_Pos)
#define ADC_IOFR2_JOFFSET2                      ADC_IOFR2_JOFFSET2_Msk

/******************  Bit definition for ADC_IOFR3 register  *******************/
#define ADC_IOFR3_JOFFSET3_Pos                  (0U)
#define ADC_IOFR3_JOFFSET3_Msk                  (0x03FFUL << ADC_IOFR3_JOFFSET3_Pos)
#define ADC_IOFR3_JOFFSET3                      ADC_IOFR3_JOFFSET3_Msk

/******************  Bit definition for ADC_IOFR4 register  *******************/
#define ADC_IOFR4_JOFFSET4_Pos                  (0U)
#define ADC_IOFR4_JOFFSET4_Msk                  (0x03FFUL << ADC_IOFR4_JOFFSET4_Pos)
#define ADC_IOFR4_JOFFSET4                      ADC_IOFR4_JOFFSET4_Msk

/******************  Bit definition for ADC_WDHTR register  *******************/
#define ADC_WDHTR_HT_Pos                        (0U)
#define ADC_WDHTR_HT_Msk                        (0x03FFUL << ADC_WDHTR_HT_Pos)
#define ADC_WDHTR_HT                            ADC_WDHTR_HT_Msk

/******************  Bit definition for ADC_WDLTR register  *******************/
#define ADC_WDLTR_LT_Pos                        (0U)
#define ADC_WDLTR_LT_Msk                        (0x03FFUL << ADC_WDLTR_LT_Pos)
#define ADC_WDLTR_LT                            ADC_WDLTR_LT_Msk

/******************  Bit definition for ADC_RSQR1 register  *******************/
#define ADC_RSQR1_SQ13_Pos                      (0U)
#define ADC_RSQR1_SQ13_Msk                      (0x1FUL << ADC_RSQR1_SQ13_Pos)
#define ADC_RSQR1_SQ13                          ADC_RSQR1_SQ13_Msk
#define ADC_RSQR1_SQ14_Pos                      (5U)
#define ADC_RSQR1_SQ14_Msk                      (0x1FUL << ADC_RSQR1_SQ14_Pos)
#define ADC_RSQR1_SQ14                          ADC_RSQR1_SQ14_Msk
#define ADC_RSQR1_SQ15_Pos                      (10U)
#define ADC_RSQR1_SQ15_Msk                      (0x1FUL << ADC_RSQR1_SQ15_Pos)
#define ADC_RSQR1_SQ15                          ADC_RSQR1_SQ15_Msk
#define ADC_RSQR1_SQ16_Pos                      (15U)
#define ADC_RSQR1_SQ16_Msk                      (0x1FUL << ADC_RSQR1_SQ16_Pos)
#define ADC_RSQR1_SQ16                          ADC_RSQR1_SQ16_Msk
#define ADC_RSQR1_L_Pos                         (20U)
#define ADC_RSQR1_L_Msk                         (0x0FUL << ADC_RSQR1_L_Pos)
#define ADC_RSQR1_L                             ADC_RSQR1_L_Msk

/******************  Bit definition for ADC_RSQR2 register  *******************/
#define ADC_RSQR2_SQ7_Pos                       (0U)
#define ADC_RSQR2_SQ7_Msk                       (0x1FUL << ADC_RSQR2_SQ7_Pos)
#define ADC_RSQR2_SQ7                           ADC_RSQR2_SQ7_Msk
#define ADC_RSQR2_SQ8_Pos                       (5U)
#define ADC_RSQR2_SQ8_Msk                       (0x1FUL << ADC_RSQR2_SQ8_Pos)
#define ADC_RSQR2_SQ8                           ADC_RSQR2_SQ8_Msk
#define ADC_RSQR2_SQ9_Pos                       (10U)
#define ADC_RSQR2_SQ9_Msk                       (0x1FUL << ADC_RSQR2_SQ9_Pos)
#define ADC_RSQR2_SQ9                           ADC_RSQR2_SQ9_Msk
#define ADC_RSQR2_SQ10_Pos                      (15U)
#define ADC_RSQR2_SQ10_Msk                      (0x1FUL << ADC_RSQR2_SQ10_Pos)
#define ADC_RSQR2_SQ10                          ADC_RSQR2_SQ10_Msk
#define ADC_RSQR2_SQ11_Pos                      (20U)
#define ADC_RSQR2_SQ11_Msk                      (0x1FUL << ADC_RSQR2_SQ11_Pos)
#define ADC_RSQR2_SQ11                          ADC_RSQR2_SQ11_Msk
#define ADC_RSQR2_SQ12_Pos                      (25U)
#define ADC_RSQR2_SQ12_Msk                      (0x1FUL << ADC_RSQR2_SQ12_Pos)
#define ADC_RSQR2_SQ12                          ADC_RSQR2_SQ12_Msk

/******************  Bit definition for ADC_RSQR3 register  *******************/
#define ADC_RSQR3_SQ1_Pos                       (0U)
#define ADC_RSQR3_SQ1_Msk                       (0x1FUL << ADC_RSQR3_SQ1_Pos)
#define ADC_RSQR3_SQ1                           ADC_RSQR3_SQ1_Msk
#define ADC_RSQR3_SQ2_Pos                       (5U)
#define ADC_RSQR3_SQ2_Msk                       (0x1FUL << ADC_RSQR3_SQ2_Pos)
#define ADC_RSQR3_SQ2                           ADC_RSQR3_SQ2_Msk
#define ADC_RSQR3_SQ3_Pos                       (10U)
#define ADC_RSQR3_SQ3_Msk                       (0x1FUL << ADC_RSQR3_SQ3_Pos)
#define ADC_RSQR3_SQ3                           ADC_RSQR3_SQ3_Msk
#define ADC_RSQR3_SQ4_Pos                       (15U)
#define ADC_RSQR3_SQ4_Msk                       (0x1FUL << ADC_RSQR3_SQ4_Pos)
#define ADC_RSQR3_SQ4                           ADC_RSQR3_SQ4_Msk
#define ADC_RSQR3_SQ5_Pos                       (20U)
#define ADC_RSQR3_SQ5_Msk                       (0x1FUL << ADC_RSQR3_SQ5_Pos)
#define ADC_RSQR3_SQ5                           ADC_RSQR3_SQ5_Msk
#define ADC_RSQR3_SQ6_Pos                       (25U)
#define ADC_RSQR3_SQ6_Msk                       (0x1FUL << ADC_RSQR3_SQ6_Pos)
#define ADC_RSQR3_SQ6                           ADC_RSQR3_SQ6_Msk

/******************  Bit definition for ADC_ISQR register  ********************/
#define ADC_ISQR_JSQ1_Pos                       (0U)
#define ADC_ISQR_JSQ1_Msk                       (0x1F << ADC_ISQR_JSQ1_Pos)
#define ADC_ISQR_JSQ1                           ADC_ISQR_JSQ1_Msk
#define ADC_ISQR_JSQ2_Pos                       (5U)
#define ADC_ISQR_JSQ2_Msk                       (0x1F << ADC_ISQR_JSQ2_Pos)
#define ADC_ISQR_JSQ2                           ADC_ISQR_JSQ2_Msk
#define ADC_ISQR_JSQ3_Pos                       (10U)
#define ADC_ISQR_JSQ3_Msk                       (0x1F << ADC_ISQR_JSQ3_Pos)
#define ADC_ISQR_JSQ3                           ADC_ISQR_JSQ3_Msk
#define ADC_ISQR_JSQ4_Pos                       (15U)
#define ADC_ISQR_JSQ4_Msk                       (0x1F << ADC_ISQR_JSQ4_Pos)
#define ADC_ISQR_JSQ4                           ADC_ISQR_JSQ4_Msk
#define ADC_ISQR_JL_Pos                         (20U)
#define ADC_ISQR_JL_Msk                         (0x03UL << ADC_ISQR_JL_Pos)
#define ADC_ISQR_JL                             ADC_ISQR_JL_Msk

/******************  Bit definition for ADC_IDATAR1 register  *****************/
#define ADC_IDATAR1_IDATA_Pos                   (0U)
#define ADC_IDATAR1_IDATA_Msk                   (0xFFFFUL << ADC_IDATAR1_IDATA_Pos)
#define ADC_IDATAR1_IDATA                       ADC_IDATAR1_IDATA_Msk

/******************  Bit definition for ADC_IDATAR2 register  *****************/
#define ADC_IDATAR2_IDATA_Pos                   (0U)
#define ADC_IDATAR2_IDATA_Msk                   (0xFFFFUL << ADC_IDATAR2_IDATA_Pos)
#define ADC_IDATAR2_IDATA                       ADC_IDATAR2_IDATA_Msk

/******************  Bit definition for ADC_IDATAR3 register  *****************/
#define ADC_IDATAR3_IDATA_Pos                   (0U)
#define ADC_IDATAR3_IDATA_Msk                   (0xFFFFUL << ADC_IDATAR3_IDATA_Pos)
#define ADC_IDATAR3_IDATA                       ADC_IDATAR3_IDATA_Msk

/******************  Bit definition for ADC_IDATAR4 register  *****************/
#define ADC_IDATAR4_IDATA_Pos                   (0U)
#define ADC_IDATAR4_IDATA_Msk                   (0xFFFFUL << ADC_IDATAR4_IDATA_Pos)
#define ADC_IDATAR4_IDATA                       ADC_IDATAR4_IDATA_Msk

/******************  Bit definition for ADC_RDATAR register  ******************/
#define ADC_RDATAR_DATA_Pos                     (0U)
#define ADC_RDATAR_DATA_Msk                     (0xFFFFFFFFUL << ADC_RDATAR_DATA_Pos)
#define ADC_RDATAR_DATA                         ADC_RDATAR_DATA_Msk

/******************  Bit definition for ADC_DLYR register  ********************/
#define ADC_DLYR_DLYVLU_Pos                     (0U)
#define ADC_DLYR_DLYVLU_Msk                     (0x01FFUL << ADC_DLYR_DLYVLU_Pos)
#define ADC_DLYR_DLYVLU                         ADC_DLYR_DLYVLU_Msk
#define ADC_DLYR_DLYSRC_Pos                     (9U)
#define ADC_DLYR_DLYSRC_Msk                     (0x01UL << ADC_DLYR_DLYSRC_Pos)
#define ADC_DLYR_DLYSRC                         ADC_DLYR_DLYSRC_Msk

/******************************************************************************/
/*                               DMA Controller                               */
/******************************************************************************/
/******************  Bit definition for DMA_INTFR register  *******************/
#define DMA_INTFR_GIF1_Pos                      (0U)
#define DMA_INTFR_GIF1_Msk                      (0x01UL << DMA_INTFR_GIF1_Pos)
#define DMA_INTFR_GIF1                          DMA_INTFR_GIF1_Msk
#define DMA_INTFR_TCIF1_Pos                     (1U)
#define DMA_INTFR_TCIF1_Msk                     (0x01UL << DMA_INTFR_TCIF1_Pos)
#define DMA_INTFR_TCIF1                         DMA_INTFR_TCIF1_Msk
#define DMA_INTFR_HTIF1_Pos                     (2U)
#define DMA_INTFR_HTIF1_Msk                     (0x01UL << DMA_INTFR_HTIF1_Pos)
#define DMA_INTFR_HTIF1                         DMA_INTFR_HTIF1_Msk
#define DMA_INTFR_TEIF1_Pos                     (3U)
#define DMA_INTFR_TEIF1_Msk                     (0x01UL << DMA_INTFR_TEIF1_Pos)
#define DMA_INTFR_TEIF1                         DMA_INTFR_TEIF1_Msk
#define DMA_INTFR_GIF2_Pos                      (4U)
#define DMA_INTFR_GIF2_Msk                      (0x01UL << DMA_INTFR_GIF2_Pos)
#define DMA_INTFR_GIF2                          DMA_INTFR_GIF2_Msk
#define DMA_INTFR_TCIF2_Pos                     (5U)
#define DMA_INTFR_TCIF2_Msk                     (0x01UL << DMA_INTFR_TCIF2_Pos)
#define DMA_INTFR_TCIF2                         DMA_INTFR_TCIF2_Msk
#define DMA_INTFR_HTIF2_Pos                     (6U)
#define DMA_INTFR_HTIF2_Msk                     (0x01UL << DMA_INTFR_HTIF2_Pos)
#define DMA_INTFR_HTIF2                         DMA_INTFR_HTIF2_Msk
#define DMA_INTFR_TEIF2_Pos                     (7U)
#define DMA_INTFR_TEIF2_Msk                     (0x01UL << DMA_INTFR_TEIF2_Pos)
#define DMA_INTFR_TEIF2                         DMA_INTFR_TEIF2_Msk
#define DMA_INTFR_GIF3_Pos                      (8U)
#define DMA_INTFR_GIF3_Msk                      (0x01UL << DMA_INTFR_GIF3_Pos)
#define DMA_INTFR_GIF3                          DMA_INTFR_GIF3_Msk
#define DMA_INTFR_TCIF3_Pos                     (9U)
#define DMA_INTFR_TCIF3_Msk                     (0x01UL << DMA_INTFR_TCIF3_Pos)
#define DMA_INTFR_TCIF3                         DMA_INTFR_TCIF3_Msk
#define DMA_INTFR_HTIF3_Pos                     (10U)
#define DMA_INTFR_HTIF3_Msk                     (0x01UL << DMA_INTFR_HTIF3_Pos)
#define DMA_INTFR_HTIF3                         DMA_INTFR_HTIF3_Msk
#define DMA_INTFR_TEIF3_Pos                     (11U)
#define DMA_INTFR_TEIF3_Msk                     (0x01UL << DMA_INTFR_TEIF3_Pos)
#define DMA_INTFR_TEIF3                         DMA_INTFR_TEIF3_Msk
#define DMA_INTFR_GIF4_Pos                      (12U)
#define DMA_INTFR_GIF4_Msk                      (0x01UL << DMA_INTFR_GIF4_Pos)
#define DMA_INTFR_GIF4                          DMA_INTFR_GIF4_Msk
#define DMA_INTFR_TCIF4_Pos                     (13U)
#define DMA_INTFR_TCIF4_Msk                     (0x01UL << DMA_INTFR_TCIF4_Pos)
#define DMA_INTFR_TCIF4                         DMA_INTFR_TCIF4_Msk
#define DMA_INTFR_HTIF4_Pos                     (14U)
#define DMA_INTFR_HTIF4_Msk                     (0x01UL << DMA_INTFR_HTIF4_Pos)
#define DMA_INTFR_HTIF4                         DMA_INTFR_HTIF4_Msk
#define DMA_INTFR_TEIF4_Pos                     (15U)
#define DMA_INTFR_TEIF4_Msk                     (0x01UL << DMA_INTFR_TEIF4_Pos)
#define DMA_INTFR_TEIF4                         DMA_INTFR_TEIF4_Msk
#define DMA_INTFR_GIF5_Pos                      (16U)
#define DMA_INTFR_GIF5_Msk                      (0x01UL << DMA_INTFR_GIF5_Pos)
#define DMA_INTFR_GIF5                          DMA_INTFR_GIF5_Msk
#define DMA_INTFR_TCIF5_Pos                     (17U)
#define DMA_INTFR_TCIF5_Msk                     (0x01UL << DMA_INTFR_TCIF5_Pos)
#define DMA_INTFR_TCIF5                         DMA_INTFR_TCIF5_Msk
#define DMA_INTFR_HTIF5_Pos                     (18U)
#define DMA_INTFR_HTIF5_Msk                     (0x01UL << DMA_INTFR_HTIF5_Pos)
#define DMA_INTFR_HTIF5                         DMA_INTFR_HTIF5_Msk
#define DMA_INTFR_TEIF5_Pos                     (19U)
#define DMA_INTFR_TEIF5_Msk                     (0x01UL << DMA_INTFR_TEIF5_Pos)
#define DMA_INTFR_TEIF5                         DMA_INTFR_TEIF5_Msk
#define DMA_INTFR_GIF6_Pos                      (20U)
#define DMA_INTFR_GIF6_Msk                      (0x01UL << DMA_INTFR_GIF6_Pos)
#define DMA_INTFR_GIF6                          DMA_INTFR_GIF6_Msk
#define DMA_INTFR_TCIF6_Pos                     (21U)
#define DMA_INTFR_TCIF6_Msk                     (0x01UL << DMA_INTFR_TCIF6_Pos)
#define DMA_INTFR_TCIF6                         DMA_INTFR_TCIF6_Msk
#define DMA_INTFR_HTIF6_Pos                     (22U)
#define DMA_INTFR_HTIF6_Msk                     (0x01UL << DMA_INTFR_HTIF6_Pos)
#define DMA_INTFR_HTIF6                         DMA_INTFR_HTIF6_Msk
#define DMA_INTFR_TEIF6_Pos                     (23U)
#define DMA_INTFR_TEIF6_Msk                     (0x01UL << DMA_INTFR_TEIF6_Pos)
#define DMA_INTFR_TEIF6                         DMA_INTFR_TEIF6_Msk
#define DMA_INTFR_GIF7_Pos                      (24U)
#define DMA_INTFR_GIF7_Msk                      (0x01UL << DMA_INTFR_GIF7_Pos)
#define DMA_INTFR_GIF7                          DMA_INTFR_GIF7_Msk
#define DMA_INTFR_TCIF7_Pos                     (25U)
#define DMA_INTFR_TCIF7_Msk                     (0x01UL << DMA_INTFR_TCIF7_Pos)
#define DMA_INTFR_TCIF7                         DMA_INTFR_TCIF7_Msk
#define DMA_INTFR_HTIF7_Pos                     (26U)
#define DMA_INTFR_HTIF7_Msk                     (0x01UL << DMA_INTFR_HTIF7_Pos)
#define DMA_INTFR_HTIF7                         DMA_INTFR_HTIF7_Msk
#define DMA_INTFR_TEIF7_Pos                     (27U)
#define DMA_INTFR_TEIF7_Msk                     (0x01UL << DMA_INTFR_TEIF7_Pos)
#define DMA_INTFR_TEIF7                         DMA_INTFR_TEIF7_Msk

/******************  Bit definition for DMA_INTFCR register  ******************/
#define DMA_INTFCR_CGIF1_Pos                    (0U)
#define DMA_INTFCR_CGIF1_Msk                    (0x01UL << DMA_INTFCR_CGIF1_Pos)
#define DMA_INTFCR_CGIF1                        DMA_INTFCR_CGIF1_Msk
#define DMA_INTFCR_CTCIF1_Pos                   (1U)
#define DMA_INTFCR_CTCIF1_Msk                   (0x01UL << DMA_INTFCR_CTCIF1_Pos)
#define DMA_INTFCR_CTCIF1                       DMA_INTFCR_CTCIF1_Msk
#define DMA_INTFCR_CHTIF1_Pos                   (2U)
#define DMA_INTFCR_CHTIF1_Msk                   (0x01UL << DMA_INTFCR_CHTIF1_Pos)
#define DMA_INTFCR_CHTIF1                       DMA_INTFCR_CHTIF1_Msk
#define DMA_INTFCR_CTEIF1_Pos                   (3U)
#define DMA_INTFCR_CTEIF1_Msk                   (0x01UL << DMA_INTFCR_CTEIF1_Pos)
#define DMA_INTFCR_CTEIF1                       DMA_INTFCR_CTEIF1_Msk
#define DMA_INTFCR_CGIF2_Pos                    (4U)
#define DMA_INTFCR_CGIF2_Msk                    (0x01UL << DMA_INTFCR_CGIF2_Pos)
#define DMA_INTFCR_CGIF2                        DMA_INTFCR_CGIF2_Msk
#define DMA_INTFCR_CTCIF2_Pos                   (5U)
#define DMA_INTFCR_CTCIF2_Msk                   (0x01UL << DMA_INTFCR_CTCIF2_Pos)
#define DMA_INTFCR_CTCIF2                       DMA_INTFCR_CTCIF2_Msk
#define DMA_INTFCR_CHTIF2_Pos                   (6U)
#define DMA_INTFCR_CHTIF2_Msk                   (0x01UL << DMA_INTFCR_CHTIF2_Pos)
#define DMA_INTFCR_CHTIF2                       DMA_INTFCR_CHTIF2_Msk
#define DMA_INTFCR_CTEIF2_Pos                   (7U)
#define DMA_INTFCR_CTEIF2_Msk                   (0x01UL << DMA_INTFCR_CTEIF2_Pos)
#define DMA_INTFCR_CTEIF2                       DMA_INTFCR_CTEIF2_Msk
#define DMA_INTFCR_CGIF3_Pos                    (8U)
#define DMA_INTFCR_CGIF3_Msk                    (0x01UL << DMA_INTFCR_CGIF3_Pos)
#define DMA_INTFCR_CGIF3                        DMA_INTFCR_CGIF3_Msk
#define DMA_INTFCR_CTCIF3_Pos                   (9U)
#define DMA_INTFCR_CTCIF3_Msk                   (0x01UL << DMA_INTFCR_CTCIF3_Pos)
#define DMA_INTFCR_CTCIF3                       DMA_INTFCR_CTCIF3_Msk
#define DMA_INTFCR_CHTIF3_Pos                   (10U)
#define DMA_INTFCR_CHTIF3_Msk                   (0x01UL << DMA_INTFCR_CHTIF3_Pos)
#define DMA_INTFCR_CHTIF3                       DMA_INTFCR_CHTIF3_Msk
#define DMA_INTFCR_CTEIF3_Pos                   (11U)
#define DMA_INTFCR_CTEIF3_Msk                   (0x01UL << DMA_INTFCR_CTEIF3_Pos)
#define DMA_INTFCR_CTEIF3                       DMA_INTFCR_CTEIF3_Msk
#define DMA_INTFCR_CGIF4_Pos                    (12U)
#define DMA_INTFCR_CGIF4_Msk                    (0x01UL << DMA_INTFCR_CGIF4_Pos)
#define DMA_INTFCR_CGIF4                        DMA_INTFCR_CGIF4_Msk
#define DMA_INTFCR_CTCIF4_Pos                   (13U)
#define DMA_INTFCR_CTCIF4_Msk                   (0x01UL << DMA_INTFCR_CTCIF4_Pos)
#define DMA_INTFCR_CTCIF4                       DMA_INTFCR_CTCIF4_Msk
#define DMA_INTFCR_CHTIF4_Pos                   (14U)
#define DMA_INTFCR_CHTIF4_Msk                   (0x01UL << DMA_INTFCR_CHTIF4_Pos)
#define DMA_INTFCR_CHTIF4                       DMA_INTFCR_CHTIF4_Msk
#define DMA_INTFCR_CTEIF4_Pos                   (15U)
#define DMA_INTFCR_CTEIF4_Msk                   (0x01UL << DMA_INTFCR_CTEIF4_Pos)
#define DMA_INTFCR_CTEIF4                       DMA_INTFCR_CTEIF4_Msk
#define DMA_INTFCR_CGIF5_Pos                    (16U)
#define DMA_INTFCR_CGIF5_Msk                    (0x01UL << DMA_INTFCR_CGIF5_Pos)
#define DMA_INTFCR_CGIF5                        DMA_INTFCR_CGIF5_Msk
#define DMA_INTFCR_CTCIF5_Pos                   (17U)
#define DMA_INTFCR_CTCIF5_Msk                   (0x01UL << DMA_INTFCR_CTCIF5_Pos)
#define DMA_INTFCR_CTCIF5                       DMA_INTFCR_CTCIF5_Msk
#define DMA_INTFCR_CHTIF5_Pos                   (18U)
#define DMA_INTFCR_CHTIF5_Msk                   (0x01UL << DMA_INTFCR_CHTIF5_Pos)
#define DMA_INTFCR_CHTIF5                       DMA_INTFCR_CHTIF5_Msk
#define DMA_INTFCR_CTEIF5_Pos                   (19U)
#define DMA_INTFCR_CTEIF5_Msk                   (0x01UL << DMA_INTFCR_CTEIF5_Pos)
#define DMA_INTFCR_CTEIF5                       DMA_INTFCR_CTEIF5_Msk
#define DMA_INTFCR_CGIF6_Pos                    (20U)
#define DMA_INTFCR_CGIF6_Msk                    (0x01UL << DMA_INTFCR_CGIF6_Pos)
#define DMA_INTFCR_CGIF6                        DMA_INTFCR_CGIF6_Msk
#define DMA_INTFCR_CTCIF6_Pos                   (21U)
#define DMA_INTFCR_CTCIF6_Msk                   (0x01UL << DMA_INTFCR_CTCIF6_Pos)
#define DMA_INTFCR_CTCIF6                       DMA_INTFCR_CTCIF6_Msk
#define DMA_INTFCR_CHTIF6_Pos                   (22U)
#define DMA_INTFCR_CHTIF6_Msk                   (0x01UL << DMA_INTFCR_CHTIF6_Pos)
#define DMA_INTFCR_CHTIF6                       DMA_INTFCR_CHTIF6_Msk
#define DMA_INTFCR_CTEIF6_Pos                   (23U)
#define DMA_INTFCR_CTEIF6_Msk                   (0x01UL << DMA_INTFCR_CTEIF6_Pos)
#define DMA_INTFCR_CTEIF6                       DMA_INTFCR_CTEIF6_Msk
#define DMA_INTFCR_CGIF7_Pos                    (24U)
#define DMA_INTFCR_CGIF7_Msk                    (0x01UL << DMA_INTFCR_CGIF7_Pos)
#define DMA_INTFCR_CGIF7                        DMA_INTFCR_CGIF7_Msk
#define DMA_INTFCR_CTCIF7_Pos                   (25U)
#define DMA_INTFCR_CTCIF7_Msk                   (0x01UL << DMA_INTFCR_CTCIF7_Pos)
#define DMA_INTFCR_CTCIF7                       DMA_INTFCR_CTCIF7_Msk
#define DMA_INTFCR_CHTIF7_Pos                   (26U)
#define DMA_INTFCR_CHTIF7_Msk                   (0x01UL << DMA_INTFCR_CHTIF7_Pos)
#define DMA_INTFCR_CHTIF7                       DMA_INTFCR_CHTIF7_Msk
#define DMA_INTFCR_CTEIF7_Pos                   (27U)
#define DMA_INTFCR_CTEIF7_Msk                   (0x01UL << DMA_INTFCR_CTEIF7_Pos)
#define DMA_INTFCR_CTEIF7                       DMA_INTFCR_CTEIF7_Msk

/******************  Bit definition for DMA_CFGRx register  *******************/
#define DMA_CFGR_EN_Pos                         (0U)
#define DMA_CFGR_EN_Msk                         (0x01UL << DMA_CFGR_EN_Pos)
#define DMA_CFGR_EN                             DMA_CFGR_EN_Msk
#define DMA_CFGR_TCIE_Pos                       (1U)
#define DMA_CFGR_TCIE_Msk                       (0x01UL << DMA_CFGR_TCIE_Pos)
#define DMA_CFGR_TCIE                           DMA_CFGR_TCIE_Msk
#define DMA_CFGR_HTIE_Pos                       (2U)
#define DMA_CFGR_HTIE_Msk                       (0x01UL << DMA_CFGR_HTIE_Pos)
#define DMA_CFGR_HTIE                           DMA_CFGR_HTIE_Msk
#define DMA_CFGR_TEIE_Pos                       (3U)
#define DMA_CFGR_TEIE_Msk                       (0x01UL << DMA_CFGR_TEIE_Pos)
#define DMA_CFGR_TEIE                           DMA_CFGR_TEIE_Msk
#define DMA_CFGR_DIR_Pos                        (4U)
#define DMA_CFGR_DIR_Msk                        (0x01UL << DMA_CFGR_DIR_Pos)
#define DMA_CFGR_DIR                            DMA_CFGR_DIR_Msk
#define DMA_CFGR_CIRC_Pos                       (5U)
#define DMA_CFGR_CIRC_Msk                       (0x01UL << DMA_CFGR_CIRC_Pos)
#define DMA_CFGR_CIRC                           DMA_CFGR_CIRC_Msk
#define DMA_CFGR_PINC_Pos                       (6U)
#define DMA_CFGR_PINC_Msk                       (0x01UL << DMA_CFGR_PINC_Pos)
#define DMA_CFGR_PINC                           DMA_CFGR_PINC_Msk
#define DMA_CFGR_MINC_Pos                       (7U)
#define DMA_CFGR_MINC_Msk                       (0x01UL << DMA_CFGR_MINC_Pos)
#define DMA_CFGR_MINC                           DMA_CFGR_MINC_Msk
#define DMA_CFGR_PSIZE_Pos                      (8U)
#define DMA_CFGR_PSIZE_Msk                      (0x03UL << DMA_CFGR_PSIZE_Pos)
#define DMA_CFGR_PSIZE                          DMA_CFGR_PSIZE_Msk
#define DMA_CFGR_MSIZE_Pos                      (10U)
#define DMA_CFGR_MSIZE_Msk                      (0x03UL << DMA_CFGR_MSIZE_Pos)
#define DMA_CFGR_MSIZE                          DMA_CFGR_MSIZE_Msk
#define DMA_CFGR_PL_Pos                         (12U)
#define DMA_CFGR_PL_Msk                         (0x03UL << DMA_CFGR_PL_Pos)
#define DMA_CFGR_PL                             DMA_CFGR_PL_Msk
#define DMA_CFGR_MEM2MEM_Pos                    (14U)
#define DMA_CFGR_MEM2MEM_Msk                    (0x01UL << DMA_CFGR_MEM2MEM_Pos)
#define DMA_CFGR_MEM2MEM                        DMA_CFGR_MEM2MEM_Msk

/******************  Bit definition for DMA_CNTRx register  *******************/
#define DMA_CNTR_NDT_Pos                        (0U)
#define DMA_CNTR_NDT_Msk                        (0xFFFFUL << DMA_CNTR_NDT_Pos)
#define DMA_CNTR_NDT                            DMA_CNTR_NDT_Msk

/******************  Bit definition for DMA_PADDRx register  ******************/
#define DMA_PADDR_PA_Pos                        (0U)
#define DMA_PADDR_PA_Msk                        (0xFFFFFFFFUL << DMA_PADDR_PA_Pos)
#define DMA_PADDR_PA                            DMA_PADDR_PA_Msk

/******************  Bit definition for DMA_MADDRx register  ******************/
#define DMA_MADDR_MA_Pos                        (0U)
#define DMA_MADDR_MA_Msk                        (0xFFFFFFFFUL << DMA_MADDR_MA_Pos)
#define DMA_MADDR_MA                            DMA_MADDR_MA_Msk

/******************************************************************************/
/*                    External Interrupt/Event Controller                     */
/******************************************************************************/
/******************  Bit definition for EXTI_INTENR register  *****************/
#define EXTI_INTENR_MR0_Pos                     (0U)
#define EXTI_INTENR_MR0_Msk                     (0x01UL << EXTI_INTENR_MR0_Pos)
#define EXTI_INTENR_MR0                         EXTI_INTENR_MR0_Msk
#define EXTI_INTENR_MR1_Pos                     (1U)
#define EXTI_INTENR_MR1_Msk                     (0x01UL << EXTI_INTENR_MR1_Pos)
#define EXTI_INTENR_MR1                         EXTI_INTENR_MR1_Msk
#define EXTI_INTENR_MR2_Pos                     (2U)
#define EXTI_INTENR_MR2_Msk                     (0x01UL << EXTI_INTENR_MR2_Pos)
#define EXTI_INTENR_MR2                         EXTI_INTENR_MR2_Msk
#define EXTI_INTENR_MR3_Pos                     (3U)
#define EXTI_INTENR_MR3_Msk                     (0x01UL << EXTI_INTENR_MR3_Pos)
#define EXTI_INTENR_MR3                         EXTI_INTENR_MR3_Msk
#define EXTI_INTENR_MR4_Pos                     (4U)
#define EXTI_INTENR_MR4_Msk                     (0x01UL << EXTI_INTENR_MR4_Pos)
#define EXTI_INTENR_MR4                         EXTI_INTENR_MR4_Msk
#define EXTI_INTENR_MR5_Pos                     (5U)
#define EXTI_INTENR_MR5_Msk                     (0x01UL << EXTI_INTENR_MR5_Pos)
#define EXTI_INTENR_MR5                         EXTI_INTENR_MR5_Msk
#define EXTI_INTENR_MR6_Pos                     (6U)
#define EXTI_INTENR_MR6_Msk                     (0x01UL << EXTI_INTENR_MR6_Pos)
#define EXTI_INTENR_MR6                         EXTI_INTENR_MR6_Msk
#define EXTI_INTENR_MR7_Pos                     (7U)
#define EXTI_INTENR_MR7_Msk                     (0x01UL << EXTI_INTENR_MR7_Pos)
#define EXTI_INTENR_MR7                         EXTI_INTENR_MR7_Msk
#define EXTI_INTENR_MR8_Pos                     (8U)
#define EXTI_INTENR_MR8_Msk                     (0x01UL << EXTI_INTENR_MR8_Pos)
#define EXTI_INTENR_MR8                         EXTI_INTENR_MR8_Msk
#define EXTI_INTENR_MR9_Pos                     (9U)
#define EXTI_INTENR_MR9_Msk                     (0x01UL << EXTI_INTENR_MR9_Pos)
#define EXTI_INTENR_MR9                         EXTI_INTENR_MR9_Msk

/******************  Bit definition for EXTI_EVENR register  ******************/
#define EXTI_EVENR_MR0_Pos                      (0U)
#define EXTI_EVENR_MR0_Msk                      (0x01UL << EXTI_EVENR_MR0_Pos)
#define EXTI_EVENR_MR0                          EXTI_EVENR_MR0_Msk
#define EXTI_EVENR_MR1_Pos                      (1U)
#define EXTI_EVENR_MR1_Msk                      (0x01UL << EXTI_EVENR_MR1_Pos)
#define EXTI_EVENR_MR1                          EXTI_EVENR_MR1_Msk
#define EXTI_EVENR_MR2_Pos                      (2U)
#define EXTI_EVENR_MR2_Msk                      (0x01UL << EXTI_EVENR_MR2_Pos)
#define EXTI_EVENR_MR2                          EXTI_EVENR_MR2_Msk
#define EXTI_EVENR_MR3_Pos                      (3U)
#define EXTI_EVENR_MR3_Msk                      (0x01UL << EXTI_EVENR_MR3_Pos)
#define EXTI_EVENR_MR3                          EXTI_EVENR_MR3_Msk
#define EXTI_EVENR_MR4_Pos                      (4U)
#define EXTI_EVENR_MR4_Msk                      (0x01UL << EXTI_EVENR_MR4_Pos)
#define EXTI_EVENR_MR4                          EXTI_EVENR_MR4_Msk
#define EXTI_EVENR_MR5_Pos                      (5U)
#define EXTI_EVENR_MR5_Msk                      (0x01UL << EXTI_EVENR_MR5_Pos)
#define EXTI_EVENR_MR5                          EXTI_EVENR_MR5_Msk
#define EXTI_EVENR_MR6_Pos                      (6U)
#define EXTI_EVENR_MR6_Msk                      (0x01UL << EXTI_EVENR_MR6_Pos)
#define EXTI_EVENR_MR6                          EXTI_EVENR_MR6_Msk
#define EXTI_EVENR_MR7_Pos                      (7U)
#define EXTI_EVENR_MR7_Msk                      (0x01UL << EXTI_EVENR_MR7_Pos)
#define EXTI_EVENR_MR7                          EXTI_EVENR_MR7_Msk
#define EXTI_EVENR_MR8_Pos                      (8U)
#define EXTI_EVENR_MR8_Msk                      (0x01UL << EXTI_EVENR_MR8_Pos)
#define EXTI_EVENR_MR8                          EXTI_EVENR_MR8_Msk
#define EXTI_EVENR_MR9_Pos                      (9U)
#define EXTI_EVENR_MR9_Msk                      (0x01UL << EXTI_EVENR_MR9_Pos)
#define EXTI_EVENR_MR9                          EXTI_EVENR_MR9_Msk

/******************  Bit definition for EXTI_RTENR register  ******************/
#define EXTI_RTENR_TR0_Pos                      (0U)
#define EXTI_RTENR_TR0_Msk                      (0x01UL << EXTI_RTENR_TR0_Pos)
#define EXTI_RTENR_TR0                          EXTI_RTENR_TR0_Msk
#define EXTI_RTENR_TR1_Pos                      (1U)
#define EXTI_RTENR_TR1_Msk                      (0x01UL << EXTI_RTENR_TR1_Pos)
#define EXTI_RTENR_TR1                          EXTI_RTENR_TR1_Msk
#define EXTI_RTENR_TR2_Pos                      (2U)
#define EXTI_RTENR_TR2_Msk                      (0x01UL << EXTI_RTENR_TR2_Pos)
#define EXTI_RTENR_TR2                          EXTI_RTENR_TR2_Msk
#define EXTI_RTENR_TR3_Pos                      (3U)
#define EXTI_RTENR_TR3_Msk                      (0x01UL << EXTI_RTENR_TR3_Pos)
#define EXTI_RTENR_TR3                          EXTI_RTENR_TR3_Msk
#define EXTI_RTENR_TR4_Pos                      (4U)
#define EXTI_RTENR_TR4_Msk                      (0x01UL << EXTI_RTENR_TR4_Pos)
#define EXTI_RTENR_TR4                          EXTI_RTENR_TR4_Msk
#define EXTI_RTENR_TR5_Pos                      (5U)
#define EXTI_RTENR_TR5_Msk                      (0x01UL << EXTI_RTENR_TR5_Pos)
#define EXTI_RTENR_TR5                          EXTI_RTENR_TR5_Msk
#define EXTI_RTENR_TR6_Pos                      (6U)
#define EXTI_RTENR_TR6_Msk                      (0x01UL << EXTI_RTENR_TR6_Pos)
#define EXTI_RTENR_TR6                          EXTI_RTENR_TR6_Msk
#define EXTI_RTENR_TR7_Pos                      (7U)
#define EXTI_RTENR_TR7_Msk                      (0x01UL << EXTI_RTENR_TR7_Pos)
#define EXTI_RTENR_TR7                          EXTI_RTENR_TR7_Msk
#define EXTI_RTENR_TR8_Pos                      (8U)
#define EXTI_RTENR_TR8_Msk                      (0x01UL << EXTI_RTENR_TR8_Pos)
#define EXTI_RTENR_TR8                          EXTI_RTENR_TR8_Msk
#define EXTI_RTENR_TR9_Pos                      (9U)
#define EXTI_RTENR_TR9_Msk                      (0x01UL << EXTI_RTENR_TR9_Pos)
#define EXTI_RTENR_TR9                          EXTI_RTENR_TR9_Msk

/******************  Bit definition for EXTI_FTENR register  ******************/
#define EXTI_FTENR_TR0_Pos                      (0U)
#define EXTI_FTENR_TR0_Msk                      (0x01UL << EXTI_FTENR_TR0_Pos)
#define EXTI_FTENR_TR0                          EXTI_FTENR_TR0_Msk
#define EXTI_FTENR_TR1_Pos                      (1U)
#define EXTI_FTENR_TR1_Msk                      (0x01UL << EXTI_FTENR_TR1_Pos)
#define EXTI_FTENR_TR1                          EXTI_FTENR_TR1_Msk
#define EXTI_FTENR_TR2_Pos                      (2U)
#define EXTI_FTENR_TR2_Msk                      (0x01UL << EXTI_FTENR_TR2_Pos)
#define EXTI_FTENR_TR2                          EXTI_FTENR_TR2_Msk
#define EXTI_FTENR_TR3_Pos                      (3U)
#define EXTI_FTENR_TR3_Msk                      (0x01UL << EXTI_FTENR_TR3_Pos)
#define EXTI_FTENR_TR3                          EXTI_FTENR_TR3_Msk
#define EXTI_FTENR_TR4_Pos                      (4U)
#define EXTI_FTENR_TR4_Msk                      (0x01UL << EXTI_FTENR_TR4_Pos)
#define EXTI_FTENR_TR4                          EXTI_FTENR_TR4_Msk
#define EXTI_FTENR_TR5_Pos                      (5U)
#define EXTI_FTENR_TR5_Msk                      (0x01UL << EXTI_FTENR_TR5_Pos)
#define EXTI_FTENR_TR5                          EXTI_FTENR_TR5_Msk
#define EXTI_FTENR_TR6_Pos                      (6U)
#define EXTI_FTENR_TR6_Msk                      (0x01UL << EXTI_FTENR_TR6_Pos)
#define EXTI_FTENR_TR6                          EXTI_FTENR_TR6_Msk
#define EXTI_FTENR_TR7_Pos                      (7U)
#define EXTI_FTENR_TR7_Msk                      (0x01UL << EXTI_FTENR_TR7_Pos)
#define EXTI_FTENR_TR7                          EXTI_FTENR_TR7_Msk
#define EXTI_FTENR_TR8_Pos                      (8U)
#define EXTI_FTENR_TR8_Msk                      (0x01UL << EXTI_FTENR_TR8_Pos)
#define EXTI_FTENR_TR8                          EXTI_FTENR_TR8_Msk
#define EXTI_FTENR_TR9_Pos                      (9U)
#define EXTI_FTENR_TR9_Msk                      (0x01UL << EXTI_FTENR_TR9_Pos)
#define EXTI_FTENR_TR9                          EXTI_FTENR_TR9_Msk

/******************  Bit definition for EXTI_SWIEVR register  *****************/
#define EXTI_SWIEVR_SWIE0_Pos                   (0U)
#define EXTI_SWIEVR_SWIE0_Msk                   (0x01UL << EXTI_SWIEVR_SWIE0_Pos)
#define EXTI_SWIEVR_SWIE0                       EXTI_SWIEVR_SWIE0_Msk
#define EXTI_SWIEVR_SWIE1_Pos                   (1U)
#define EXTI_SWIEVR_SWIE1_Msk                   (0x01UL << EXTI_SWIEVR_SWIE1_Pos)
#define EXTI_SWIEVR_SWIE1                       EXTI_SWIEVR_SWIE1_Msk
#define EXTI_SWIEVR_SWIE2_Pos                   (2U)
#define EXTI_SWIEVR_SWIE2_Msk                   (0x01UL << EXTI_SWIEVR_SWIE2_Pos)
#define EXTI_SWIEVR_SWIE2                       EXTI_SWIEVR_SWIE2_Msk
#define EXTI_SWIEVR_SWIE3_Pos                   (3U)
#define EXTI_SWIEVR_SWIE3_Msk                   (0x01UL << EXTI_SWIEVR_SWIE3_Pos)
#define EXTI_SWIEVR_SWIE3                       EXTI_SWIEVR_SWIE3_Msk
#define EXTI_SWIEVR_SWIE4_Pos                   (4U)
#define EXTI_SWIEVR_SWIE4_Msk                   (0x01UL << EXTI_SWIEVR_SWIE4_Pos)
#define EXTI_SWIEVR_SWIE4                       EXTI_SWIEVR_SWIE4_Msk
#define EXTI_SWIEVR_SWIE5_Pos                   (5U)
#define EXTI_SWIEVR_SWIE5_Msk                   (0x01UL << EXTI_SWIEVR_SWIE5_Pos)
#define EXTI_SWIEVR_SWIE5                       EXTI_SWIEVR_SWIE5_Msk
#define EXTI_SWIEVR_SWIE6_Pos                   (6U)
#define EXTI_SWIEVR_SWIE6_Msk                   (0x01UL << EXTI_SWIEVR_SWIE6_Pos)
#define EXTI_SWIEVR_SWIE6                       EXTI_SWIEVR_SWIE6_Msk
#define EXTI_SWIEVR_SWIE7_Pos                   (7U)
#define EXTI_SWIEVR_SWIE7_Msk                   (0x01UL << EXTI_SWIEVR_SWIE7_Pos)
#define EXTI_SWIEVR_SWIE7                       EXTI_SWIEVR_SWIE7_Msk
#define EXTI_SWIEVR_SWIE8_Pos                   (8U)
#define EXTI_SWIEVR_SWIE8_Msk                   (0x01UL << EXTI_SWIEVR_SWIE8_Pos)
#define EXTI_SWIEVR_SWIE8                       EXTI_SWIEVR_SWIE8_Msk
#define EXTI_SWIEVR_SWIE9_Pos                   (9U)
#define EXTI_SWIEVR_SWIE9_Msk                   (0x01UL << EXTI_SWIEVR_SWIE9_Pos)
#define EXTI_SWIEVR_SWIE9                       EXTI_SWIEVR_SWIE9_Msk

/******************  Bit definition for EXTI_INTFR register  ******************/
#define EXTI_INTFR_IF0_Pos                      (0U)
#define EXTI_INTFR_IF0_Msk                      (0x01UL << EXTI_INTFR_IF0_Pos)
#define EXTI_INTFR_IF0                          EXTI_INTFR_IF0_Msk
#define EXTI_INTFR_IF1_Pos                      (1U)
#define EXTI_INTFR_IF1_Msk                      (0x01UL << EXTI_INTFR_IF1_Pos)
#define EXTI_INTFR_IF1                          EXTI_INTFR_IF1_Msk
#define EXTI_INTFR_IF2_Pos                      (2U)
#define EXTI_INTFR_IF2_Msk                      (0x01UL << EXTI_INTFR_IF2_Pos)
#define EXTI_INTFR_IF2                          EXTI_INTFR_IF2_Msk
#define EXTI_INTFR_IF3_Pos                      (3U)
#define EXTI_INTFR_IF3_Msk                      (0x01UL << EXTI_INTFR_IF3_Pos)
#define EXTI_INTFR_IF3                          EXTI_INTFR_IF3_Msk
#define EXTI_INTFR_IF4_Pos                      (4U)
#define EXTI_INTFR_IF4_Msk                      (0x01UL << EXTI_INTFR_IF4_Pos)
#define EXTI_INTFR_IF4                          EXTI_INTFR_IF4_Msk
#define EXTI_INTFR_IF5_Pos                      (5U)
#define EXTI_INTFR_IF5_Msk                      (0x01UL << EXTI_INTFR_IF5_Pos)
#define EXTI_INTFR_IF5                          EXTI_INTFR_IF5_Msk
#define EXTI_INTFR_IF6_Pos                      (6U)
#define EXTI_INTFR_IF6_Msk                      (0x01UL << EXTI_INTFR_IF6_Pos)
#define EXTI_INTFR_IF6                          EXTI_INTFR_IF6_Msk
#define EXTI_INTFR_IF7_Pos                      (7U)
#define EXTI_INTFR_IF7_Msk                      (0x01UL << EXTI_INTFR_IF7_Pos)
#define EXTI_INTFR_IF7                          EXTI_INTFR_IF7_Msk
#define EXTI_INTFR_IF8_Pos                      (8U)
#define EXTI_INTFR_IF8_Msk                      (0x01UL << EXTI_INTFR_IF8_Pos)
#define EXTI_INTFR_IF8                          EXTI_INTFR_IF8_Msk
#define EXTI_INTFR_IF9_Pos                      (9U)
#define EXTI_INTFR_IF9_Msk                      (0x01UL << EXTI_INTFR_IF9_Pos)
#define EXTI_INTFR_IF9                          EXTI_INTFR_IF9_Msk

/******************************************************************************/
/*                      FLASH and Option Bytes Registers                      */
/******************************************************************************/
/******************  Bit definition for FLASH_ACTLR register  *****************/
#define FLASH_ACTLR_LATENCY_Pos                 (0U)
#define FLASH_ACTLR_LATENCY_Msk                 (0x03UL << FLASH_ACTLR_LATENCY_Pos)
#define FLASH_ACTLR_LATENCY                     FLASH_ACTLR_LATENCY_Msk

/******************  Bit definition for FLASH_KEYR register  ******************/
#define FLASH_KEYR_KEYR_Pos                     (0U)
#define FLASH_KEYR_KEYR_Msk                     (0xFFFFFFFFUL << FLASH_KEYR_KEYR_Pos)
#define FLASH_KEYR_KEYR                         FLASH_KEYR_KEYR_Msk

/******************  Bit definition for FLASH_OBKEYR register  ****************/
#define FLASH_OBTKEYR_OBKEYR_Pos                (0U)
#define FLASH_OBTKEYR_OBKEYR_Msk                (0xFFFFFFFFUL << FLASH_OBTKEYR_OBKEYR_Pos)
#define FLASH_OBTKEYR_OBKEYR                    FLASH_OBTKEYR_OBKEYR_Msk

/******************  Bit definition for FLASH_STATR register  *****************/
#define FLASH_STATR_BUSY_Pos                    (0U)
#define FLASH_STATR_BUSY_Msk                    (0x01UL << FLASH_STATR_BUSY_Pos)
#define FLASH_STATR_BUSY                        FLASH_STATR_BUSY_Msk
#define FLASH_STATR_WRPRTERR_Pos                (4U)
#define FLASH_STATR_WRPRTERR_Msk                (0x01UL << FLASH_STATR_WRPRTERR_Pos)
#define FLASH_STATR_WRPRTERR                    FLASH_STATR_WRPRTERR_Msk
#define FLASH_STATR_EOP_Pos                     (5U)
#define FLASH_STATR_EOP_Msk                     (0x01UL << FLASH_STATR_EOP_Pos)
#define FLASH_STATR_EOP                         FLASH_STATR_EOP_Msk
#define FLASH_STATR_MODE_Pos                    (14U)
#define FLASH_STATR_MODE_Msk                    (0x01UL << FLASH_STATR_MODE_Pos)
#define FLASH_STATR_MODE                        FLASH_STATR_MODE_Msk
#define FLASH_STATR_LOCK_Pos                    (15U)
#define FLASH_STATR_LOCK_Msk                    (0x01UL << FLASH_STATR_LOCK_Pos)
#define FLASH_STATR_LOCK                        FLASH_STATR_LOCK_Msk

/******************  Bit definition for FLASH_CTLR register  ******************/
#define FLASH_CTLR_PG_Pos                       (0U)
#define FLASH_CTLR_PG_Msk                       (0x01UL << FLASH_CTLR_PG_Pos)
#define FLASH_CTLR_PG                           FLASH_CTLR_PG_Msk
#define FLASH_CTLR_PER_Pos                      (1U)
#define FLASH_CTLR_PER_Msk                      (0x01UL << FLASH_CTLR_PER_Pos)
#define FLASH_CTLR_PER                          FLASH_CTLR_PER_Msk
#define FLASH_CTLR_MER_Pos                      (2U)
#define FLASH_CTLR_MER_Msk                      (0x01UL << FLASH_CTLR_MER_Pos)
#define FLASH_CTLR_MER                          FLASH_CTLR_MER_Msk
#define FLASH_CTLR_OBPG_Pos                     (4U)
#define FLASH_CTLR_OBPG_Msk                     (0x01UL << FLASH_CTLR_OBPG_Pos)
#define FLASH_CTLR_OBPG                         FLASH_CTLR_OBPG_Msk
#define FLASH_CTLR_OBER_Pos                     (5U)
#define FLASH_CTLR_OBER_Msk                     (0x01UL << FLASH_CTLR_OBER_Pos)
#define FLASH_CTLR_OBER                         FLASH_CTLR_OBER_Msk
#define FLASH_CTLR_STRT_Pos                     (6U)
#define FLASH_CTLR_STRT_Msk                     (0x01UL << FLASH_CTLR_STRT_Pos)
#define FLASH_CTLR_STRT                         FLASH_CTLR_STRT_Msk
#define FLASH_CTLR_LOCK_Pos                     (7U)
#define FLASH_CTLR_LOCK_Msk                     (0x01UL << FLASH_CTLR_LOCK_Pos)
#define FLASH_CTLR_LOCK                         FLASH_CTLR_LOCK_Msk
#define FLASH_CTLR_OBWRE_Pos                    (9U)
#define FLASH_CTLR_OBWRE_Msk                    (0x01UL << FLASH_CTLR_OBWRE_Pos)
#define FLASH_CTLR_OBWRE                        FLASH_CTLR_OBWRE_Msk
#define FLASH_CTLR_ERRIE_Pos                    (10U)
#define FLASH_CTLR_ERRIE_Msk                    (0x01UL << FLASH_CTLR_ERRIE_Pos)
#define FLASH_CTLR_ERRIE                        FLASH_CTLR_ERRIE_Msk
#define FLASH_CTLR_EOPIE_Pos                    (12U)
#define FLASH_CTLR_EOPIE_Msk                    (0x01UL << FLASH_CTLR_EOPIE_Pos)
#define FLASH_CTLR_EOPIE                        FLASH_CTLR_EOPIE_Msk
#define FLASH_CTLR_FLOCK_Pos                    (15U)
#define FLASH_CTLR_FLOCK_Msk                    (0x01UL << FLASH_CTLR_FLOCK_Pos)
#define FLASH_CTLR_FLOCK                        FLASH_CTLR_FLOCK_Msk
#define FLASH_CTLR_FTPG_Pos                     (16U)
#define FLASH_CTLR_FTPG_Msk                     (0x01UL << FLASH_CTLR_FTPG_Pos)
#define FLASH_CTLR_FTPG                         FLASH_CTLR_FTPG_Msk
#define FLASH_CTLR_FTER_Pos                     (17U)
#define FLASH_CTLR_FTER_Msk                     (0x01UL << FLASH_CTLR_FTER_Pos)
#define FLASH_CTLR_FTER                         FLASH_CTLR_FTER_Msk
#define FLASH_CTLR_BUFLOAD_Pos                  (18U)
#define FLASH_CTLR_BUFLOAD_Msk                  (0x01UL << FLASH_CTLR_BUFLOAD_Pos)
#define FLASH_CTLR_BUFLOAD                      FLASH_CTLR_BUFLOAD_Msk
#define FLASH_CTLR_BUFRST_Pos                   (19U)
#define FLASH_CTLR_BUFRST_Msk                   (0x01UL << FLASH_CTLR_BUFRST_Pos)
#define FLASH_CTLR_BUFRST                       FLASH_CTLR_BUFRST_Msk

/******************  Bit definition for FLASH_ADDR register  ******************/
#define FLASH_ADDR_FAR_Pos                      (0U)
#define FLASH_ADDR_FAR_Msk                      (0xFFFFFFFFUL << FLASH_ADDR_FAR_Pos)
#define FLASH_ADDR_FAR                          FLASH_ADDR_FAR_Msk

/******************  Bit definition for FLASH_OBR register  *******************/
#define FLASH_OBR_OBERR_Pos                     (0U)
#define FLASH_OBR_OBERR_Msk                     (0x01UL << FLASH_OBR_OBERR_Pos)
#define FLASH_OBR_OBERR                         FLASH_OBR_OBERR_Msk
#define FLASH_OBR_RDPRT_Pos                     (1U)
#define FLASH_OBR_RDPRT_Msk                     (0x01UL << FLASH_OBR_RDPRT_Pos)
#define FLASH_OBR_RDPRT                         FLASH_OBR_RDPRT_Msk
#define FLASH_OBR_USER_Pos                      (2U)
#define FLASH_OBR_USER_Msk                      (0x1FUL << FLASH_OBR_USER_Pos)
#define FLASH_OBR_USER                          FLASH_OBR_USER_Msk
#define FLASH_OBR_IWDGSW_Pos                    (2U)
#define FLASH_OBR_IWDGSW_Msk                    (0x01UL << FLASH_OBR_IWDGSW_Pos)
#define FLASH_OBR_IWDGSW                        FLASH_OBR_IWDGSW_Msk
#define FLASH_OBR_STOPRST_Pos                   (3U)
#define FLASH_OBR_STOPRST_Msk                   (0x01UL << FLASH_OBR_STOPRST_Pos)
#define FLASH_OBR_STOPRST                       FLASH_OBR_STOPRST_Msk
#define FLASH_OBR_STANDYRST_Pos                 (4U)
#define FLASH_OBR_STANDYRST_Msk                 (0x01UL << FLASH_OBR_STANDYRST_Pos)
#define FLASH_OBR_STANDYRST                     FLASH_OBR_STANDYRST_Msk
#define FLASH_OBR_CFGRSTT_Pos                   (5U)
#define FLASH_OBR_CFGRSTT_Msk                   (0x03UL << FLASH_OBR_CFGRSTT_Pos)
#define FLASH_OBR_CFGRSTT                       FLASH_OBR_CFGRSTT_Msk
#define FLASH_OBR_DATA0_Pos                     (10U)
#define FLASH_OBR_DATA0_Msk                     (0xFFUL << FLASH_OBR_DATA0_Pos)
#define FLASH_OBR_DATA0                         FLASH_OBR_DATA0_Msk
#define FLASH_OBR_DATA1_Pos                     (18U)
#define FLASH_OBR_DATA1_Msk                     (0xFFUL << FLASH_OBR_DATA1_Pos)
#define FLASH_OBR_DATA1                         FLASH_OBR_DATA1_Msk

/******************  Bit definition for FLASH_WPR register  *******************/
#define FLASH_WPR_WPR_Pos                       (0U)
#define FLASH_WPR_WPR_Msk                       (0xFFFFUL << FLASH_WPR_WPR_Pos)
#define FLASH_WPR_WPR                           FLASH_WPR_WPR_Msk

/******************  Bit definition for FLASH_MODEKEYR register  **************/
#define FLASH_MODEKEYR_MODEKEYR_Pos             (0U)
#define FLASH_MODEKEYR_MODEKEYR_Msk             (0xFFFFFFFFUL << FLASH_MODEKEYR_MODEKEYR_Pos)
#define FLASH_MODEKEYR_MODEKEYR                 FLASH_MODEKEYR_MODEKEYR_Msk

/******************  Bit definition for FLASH_BOOT_MODEKEYP register  **************/
#define FLASH_BOOT_MODEKEYP_MODEKEYR_Pos        (0U)
#define FLASH_BOOT_MODEKEYP_MODEKEYR_Msk        (0xFFFFFFFFUL << FLASH_BOOT_MODEKEYP_MODEKEYR_Pos)
#define FLASH_BOOT_MODEKEYP_MODEKEYR            FLASH_BOOT_MODEKEYP_MODEKEYR_Msk

/******************  Bit definition for UOB_RDPR register  ********************/
#define UOB_RDPR_RDPR_Pos                       (0U)
#define UOB_RDPR_RDPR_Msk                       (0xFFUL << UOB_RDPR_RDPR_Pos)
#define UOB_RDPR_RDPR                           UOB_RDPR_RDPR_Msk
#define UOB_RDPR_NRDPR_Pos                      (8U)
#define UOB_RDPR_NRDPR_Msk                      (0xFFUL << UOB_RDPR_NRDPR_Pos)
#define UOB_RDPR_NRDPR                          UOB_RDPR_NRDPR_Msk

/******************  Bit definition for UOB_USER register  ********************/
#define UOB_USER_USER_Pos                       (0U)
#define UOB_USER_USER_Msk                       (0x3FUL << UOB_USER_USER_Pos)
#define UOB_USER_USER                           UOB_USER_USER_Msk
#define UOB_USER_IWDGSW_Pos                     (0U)
#define UOB_USER_IWDGSW_Msk                     (0x01UL << UOB_USER_IWDGSW_Pos)
#define UOB_USER_IWDGSW                         UOB_USER_IWDGSW_Msk
#define UOB_USER_STOPRST_Pos                    (1U)
#define UOB_USER_STOPRST_Msk                    (0x01UL << UOB_USER_STOPRST_Pos)
#define UOB_USER_STOPRST                        UOB_USER_STOPRST_Msk
#define UOB_USER_STANDYRST_Pos                  (2U)
#define UOB_USER_STANDYRST_Msk                  (0x01UL << UOB_USER_STANDYRST_Pos)
#define UOB_USER_STANDYRST                      UOB_USER_STANDYRST_Msk
#define UOB_USER_RSTMODE_Pos                    (3U)
#define UOB_USER_RSTMODE_Msk                    (0x03UL << UOB_USER_RSTMODE_Pos)
#define UOB_USER_RSTMODE                        UOB_USER_RSTMODE_Msk
#define UOB_USER_STARTMODE_Pos                  (5U)
#define UOB_USER_STARTMODE_Msk                  (0x01UL << UOB_USER_STARTMODE_Pos)
#define UOB_USER_STARTMODE                      UOB_USER_STARTMODE_Msk
#define UOB_USER_NUSER_Pos                      (8U)
#define UOB_USER_NUSER_Msk                      (0x3FUL << UOB_USER_NUSER_Pos)
#define UOB_USER_NUSER                          UOB_USER_NUSER_Msk
#define UOB_USER_NIWDGSW_Pos                    (8U)
#define UOB_USER_NIWDGSW_Msk                    (0x01UL << UOB_USER_NIWDGSW_Pos)
#define UOB_USER_NIWDGSW                        UOB_USER_NIWDGSW_Msk
#define UOB_USER_NSTOPRST_Pos                   (9U)
#define UOB_USER_NSTOPRST_Msk                   (0x01UL << UOB_USER_NSTOPRST_Pos)
#define UOB_USER_NSTOPRST                       UOB_USER_NSTOPRST_Msk
#define UOB_USER_NSTANDYRST_Pos                 (10U)
#define UOB_USER_NSTANDYRST_Msk                 (0x01UL << UOB_USER_NSTANDYRST_Pos)
#define UOB_USER_NSTANDYRST                     UOB_USER_NSTANDYRST_Msk
#define UOB_USER_NRSTMODE_Pos                   (11U)
#define UOB_USER_NRSTMODE_Msk                   (0x02UL << UOB_USER_NRSTMODE_Pos)
#define UOB_USER_NRSTMODE                       UOB_USER_NRSTMODE_Msk
#define UOB_USER_NSTARTMODE_Pos                 (13U)
#define UOB_USER_NSTARTMODE_Msk                 (0x01UL << UOB_USER_NSTARTMODE_Pos)
#define UOB_USER_NSTARTMODE                     UOB_USER_NSTARTMODE_Msk

/******************  Bit definition for UOB_DATA0 register  *******************/
#define UOB_DATA0_DATA0_Pos                     (0U)
#define UOB_DATA0_DATA0_Msk                     (0xFFUL << UOB_DATA0_DATA0_Pos)
#define UOB_DATA0_DATA0                         UOB_DATA0_DATA0_Msk
#define UOB_DATA0_NDATA0_Pos                    (8U)
#define UOB_DATA0_NDATA0_Msk                    (0xFFUL << UOB_DATA0_NDATA0_Pos)
#define UOB_DATA0_NDATA0                        UOB_DATA0_NDATA0_Msk

/******************  Bit definition for UOB_DATA1 register  *******************/
#define UOB_DATA1_DATA1_Pos                     (0U)
#define UOB_DATA1_DATA1_Msk                     (0xFFUL << UOB_DATA1_DATA1_Pos)
#define UOB_DATA1_DATA1                         UOB_DATA1_DATA1_Msk
#define UOB_DATA1_NDATA1_Pos                    (8U)
#define UOB_DATA1_NDATA1_Msk                    (0xFFUL << UOB_DATA1_NDATA1_Pos)
#define UOB_DATA1_NDATA1                        UOB_DATA1_NDATA1_Msk

/******************  Bit definition for UOB_WRPR0 register  *******************/
#define UOB_WRPR0_WRPR0_Pos                     (0U)
#define UOB_WRPR0_WRPR0_Msk                     (0xFFUL << UOB_WRPR0_WRPR0_Pos)
#define UOB_WRPR0_WRPR0                         UOB_WRPR0_WRPR0_Msk
#define UOB_WRPR0_NWRPR0_Pos                    (8U)
#define UOB_WRPR0_NWRPR0_Msk                    (0xFFUL << UOB_WRPR0_NWRPR0_Pos)
#define UOB_WRPR0_NWRPR0                        UOB_WRPR0_NWRPR0_Msk

/******************  Bit definition for UOB_WRPR1 register  *******************/
#define UOB_WRPR1_WRPR1_Pos                     (0U)
#define UOB_WRPR1_WRPR1_Msk                     (0xFFUL << UOB_WRPR1_WRPR1_Pos)
#define UOB_WRPR1_WRPR1                         UOB_WRPR1_WRPR1_Msk
#define UOB_WRPR1_NWRPR1_Pos                    (8U)
#define UOB_WRPR1_NWRPR1_Msk                    (0xFFUL << UOB_WRPR1_NWRPR1_Pos)
#define UOB_WRPR1_NWRPR1                        UOB_WRPR1_NWRPR1_Msk

/******************************************************************************/
/*                 General Purpose and Alternate Function I/O                 */
/******************************************************************************/
/******************  Bit definition for GPIO_CFGLR register  ******************/
#define GPIO_CFGLR_MODE_Pos                     (0U)
#define GPIO_CFGLR_MODE_Msk                     (0x03UL << GPIO_CFGLR_MODE_Pos)
#define GPIO_CFGLR_MODE                         GPIO_CFGLR_MODE_Msk
#define GPIO_CFGLR_CNF_Pos                      (2U)
#define GPIO_CFGLR_CNF_Msk                      (0x03UL << GPIO_CFGLR_CNF_Pos)
#define GPIO_CFGLR_CNF                          GPIO_CFGLR_CNF_Msk
#define GPIO_CFGLR_MODE0_Pos                    (0U)
#define GPIO_CFGLR_MODE0_Msk                    (0x03UL << GPIO_CFGLR_MODE0_Pos)
#define GPIO_CFGLR_MODE0                        GPIO_CFGLR_MODE0_Msk
#define GPIO_CFGLR_CNF0_Pos                     (2U)
#define GPIO_CFGLR_CNF0_Msk                     (0x03UL << GPIO_CFGLR_CNF0_Pos)
#define GPIO_CFGLR_CNF0                         GPIO_CFGLR_CNF0_Msk
#define GPIO_CFGLR_MODE1_Pos                    (4U)
#define GPIO_CFGLR_MODE1_Msk                    (0x03UL << GPIO_CFGLR_MODE1_Pos)
#define GPIO_CFGLR_MODE1                        GPIO_CFGLR_MODE1_Msk
#define GPIO_CFGLR_CNF1_Pos                     (6U)
#define GPIO_CFGLR_CNF1_Msk                     (0x03UL << GPIO_CFGLR_CNF1_Pos)
#define GPIO_CFGLR_CNF1                         GPIO_CFGLR_CNF1_Msk
#define GPIO_CFGLR_MODE2_Pos                    (8U)
#define GPIO_CFGLR_MODE2_Msk                    (0x03UL << GPIO_CFGLR_MODE2_Pos)
#define GPIO_CFGLR_MODE2                        GPIO_CFGLR_MODE2_Msk
#define GPIO_CFGLR_CNF2_Pos                     (10U)
#define GPIO_CFGLR_CNF2_Msk                     (0x03UL << GPIO_CFGLR_CNF2_Pos)
#define GPIO_CFGLR_CNF2                         GPIO_CFGLR_CNF2_Msk
#define GPIO_CFGLR_MODE3_Pos                    (12U)
#define GPIO_CFGLR_MODE3_Msk                    (0x03UL << GPIO_CFGLR_MODE3_Pos)
#define GPIO_CFGLR_MODE3                        GPIO_CFGLR_MODE3_Msk
#define GPIO_CFGLR_CNF3_Pos                     (14U)
#define GPIO_CFGLR_CNF3_Msk                     (0x03UL << GPIO_CFGLR_CNF3_Pos)
#define GPIO_CFGLR_CNF3                         GPIO_CFGLR_CNF3_Msk
#define GPIO_CFGLR_MODE4_Pos                    (16U)
#define GPIO_CFGLR_MODE4_Msk                    (0x03UL << GPIO_CFGLR_MODE4_Pos)
#define GPIO_CFGLR_MODE4                        GPIO_CFGLR_MODE4_Msk
#define GPIO_CFGLR_CNF4_Pos                     (18U)
#define GPIO_CFGLR_CNF4_Msk                     (0x03UL << GPIO_CFGLR_CNF4_Pos)
#define GPIO_CFGLR_CNF4                         GPIO_CFGLR_CNF4_Msk
#define GPIO_CFGLR_MODE5_Pos                    (20U)
#define GPIO_CFGLR_MODE5_Msk                    (0x03UL << GPIO_CFGLR_MODE5_Pos)
#define GPIO_CFGLR_MODE5                        GPIO_CFGLR_MODE5_Msk
#define GPIO_CFGLR_CNF5_Pos                     (22U)
#define GPIO_CFGLR_CNF5_Msk                     (0x03UL << GPIO_CFGLR_CNF5_Pos)
#define GPIO_CFGLR_CNF5                         GPIO_CFGLR_CNF5_Msk
#define GPIO_CFGLR_MODE6_Pos                    (24U)
#define GPIO_CFGLR_MODE6_Msk                    (0x03UL << GPIO_CFGLR_MODE6_Pos)
#define GPIO_CFGLR_MODE6                        GPIO_CFGLR_MODE6_Msk
#define GPIO_CFGLR_CNF6_Pos                     (26U)
#define GPIO_CFGLR_CNF6_Msk                     (0x03UL << GPIO_CFGLR_CNF6_Pos)
#define GPIO_CFGLR_CNF6                         GPIO_CFGLR_CNF6_Msk
#define GPIO_CFGLR_MODE7_Pos                    (28U)
#define GPIO_CFGLR_MODE7_Msk                    (0x03UL << GPIO_CFGLR_MODE7_Pos)
#define GPIO_CFGLR_MODE7                        GPIO_CFGLR_MODE7_Msk
#define GPIO_CFGLR_CNF7_Pos                     (30U)
#define GPIO_CFGLR_CNF7_Msk                     (0x03UL << GPIO_CFGLR_CNF7_Pos)
#define GPIO_CFGLR_CNF7                         GPIO_CFGLR_CNF7_Msk

/******************  Bit definition for GPIO_CFGHR register  ******************/
#define GPIO_CFGHR_MODE_Pos                     (0U)
#define GPIO_CFGHR_MODE_Msk                     (0x03UL << GPIO_CFGHR_MODE_Pos)
#define GPIO_CFGHR_MODE                         GPIO_CFGHR_MODE_Msk
#define GPIO_CFGHR_CNF_Pos                      (2U)
#define GPIO_CFGHR_CNF_Msk                      (0x03UL << GPIO_CFGHR_CNF_Pos)
#define GPIO_CFGHR_CNF                          GPIO_CFGHR_CNF_Msk
#define GPIO_CFGHR_MODE8_Pos                    (0U)
#define GPIO_CFGHR_MODE8_Msk                    (0x03UL << GPIO_CFGHR_MODE8_Pos)
#define GPIO_CFGHR_MODE8                        GPIO_CFGHR_MODE8_Msk
#define GPIO_CFGHR_CNF8_Pos                     (2U)
#define GPIO_CFGHR_CNF8_Msk                     (0x03UL << GPIO_CFGHR_CNF8_Pos)
#define GPIO_CFGHR_CNF8                         GPIO_CFGHR_CNF8_Msk
#define GPIO_CFGHR_MODE9_Pos                    (4U)
#define GPIO_CFGHR_MODE9_Msk                    (0x03UL << GPIO_CFGHR_MODE9_Pos)
#define GPIO_CFGHR_MODE9                        GPIO_CFGHR_MODE9_Msk
#define GPIO_CFGHR_CNF9_Pos                     (6U)
#define GPIO_CFGHR_CNF9_Msk                     (0x03UL << GPIO_CFGHR_CNF9_Pos)
#define GPIO_CFGHR_CNF9                         GPIO_CFGHR_CNF9_Msk
#define GPIO_CFGHR_MODE10_Pos                   (8U)
#define GPIO_CFGHR_MODE10_Msk                   (0x03UL << GPIO_CFGHR_MODE10_Pos)
#define GPIO_CFGHR_MODE10                       GPIO_CFGHR_MODE10_Msk
#define GPIO_CFGHR_CNF10_Pos                    (10U)
#define GPIO_CFGHR_CNF10_Msk                    (0x03UL << GPIO_CFGHR_CNF10_Pos)
#define GPIO_CFGHR_CNF10                        GPIO_CFGHR_CNF10_Msk
#define GPIO_CFGHR_MODE11_Pos                   (12U)
#define GPIO_CFGHR_MODE11_Msk                   (0x03UL << GPIO_CFGHR_MODE11_Pos)
#define GPIO_CFGHR_MODE11                       GPIO_CFGHR_MODE11_Msk
#define GPIO_CFGHR_CNF11_Pos                    (14U)
#define GPIO_CFGHR_CNF11_Msk                    (0x03UL << GPIO_CFGHR_CNF11_Pos)
#define GPIO_CFGHR_CNF11                        GPIO_CFGHR_CNF11_Msk
#define GPIO_CFGHR_MODE12_Pos                   (16U)
#define GPIO_CFGHR_MODE12_Msk                   (0x03UL << GPIO_CFGHR_MODE12_Pos)
#define GPIO_CFGHR_MODE12                       GPIO_CFGHR_MODE12_Msk
#define GPIO_CFGHR_CNF12_Pos                    (18U)
#define GPIO_CFGHR_CNF12_Msk                    (0x03UL << GPIO_CFGHR_CNF12_Pos)
#define GPIO_CFGHR_CNF12                        GPIO_CFGHR_CNF12_Msk
#define GPIO_CFGHR_MODE13_Pos                   (20U)
#define GPIO_CFGHR_MODE13_Msk                   (0x03UL << GPIO_CFGHR_MODE13_Pos)
#define GPIO_CFGHR_MODE13                       GPIO_CFGHR_MODE13_Msk
#define GPIO_CFGHR_CNF13_Pos                    (22U)
#define GPIO_CFGHR_CNF13_Msk                    (0x03UL << GPIO_CFGHR_CNF13_Pos)
#define GPIO_CFGHR_CNF13                        GPIO_CFGHR_CNF13_Msk
#define GPIO_CFGHR_MODE14_Pos                   (24U)
#define GPIO_CFGHR_MODE14_Msk                   (0x03UL << GPIO_CFGHR_MODE14_Pos)
#define GPIO_CFGHR_MODE14                       GPIO_CFGHR_MODE14_Msk
#define GPIO_CFGHR_CNF14_Pos                    (26U)
#define GPIO_CFGHR_CNF14_Msk                    (0x03UL << GPIO_CFGHR_CNF14_Pos)
#define GPIO_CFGHR_CNF14                        GPIO_CFGHR_CNF14_Msk
#define GPIO_CFGHR_MODE15_Pos                   (28U)
#define GPIO_CFGHR_MODE15_Msk                   (0x03UL << GPIO_CFGHR_MODE15_Pos)
#define GPIO_CFGHR_MODE15                       GPIO_CFGHR_MODE15_Msk
#define GPIO_CFGHR_CNF15_Pos                    (30U)
#define GPIO_CFGHR_CNF15_Msk                    (0x03UL << GPIO_CFGHR_CNF15_Pos)
#define GPIO_CFGHR_CNF15                        GPIO_CFGHR_CNF15_Msk

/******************  Bit definition for GPIO_INDR register  *******************/
#define GPIO_INDR_IDR0_Pos                      (0U)
#define GPIO_INDR_IDR0_Msk                      (0x01UL << GPIO_INDR_IDR0_Pos)
#define GPIO_INDR_IDR0                          GPIO_INDR_IDR0_Msk
#define GPIO_INDR_IDR1_Pos                      (1U)
#define GPIO_INDR_IDR1_Msk                      (0x01UL << GPIO_INDR_IDR1_Pos)
#define GPIO_INDR_IDR1                          GPIO_INDR_IDR1_Msk
#define GPIO_INDR_IDR2_Pos                      (2U)
#define GPIO_INDR_IDR2_Msk                      (0x01UL << GPIO_INDR_IDR2_Pos)
#define GPIO_INDR_IDR2                          GPIO_INDR_IDR2_Msk
#define GPIO_INDR_IDR3_Pos                      (3U)
#define GPIO_INDR_IDR3_Msk                      (0x01UL << GPIO_INDR_IDR3_Pos)
#define GPIO_INDR_IDR3                          GPIO_INDR_IDR3_Msk
#define GPIO_INDR_IDR4_Pos                      (4U)
#define GPIO_INDR_IDR4_Msk                      (0x01UL << GPIO_INDR_IDR4_Pos)
#define GPIO_INDR_IDR4                          GPIO_INDR_IDR4_Msk
#define GPIO_INDR_IDR5_Pos                      (5U)
#define GPIO_INDR_IDR5_Msk                      (0x01UL << GPIO_INDR_IDR5_Pos)
#define GPIO_INDR_IDR5                          GPIO_INDR_IDR5_Msk
#define GPIO_INDR_IDR6_Pos                      (6U)
#define GPIO_INDR_IDR6_Msk                      (0x01UL << GPIO_INDR_IDR6_Pos)
#define GPIO_INDR_IDR6                          GPIO_INDR_IDR6_Msk
#define GPIO_INDR_IDR7_Pos                      (7U)
#define GPIO_INDR_IDR7_Msk                      (0x01UL << GPIO_INDR_IDR7_Pos)
#define GPIO_INDR_IDR7                          GPIO_INDR_IDR7_Msk
#define GPIO_INDR_IDR8_Pos                      (8U)
#define GPIO_INDR_IDR8_Msk                      (0x01UL << GPIO_INDR_IDR8_Pos)
#define GPIO_INDR_IDR8                          GPIO_INDR_IDR8_Msk
#define GPIO_INDR_IDR9_Pos                      (9U)
#define GPIO_INDR_IDR9_Msk                      (0x01UL << GPIO_INDR_IDR9_Pos)
#define GPIO_INDR_IDR9                          GPIO_INDR_IDR9_Msk
#define GPIO_INDR_IDR10_Pos                     (10U)
#define GPIO_INDR_IDR10_Msk                     (0x01UL << GPIO_INDR_IDR10_Pos)
#define GPIO_INDR_IDR10                         GPIO_INDR_IDR10_Msk
#define GPIO_INDR_IDR11_Pos                     (11U)
#define GPIO_INDR_IDR11_Msk                     (0x01UL << GPIO_INDR_IDR11_Pos)
#define GPIO_INDR_IDR11                         GPIO_INDR_IDR11_Msk
#define GPIO_INDR_IDR12_Pos                     (12U)
#define GPIO_INDR_IDR12_Msk                     (0x01UL << GPIO_INDR_IDR12_Pos)
#define GPIO_INDR_IDR12                         GPIO_INDR_IDR12_Msk
#define GPIO_INDR_IDR13_Pos                     (13U)
#define GPIO_INDR_IDR13_Msk                     (0x01UL << GPIO_INDR_IDR13_Pos)
#define GPIO_INDR_IDR13                         GPIO_INDR_IDR13_Msk
#define GPIO_INDR_IDR14_Pos                     (14U)
#define GPIO_INDR_IDR14_Msk                     (0x01UL << GPIO_INDR_IDR14_Pos)
#define GPIO_INDR_IDR14                         GPIO_INDR_IDR14_Msk
#define GPIO_INDR_IDR15_Pos                     (15U)
#define GPIO_INDR_IDR15_Msk                     (0x01UL << GPIO_INDR_IDR15_Pos)
#define GPIO_INDR_IDR15                         GPIO_INDR_IDR15_Msk

/******************  Bit definition for GPIO_OUTDR register  ******************/
#define GPIO_OUTDR_ODR0_Pos                     (0U)
#define GPIO_OUTDR_ODR0_Msk                     (0x01UL << GPIO_OUTDR_ODR0_Pos)
#define GPIO_OUTDR_ODR0                         GPIO_OUTDR_ODR0_Msk
#define GPIO_OUTDR_ODR1_Pos                     (1U)
#define GPIO_OUTDR_ODR1_Msk                     (0x01UL << GPIO_OUTDR_ODR1_Pos)
#define GPIO_OUTDR_ODR1                         GPIO_OUTDR_ODR1_Msk
#define GPIO_OUTDR_ODR2_Pos                     (2U)
#define GPIO_OUTDR_ODR2_Msk                     (0x01UL << GPIO_OUTDR_ODR2_Pos)
#define GPIO_OUTDR_ODR2                         GPIO_OUTDR_ODR2_Msk
#define GPIO_OUTDR_ODR3_Pos                     (3U)
#define GPIO_OUTDR_ODR3_Msk                     (0x01UL << GPIO_OUTDR_ODR3_Pos)
#define GPIO_OUTDR_ODR3                         GPIO_OUTDR_ODR3_Msk
#define GPIO_OUTDR_ODR4_Pos                     (4U)
#define GPIO_OUTDR_ODR4_Msk                     (0x01UL << GPIO_OUTDR_ODR4_Pos)
#define GPIO_OUTDR_ODR4                         GPIO_OUTDR_ODR4_Msk
#define GPIO_OUTDR_ODR5_Pos                     (5U)
#define GPIO_OUTDR_ODR5_Msk                     (0x01UL << GPIO_OUTDR_ODR5_Pos)
#define GPIO_OUTDR_ODR5                         GPIO_OUTDR_ODR5_Msk
#define GPIO_OUTDR_ODR6_Pos                     (6U)
#define GPIO_OUTDR_ODR6_Msk                     (0x01UL << GPIO_OUTDR_ODR6_Pos)
#define GPIO_OUTDR_ODR6                         GPIO_OUTDR_ODR6_Msk
#define GPIO_OUTDR_ODR7_Pos                     (7U)
#define GPIO_OUTDR_ODR7_Msk                     (0x01UL << GPIO_OUTDR_ODR7_Pos)
#define GPIO_OUTDR_ODR7                         GPIO_OUTDR_ODR7_Msk
#define GPIO_OUTDR_ODR8_Pos                     (8U)
#define GPIO_OUTDR_ODR8_Msk                     (0x01UL << GPIO_OUTDR_ODR8_Pos)
#define GPIO_OUTDR_ODR8                         GPIO_OUTDR_ODR8_Msk
#define GPIO_OUTDR_ODR9_Pos                     (9U)
#define GPIO_OUTDR_ODR9_Msk                     (0x01UL << GPIO_OUTDR_ODR9_Pos)
#define GPIO_OUTDR_ODR9                         GPIO_OUTDR_ODR9_Msk
#define GPIO_OUTDR_ODR10_Pos                    (10U)
#define GPIO_OUTDR_ODR10_Msk                    (0x01UL << GPIO_OUTDR_ODR10_Pos)
#define GPIO_OUTDR_ODR10                        GPIO_OUTDR_ODR10_Msk
#define GPIO_OUTDR_ODR11_Pos                    (11U)
#define GPIO_OUTDR_ODR11_Msk                    (0x01UL << GPIO_OUTDR_ODR11_Pos)
#define GPIO_OUTDR_ODR11                        GPIO_OUTDR_ODR11_Msk
#define GPIO_OUTDR_ODR12_Pos                    (12U)
#define GPIO_OUTDR_ODR12_Msk                    (0x01UL << GPIO_OUTDR_ODR12_Pos)
#define GPIO_OUTDR_ODR12                        GPIO_OUTDR_ODR12_Msk
#define GPIO_OUTDR_ODR13_Pos                    (13U)
#define GPIO_OUTDR_ODR13_Msk                    (0x01UL << GPIO_OUTDR_ODR13_Pos)
#define GPIO_OUTDR_ODR13                        GPIO_OUTDR_ODR13_Msk
#define GPIO_OUTDR_ODR14_Pos                    (14U)
#define GPIO_OUTDR_ODR14_Msk                    (0x01UL << GPIO_OUTDR_ODR14_Pos)
#define GPIO_OUTDR_ODR14                        GPIO_OUTDR_ODR14_Msk
#define GPIO_OUTDR_ODR15_Pos                    (15U)
#define GPIO_OUTDR_ODR15_Msk                    (0x01UL << GPIO_OUTDR_ODR15_Pos)
#define GPIO_OUTDR_ODR15                        GPIO_OUTDR_ODR15_Msk

/******************  Bit definition for GPIO_BSHR register  *******************/
#define GPIO_BSHR_BS0_Pos               (0U)
#define GPIO_BSHR_BS0_Msk                       (0x01UL << GPIO_BSHR_BS0_Pos)
#define GPIO_BSHR_BS0                           GPIO_BSHR_BS0_Msk
#define GPIO_BSHR_BS1_Pos                       (1U)
#define GPIO_BSHR_BS1_Msk                       (0x01UL << GPIO_BSHR_BS1_Pos)
#define GPIO_BSHR_BS1                           GPIO_BSHR_BS1_Msk
#define GPIO_BSHR_BS2_Pos                       (2U)
#define GPIO_BSHR_BS2_Msk                       (0x01UL << GPIO_BSHR_BS2_Pos)
#define GPIO_BSHR_BS2                           GPIO_BSHR_BS2_Msk
#define GPIO_BSHR_BS3_Pos                       (3U)
#define GPIO_BSHR_BS3_Msk                       (0x01UL << GPIO_BSHR_BS3_Pos)
#define GPIO_BSHR_BS3                           GPIO_BSHR_BS3_Msk
#define GPIO_BSHR_BS4_Pos                       (4U)
#define GPIO_BSHR_BS4_Msk                       (0x01UL << GPIO_BSHR_BS4_Pos)
#define GPIO_BSHR_BS4                           GPIO_BSHR_BS4_Msk
#define GPIO_BSHR_BS5_Pos                       (5U)
#define GPIO_BSHR_BS5_Msk                       (0x01UL << GPIO_BSHR_BS5_Pos)
#define GPIO_BSHR_BS5                           GPIO_BSHR_BS5_Msk
#define GPIO_BSHR_BS6_Pos                       (6U)
#define GPIO_BSHR_BS6_Msk                       (0x01UL << GPIO_BSHR_BS6_Pos)
#define GPIO_BSHR_BS6                           GPIO_BSHR_BS6_Msk
#define GPIO_BSHR_BS7_Pos                       (7U)
#define GPIO_BSHR_BS7_Msk                       (0x01UL << GPIO_BSHR_BS7_Pos)
#define GPIO_BSHR_BS7                           GPIO_BSHR_BS7_Msk
#define GPIO_BSHR_BS8_Pos                       (8U)
#define GPIO_BSHR_BS8_Msk                       (0x01UL << GPIO_BSHR_BS8_Pos)
#define GPIO_BSHR_BS8                           GPIO_BSHR_BS8_Msk
#define GPIO_BSHR_BS9_Pos                       (9U)
#define GPIO_BSHR_BS9_Msk                       (0x01UL << GPIO_BSHR_BS9_Pos)
#define GPIO_BSHR_BS9                           GPIO_BSHR_BS9_Msk
#define GPIO_BSHR_BS10_Pos                      (10U)
#define GPIO_BSHR_BS10_Msk                      (0x01UL << GPIO_BSHR_BS10_Pos)
#define GPIO_BSHR_BS10                          GPIO_BSHR_BS10_Msk
#define GPIO_BSHR_BS11_Pos                      (11U)
#define GPIO_BSHR_BS11_Msk                      (0x01UL << GPIO_BSHR_BS11_Pos)
#define GPIO_BSHR_BS11                          GPIO_BSHR_BS11_Msk
#define GPIO_BSHR_BS12_Pos                      (12U)
#define GPIO_BSHR_BS12_Msk                      (0x01UL << GPIO_BSHR_BS12_Pos)
#define GPIO_BSHR_BS12                          GPIO_BSHR_BS12_Msk
#define GPIO_BSHR_BS13_Pos                      (13U)
#define GPIO_BSHR_BS13_Msk                      (0x01UL << GPIO_BSHR_BS13_Pos)
#define GPIO_BSHR_BS13                          GPIO_BSHR_BS13_Msk
#define GPIO_BSHR_BS14_Pos                      (14U)
#define GPIO_BSHR_BS14_Msk                      (0x01UL << GPIO_BSHR_BS14_Pos)
#define GPIO_BSHR_BS14                          GPIO_BSHR_BS14_Msk
#define GPIO_BSHR_BS15_Pos                      (15U)
#define GPIO_BSHR_BS15_Msk                      (0x01UL << GPIO_BSHR_BS15_Pos)
#define GPIO_BSHR_BS15                          GPIO_BSHR_BS15_Msk
#define GPIO_BSHR_BR0_Pos                       (16U)
#define GPIO_BSHR_BR0_Msk                       (0x01UL << GPIO_BSHR_BR0_Pos)
#define GPIO_BSHR_BR0                           GPIO_BSHR_BR0_Msk
#define GPIO_BSHR_BR1_Pos                       (17U)
#define GPIO_BSHR_BR1_Msk                       (0x01UL << GPIO_BSHR_BR1_Pos)
#define GPIO_BSHR_BR1                           GPIO_BSHR_BR1_Msk
#define GPIO_BSHR_BR2_Pos                       (18U)
#define GPIO_BSHR_BR2_Msk                       (0x01UL << GPIO_BSHR_BR2_Pos)
#define GPIO_BSHR_BR2                           GPIO_BSHR_BR2_Msk
#define GPIO_BSHR_BR3_Pos                       (19U)
#define GPIO_BSHR_BR3_Msk                       (0x01UL << GPIO_BSHR_BR3_Pos)
#define GPIO_BSHR_BR3                           GPIO_BSHR_BR3_Msk
#define GPIO_BSHR_BR4_Pos                       (20U)
#define GPIO_BSHR_BR4_Msk                       (0x01UL << GPIO_BSHR_BR4_Pos)
#define GPIO_BSHR_BR4                           GPIO_BSHR_BR4_Msk
#define GPIO_BSHR_BR5_Pos                       (21U)
#define GPIO_BSHR_BR5_Msk                       (0x01UL << GPIO_BSHR_BR5_Pos)
#define GPIO_BSHR_BR5                           GPIO_BSHR_BR5_Msk
#define GPIO_BSHR_BR6_Pos                       (22U)
#define GPIO_BSHR_BR6_Msk                       (0x01UL << GPIO_BSHR_BR6_Pos)
#define GPIO_BSHR_BR6                           GPIO_BSHR_BR6_Msk
#define GPIO_BSHR_BR7_Pos                       (23U)
#define GPIO_BSHR_BR7_Msk                       (0x01UL << GPIO_BSHR_BR7_Pos)
#define GPIO_BSHR_BR7                           GPIO_BSHR_BR7_Msk
#define GPIO_BSHR_BR8_Pos                       (24U)
#define GPIO_BSHR_BR8_Msk                       (0x01UL << GPIO_BSHR_BR8_Pos)
#define GPIO_BSHR_BR8                           GPIO_BSHR_BR8_Msk
#define GPIO_BSHR_BR9_Pos                       (25U)
#define GPIO_BSHR_BR9_Msk                       (0x01UL << GPIO_BSHR_BR9_Pos)
#define GPIO_BSHR_BR9                           GPIO_BSHR_BR9_Msk
#define GPIO_BSHR_BR10_Pos                      (26U)
#define GPIO_BSHR_BR10_Msk                      (0x01UL << GPIO_BSHR_BR10_Pos)
#define GPIO_BSHR_BR10                          GPIO_BSHR_BR10_Msk
#define GPIO_BSHR_BR11_Pos                      (27U)
#define GPIO_BSHR_BR11_Msk                      (0x01UL << GPIO_BSHR_BR11_Pos)
#define GPIO_BSHR_BR11                          GPIO_BSHR_BR11_Msk
#define GPIO_BSHR_BR12_Pos                      (28U)
#define GPIO_BSHR_BR12_Msk                      (0x01UL << GPIO_BSHR_BR12_Pos)
#define GPIO_BSHR_BR12                          GPIO_BSHR_BR12_Msk
#define GPIO_BSHR_BR13_Pos                      (29U)
#define GPIO_BSHR_BR13_Msk                      (0x01UL << GPIO_BSHR_BR13_Pos)
#define GPIO_BSHR_BR13                          GPIO_BSHR_BR13_Msk
#define GPIO_BSHR_BR14_Pos                      (30U)
#define GPIO_BSHR_BR14_Msk                      (0x01UL << GPIO_BSHR_BR14_Pos)
#define GPIO_BSHR_BR14                          GPIO_BSHR_BR14_Msk
#define GPIO_BSHR_BR15_Pos                      (31U)
#define GPIO_BSHR_BR15_Msk                      (0x01UL << GPIO_BSHR_BR15_Pos)
#define GPIO_BSHR_BR15                          GPIO_BSHR_BR15_Msk

/******************  Bit definition for GPIO_BCR register  ********************/
#define GPIO_BCR_BR0_Pos                        (0U)
#define GPIO_BCR_BR0_Msk                        (0x01UL << GPIO_BCR_BR0_Pos)
#define GPIO_BCR_BR0                            GPIO_BCR_BR0_Msk
#define GPIO_BCR_BR1_Pos                        (1U)
#define GPIO_BCR_BR1_Msk                        (0x01UL << GPIO_BCR_BR1_Pos)
#define GPIO_BCR_BR1                            GPIO_BCR_BR1_Msk
#define GPIO_BCR_BR2_Pos                        (2U)
#define GPIO_BCR_BR2_Msk                        (0x01UL << GPIO_BCR_BR2_Pos)
#define GPIO_BCR_BR2                            GPIO_BCR_BR2_Msk
#define GPIO_BCR_BR3_Pos                        (3U)
#define GPIO_BCR_BR3_Msk                        (0x01UL << GPIO_BCR_BR3_Pos)
#define GPIO_BCR_BR3                            GPIO_BCR_BR3_Msk
#define GPIO_BCR_BR4_Pos                        (4U)
#define GPIO_BCR_BR4_Msk                        (0x01UL << GPIO_BCR_BR4_Pos)
#define GPIO_BCR_BR4                            GPIO_BCR_BR4_Msk
#define GPIO_BCR_BR5_Pos                        (5U)
#define GPIO_BCR_BR5_Msk                        (0x01UL << GPIO_BCR_BR5_Pos)
#define GPIO_BCR_BR5                            GPIO_BCR_BR5_Msk
#define GPIO_BCR_BR6_Pos                        (6U)
#define GPIO_BCR_BR6_Msk                        (0x01UL << GPIO_BCR_BR6_Pos)
#define GPIO_BCR_BR6                            GPIO_BCR_BR6_Msk
#define GPIO_BCR_BR7_Pos                        (7U)
#define GPIO_BCR_BR7_Msk                        (0x01UL << GPIO_BCR_BR7_Pos)
#define GPIO_BCR_BR7                            GPIO_BCR_BR7_Msk
#define GPIO_BCR_BR8_Pos                        (8U)
#define GPIO_BCR_BR8_Msk                        (0x01UL << GPIO_BCR_BR8_Pos)
#define GPIO_BCR_BR8                            GPIO_BCR_BR8_Msk
#define GPIO_BCR_BR9_Pos                        (9U)
#define GPIO_BCR_BR9_Msk                        (0x01UL << GPIO_BCR_BR9_Pos)
#define GPIO_BCR_BR9                            GPIO_BCR_BR9_Msk
#define GPIO_BCR_BR10_Pos                       (10U)
#define GPIO_BCR_BR10_Msk                       (0x01UL << GPIO_BCR_BR10_Pos)
#define GPIO_BCR_BR10                           GPIO_BCR_BR10_Msk
#define GPIO_BCR_BR11_Pos                       (11U)
#define GPIO_BCR_BR11_Msk                       (0x01UL << GPIO_BCR_BR11_Pos)
#define GPIO_BCR_BR11                           GPIO_BCR_BR11_Msk
#define GPIO_BCR_BR12_Pos                       (12U)
#define GPIO_BCR_BR12_Msk                       (0x01UL << GPIO_BCR_BR12_Pos)
#define GPIO_BCR_BR12                           GPIO_BCR_BR12_Msk
#define GPIO_BCR_BR13_Pos                       (13U)
#define GPIO_BCR_BR13_Msk                       (0x01UL << GPIO_BCR_BR13_Pos)
#define GPIO_BCR_BR13                           GPIO_BCR_BR13_Msk
#define GPIO_BCR_BR14_Pos                       (14U)
#define GPIO_BCR_BR14_Msk                       (0x01UL << GPIO_BCR_BR14_Pos)
#define GPIO_BCR_BR14                           GPIO_BCR_BR14_Msk
#define GPIO_BCR_BR15_Pos                       (15U)
#define GPIO_BCR_BR15_Msk                       (0x01UL << GPIO_BCR_BR15_Pos)
#define GPIO_BCR_BR15                           GPIO_BCR_BR15_Msk

/******************  Bit definition for GPIO_LCKR register  *******************/
#define GPIO_LCKR_LCK0_Pos                      (0U)
#define GPIO_LCKR_LCK0_Msk                      (0x01UL << GPIO_LCKR_LCK0_Pos)
#define GPIO_LCKR_LCK0                          GPIO_LCKR_LCK0_Msk
#define GPIO_LCKR_LCK1_Pos                      (1U)
#define GPIO_LCKR_LCK1_Msk                      (0x01UL << GPIO_LCKR_LCK1_Pos)
#define GPIO_LCKR_LCK1                          GPIO_LCKR_LCK1_Msk
#define GPIO_LCKR_LCK2_Pos                      (2U)
#define GPIO_LCKR_LCK2_Msk                      (0x01UL << GPIO_LCKR_LCK2_Pos)
#define GPIO_LCKR_LCK2                          GPIO_LCKR_LCK2_Msk
#define GPIO_LCKR_LCK3_Pos                      (3U)
#define GPIO_LCKR_LCK3_Msk                      (0x01UL << GPIO_LCKR_LCK3_Pos)
#define GPIO_LCKR_LCK3                          GPIO_LCKR_LCK3_Msk
#define GPIO_LCKR_LCK4_Pos                      (4U)
#define GPIO_LCKR_LCK4_Msk                      (0x01UL << GPIO_LCKR_LCK4_Pos)
#define GPIO_LCKR_LCK4                          GPIO_LCKR_LCK4_Msk
#define GPIO_LCKR_LCK5_Pos                      (5U)
#define GPIO_LCKR_LCK5_Msk                      (0x01UL << GPIO_LCKR_LCK5_Pos)
#define GPIO_LCKR_LCK5                          GPIO_LCKR_LCK5_Msk
#define GPIO_LCKR_LCK6_Pos                      (6U)
#define GPIO_LCKR_LCK6_Msk                      (0x01UL << GPIO_LCKR_LCK6_Pos)
#define GPIO_LCKR_LCK6                          GPIO_LCKR_LCK6_Msk
#define GPIO_LCKR_LCK7_Pos                      (7U)
#define GPIO_LCKR_LCK7_Msk                      (0x01UL << GPIO_LCKR_LCK7_Pos)
#define GPIO_LCKR_LCK7                          GPIO_LCKR_LCK7_Msk
#define GPIO_LCKR_LCK8_Pos                      (8U)
#define GPIO_LCKR_LCK8_Msk                      (0x01UL << GPIO_LCKR_LCK8_Pos)
#define GPIO_LCKR_LCK8                          GPIO_LCKR_LCK8_Msk
#define GPIO_LCKR_LCK9_Pos                      (9U)
#define GPIO_LCKR_LCK9_Msk                      (0x01UL << GPIO_LCKR_LCK9_Pos)
#define GPIO_LCKR_LCK9                          GPIO_LCKR_LCK9_Msk
#define GPIO_LCKR_LCK10_Pos                     (10U)
#define GPIO_LCKR_LCK10_Msk                     (0x01UL << GPIO_LCKR_LCK10_Pos)
#define GPIO_LCKR_LCK10                         GPIO_LCKR_LCK10_Msk
#define GPIO_LCKR_LCK11_Pos                     (11U)
#define GPIO_LCKR_LCK11_Msk                     (0x01UL << GPIO_LCKR_LCK11_Pos)
#define GPIO_LCKR_LCK11                         GPIO_LCKR_LCK11_Msk
#define GPIO_LCKR_LCK12_Pos                     (12U)
#define GPIO_LCKR_LCK12_Msk                     (0x01UL << GPIO_LCKR_LCK12_Pos)
#define GPIO_LCKR_LCK12                         GPIO_LCKR_LCK12_Msk
#define GPIO_LCKR_LCK13_Pos                     (13U)
#define GPIO_LCKR_LCK13_Msk                     (0x01UL << GPIO_LCKR_LCK13_Pos)
#define GPIO_LCKR_LCK13                         GPIO_LCKR_LCK13_Msk
#define GPIO_LCKR_LCK14_Pos                     (14U)
#define GPIO_LCKR_LCK14_Msk                     (0x01UL << GPIO_LCKR_LCK14_Pos)
#define GPIO_LCKR_LCK14                         GPIO_LCKR_LCK14_Msk
#define GPIO_LCKR_LCK15_Pos                     (15U)
#define GPIO_LCKR_LCK15_Msk                     (0x01UL << GPIO_LCKR_LCK15_Pos)
#define GPIO_LCKR_LCK15                         GPIO_LCKR_LCK15_Msk

/******************  Bit definition for AFIO_PCFR1 register  ******************/
#define AFIO_PCFR1_SPI1_RM_Pos                  (0U)
#define AFIO_PCFR1_SPI1_RM_Msk                  (0x01UL << AFIO_PCFR1_SPI1_RM_Pos)
#define AFIO_PCFR1_SPI1_RM                      AFIO_PCFR1_SPI1_RM_Msk
#define AFIO_PCFR1_I2C1_RM_Pos                  (1U)
#define AFIO_PCFR1_I2C1_RM_Msk                  (0x01UL << AFIO_PCFR1_I2C1_RM_Pos)
#define AFIO_PCFR1_I2C1_RM                      AFIO_PCFR1_I2C1_RM_Msk
#define AFIO_PCFR1_USART1_RM_Pos                (2U)
#define AFIO_PCFR1_USART1_RM_Msk                (0x01UL << AFIO_PCFR1_USART1_RM_Pos)
#define AFIO_PCFR1_USART1_RM                    AFIO_PCFR1_USART1_RM_Msk
#define AFIO_PCFR1_TIM1_RM_Pos                  (6U)
#define AFIO_PCFR1_TIM1_RM_Msk                  (0x03UL << AFIO_PCFR1_TIM1_RM_Pos)
#define AFIO_PCFR1_TIM1_RM                      AFIO_PCFR1_TIM1_RM_Msk
#define AFIO_PCFR1_TIM2_RM_Pos                  (8U)
#define AFIO_PCFR1_TIM2_RM_Msk                  (0x03UL << AFIO_PCFR1_TIM2_RM_Pos)
#define AFIO_PCFR1_TIM2_RM                      AFIO_PCFR1_TIM2_RM_Msk
#define AFIO_PCFR1_PA12_RM_Pos                  (15U)
#define AFIO_PCFR1_PA12_RM_Msk                  (0x01UL << AFIO_PCFR1_PA12_RM_Pos)
#define AFIO_PCFR1_PA12_RM                      AFIO_PCFR1_PA12_RM_Msk
#define AFIO_PCFR1_ADC_ETRGINJ_RM_Pos           (17U)
#define AFIO_PCFR1_ADC_ETRGINJ_RM_Msk           (0x01UL << AFIO_PCFR1_ADC_ETRGINJ_RM_Pos)
#define AFIO_PCFR1_ADC_ETRGINJ_RM               AFIO_PCFR1_ADC_ETRGINJ_RM_Msk
#define AFIO_PCFR1_ADC_ETRGREG_RM_Pos           (18U)
#define AFIO_PCFR1_ADC_ETRGREG_RM_Msk           (0x01UL << AFIO_PCFR1_ADC_ETRGREG_RM_Pos)
#define AFIO_PCFR1_ADC_ETRGREG_RM               AFIO_PCFR1_ADC_ETRGREG_RM_Msk
#define AFIO_PCFR1_USART1_RM1_Pos               (21U)
#define AFIO_PCFR1_USART1_RM1_Msk               (0x01UL << AFIO_PCFR1_USART1_RM1_Pos)
#define AFIO_PCFR1_USART1_RM1                   AFIO_PCFR1_USART1_RM1_Msk
#define AFIO_PCFR1_I2C1_RM1_Pos                 (22U)
#define AFIO_PCFR1_I2C1_RM1_Msk                 (0x01UL << AFIO_PCFR1_I2C1_RM1_Pos)
#define AFIO_PCFR1_I2C1_RM1                     AFIO_PCFR1_I2C1_RM1_Msk
#define AFIO_PCFR1_TIM1_IRM_Pos                 (23U)
#define AFIO_PCFR1_TIM1_IRM_Msk                 (0x01UL << AFIO_PCFR1_TIM1_IRM_Pos)
#define AFIO_PCFR1_TIM1_IRM                     AFIO_PCFR1_TIM1_IRM_Msk
#define AFIO_PCFR1_SWCFG_RM_Pos                 (24U)
#define AFIO_PCFR1_SWCFG_RM_Msk                 (0x07UL << AFIO_PCFR1_SWCFG_RM_Pos)
#define AFIO_PCFR1_SWCFG_RM                     AFIO_PCFR1_SWCFG_RM_Msk

/******************  Bit definition for AFIO_EXTICR register  *****************/
#define AFIO_EXTICR_EXTI0_Pos                   (0U)
#define AFIO_EXTICR_EXTI0_Msk                   (0x03UL << AFIO_EXTICR_EXTI0_Pos)
#define AFIO_EXTICR_EXTI0                       AFIO_EXTICR_EXTI0_Msk
#define AFIO_EXTICR_EXTI1_Pos                   (2U)
#define AFIO_EXTICR_EXTI1_Msk                   (0x03UL << AFIO_EXTICR_EXTI1_Pos)
#define AFIO_EXTICR_EXTI1                       AFIO_EXTICR_EXTI1_Msk
#define AFIO_EXTICR_EXTI2_Pos                   (4U)
#define AFIO_EXTICR_EXTI2_Msk                   (0x03UL << AFIO_EXTICR_EXTI2_Pos)
#define AFIO_EXTICR_EXTI2                       AFIO_EXTICR_EXTI2_Msk
#define AFIO_EXTICR_EXTI3_Pos                   (6U)
#define AFIO_EXTICR_EXTI3_Msk                   (0x03UL << AFIO_EXTICR_EXTI3_Pos)
#define AFIO_EXTICR_EXTI3                       AFIO_EXTICR_EXTI3_Msk
#define AFIO_EXTICR_EXTI4_Pos                   (8U)
#define AFIO_EXTICR_EXTI4_Msk                   (0x03UL << AFIO_EXTICR_EXTI4_Pos)
#define AFIO_EXTICR_EXTI4                       AFIO_EXTICR_EXTI4_Msk
#define AFIO_EXTICR_EXTI5_Pos                   (10U)
#define AFIO_EXTICR_EXTI5_Msk                   (0x03UL << AFIO_EXTICR_EXTI5_Pos)
#define AFIO_EXTICR_EXTI5                       AFIO_EXTICR_EXTI5_Msk
#define AFIO_EXTICR_EXTI6_Pos                   (12U)
#define AFIO_EXTICR_EXTI6_Msk                   (0x03UL << AFIO_EXTICR_EXTI6_Pos)
#define AFIO_EXTICR_EXTI6                       AFIO_EXTICR_EXTI6_Msk
#define AFIO_EXTICR_EXTI7_Pos                   (14U)
#define AFIO_EXTICR_EXTI7_Msk                   (0x03UL << AFIO_EXTICR_EXTI7_Pos)
#define AFIO_EXTICR_EXTI7                       AFIO_EXTICR_EXTI7_Msk

/******************************************************************************/
/*                            Independent WATCHDOG                            */
/******************************************************************************/
/******************  Bit definition for IWDG_CTLR register  *******************/
#define IWDG_CTLR_KEY_Pos                       (0U)
#define IWDG_CTLR_KEY_Msk                       (0xFFFFUL << IWDG_CTLR_KEY_Pos)
#define IWDG_CTLR_KEY                           IWDG_CTLR_KEY_Msk

/******************  Bit definition for IWDG_PSCR register  *******************/
#define IWDG_PSCR_PR_Pos                        (0U)
#define IWDG_PSCR_PR_Msk                        (0x07UL << IWDG_PSCR_PR_Pos)
#define IWDG_PSCR_PR                            IWDG_PSCR_PR_Msk

/******************  Bit definition for IWDG_RLDR register  *******************/
#define IWDG_RLDR_RL_Pos                        (0U)
#define IWDG_RLDR_RL_Msk                        (0x0FFFUL << IWDG_RLDR_RL_Pos)
#define IWDG_RLDR_RL                            IWDG_RLDR_RL_Msk

/******************  Bit definition for IWDG_STATR register  ******************/
#define IWDG_STATR_PVU_Pos                      (0U)
#define IWDG_STATR_PVU_Msk                      (0x01UL << IWDG_STATR_PVU_Pos)
#define IWDG_STATR_PVU                          IWDG_STATR_PVU_Msk
#define IWDG_STATR_RVU_Pos                      (1U)
#define IWDG_STATR_RVU_Msk                      (0x01UL << IWDG_STATR_RVU_Pos)
#define IWDG_STATR_RVU                          IWDG_STATR_RVU_Msk

/******************************************************************************/
/*                     Inter-integrated Circuit Interface                     */
/******************************************************************************/
/******************  Bit definition for I2C_CTLR1 register  *******************/
#define I2C_CTLR1_PE_Pos                        (0U)
#define I2C_CTLR1_PE_Msk                        (0x01UL << I2C_CTLR1_PE_Pos)
#define I2C_CTLR1_PE                            I2C_CTLR1_PE_Msk
#define I2C_CTLR1_ENPEC_Pos                     (5U)
#define I2C_CTLR1_ENPEC_Msk                     (0x01UL << I2C_CTLR1_ENPEC_Pos)
#define I2C_CTLR1_ENPEC                         I2C_CTLR1_ENPEC_Msk
#define I2C_CTLR1_ENGC_Pos                      (6U)
#define I2C_CTLR1_ENGC_Msk                      (0x01UL << I2C_CTLR1_ENGC_Pos)
#define I2C_CTLR1_ENGC                          I2C_CTLR1_ENGC_Msk
#define I2C_CTLR1_NOSTRETCH_Pos                 (7U)
#define I2C_CTLR1_NOSTRETCH_Msk                 (0x01UL << I2C_CTLR1_NOSTRETCH_Pos)
#define I2C_CTLR1_NOSTRETCH                     I2C_CTLR1_NOSTRETCH_Msk
#define I2C_CTLR1_START_Pos                     (8U)
#define I2C_CTLR1_START_Msk                     (0x01UL << I2C_CTLR1_START_Pos)
#define I2C_CTLR1_START                         I2C_CTLR1_START_Msk
#define I2C_CTLR1_STOP_Pos                      (9U)
#define I2C_CTLR1_STOP_Msk                      (0x01UL << I2C_CTLR1_STOP_Pos)
#define I2C_CTLR1_STOP                          I2C_CTLR1_STOP_Msk
#define I2C_CTLR1_ACK_Pos                       (10U)
#define I2C_CTLR1_ACK_Msk                       (0x01UL << I2C_CTLR1_ACK_Pos)
#define I2C_CTLR1_ACK                           I2C_CTLR1_ACK_Msk
#define I2C_CTLR1_POS_Pos                       (11U)
#define I2C_CTLR1_POS_Msk                       (0x01UL << I2C_CTLR1_POS_Pos)
#define I2C_CTLR1_POS                           I2C_CTLR1_POS_Msk
#define I2C_CTLR1_PEC_Pos                       (12U)
#define I2C_CTLR1_PEC_Msk                       (0x01UL << I2C_CTLR1_PEC_Pos)
#define I2C_CTLR1_PEC                           I2C_CTLR1_PEC_Msk
#define I2C_CTLR1_SWRST_Pos                     (15U)
#define I2C_CTLR1_SWRST_Msk                     (0x01UL << I2C_CTLR1_SWRST_Pos)
#define I2C_CTLR1_SWRST                         I2C_CTLR1_SWRST_Msk

/******************  Bit definition for I2C_CTLR2 register  *******************/
#define I2C_CTLR2_FREQ_Pos                      (0U)
#define I2C_CTLR2_FREQ_Msk                      (0x3FUL << I2C_CTLR2_FREQ_Pos)
#define I2C_CTLR2_FREQ                          I2C_CTLR2_FREQ_Msk
#define I2C_CTLR2_ITERREN_Pos                   (8U)
#define I2C_CTLR2_ITERREN_Msk                   (0x01UL << I2C_CTLR2_ITERREN_Pos)
#define I2C_CTLR2_ITERREN                       I2C_CTLR2_ITERREN_Msk
#define I2C_CTLR2_ITEVTEN_Pos                   (9U)
#define I2C_CTLR2_ITEVTEN_Msk                   (0x01UL << I2C_CTLR2_ITEVTEN_Pos)
#define I2C_CTLR2_ITEVTEN                       I2C_CTLR2_ITEVTEN_Msk
#define I2C_CTLR2_ITBUFEN_Pos                   (10U)
#define I2C_CTLR2_ITBUFEN_Msk                   (0x01UL << I2C_CTLR2_ITBUFEN_Pos)
#define I2C_CTLR2_ITBUFEN                       I2C_CTLR2_ITBUFEN_Msk
#define I2C_CTLR2_DMAEN_Pos                     (11U)
#define I2C_CTLR2_DMAEN_Msk                     (0x01UL << I2C_CTLR2_DMAEN_Pos)
#define I2C_CTLR2_DMAEN                         I2C_CTLR2_DMAEN_Msk
#define I2C_CTLR2_LAST_Pos                      (12U)
#define I2C_CTLR2_LAST_Msk                      (0x01UL << I2C_CTLR2_LAST_Pos)
#define I2C_CTLR2_LAST                          I2C_CTLR2_LAST_Msk

/******************  Bit definition for I2C_OAR1 register  ********************/
#define I2C_OAR1_ADD_Pos                        (0U)
#define I2C_OAR1_ADD_Msk                        (0x03FF << I2C_OAR1_ADD_Pos)
#define I2C_OAR1_ADD                            I2C_OAR1_ADD_Msk
#define I2C_OAR1_ADDMODE_Pos                    (15U)
#define I2C_OAR1_ADDMODE_Msk                    (0x01UL << I2C_OAR1_ADDMODE_Pos)
#define I2C_OAR1_ADDMODE                        I2C_OAR1_ADDMODE_Msk

/******************  Bit definition for I2C_OAR2 register  ********************/
#define I2C_OAR2_ENDUAL_Pos                     (0U)
#define I2C_OAR2_ENDUAL_Msk                     (0x01UL << I2C_OAR2_ENDUAL_Pos)
#define I2C_OAR2_ENDUAL                         I2C_OAR2_ENDUAL_Msk
#define I2C_OAR2_ADD2_Pos                       (1U)
#define I2C_OAR2_ADD2_Msk                       (0x7FUL << I2C_OAR2_ADD2_Pos)
#define I2C_OAR2_ADD2                           I2C_OAR2_ADD2_Msk

/******************  Bit definition for I2C_DATAR register  *******************/
#define I2C_DATAR_DR_Pos                        (0U)
#define I2C_DATAR_DR_Msk                        (0xFFUL << I2C_DATAR_DR_Pos)
#define I2C_DATAR_DR                            I2C_DATAR_DR_Msk

/******************  Bit definition for I2C_STAR1 register  *******************/
#define I2C_STAR1_SB_Pos                        (0U)
#define I2C_STAR1_SB_Msk                        (0x01UL << I2C_STAR1_SB_Pos)
#define I2C_STAR1_SB                            I2C_STAR1_SB_Msk
#define I2C_STAR1_ADDR_Pos                      (1U)
#define I2C_STAR1_ADDR_Msk                      (0x01UL << I2C_STAR1_ADDR_Pos)
#define I2C_STAR1_ADDR                          I2C_STAR1_ADDR_Msk
#define I2C_STAR1_BTF_Pos                       (2U)
#define I2C_STAR1_BTF_Msk                       (0x01UL << I2C_STAR1_BTF_Pos)
#define I2C_STAR1_BTF                           I2C_STAR1_BTF_Msk
#define I2C_STAR1_ADD10_Pos                     (3U)
#define I2C_STAR1_ADD10_Msk                     (0x01UL << I2C_STAR1_ADD10_Pos)
#define I2C_STAR1_ADD10                         I2C_STAR1_ADD10_Msk
#define I2C_STAR1_STOPF_Pos                     (4U)
#define I2C_STAR1_STOPF_Msk                     (0x01UL << I2C_STAR1_STOPF_Pos)
#define I2C_STAR1_STOPF                         I2C_STAR1_STOPF_Msk
#define I2C_STAR1_RXNE_Pos                      (6U)
#define I2C_STAR1_RXNE_Msk                      (0x01UL << I2C_STAR1_RXNE_Pos)
#define I2C_STAR1_RXNE                          I2C_STAR1_RXNE_Msk
#define I2C_STAR1_TXE_Pos                       (7U)
#define I2C_STAR1_TXE_Msk                       (0x01UL << I2C_STAR1_TXE_Pos)
#define I2C_STAR1_TXE                           I2C_STAR1_TXE_Msk
#define I2C_STAR1_BERR_Pos                      (8U)
#define I2C_STAR1_BERR_Msk                      (0x01UL << I2C_STAR1_BERR_Pos)
#define I2C_STAR1_BERR                          I2C_STAR1_BERR_Msk
#define I2C_STAR1_ARLO_Pos                      (9U)
#define I2C_STAR1_ARLO_Msk                      (0x01UL << I2C_STAR1_ARLO_Pos)
#define I2C_STAR1_ARLO                          I2C_STAR1_ARLO_Msk
#define I2C_STAR1_AF_Pos                        (10U)
#define I2C_STAR1_AF_Msk                        (0x01UL << I2C_STAR1_AF_Pos)
#define I2C_STAR1_AF                            I2C_STAR1_AF_Msk
#define I2C_STAR1_OVR_Pos                       (11U)
#define I2C_STAR1_OVR_Msk                       (0x01UL << I2C_STAR1_OVR_Pos)
#define I2C_STAR1_OVR                           I2C_STAR1_OVR_Msk
#define I2C_STAR1_PECERR_Pos                    (12U)
#define I2C_STAR1_PECERR_Msk                    (0x01UL << I2C_STAR1_PECERR_Pos)
#define I2C_STAR1_PECERR                        I2C_STAR1_PECERR_Msk

/******************  Bit definition for I2C_STAR2 register  *******************/
#define I2C_STAR2_MSL_Pos                       (0U)
#define I2C_STAR2_MSL_Msk                       (0x01UL << I2C_STAR2_MSL_Pos)
#define I2C_STAR2_MSL                           I2C_STAR2_MSL_Msk
#define I2C_STAR2_BUSY_Pos                      (1U)
#define I2C_STAR2_BUSY_Msk                      (0x01UL << I2C_STAR2_BUSY_Pos)
#define I2C_STAR2_BUSY                          I2C_STAR2_BUSY_Msk
#define I2C_STAR2_TRA_Pos                       (2U)
#define I2C_STAR2_TRA_Msk                       (0x01UL << I2C_STAR2_TRA_Pos)
#define I2C_STAR2_TRA                           I2C_STAR2_TRA_Msk
#define I2C_STAR2_GENCALL_Pos                   (4U)
#define I2C_STAR2_GENCALL_Msk                   (0x01UL << I2C_STAR2_GENCALL_Pos)
#define I2C_STAR2_GENCALL                       I2C_STAR2_GENCALL_Msk
#define I2C_STAR2_DUALF_Pos                     (7U)
#define I2C_STAR2_DUALF_Msk                     (0x01UL << I2C_STAR2_DUALF_Pos)
#define I2C_STAR2_DUALF                         I2C_STAR2_DUALF_Msk
#define I2C_STAR2_PEC_Pos                       (8U)
#define I2C_STAR2_PEC_Msk                       (0xFFUL << I2C_STAR2_PEC_Pos)
#define I2C_STAR2_PEC                           I2C_STAR2_PEC_Msk

/******************  Bit definition for I2C_CKCFGR register  ******************/
#define I2C_CKCFGR_CCR_Pos                      (0U)
#define I2C_CKCFGR_CCR_Msk                      (0x0FFFUL << I2C_CKCFGR_CCR_Pos)
#define I2C_CKCFGR_CCR                          I2C_CKCFGR_CCR_Msk
#define I2C_CKCFGR_DUTY_Pos                     (14U)
#define I2C_CKCFGR_DUTY_Msk                     (0x01UL << I2C_CKCFGR_DUTY_Pos)
#define I2C_CKCFGR_DUTY                         I2C_CKCFGR_DUTY_Msk
#define I2C_CKCFGR_FS_Pos                       (15U)
#define I2C_CKCFGR_FS_Msk                       (0x01UL << I2C_CKCFGR_FS_Pos)
#define I2C_CKCFGR_FS                           I2C_CKCFGR_FS_Msk

/******************************************************************************/
/*                               Power Control                                */
/******************************************************************************/
/******************  Bit definition for PWR_CTLR register  ********************/
#define PWR_CTLR_PDDS_Pos                       (1U)
#define PWR_CTLR_PDDS_Msk                       (0x01UL << PWR_CTLR_PDDS_Pos)
#define PWR_CTLR_PDDS                           PWR_CTLR_PDDS_Msk
#define PWR_CTLR_PVDE_Pos                       (4U)
#define PWR_CTLR_PVDE_Msk                       (0x01UL << PWR_CTLR_PVDE_Pos)
#define PWR_CTLR_PVDE                           PWR_CTLR_PVDE_Msk
#define PWR_CTLR_PLS_Pos                        (5U)
#define PWR_CTLR_PLS_Msk                        (0x07UL << PWR_CTLR_PLS_Pos)
#define PWR_CTLR_PLS                            PWR_CTLR_PLS_Msk

/******************  Bit definition for PWR_CSR register  *********************/
#define PWR_CSR_PVD0_Pos                        (2U)
#define PWR_CSR_PVD0_Msk                        (0x01UL << PWR_CSR_PVD0_Pos)
#define PWR_CSR_PVD0                            PWR_CSR_PVD0_Msk

/******************  Bit definition for PWR_AWUCSR register  ******************/
#define PWR_AWUCSR_AWUEN_Pos                    (1U)
#define PWR_AWUCSR_AWUEN_Msk                    (0x01UL << PWR_AWUCSR_AWUEN_Pos)
#define PWR_AWUCSR_AWUEN                        PWR_AWUCSR_AWUEN_Msk

/******************  Bit definition for PWR_AWUWR register  *******************/
#define PWR_AWUWR_AWUWR_Pos                     (0U)
#define PWR_AWUWR_AWUWR_Msk                     (0x3FUL << PWR_AWUWR_AWUWR_Pos)
#define PWR_AWUWR_AWUWR                         PWR_AWUWR_AWUWR_Msk

/******************  Bit definition for PWR_AWUPSC register  ******************/
#define PWR_AWUPSC_AWUPSC_Pos                   (0U)
#define PWR_AWUPSC_AWUPSC_Msk                   (0x0FUL << PWR_AWUPSC_AWUPSC_Pos)
#define PWR_AWUPSC_AWUPSC                       PWR_AWUPSC_AWUPSC_Msk

/******************************************************************************/
/*                          Reset and Clock Control                           */
/******************************************************************************/
/******************  Bit definition for RCC_CTLR register  ********************/
#define RCC_CTLR_HSION_Pos                      (0U)
#define RCC_CTLR_HSION_Msk                      (0x01UL << RCC_CTLR_HSION_Pos)
#define RCC_CTLR_HSION                          RCC_CTLR_HSION_Msk
#define RCC_CTLR_HSIRDY_Pos                     (1U)
#define RCC_CTLR_HSIRDY_Msk                     (0x01UL << RCC_CTLR_HSIRDY_Pos)
#define RCC_CTLR_HSIRDY                         RCC_CTLR_HSIRDY_Msk
#define RCC_CTLR_HSITRIM_Pos                    (3U)
#define RCC_CTLR_HSITRIM_Msk                    (0x1FUL << RCC_CTLR_HSITRIM_Pos)
#define RCC_CTLR_HSITRIM                        RCC_CTLR_HSITRIM_Msk
#define RCC_CTLR_HSICAL_Pos                     (8U)
#define RCC_CTLR_HSICAL_Msk                     (0xFFUL << RCC_CTLR_HSICAL_Pos)
#define RCC_CTLR_HSICAL                         RCC_CTLR_HSICAL_Msk
#define RCC_CTLR_HSEON_Pos                      (16U)
#define RCC_CTLR_HSEON_Msk                      (0x01UL << RCC_CTLR_HSEON_Pos)
#define RCC_CTLR_HSEON                          RCC_CTLR_HSEON_Msk
#define RCC_CTLR_HSERDY_Pos                     (17U)
#define RCC_CTLR_HSERDY_Msk                     (0x01UL << RCC_CTLR_HSERDY_Pos)
#define RCC_CTLR_HSERDY                         RCC_CTLR_HSERDY_Msk
#define RCC_CTLR_HSEBYP_Pos                     (18U)
#define RCC_CTLR_HSEBYP_Msk                     (0x01UL << RCC_CTLR_HSEBYP_Pos)
#define RCC_CTLR_HSEBYP                         RCC_CTLR_HSEBYP_Msk
#define RCC_CTLR_CSSON_Pos                      (19U)
#define RCC_CTLR_CSSON_Msk                      (0x01UL << RCC_CTLR_CSSON_Pos)
#define RCC_CTLR_CSSON                          RCC_CTLR_CSSON_Msk
#define RCC_CTLR_PLLON_Pos                      (24U)
#define RCC_CTLR_PLLON_Msk                      (0x01UL << RCC_CTLR_PLLON_Pos)
#define RCC_CTLR_PLLON                          RCC_CTLR_PLLON_Msk
#define RCC_CTLR_PLLRDY_Pos                     (25U)
#define RCC_CTLR_PLLRDY_Msk                     (0x01UL << RCC_CTLR_PLLRDY_Pos)
#define RCC_CTLR_PLLRDY                         RCC_CTLR_PLLRDY_Msk

/******************  Bit definition for RCC_CFGR0 register  *******************/
#define RCC_CFGR0_SW_Pos                        (0U)
#define RCC_CFGR0_SW_Msk                        (0x03UL << RCC_CFGR0_SW_Pos)
#define RCC_CFGR0_SW                            RCC_CFGR0_SW_Msk
#define RCC_CFGR0_SWS_Pos                       (2U)
#define RCC_CFGR0_SWS_Msk                       (0x03UL << RCC_CFGR0_SWS_Pos)
#define RCC_CFGR0_SWS                           RCC_CFGR0_SWS_Msk
#define RCC_CFGR0_HPRE_Pos                      (4U)
#define RCC_CFGR0_HPRE_Msk                      (0x0FUL << RCC_CFGR0_HPRE_Pos)
#define RCC_CFGR0_HPRE                          RCC_CFGR0_HPRE_Msk
#define RCC_CFGR0_ADCPRE_Pos                    (11U)
#define RCC_CFGR0_ADCPRE_Msk                    (0x1FUL << RCC_CFGR0_ADCPRE_Pos)
#define RCC_CFGR0_ADCPRE                        RCC_CFGR0_ADCPRE_Msk
#define RCC_CFGR0_PLLSRC_Pos                    (16U)
#define RCC_CFGR0_PLLSRC_Msk                    (0x01UL << RCC_CFGR0_PLLSRC_Pos)
#define RCC_CFGR0_PLLSRC                        RCC_CFGR0_PLLSRC_Msk
#define RCC_CFGR0_MCO_Pos                       (24U)
#define RCC_CFGR0_MCO_Msk                       (0x07UL << RCC_CFGR0_MCO_Pos)
#define RCC_CFGR0_MCO                           RCC_CFGR0_MCO_Msk

/******************  Bit definition for RCC_INTR register  ********************/
#define RCC_INTR_LSIRDYF_Pos                    (0U)
#define RCC_INTR_LSIRDYF_Msk                    (0x01UL << RCC_INTR_LSIRDYF_Pos)
#define RCC_INTR_LSIRDYF                        RCC_INTR_LSIRDYF_Msk
#define RCC_INTR_HSIRDYF_Pos                    (2U)
#define RCC_INTR_HSIRDYF_Msk                    (0x01UL << RCC_INTR_HSIRDYF_Pos)
#define RCC_INTR_HSIRDYF                        RCC_INTR_HSIRDYF_Msk
#define RCC_INTR_HSERDYF_Pos                    (3U)
#define RCC_INTR_HSERDYF_Msk                    (0x01UL << RCC_INTR_HSERDYF_Pos)
#define RCC_INTR_HSERDYF                        RCC_INTR_HSERDYF_Msk
#define RCC_INTR_PLLRDYF_Pos                    (4U)
#define RCC_INTR_PLLRDYF_Msk                    (0x01UL << RCC_INTR_PLLRDYF_Pos)
#define RCC_INTR_PLLRDYF                        RCC_INTR_PLLRDYF_Msk
#define RCC_INTR_CSSF_Pos                       (7U)
#define RCC_INTR_CSSF_Msk                       (0x01UL << RCC_INTR_CSSF_Pos)
#define RCC_INTR_CSSF                           RCC_INTR_CSSF_Msk
#define RCC_INTR_LSIRDYIE_Pos                   (8U)
#define RCC_INTR_LSIRDYIE_Msk                   (0x01UL << RCC_INTR_LSIRDYIE_Pos)
#define RCC_INTR_LSIRDYIE                       RCC_INTR_LSIRDYIE_Msk
#define RCC_INTR_HSIRDYIE_Pos                   (10U)
#define RCC_INTR_HSIRDYIE_Msk                   (0x01UL << RCC_INTR_HSIRDYIE_Pos)
#define RCC_INTR_HSIRDYIE                       RCC_INTR_HSIRDYIE_Msk
#define RCC_INTR_HSERDYIE_Pos                   (11U)
#define RCC_INTR_HSERDYIE_Msk                   (0x01UL << RCC_INTR_HSERDYIE_Pos)
#define RCC_INTR_HSERDYIE                       RCC_INTR_HSERDYIE_Msk
#define RCC_INTR_PLLRDYIE_Pos                   (12U)
#define RCC_INTR_PLLRDYIE_Msk                   (0x01UL << RCC_INTR_PLLRDYIE_Pos)
#define RCC_INTR_PLLRDYIE                       RCC_INTR_PLLRDYIE_Msk
#define RCC_INTR_LSIRDYC_Pos                    (16U)
#define RCC_INTR_LSIRDYC_Msk                    (0x01UL << RCC_INTR_LSIRDYC_Pos)
#define RCC_INTR_LSIRDYC                        RCC_INTR_LSIRDYC_Msk
#define RCC_INTR_HSIRDYC_Pos                    (18U)
#define RCC_INTR_HSIRDYC_Msk                    (0x01UL << RCC_INTR_HSIRDYC_Pos)
#define RCC_INTR_HSIRDYC                        RCC_INTR_HSIRDYC_Msk
#define RCC_INTR_HSERDYC_Pos                    (19U)
#define RCC_INTR_HSERDYC_Msk                    (0x01UL << RCC_INTR_HSERDYC_Pos)
#define RCC_INTR_HSERDYC                        RCC_INTR_HSERDYC_Msk
#define RCC_INTR_PLLRDYC_Pos                    (20U)
#define RCC_INTR_PLLRDYC_Msk                    (0x01UL << RCC_INTR_PLLRDYC_Pos)
#define RCC_INTR_PLLRDYC                        RCC_INTR_PLLRDYC_Msk
#define RCC_INTR_CSSC_Pos                       (23U)
#define RCC_INTR_CSSC_Msk                       (0x01UL << RCC_INTR_CSSC_Pos)
#define RCC_INTR_CSSC                           RCC_INTR_CSSC_Msk

/******************  Bit definition for RCC_APB2PRSTR register  ***************/
#define RCC_APB2PRSTR_AFIORST_Pos               (0U)
#define RCC_APB2PRSTR_AFIORST_Msk               (0x01UL << RCC_APB2PRSTR_AFIORST_Pos)
#define RCC_APB2PRSTR_AFIORST                   RCC_APB2PRSTR_AFIORST_Msk
#define RCC_APB2PRSTR_IOPARST_Pos               (2U)
#define RCC_APB2PRSTR_IOPARST_Msk               (0x01UL << RCC_APB2PRSTR_IOPARST_Pos)
#define RCC_APB2PRSTR_IOPARST                   RCC_APB2PRSTR_IOPARST_Msk
#define RCC_APB2PRSTR_IOPCRST_Pos               (4U)
#define RCC_APB2PRSTR_IOPCRST_Msk               (0x01UL << RCC_APB2PRSTR_IOPCRST_Pos)
#define RCC_APB2PRSTR_IOPCRST                   RCC_APB2PRSTR_IOPCRST_Msk
#define RCC_APB2PRSTR_IOPDRST_Pos               (5U)
#define RCC_APB2PRSTR_IOPDRST_Msk               (0x01UL << RCC_APB2PRSTR_IOPDRST_Pos)
#define RCC_APB2PRSTR_IOPDRST                   RCC_APB2PRSTR_IOPDRST_Msk
#define RCC_APB2PRSTR_ADC1RST_Pos               (9U)
#define RCC_APB2PRSTR_ADC1RST_Msk               (0x01UL << RCC_APB2PRSTR_ADC1RST_Pos)
#define RCC_APB2PRSTR_ADC1RST                   RCC_APB2PRSTR_ADC1RST_Msk
#define RCC_APB2PRSTR_TIM1RST_Pos               (11U)
#define RCC_APB2PRSTR_TIM1RST_Msk               (0x01UL << RCC_APB2PRSTR_TIM1RST_Pos)
#define RCC_APB2PRSTR_TIM1RST                   RCC_APB2PRSTR_TIM1RST_Msk
#define RCC_APB2PRSTR_SPI1RST_Pos               (12U)
#define RCC_APB2PRSTR_SPI1RST_Msk               (0x01UL << RCC_APB2PRSTR_SPI1RST_Pos)
#define RCC_APB2PRSTR_SPI1RST                   RCC_APB2PRSTR_SPI1RST_Msk
#define RCC_APB2PRSTR_USART1RST_Pos             (14U)
#define RCC_APB2PRSTR_USART1RST_Msk             (0x01UL << RCC_APB2PRSTR_USART1RST_Pos)
#define RCC_APB2PRSTR_USART1RST                 RCC_APB2PRSTR_USART1RST_Msk

/******************  Bit definition for RCC_APB1PRSTR register  ***************/
#define RCC_APB1PRSTR_TIM2RST_Pos               (0U)
#define RCC_APB1PRSTR_TIM2RST_Msk               (0x01UL << RCC_APB1PRSTR_TIM2RST_Pos)
#define RCC_APB1PRSTR_TIM2RST                   RCC_APB1PRSTR_TIM2RST_Msk
#define RCC_APB1PRSTR_WWDGRST_Pos               (11U)
#define RCC_APB1PRSTR_WWDGRST_Msk               (0x01UL << RCC_APB1PRSTR_WWDGRST_Pos)
#define RCC_APB1PRSTR_WWDGRST                   RCC_APB1PRSTR_WWDGRST_Msk
#define RCC_APB1PRSTR_I2C1RST_Pos               (21U)
#define RCC_APB1PRSTR_I2C1RST_Msk               (0x01UL << RCC_APB1PRSTR_I2C1RST_Pos)
#define RCC_APB1PRSTR_I2C1RST                   RCC_APB1PRSTR_I2C1RST_Msk
#define RCC_APB1PRSTR_PWRRST_Pos                (28U)
#define RCC_APB1PRSTR_PWRRST_Msk                (0x01UL << RCC_APB1PRSTR_PWRRST_Pos)
#define RCC_APB1PRSTR_PWRRST                    RCC_APB1PRSTR_PWRRST_Msk

/******************  Bit definition for RCC_AHBPCENR register  ****************/
#define RCC_AHBPCENR_DMA1EN_Pos                 (0U)
#define RCC_AHBPCENR_DMA1EN_Msk                 (0x01UL << RCC_AHBPCENR_DMA1EN_Pos)
#define RCC_AHBPCENR_DMA1EN                     RCC_AHBPCENR_DMA1EN_Msk
#define RCC_AHBPCENR_SRAMEN_Pos                 (2U)
#define RCC_AHBPCENR_SRAMEN_Msk                 (0x01UL << RCC_AHBPCENR_SRAMEN_Pos)
#define RCC_AHBPCENR_SRAMEN                     RCC_AHBPCENR_SRAMEN_Msk

/******************  Bit definition for RCC_APB2PCENR register  ***************/
#define RCC_APB2PCENR_AFIOEN_Pos                (0U)
#define RCC_APB2PCENR_AFIOEN_Msk                (0x01UL << RCC_APB2PCENR_AFIOEN_Pos)
#define RCC_APB2PCENR_AFIOEN                    RCC_APB2PCENR_AFIOEN_Msk
#define RCC_APB2PCENR_IOPAEN_Pos                (2U)
#define RCC_APB2PCENR_IOPAEN_Msk                (0x01UL << RCC_APB2PCENR_IOPAEN_Pos)
#define RCC_APB2PCENR_IOPAEN                    RCC_APB2PCENR_IOPAEN_Msk
#define RCC_APB2PCENR_IOPCEN_Pos                (4U)
#define RCC_APB2PCENR_IOPCEN_Msk                (0x01UL << RCC_APB2PCENR_IOPCEN_Pos)
#define RCC_APB2PCENR_IOPCEN                    RCC_APB2PCENR_IOPCEN_Msk
#define RCC_APB2PCENR_IOPDEN_Pos                (5U)
#define RCC_APB2PCENR_IOPDEN_Msk                (0x01UL << RCC_APB2PCENR_IOPDEN_Pos)
#define RCC_APB2PCENR_IOPDEN                    RCC_APB2PCENR_IOPDEN_Msk
#define RCC_APB2PCENR_ADC1EN_Pos                (9U)
#define RCC_APB2PCENR_ADC1EN_Msk                (0x01UL << RCC_APB2PCENR_ADC1EN_Pos)
#define RCC_APB2PCENR_ADC1EN                    RCC_APB2PCENR_ADC1EN_Msk
#define RCC_APB2PCENR_TIM1EN_Pos                (11U)
#define RCC_APB2PCENR_TIM1EN_Msk                (0x01UL << RCC_APB2PCENR_TIM1EN_Pos)
#define RCC_APB2PCENR_TIM1EN                    RCC_APB2PCENR_TIM1EN_Msk
#define RCC_APB2PCENR_SPI1EN_Pos                (12U)
#define RCC_APB2PCENR_SPI1EN_Msk                (0x01UL << RCC_APB2PCENR_SPI1EN_Pos)
#define RCC_APB2PCENR_SPI1EN                    RCC_APB2PCENR_SPI1EN_Msk
#define RCC_APB2PCENR_USART1EN_Pos              (14U)
#define RCC_APB2PCENR_USART1EN_Msk              (0x01UL << RCC_APB2PCENR_USART1EN_Pos)
#define RCC_APB2PCENR_USART1EN                  RCC_APB2PCENR_USART1EN_Msk

/******************  Bit definition for RCC_APB1PCENR register  ***************/
#define RCC_APB1PCENR_TIM2EN_Pos                (0U)
#define RCC_APB1PCENR_TIM2EN_Msk                (0x01UL << RCC_APB1PCENR_TIM2EN_Pos)
#define RCC_APB1PCENR_TIM2EN                    RCC_APB1PCENR_TIM2EN_Msk
#define RCC_APB1PCENR_WWDGEN_Pos                (11U)
#define RCC_APB1PCENR_WWDGEN_Msk                (0x01UL << RCC_APB1PCENR_WWDGEN_Pos)
#define RCC_APB1PCENR_WWDGEN                    RCC_APB1PCENR_WWDGEN_Msk
#define RCC_APB1PCENR_I2C1EN_Pos                (21U)
#define RCC_APB1PCENR_I2C1EN_Msk                (0x01UL << RCC_APB1PCENR_I2C1EN_Pos)
#define RCC_APB1PCENR_I2C1EN                    RCC_APB1PCENR_I2C1EN_Msk
#define RCC_APB1PCENR_PWREN_Pos                 (28U)
#define RCC_APB1PCENR_PWREN_Msk                 (0x01UL << RCC_APB1PCENR_PWREN_Pos)
#define RCC_APB1PCENR_PWREN                     RCC_APB1PCENR_PWREN_Msk

/******************  Bit definition for RCC_RSTSCKR register  *****************/
#define RCC_RSTSCKR_LSION_Pos                   (0U)
#define RCC_RSTSCKR_LSION_Msk                   (0x01UL << RCC_RSTSCKR_LSION_Pos)
#define RCC_RSTSCKR_LSION                       RCC_RSTSCKR_LSION_Msk
#define RCC_RSTSCKR_LSIRDY_Pos                  (1U)
#define RCC_RSTSCKR_LSIRDY_Msk                  (0x01UL << RCC_RSTSCKR_LSIRDY_Pos)
#define RCC_RSTSCKR_LSIRDY                      RCC_RSTSCKR_LSIRDY_Msk
#define RCC_RSTSCKR_RMVF_Pos                    (24U)
#define RCC_RSTSCKR_RMVF_Msk                    (0x01UL << RCC_RSTSCKR_RMVF_Pos)
#define RCC_RSTSCKR_RMVF                        RCC_RSTSCKR_RMVF_Msk
#define RCC_RSTSCKR_PINRSTF_Pos                 (26U)
#define RCC_RSTSCKR_PINRSTF_Msk                 (0x01UL << RCC_RSTSCKR_PINRSTF_Pos)
#define RCC_RSTSCKR_PINRSTF                     RCC_RSTSCKR_PINRSTF_Msk
#define RCC_RSTSCKR_PORRSTF_Pos                 (27U)
#define RCC_RSTSCKR_PORRSTF_Msk                 (0x01UL << RCC_RSTSCKR_PORRSTF_Pos)
#define RCC_RSTSCKR_PORRSTF                     RCC_RSTSCKR_PORRSTF_Msk
#define RCC_RSTSCKR_SFTRSTF_Pos                 (28U)
#define RCC_RSTSCKR_SFTRSTF_Msk                 (0x01UL << RCC_RSTSCKR_SFTRSTF_Pos)
#define RCC_RSTSCKR_SFTRSTF                     RCC_RSTSCKR_SFTRSTF_Msk
#define RCC_RSTSCKR_IWDGRSTF_Pos                (29U)
#define RCC_RSTSCKR_IWDGRSTF_Msk                (0x01UL << RCC_RSTSCKR_IWDGRSTF_Pos)
#define RCC_RSTSCKR_IWDGRSTF                    RCC_RSTSCKR_IWDGRSTF_Msk
#define RCC_RSTSCKR_WWDGRSTF_Pos                (30U)
#define RCC_RSTSCKR_WWDGRSTF_Msk                (0x01UL << RCC_RSTSCKR_WWDGRSTF_Pos)
#define RCC_RSTSCKR_WWDGRSTF                    RCC_RSTSCKR_WWDGRSTF_Msk
#define RCC_RSTSCKR_LPWRRSTF_Pos                (31U)
#define RCC_RSTSCKR_LPWRRSTF_Msk                (0x01UL << RCC_RSTSCKR_LPWRRSTF_Pos)
#define RCC_RSTSCKR_LPWRRSTF                    RCC_RSTSCKR_LPWRRSTF_Msk

/******************************************************************************/
/*                        Serial Peripheral Interface                         */
/******************************************************************************/
/******************  Bit definition for SPI_CTLR1 register  *******************/
#define SPI_CTLR1_CPHA_Pos                      (0U)
#define SPI_CTLR1_CPHA_Msk                      (0x01UL << SPI_CTLR1_CPHA_Pos)
#define SPI_CTLR1_CPHA                          SPI_CTLR1_CPHA_Msk
#define SPI_CTLR1_CPOL_Pos                      (1U)
#define SPI_CTLR1_CPOL_Msk                      (0x01UL << SPI_CTLR1_CPOL_Pos)
#define SPI_CTLR1_CPOL                          SPI_CTLR1_CPOL_Msk
#define SPI_CTLR1_MSTR_Pos                      (2U)
#define SPI_CTLR1_MSTR_Msk                      (0x01UL << SPI_CTLR1_MSTR_Pos)
#define SPI_CTLR1_MSTR                          SPI_CTLR1_MSTR_Msk
#define SPI_CTLR1_BR_Pos                        (3U)
#define SPI_CTLR1_BR_Msk                        (0x07UL << SPI_CTLR1_BR_Pos)
#define SPI_CTLR1_BR                            SPI_CTLR1_BR_Msk
#define SPI_CTLR1_SPE_Pos                       (6U)
#define SPI_CTLR1_SPE_Msk                       (0x01UL << SPI_CTLR1_SPE_Pos)
#define SPI_CTLR1_SPE                           SPI_CTLR1_SPE_Msk
#define SPI_CTLR1_LSBFIRST_Pos                  (7U)
#define SPI_CTLR1_LSBFIRST_Msk                  (0x01UL << SPI_CTLR1_LSBFIRST_Pos)
#define SPI_CTLR1_LSBFIRST                      SPI_CTLR1_LSBFIRST_Msk
#define SPI_CTLR1_SSI_Pos                       (8U)
#define SPI_CTLR1_SSI_Msk                       (0x01UL << SPI_CTLR1_SSI_Pos)
#define SPI_CTLR1_SSI                           SPI_CTLR1_SSI_Msk
#define SPI_CTLR1_SSM_Pos                       (9U)
#define SPI_CTLR1_SSM_Msk                       (0x01UL << SPI_CTLR1_SSM_Pos)
#define SPI_CTLR1_SSM                           SPI_CTLR1_SSM_Msk
#define SPI_CTLR1_RXONLY_Pos                    (10U)
#define SPI_CTLR1_RXONLY_Msk                    (0x01UL << SPI_CTLR1_RXONLY_Pos)
#define SPI_CTLR1_RXONLY                        SPI_CTLR1_RXONLY_Msk
#define SPI_CTLR1_DFF_Pos                       (11U)
#define SPI_CTLR1_DFF_Msk                       (0x01UL << SPI_CTLR1_DFF_Pos)
#define SPI_CTLR1_DFF                           SPI_CTLR1_DFF_Msk
#define SPI_CTLR1_CRCNEXT_Pos                   (12U)
#define SPI_CTLR1_CRCNEXT_Msk                   (0x01UL << SPI_CTLR1_CRCNEXT_Pos)
#define SPI_CTLR1_CRCNEXT                       SPI_CTLR1_CRCNEXT_Msk
#define SPI_CTLR1_CRCEN_Pos                     (13U)
#define SPI_CTLR1_CRCEN_Msk                     (0x01UL << SPI_CTLR1_CRCEN_Pos)
#define SPI_CTLR1_CRCEN                         SPI_CTLR1_CRCEN_Msk
#define SPI_CTLR1_BIDIOE_Pos                    (14U)
#define SPI_CTLR1_BIDIOE_Msk                    (0x01UL << SPI_CTLR1_BIDIOE_Pos)
#define SPI_CTLR1_BIDIOE                        SPI_CTLR1_BIDIOE_Msk
#define SPI_CTLR1_BIDIMODE_Pos                  (15U)
#define SPI_CTLR1_BIDIMODE_Msk                  (0x01UL << SPI_CTLR1_BIDIMODE_Pos)
#define SPI_CTLR1_BIDIMODE                      SPI_CTLR1_BIDIMODE_Msk

/******************  Bit definition for SPI_CTLR2 register  *******************/
#define SPI_CTLR2_RXDMAEN_Pos                   (0U)
#define SPI_CTLR2_RXDMAEN_Msk                   (0x01UL << SPI_CTLR2_RXDMAEN_Pos)
#define SPI_CTLR2_RXDMAEN                       SPI_CTLR2_RXDMAEN_Msk
#define SPI_CTLR2_TXDMAEN_Pos                   (1U)
#define SPI_CTLR2_TXDMAEN_Msk                   (0x01UL << SPI_CTLR2_TXDMAEN_Pos)
#define SPI_CTLR2_TXDMAEN                       SPI_CTLR2_TXDMAEN_Msk
#define SPI_CTLR2_SSOE_Pos                      (2U)
#define SPI_CTLR2_SSOE_Msk                      (0x01UL << SPI_CTLR2_SSOE_Pos)
#define SPI_CTLR2_SSOE                          SPI_CTLR2_SSOE_Msk
#define SPI_CTLR2_ERRIE_Pos                     (5U)
#define SPI_CTLR2_ERRIE_Msk                     (0x01UL << SPI_CTLR2_ERRIE_Pos)
#define SPI_CTLR2_ERRIE                         SPI_CTLR2_ERRIE_Msk
#define SPI_CTLR2_RXNEIE_Pos                    (6U)
#define SPI_CTLR2_RXNEIE_Msk                    (0x01UL << SPI_CTLR2_RXNEIE_Pos)
#define SPI_CTLR2_RXNEIE                        SPI_CTLR2_RXNEIE_Msk
#define SPI_CTLR2_TXEIE_Pos                     (7U)
#define SPI_CTLR2_TXEIE_Msk                     (0x01UL << SPI_CTLR2_TXEIE_Pos)
#define SPI_CTLR2_TXEIE                         SPI_CTLR2_TXEIE_Msk

/******************  Bit definition for SPI_STATR register  *******************/
#define SPI_STATR_RXNE_Pos                      (0U)
#define SPI_STATR_RXNE_Msk                      (0x01UL << SPI_STATR_RXNE_Pos)
#define SPI_STATR_RXNE                          SPI_STATR_RXNE_Msk
#define SPI_STATR_TXE_Pos                       (1U)
#define SPI_STATR_TXE_Msk                       (0x01UL << SPI_STATR_TXE_Pos)
#define SPI_STATR_TXE                           SPI_STATR_TXE_Msk
#define SPI_STATR_CHSID_Pos                     (2U)
#define SPI_STATR_CHSID_Msk                     (0x01UL << SPI_STATR_CHSID_Pos)
#define SPI_STATR_CHSID                         SPI_STATR_CHSID_Msk
#define SPI_STATR_UDR_Pos                       (3U)
#define SPI_STATR_UDR_Msk                       (0x01UL << SPI_STATR_UDR_Pos)
#define SPI_STATR_UDR                           SPI_STATR_UDR_Msk
#define SPI_STATR_CRCERR_Pos                    (4U)
#define SPI_STATR_CRCERR_Msk                    (0x01UL << SPI_STATR_CRCERR_Pos)
#define SPI_STATR_CRCERR                        SPI_STATR_CRCERR_Msk
#define SPI_STATR_MODF_Pos                      (5U)
#define SPI_STATR_MODF_Msk                      (0x01UL << SPI_STATR_MODF_Pos)
#define SPI_STATR_MODF                          SPI_STATR_MODF_Msk
#define SPI_STATR_OVR_Pos                       (6U)
#define SPI_STATR_OVR_Msk                       (0x01UL << SPI_STATR_OVR_Pos)
#define SPI_STATR_OVR                           SPI_STATR_OVR_Msk
#define SPI_STATR_BSY_Pos                       (7U)
#define SPI_STATR_BSY_Msk                       (0x01UL << SPI_STATR_BSY_Pos)
#define SPI_STATR_BSY                           SPI_STATR_BSY_Msk

/******************  Bit definition for SPI_DATAR register  *******************/
#define SPI_DATAR_DR_Pos                        (0U)
#define SPI_DATAR_DR_Msk                        (0xFFFFUL << SPI_DATAR_DR_Pos)
#define SPI_DATAR_DR                            SPI_DATAR_DR_Msk

/******************  Bit definition for SPI_CRCR register  ********************/
#define SPI_CRCR_CRCPOLY_Pos                    (0U)
#define SPI_CRCR_CRCPOLY_Msk                    (0xFFFFUL << SPI_CRCR_CRCPOLY_Pos)
#define SPI_CRCR_CRCPOLY                        SPI_CRCR_CRCPOLY_Msk

/******************  Bit definition for SPI_RCRCR register  *******************/
#define SPI_RCRCR_RXCRC_Pos                     (0U)
#define SPI_RCRCR_RXCRC_Msk                     (0xFFFFUL << SPI_RCRCR_RXCRC_Pos)
#define SPI_RCRCR_RXCRC                         SPI_RCRCR_RXCRC_Msk

/******************  Bit definition for SPI_TCRCR register  *******************/
#define SPI_TCRCR_TXCRC_Pos                     (0U)
#define SPI_TCRCR_TXCRC_Msk                     (0xFFFFUL << SPI_TCRCR_TXCRC_Pos)
#define SPI_TCRCR_TXCRC                         SPI_TCRCR_TXCRC_Msk

/******************  Bit definition for SPI_HSCR register  ********************/
#define SPI_HSCR_HSRXEN_Pos                     (0U)
#define SPI_HSCR_HSRXEN_Msk                     (0x01UL << SPI_HSCR_HSRXEN_Pos)
#define SPI_HSCR_HSRXEN                         SPI_HSCR_HSRXEN_Msk

/******************************************************************************/
/*                                    TIM                                     */
/******************************************************************************/
/******************  Bit definition for TIM_CTLR1 register  *******************/
#define TIM_CTLR1_CEN_Pos                       (0U)
#define TIM_CTLR1_CEN_Msk                       (0x01UL << TIM_CTLR1_CEN_Pos)
#define TIM_CTLR1_CEN                           TIM_CTLR1_CEN_Msk
#define TIM_CTLR1_UDIS_Pos                      (1U)
#define TIM_CTLR1_UDIS_Msk                      (0x01UL << TIM_CTLR1_UDIS_Pos)
#define TIM_CTLR1_UDIS                          TIM_CTLR1_UDIS_Msk
#define TIM_CTLR1_URS_Pos                       (2U)
#define TIM_CTLR1_URS_Msk                       (0x01UL << TIM_CTLR1_URS_Pos)
#define TIM_CTLR1_URS                           TIM_CTLR1_URS_Msk
#define TIM_CTLR1_OPM_Pos                       (3U)
#define TIM_CTLR1_OPM_Msk                       (0x01UL << TIM_CTLR1_OPM_Pos)
#define TIM_CTLR1_OPM                           TIM_CTLR1_OPM_Msk
#define TIM_CTLR1_DIR_Pos                       (4U)
#define TIM_CTLR1_DIR_Msk                       (0x01UL << TIM_CTLR1_DIR_Pos)
#define TIM_CTLR1_DIR                           TIM_CTLR1_DIR_Msk
#define TIM_CTLR1_CMS_Pos                       (5U)
#define TIM_CTLR1_CMS_Msk                       (0x03UL << TIM_CTLR1_CMS_Pos)
#define TIM_CTLR1_CMS                           TIM_CTLR1_CMS_Msk
#define TIM_CTLR1_ARPE_Pos                      (7U)
#define TIM_CTLR1_ARPE_Msk                      (0x01UL << TIM_CTLR1_ARPE_Pos)
#define TIM_CTLR1_ARPE                          TIM_CTLR1_ARPE_Msk
#define TIM_CTLR1_CKD_Pos                       (8U)
#define TIM_CTLR1_CKD_Msk                       (0x03UL << TIM_CTLR1_CKD_Pos)
#define TIM_CTLR1_CKD                           TIM_CTLR1_CKD_Msk
#define TIM_CTLR1_CAPOV_Pos                     (14U)
#define TIM_CTLR1_CAPOV_Msk                     (0x01UL << TIM_CTLR1_CAPOV_Pos)
#define TIM_CTLR1_CAPOV                         TIM_CTLR1_CAPOV_Msk
#define TIM_CTLR1_CAPLVL_Pos                    (15U)
#define TIM_CTLR1_CAPLVL_Msk                    (0x01UL << TIM_CTLR1_CAPLVL_Pos)
#define TIM_CTLR1_CAPLVL                        TIM_CTLR1_CAPLVL_Msk

/******************  Bit definition for TIM_CTLR2 register  *******************/
#define TIM_CTLR2_CCPC_Pos                      (0U)
#define TIM_CTLR2_CCPC_Msk                      (0x01UL << TIM_CTLR2_CCPC_Pos)
#define TIM_CTLR2_CCPC                          TIM_CTLR2_CCPC_Msk
#define TIM_CTLR2_CCUS_Pos                      (2U)
#define TIM_CTLR2_CCUS_Msk                      (0x01UL << TIM_CTLR2_CCUS_Pos)
#define TIM_CTLR2_CCUS                          TIM_CTLR2_CCUS_Msk
#define TIM_CTLR2_CCDS_Pos                      (3U)
#define TIM_CTLR2_CCDS_Msk                      (0x01UL << TIM_CTLR2_CCDS_Pos)
#define TIM_CTLR2_CCDS                          TIM_CTLR2_CCDS_Msk
#define TIM_CTLR2_MMS_Pos                       (4U)
#define TIM_CTLR2_MMS_Msk                       (0x07UL << TIM_CTLR2_MMS_Pos)
#define TIM_CTLR2_MMS                           TIM_CTLR2_MMS_Msk
#define TIM_CTLR2_TI1S_Pos                      (7U)
#define TIM_CTLR2_TI1S_Msk                      (0x01UL << TIM_CTLR2_TI1S_Pos)
#define TIM_CTLR2_TI1S                          TIM_CTLR2_TI1S_Msk
#define TIM_CTLR2_OIS1_Pos                      (8U)
#define TIM_CTLR2_OIS1_Msk                      (0x01UL << TIM_CTLR2_OIS1_Pos)
#define TIM_CTLR2_OIS1                          TIM_CTLR2_OIS1_Msk
#define TIM_CTLR2_OIS1N_Pos                     (9U)
#define TIM_CTLR2_OIS1N_Msk                     (0x01UL << TIM_CTLR2_OIS1N_Pos)
#define TIM_CTLR2_OIS1N                         TIM_CTLR2_OIS1N_Msk
#define TIM_CTLR2_OIS2_Pos                      (10U)
#define TIM_CTLR2_OIS2_Msk                      (0x01UL << TIM_CTLR2_OIS2_Pos)
#define TIM_CTLR2_OIS2                          TIM_CTLR2_OIS2_Msk
#define TIM_CTLR2_OIS2N_Pos                     (11U)
#define TIM_CTLR2_OIS2N_Msk                     (0x01UL << TIM_CTLR2_OIS2N_Pos)
#define TIM_CTLR2_OIS2N                         TIM_CTLR2_OIS2N_Msk
#define TIM_CTLR2_OIS3_Pos                      (12U)
#define TIM_CTLR2_OIS3_Msk                      (0x01UL << TIM_CTLR2_OIS3_Pos)
#define TIM_CTLR2_OIS3                          TIM_CTLR2_OIS3_Msk
#define TIM_CTLR2_OIS3N_Pos                     (13U)
#define TIM_CTLR2_OIS3N_Msk                     (0x01UL << TIM_CTLR2_OIS3N_Pos)
#define TIM_CTLR2_OIS3N                         TIM_CTLR2_OIS3N_Msk
#define TIM_CTLR2_OIS4_Pos                      (14U)
#define TIM_CTLR2_OIS4_Msk                      (0x01UL << TIM_CTLR2_OIS4_Pos)
#define TIM_CTLR2_OIS4                          TIM_CTLR2_OIS4_Msk

/******************  Bit definition for TIM_SMCFGR register  ******************/
#define TIM_SMCFGR_SMS_Pos                      (0U)
#define TIM_SMCFGR_SMS_Msk                      (0x07UL << TIM_SMCFGR_SMS_Pos)
#define TIM_SMCFGR_SMS                          TIM_SMCFGR_SMS_Msk
#define TIM_SMCFGR_TS_Pos                       (4U)
#define TIM_SMCFGR_TS_Msk                       (0x07UL << TIM_SMCFGR_TS_Pos)
#define TIM_SMCFGR_TS                           TIM_SMCFGR_TS_Msk
#define TIM_SMCFGR_MSM_Pos                      (7U)
#define TIM_SMCFGR_MSM_Msk                      (0x01UL << TIM_SMCFGR_MSM_Pos)
#define TIM_SMCFGR_MSM                          TIM_SMCFGR_MSM_Msk
#define TIM_SMCFGR_ETF_Pos                      (8U)
#define TIM_SMCFGR_ETF_Msk                      (0x0FUL << TIM_SMCFGR_ETF_Pos)
#define TIM_SMCFGR_ETF                          TIM_SMCFGR_ETF_Msk
#define TIM_SMCFGR_ETPS_Pos                     (12U)
#define TIM_SMCFGR_ETPS_Msk                     (0x03UL << TIM_SMCFGR_ETPS_Pos)
#define TIM_SMCFGR_ETPS                         TIM_SMCFGR_ETPS_Msk
#define TIM_SMCFGR_ECE_Pos                      (14U)
#define TIM_SMCFGR_ECE_Msk                      (0x01UL << TIM_SMCFGR_ECE_Pos)
#define TIM_SMCFGR_ECE                          TIM_SMCFGR_ECE_Msk
#define TIM_SMCFGR_ETP_Pos                      (15U)
#define TIM_SMCFGR_ETP_Msk                      (0x01UL << TIM_SMCFGR_ETP_Pos)
#define TIM_SMCFGR_ETP                          TIM_SMCFGR_ETP_Msk

/******************  Bit definition for TIM_DMAINTENR register  ***************/
#define TIM_DMAINTENR_UIE_Pos                   (0U)
#define TIM_DMAINTENR_UIE_Msk                   (0x01UL << TIM_DMAINTENR_UIE_Pos)
#define TIM_DMAINTENR_UIE                       TIM_DMAINTENR_UIE_Msk
#define TIM_DMAINTENR_CC1IE_Pos                 (1U)
#define TIM_DMAINTENR_CC1IE_Msk                 (0x01UL << TIM_DMAINTENR_CC1IE_Pos)
#define TIM_DMAINTENR_CC1IE                     TIM_DMAINTENR_CC1IE_Msk
#define TIM_DMAINTENR_CC2IE_Pos                 (2U)
#define TIM_DMAINTENR_CC2IE_Msk                 (0x01UL << TIM_DMAINTENR_CC2IE_Pos)
#define TIM_DMAINTENR_CC2IE                     TIM_DMAINTENR_CC2IE_Msk
#define TIM_DMAINTENR_CC3IE_Pos                 (3U)
#define TIM_DMAINTENR_CC3IE_Msk                 (0x01UL << TIM_DMAINTENR_CC3IE_Pos)
#define TIM_DMAINTENR_CC3IE                     TIM_DMAINTENR_CC3IE_Msk
#define TIM_DMAINTENR_CC4IE_Pos                 (4U)
#define TIM_DMAINTENR_CC4IE_Msk                 (0x01UL << TIM_DMAINTENR_CC4IE_Pos)
#define TIM_DMAINTENR_CC4IE                     TIM_DMAINTENR_CC4IE_Msk
#define TIM_DMAINTENR_COMIE_Pos                 (5U)
#define TIM_DMAINTENR_COMIE_Msk                 (0x01UL << TIM_DMAINTENR_COMIE_Pos)
#define TIM_DMAINTENR_COMIE                     TIM_DMAINTENR_COMIE_Msk
#define TIM_DMAINTENR_TIE_Pos                   (6U)
#define TIM_DMAINTENR_TIE_Msk                   (0x01UL << TIM_DMAINTENR_TIE_Pos)
#define TIM_DMAINTENR_TIE                       TIM_DMAINTENR_TIE_Msk
#define TIM_DMAINTENR_BIE_Pos                   (7U)
#define TIM_DMAINTENR_BIE_Msk                   (0x01UL << TIM_DMAINTENR_BIE_Pos)
#define TIM_DMAINTENR_BIE                       TIM_DMAINTENR_BIE_Msk
#define TIM_DMAINTENR_UDE_Pos                   (8U)
#define TIM_DMAINTENR_UDE_Msk                   (0x01UL << TIM_DMAINTENR_UDE_Pos)
#define TIM_DMAINTENR_UDE                       TIM_DMAINTENR_UDE_Msk
#define TIM_DMAINTENR_CC1DE_Pos                 (9U)
#define TIM_DMAINTENR_CC1DE_Msk                 (0x01UL << TIM_DMAINTENR_CC1DE_Pos)
#define TIM_DMAINTENR_CC1DE                     TIM_DMAINTENR_CC1DE_Msk
#define TIM_DMAINTENR_CC2DE_Pos                 (10U)
#define TIM_DMAINTENR_CC2DE_Msk                 (0x01UL << TIM_DMAINTENR_CC2DE_Pos)
#define TIM_DMAINTENR_CC2DE                     TIM_DMAINTENR_CC2DE_Msk
#define TIM_DMAINTENR_CC3DE_Pos                 (11U)
#define TIM_DMAINTENR_CC3DE_Msk                 (0x01UL << TIM_DMAINTENR_CC3DE_Pos)
#define TIM_DMAINTENR_CC3DE                     TIM_DMAINTENR_CC3DE_Msk
#define TIM_DMAINTENR_CC4DE_Pos                 (12U)
#define TIM_DMAINTENR_CC4DE_Msk                 (0x01UL << TIM_DMAINTENR_CC4DE_Pos)
#define TIM_DMAINTENR_CC4DE                     TIM_DMAINTENR_CC4DE_Msk
#define TIM_DMAINTENR_COMDE_Pos                 (13U)
#define TIM_DMAINTENR_COMDE_Msk                 (0x01UL << TIM_DMAINTENR_COMDE_Pos)
#define TIM_DMAINTENR_COMDE                     TIM_DMAINTENR_COMDE_Msk
#define TIM_DMAINTENR_TDE_Pos                   (14U)
#define TIM_DMAINTENR_TDE_Msk                   (0x01UL << TIM_DMAINTENR_TDE_Pos)
#define TIM_DMAINTENR_TDE                       TIM_DMAINTENR_TDE_Msk

/******************  Bit definition for TIM_INTFR register  *******************/
#define TIM_INTFR_UIF_Pos                       (0U)
#define TIM_INTFR_UIF_Msk                       (0x01UL << TIM_INTFR_UIF_Pos)
#define TIM_INTFR_UIF                           TIM_INTFR_UIF_Msk
#define TIM_INTFR_CC1IF_Pos                     (1U)
#define TIM_INTFR_CC1IF_Msk                     (0x01UL << TIM_INTFR_CC1IF_Pos)
#define TIM_INTFR_CC1IF                         TIM_INTFR_CC1IF_Msk
#define TIM_INTFR_CC2IF_Pos                     (2U)
#define TIM_INTFR_CC2IF_Msk                     (0x01UL << TIM_INTFR_CC2IF_Pos)
#define TIM_INTFR_CC2IF                         TIM_INTFR_CC2IF_Msk
#define TIM_INTFR_CC3IF_Pos                     (3U)
#define TIM_INTFR_CC3IF_Msk                     (0x01UL << TIM_INTFR_CC3IF_Pos)
#define TIM_INTFR_CC3IF                         TIM_INTFR_CC3IF_Msk
#define TIM_INTFR_CC4IF_Pos                     (4U)
#define TIM_INTFR_CC4IF_Msk                     (0x01UL << TIM_INTFR_CC4IF_Pos)
#define TIM_INTFR_CC4IF                         TIM_INTFR_CC4IF_Msk
#define TIM_INTFR_COMIF_Pos                     (5U)
#define TIM_INTFR_COMIF_Msk                     (0x01UL << TIM_INTFR_COMIF_Pos)
#define TIM_INTFR_COMIF                         TIM_INTFR_COMIF_Msk
#define TIM_INTFR_TIF_Pos                       (6U)
#define TIM_INTFR_TIF_Msk                       (0x01UL << TIM_INTFR_TIF_Pos)
#define TIM_INTFR_TIF                           TIM_INTFR_TIF_Msk
#define TIM_INTFR_BIF_Pos                       (7U)
#define TIM_INTFR_BIF_Msk                       (0x01UL << TIM_INTFR_BIF_Pos)
#define TIM_INTFR_BIF                           TIM_INTFR_BIF_Msk
#define TIM_INTFR_CC1OF_Pos                     (9U)
#define TIM_INTFR_CC1OF_Msk                     (0x01UL << TIM_INTFR_CC1OF_Pos)
#define TIM_INTFR_CC1OF                         TIM_INTFR_CC1OF_Msk
#define TIM_INTFR_CC2OF_Pos                     (10U)
#define TIM_INTFR_CC2OF_Msk                     (0x01UL << TIM_INTFR_CC2OF_Pos)
#define TIM_INTFR_CC2OF                         TIM_INTFR_CC2OF_Msk
#define TIM_INTFR_CC3OF_Pos                     (11U)
#define TIM_INTFR_CC3OF_Msk                     (0x01UL << TIM_INTFR_CC3OF_Pos)
#define TIM_INTFR_CC3OF                         TIM_INTFR_CC3OF_Msk
#define TIM_INTFR_CC4OF_Pos                     (12U)
#define TIM_INTFR_CC4OF_Msk                     (0x01UL << TIM_INTFR_CC4OF_Pos)
#define TIM_INTFR_CC4OF                         TIM_INTFR_CC4OF_Msk

/******************  Bit definition for TIM_SWEVGR register  ******************/
#define TIM_SWEVGR_UG_Pos                       (0U)
#define TIM_SWEVGR_UG_Msk                       (0x01UL << TIM_SWEVGR_UG_Pos)
#define TIM_SWEVGR_UG                           TIM_SWEVGR_UG_Msk
#define TIM_SWEVGR_CC1G_Pos                     (1U)
#define TIM_SWEVGR_CC1G_Msk                     (0x01UL << TIM_SWEVGR_CC1G_Pos)
#define TIM_SWEVGR_CC1G                         TIM_SWEVGR_CC1G_Msk
#define TIM_SWEVGR_CC2G_Pos                     (2U)
#define TIM_SWEVGR_CC2G_Msk                     (0x01UL << TIM_SWEVGR_CC2G_Pos)
#define TIM_SWEVGR_CC2G                         TIM_SWEVGR_CC2G_Msk
#define TIM_SWEVGR_CC3G_Pos                     (3U)
#define TIM_SWEVGR_CC3G_Msk                     (0x01UL << TIM_SWEVGR_CC3G_Pos)
#define TIM_SWEVGR_CC3G                         TIM_SWEVGR_CC3G_Msk
#define TIM_SWEVGR_CC4G_Pos                     (4U)
#define TIM_SWEVGR_CC4G_Msk                     (0x01UL << TIM_SWEVGR_CC4G_Pos)
#define TIM_SWEVGR_CC4G                         TIM_SWEVGR_CC4G_Msk
#define TIM_SWEVGR_COMG_Pos                     (5U)
#define TIM_SWEVGR_COMG_Msk                     (0x01UL << TIM_SWEVGR_COMG_Pos)
#define TIM_SWEVGR_COMG                         TIM_SWEVGR_COMG_Msk
#define TIM_SWEVGR_TG_Pos                       (6U)
#define TIM_SWEVGR_TG_Msk                       (0x01UL << TIM_SWEVGR_TG_Pos)
#define TIM_SWEVGR_TG                           TIM_SWEVGR_TG_Msk
#define TIM_SWEVGR_BG_Pos                       (7U)
#define TIM_SWEVGR_BG_Msk                       (0x01UL << TIM_SWEVGR_BG_Pos)
#define TIM_SWEVGR_BG                           TIM_SWEVGR_BG_Msk

/******************  Bit definition for TIM_CHCTLR1 register  *****************/
#define TIM_CHCTLR1_CC1S_Pos                    (0U)
#define TIM_CHCTLR1_CC1S_Msk                    (0x03UL << TIM_CHCTLR1_CC1S_Pos)
#define TIM_CHCTLR1_CC1S                        TIM_CHCTLR1_CC1S_Msk
#define TIM_CHCTLR1_OC1FE_Pos                   (2U)
#define TIM_CHCTLR1_OC1FE_Msk                   (0x01UL << TIM_CHCTLR1_OC1FE_Pos)
#define TIM_CHCTLR1_OC1FE                       TIM_CHCTLR1_OC1FE_Msk
#define TIM_CHCTLR1_OC1PE_Pos                   (3U)
#define TIM_CHCTLR1_OC1PE_Msk                   (0x01UL << TIM_CHCTLR1_OC1PE_Pos)
#define TIM_CHCTLR1_OC1PE                       TIM_CHCTLR1_OC1PE_Msk
#define TIM_CHCTLR1_OC1M_Pos                    (4U)
#define TIM_CHCTLR1_OC1M_Msk                    (0x07UL << TIM_CHCTLR1_OC1M_Pos)
#define TIM_CHCTLR1_OC1M                        TIM_CHCTLR1_OC1M_Msk
#define TIM_CHCTLR1_OC1CE_Pos                   (7U)
#define TIM_CHCTLR1_OC1CE_Msk                   (0x01UL << TIM_CHCTLR1_OC1CE_Pos)
#define TIM_CHCTLR1_OC1CE                       TIM_CHCTLR1_OC1CE_Msk
#define TIM_CHCTLR1_CC2S_Pos                    (8U)
#define TIM_CHCTLR1_CC2S_Msk                    (0x03UL << TIM_CHCTLR1_CC2S_Pos)
#define TIM_CHCTLR1_CC2S                        TIM_CHCTLR1_CC2S_Msk
#define TIM_CHCTLR1_OC2FE_Pos                   (10U)
#define TIM_CHCTLR1_OC2FE_Msk                   (0x01UL << TIM_CHCTLR1_OC2FE_Pos)
#define TIM_CHCTLR1_OC2FE                       TIM_CHCTLR1_OC2FE_Msk
#define TIM_CHCTLR1_OC2PE_Pos                   (11U)
#define TIM_CHCTLR1_OC2PE_Msk                   (0x01UL << TIM_CHCTLR1_OC2PE_Pos)
#define TIM_CHCTLR1_OC2PE                       TIM_CHCTLR1_OC2PE_Msk
#define TIM_CHCTLR1_OC2M_Pos                    (12U)
#define TIM_CHCTLR1_OC2M_Msk                    (0x07UL << TIM_CHCTLR1_OC2M_Pos)
#define TIM_CHCTLR1_OC2M                        TIM_CHCTLR1_OC2M_Msk
#define TIM_CHCTLR1_OC2CE_Pos                   (15U)
#define TIM_CHCTLR1_OC2CE_Msk                   (0x01UL << TIM_CHCTLR1_OC2CE_Pos)
#define TIM_CHCTLR1_OC2CE                       TIM_CHCTLR1_OC2CE_Msk
#define TIM_CHCTLR1_IC1PSC_Pos                  (2U)
#define TIM_CHCTLR1_IC1PSC_Msk                  (0x03UL << TIM_CHCTLR1_IC1PSC_Pos)
#define TIM_CHCTLR1_IC1PSC                      TIM_CHCTLR1_IC1PSC_Msk
#define TIM_CHCTLR1_IC1F_Pos                    (4U)
#define TIM_CHCTLR1_IC1F_Msk                    (0x0FUL << TIM_CHCTLR1_IC1F_Pos)
#define TIM_CHCTLR1_IC1F                        TIM_CHCTLR1_IC1F_Msk
#define TIM_CHCTLR1_IC2PSC_Pos                  (10U)
#define TIM_CHCTLR1_IC2PSC_Msk                  (0x03UL << TIM_CHCTLR1_IC2PSC_Pos)
#define TIM_CHCTLR1_IC2PSC                      TIM_CHCTLR1_IC2PSC_Msk
#define TIM_CHCTLR1_IC2F_Pos                    (12U)
#define TIM_CHCTLR1_IC2F_Msk                    (0x0FUL << TIM_CHCTLR1_IC2F_Pos)
#define TIM_CHCTLR1_IC2F                        TIM_CHCTLR1_IC2F_Msk

/******************  Bit definition for TIM_CHCTLR2 register  *****************/
#define TIM_CHCTLR2_CC3S_Pos                    (0U)
#define TIM_CHCTLR2_CC3S_Msk                    (0x03UL << TIM_CHCTLR2_CC3S_Pos)
#define TIM_CHCTLR2_CC3S                        TIM_CHCTLR2_CC3S_Msk
#define TIM_CHCTLR2_OC3FE_Pos                   (2U)
#define TIM_CHCTLR2_OC3FE_Msk                   (0x01UL << TIM_CHCTLR2_OC3FE_Pos)
#define TIM_CHCTLR2_OC3FE                       TIM_CHCTLR2_OC3FE_Msk
#define TIM_CHCTLR2_OC3PE_Pos                   (3U)
#define TIM_CHCTLR2_OC3PE_Msk                   (0x01UL << TIM_CHCTLR2_OC3PE_Pos)
#define TIM_CHCTLR2_OC3PE                       TIM_CHCTLR2_OC3PE_Msk
#define TIM_CHCTLR2_OC3M_Pos                    (4U)
#define TIM_CHCTLR2_OC3M_Msk                    (0x07UL << TIM_CHCTLR2_OC3M_Pos)
#define TIM_CHCTLR2_OC3M                        TIM_CHCTLR2_OC3M_Msk
#define TIM_CHCTLR2_OC3CE_Pos                   (7U)
#define TIM_CHCTLR2_OC3CE_Msk                   (0x01UL << TIM_CHCTLR2_OC3CE_Pos)
#define TIM_CHCTLR2_OC3CE                       TIM_CHCTLR2_OC3CE_Msk
#define TIM_CHCTLR2_CC4S_Pos                    (8U)
#define TIM_CHCTLR2_CC4S_Msk                    (0x03UL << TIM_CHCTLR2_CC4S_Pos)
#define TIM_CHCTLR2_CC4S                        TIM_CHCTLR2_CC4S_Msk
#define TIM_CHCTLR2_OC4FE_Pos                   (10U)
#define TIM_CHCTLR2_OC4FE_Msk                   (0x01UL << TIM_CHCTLR2_OC4FE_Pos)
#define TIM_CHCTLR2_OC4FE                       TIM_CHCTLR2_OC4FE_Msk
#define TIM_CHCTLR2_OC4PE_Pos                   (11U)
#define TIM_CHCTLR2_OC4PE_Msk                   (0x01UL << TIM_CHCTLR2_OC4PE_Pos)
#define TIM_CHCTLR2_OC4PE                       TIM_CHCTLR2_OC4PE_Msk
#define TIM_CHCTLR2_OC4M_Pos                    (12U)
#define TIM_CHCTLR2_OC4M_Msk                    (0x07UL << TIM_CHCTLR2_OC4M_Pos)
#define TIM_CHCTLR2_OC4M                        TIM_CHCTLR2_OC4M_Msk
#define TIM_CHCTLR2_OC4CE_Pos                   (15U)
#define TIM_CHCTLR2_OC4CE_Msk                   (0x01UL << TIM_CHCTLR2_OC4CE_Pos)
#define TIM_CHCTLR2_OC4CE                       TIM_CHCTLR2_OC4CE_Msk
#define TIM_CHCTLR2_IC3PSC_Pos                  (2U)
#define TIM_CHCTLR2_IC3PSC_Msk                  (0x03UL << TIM_CHCTLR2_IC3PSC_Pos)
#define TIM_CHCTLR2_IC3PSC                      TIM_CHCTLR2_IC3PSC_Msk
#define TIM_CHCTLR2_IC3F_Pos                    (4U)
#define TIM_CHCTLR2_IC3F_Msk                    (0x0FUL << TIM_CHCTLR2_IC3F_Pos)
#define TIM_CHCTLR2_IC3F                        TIM_CHCTLR2_IC3F_Msk
#define TIM_CHCTLR2_IC4PSC_Pos                  (10U)
#define TIM_CHCTLR2_IC4PSC_Msk                  (0x03UL << TIM_CHCTLR2_IC4PSC_Pos)
#define TIM_CHCTLR2_IC4PSC                      TIM_CHCTLR2_IC4PSC_Msk
#define TIM_CHCTLR2_IC4F_Pos                    (12U)
#define TIM_CHCTLR2_IC4F_Msk                    (0x0FUL << TIM_CHCTLR2_IC4F_Pos)
#define TIM_CHCTLR2_IC4F                        TIM_CHCTLR2_IC4F_Msk

/******************  Bit definition for TIM_CCER register  ********************/
#define TIM_CCER_CC1E_Pos                       (0U)
#define TIM_CCER_CC1E_Msk                       (0x01UL << TIM_CCER_CC1E_Pos)
#define TIM_CCER_CC1E                           TIM_CCER_CC1E_Msk
#define TIM_CCER_CC1P_Pos                       (1U)
#define TIM_CCER_CC1P_Msk                       (0x01UL << TIM_CCER_CC1P_Pos)
#define TIM_CCER_CC1P                           TIM_CCER_CC1P_Msk
#define TIM_CCER_CC1NE_Pos                      (2U)
#define TIM_CCER_CC1NE_Msk                      (0x01UL << TIM_CCER_CC1NE_Pos)
#define TIM_CCER_CC1NE                          TIM_CCER_CC1NE_Msk
#define TIM_CCER_CC1NP_Pos                      (3U)
#define TIM_CCER_CC1NP_Msk                      (0x01UL << TIM_CCER_CC1NP_Pos)
#define TIM_CCER_CC1NP                          TIM_CCER_CC1NP_Msk
#define TIM_CCER_CC2E_Pos                       (4U)
#define TIM_CCER_CC2E_Msk                       (0x01UL << TIM_CCER_CC2E_Pos)
#define TIM_CCER_CC2E                           TIM_CCER_CC2E_Msk
#define TIM_CCER_CC2P_Pos                       (5U)
#define TIM_CCER_CC2P_Msk                       (0x01UL << TIM_CCER_CC2P_Pos)
#define TIM_CCER_CC2P                           TIM_CCER_CC2P_Msk
#define TIM_CCER_CC2NE_Pos                      (6U)
#define TIM_CCER_CC2NE_Msk                      (0x01UL << TIM_CCER_CC2NE_Pos)
#define TIM_CCER_CC2NE                          TIM_CCER_CC2NE_Msk
#define TIM_CCER_CC2NP_Pos                      (7U)
#define TIM_CCER_CC2NP_Msk                      (0x01UL << TIM_CCER_CC2NP_Pos)
#define TIM_CCER_CC2NP                          TIM_CCER_CC2NP_Msk
#define TIM_CCER_CC3E_Pos                       (8U)
#define TIM_CCER_CC3E_Msk                       (0x01UL << TIM_CCER_CC3E_Pos)
#define TIM_CCER_CC3E                           TIM_CCER_CC3E_Msk
#define TIM_CCER_CC3P_Pos                       (9U)
#define TIM_CCER_CC3P_Msk                       (0x01UL << TIM_CCER_CC3P_Pos)
#define TIM_CCER_CC3P                           TIM_CCER_CC3P_Msk
#define TIM_CCER_CC3NE_Pos                      (10U)
#define TIM_CCER_CC3NE_Msk                      (0x01UL << TIM_CCER_CC3NE_Pos)
#define TIM_CCER_CC3NE                          TIM_CCER_CC3NE_Msk
#define TIM_CCER_CC3NP_Pos                      (11U)
#define TIM_CCER_CC3NP_Msk                      (0x01UL << TIM_CCER_CC3NP_Pos)
#define TIM_CCER_CC3NP                          TIM_CCER_CC3NP_Msk
#define TIM_CCER_CC4E_Pos                       (12U)
#define TIM_CCER_CC4E_Msk                       (0x01UL << TIM_CCER_CC4E_Pos)
#define TIM_CCER_CC4E                           TIM_CCER_CC4E_Msk
#define TIM_CCER_CC4P_Pos                       (13U)
#define TIM_CCER_CC4P_Msk                       (0x01UL << TIM_CCER_CC4P_Pos)
#define TIM_CCER_CC4P                           TIM_CCER_CC4P_Msk

/******************  Bit definition for TIM_CNT register  *********************/
#define TIM_CNT_CNT_Pos                         (0U)
#define TIM_CNT_CNT_Msk                         (0xFFFFUL << TIM_CNT_CNT_Pos)
#define TIM_CNT_CNT                             TIM_CNT_CNT_Msk

/******************  Bit definition for TIM_PSC register  *********************/
#define TIM_PSC_PSC_Pos                         (0U)
#define TIM_PSC_PSC_Msk                         (0xFFFFUL << TIM_PSC_PSC_Pos)
#define TIM_PSC_PSC                             TIM_PSC_PSC_Msk

/******************  Bit definition for TIM_ATRLR register  *******************/
#define TIM_ATRLR_ATRLR_Pos                     (0U)
#define TIM_ATRLR_ATRLR_Msk                     (0xFFFFUL << TIM_ATRLR_ATRLR_Pos)
#define TIM_ATRLR_ATRLR                         TIM_ATRLR_ATRLR_Msk

/******************  Bit definition for TIM_RPTCR register  *******************/
#define TIM_RPTCR_RPTCR_Pos                     (0U)
#define TIM_RPTCR_RPTCR_Msk                     (0xFFUL << TIM_RPTCR_RPTCR_Pos)
#define TIM_RPTCR_RPTCR                         TIM_RPTCR_RPTCR_Msk

/******************  Bit definition for TIM_CH1CVR register  ******************/
#define TIM_CH1CVR_CH1CVR_Pos                   (0U)
#define TIM_CH1CVR_CH1CVR_Msk                   (0xFFFFUL << TIM_CH1CVR_CH1CVR_Pos)
#define TIM_CH1CVR_CH1CVR                       TIM_CH1CVR_CH1CVR_Msk

/******************  Bit definition for TIM_CH2CVR register  ******************/
#define TIM_CH2CVR_CH2CVR_Pos                   (0U)
#define TIM_CH2CVR_CH2CVR_Msk                   (0xFFFFUL << TIM_CH2CVR_CH2CVR_Pos)
#define TIM_CH2CVR_CH2CVR                       TIM_CH2CVR_CH2CVR_Msk

/******************  Bit definition for TIM_CH3CVR register  ******************/
#define TIM_CH3CVR_CH3CVR_Pos                   (0U)
#define TIM_CH3CVR_CH3CVR_Msk                   (0xFFFFUL << TIM_CH3CVR_CH3CVR_Pos)
#define TIM_CH3CVR_CH3CVR                       TIM_CH3CVR_CH3CVR_Msk

/******************  Bit definition for TIM_CH4CVR register  ******************/
#define TIM_CH4CVR_CH4CVR_Pos                   (0U)
#define TIM_CH4CVR_CH4CVR_Msk                   (0xFFFFUL << TIM_CH4CVR_CH4CVR_Pos)
#define TIM_CH4CVR_CH4CVR                       TIM_CH4CVR_CH4CVR_Msk

/******************  Bit definition for TIM_BDTR register  ********************/
#define TIM_BDTR_DTG_Pos                        (0U)
#define TIM_BDTR_DTG_Msk                        (0xFFUL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG                            TIM_BDTR_DTG_Msk
#define TIM_BDTR_LOCK_Pos                       (8U)
#define TIM_BDTR_LOCK_Msk                       (0x03UL << TIM_BDTR_LOCK_Pos)
#define TIM_BDTR_LOCK                           TIM_BDTR_LOCK_Msk
#define TIM_BDTR_OSSI_Pos                       (10U)
#define TIM_BDTR_OSSI_Msk                       (0x01UL << TIM_BDTR_OSSI_Pos)
#define TIM_BDTR_OSSI                           TIM_BDTR_OSSI_Msk
#define TIM_BDTR_OSSR_Pos                       (11U)
#define TIM_BDTR_OSSR_Msk                       (0x01UL << TIM_BDTR_OSSR_Pos)
#define TIM_BDTR_OSSR                           TIM_BDTR_OSSR_Msk
#define TIM_BDTR_BKE_Pos                        (12U)
#define TIM_BDTR_BKE_Msk                        (0x01UL << TIM_BDTR_BKE_Pos)
#define TIM_BDTR_BKE                            TIM_BDTR_BKE_Msk
#define TIM_BDTR_BKP_Pos                        (13U)
#define TIM_BDTR_BKP_Msk                        (0x01UL << TIM_BDTR_BKP_Pos)
#define TIM_BDTR_BKP                            TIM_BDTR_BKP_Msk
#define TIM_BDTR_AOE_Pos                        (14U)
#define TIM_BDTR_AOE_Msk                        (0x01UL << TIM_BDTR_AOE_Pos)
#define TIM_BDTR_AOE                            TIM_BDTR_AOE_Msk
#define TIM_BDTR_MOE_Pos                        (15U)
#define TIM_BDTR_MOE_Msk                        (0x01UL << TIM_BDTR_MOE_Pos)
#define TIM_BDTR_MOE                            TIM_BDTR_MOE_Msk

/******************  Bit definition for TIM_DMACFGR register  *****************/
#define TIM_DMACFGR_DBA_Pos                     (0U)
#define TIM_DMACFGR_DBA_Msk                     (0x1FUL << TIM_DMACFGR_DBA_Pos)
#define TIM_DMACFGR_DBA                         TIM_DMACFGR_DBA_Msk
#define TIM_DMACFGR_DBL_Pos                     (8U)
#define TIM_DMACFGR_DBL_Msk                     (0x1FUL << TIM_DMACFGR_DBL_Pos)
#define TIM_DMACFGR_DBL                         TIM_DMACFGR_DBL_Msk

/******************  Bit definition for TIM_DMAADR register  ******************/
#define TIM_DMAADR_DMAB_Pos                     (0U)
#define TIM_DMAADR_DMAB_Msk                     (0xFFFFUL << TIM_DMAADR_DMAB_Pos)
#define TIM_DMAADR_DMAB                         TIM_DMAADR_DMAB_Msk

/******************************************************************************/
/*          Universal Synchronous Asynchronous Receiver Transmitter           */
/******************************************************************************/
/******************  Bit definition for USART_STATR register  *****************/
#define USART_STATR_PE_Pos                      (0U)
#define USART_STATR_PE_Msk                      (0x01UL << USART_STATR_PE_Pos)
#define USART_STATR_PE                          USART_STATR_PE_Msk
#define USART_STATR_FE_Pos                      (1U)
#define USART_STATR_FE_Msk                      (0x01UL << USART_STATR_FE_Pos)
#define USART_STATR_FE                          USART_STATR_FE_Msk
#define USART_STATR_NE_Pos                      (2U)
#define USART_STATR_NE_Msk                      (0x01UL << USART_STATR_NE_Pos)
#define USART_STATR_NE                          USART_STATR_NE_Msk
#define USART_STATR_ORE_Pos                     (3U)
#define USART_STATR_ORE_Msk                     (0x01UL << USART_STATR_ORE_Pos)
#define USART_STATR_ORE                         USART_STATR_ORE_Msk
#define USART_STATR_IDLE_Pos                    (4U)
#define USART_STATR_IDLE_Msk                    (0x01UL << USART_STATR_IDLE_Pos)
#define USART_STATR_IDLE                        USART_STATR_IDLE_Msk
#define USART_STATR_RXNE_Pos                    (5U)
#define USART_STATR_RXNE_Msk                    (0x01UL << USART_STATR_RXNE_Pos)
#define USART_STATR_RXNE                        USART_STATR_RXNE_Msk
#define USART_STATR_TC_Pos                      (6U)
#define USART_STATR_TC_Msk                      (0x01UL << USART_STATR_TC_Pos)
#define USART_STATR_TC                          USART_STATR_TC_Msk
#define USART_STATR_TXE_Pos                     (7U)
#define USART_STATR_TXE_Msk                     (0x01UL << USART_STATR_TXE_Pos)
#define USART_STATR_TXE                         USART_STATR_TXE_Msk
#define USART_STATR_LBD_Pos                     (8U)
#define USART_STATR_LBD_Msk                     (0x01UL << USART_STATR_LBD_Pos)
#define USART_STATR_LBD                         USART_STATR_LBD_Msk
#define USART_STATR_CTS_Pos                     (9U)
#define USART_STATR_CTS_Msk                     (0x01UL << USART_STATR_CTS_Pos)
#define USART_STATR_CTS                         USART_STATR_CTS_Msk

/******************  Bit definition for USART_DATAR register  *****************/
#define USART_DATAR_DR_Pos                      (0U)
#define USART_DATAR_DR_Msk                      (0x01FFUL << USART_DATAR_DR_Pos)
#define USART_DATAR_DR                          USART_DATAR_DR_Msk

/******************  Bit definition for USART_BRR register  *******************/
#define USART_BRR_DIV_FRACTION_Pos              (0U)
#define USART_BRR_DIV_FRACTION_Msk              (0x0FUL << USART_BRR_DIV_FRACTION_Pos)
#define USART_BRR_DIV_FRACTION                  USART_BRR_DIV_FRACTION_Msk
#define USART_BRR_DIV_MANTISSA_Pos              (4U)
#define USART_BRR_DIV_MANTISSA_Msk              (0x0FFFUL << USART_BRR_DIV_MANTISSA_Pos)
#define USART_BRR_DIV_MANTISSA                  USART_BRR_DIV_MANTISSA_Msk

/******************  Bit definition for USART_CTLR1 register  *****************/
#define USART_CTLR1_SBK_Pos                     (0U)
#define USART_CTLR1_SBK_Msk                     (0x01UL << USART_CTLR1_SBK_Pos)
#define USART_CTLR1_SBK                         USART_CTLR1_SBK_Msk
#define USART_CTLR1_RWU_Pos                     (1U)
#define USART_CTLR1_RWU_Msk                     (0x01UL << USART_CTLR1_RWU_Pos)
#define USART_CTLR1_RWU                         USART_CTLR1_RWU_Msk
#define USART_CTLR1_RE_Pos                      (2U)
#define USART_CTLR1_RE_Msk                      (0x01UL << USART_CTLR1_RE_Pos)
#define USART_CTLR1_RE                          USART_CTLR1_RE_Msk
#define USART_CTLR1_TE_Pos                      (3U)
#define USART_CTLR1_TE_Msk                      (0x01UL << USART_CTLR1_TE_Pos)
#define USART_CTLR1_TE                          USART_CTLR1_TE_Msk
#define USART_CTLR1_IDLEIE_Pos                  (4U)
#define USART_CTLR1_IDLEIE_Msk                  (0x01UL << USART_CTLR1_IDLEIE_Pos)
#define USART_CTLR1_IDLEIE                      USART_CTLR1_IDLEIE_Msk
#define USART_CTLR1_RXNEIE_Pos                  (5U)
#define USART_CTLR1_RXNEIE_Msk                  (0x01UL << USART_CTLR1_RXNEIE_Pos)
#define USART_CTLR1_RXNEIE                      USART_CTLR1_RXNEIE_Msk
#define USART_CTLR1_TCIE_Pos                    (6U)
#define USART_CTLR1_TCIE_Msk                    (0x01UL << USART_CTLR1_TCIE_Pos)
#define USART_CTLR1_TCIE                        USART_CTLR1_TCIE_Msk
#define USART_CTLR1_TXEIE_Pos                   (7U)
#define USART_CTLR1_TXEIE_Msk                   (0x01UL << USART_CTLR1_TXEIE_Pos)
#define USART_CTLR1_TXEIE                       USART_CTLR1_TXEIE_Msk
#define USART_CTLR1_PEIE_Pos                    (8U)
#define USART_CTLR1_PEIE_Msk                    (0x01UL << USART_CTLR1_PEIE_Pos)
#define USART_CTLR1_PEIE                        USART_CTLR1_PEIE_Msk
#define USART_CTLR1_PS_Pos                      (9U)
#define USART_CTLR1_PS_Msk                      (0x01UL << USART_CTLR1_PS_Pos)
#define USART_CTLR1_PS                          USART_CTLR1_PS_Msk
#define USART_CTLR1_PCE_Pos                     (10U)
#define USART_CTLR1_PCE_Msk                     (0x01UL << USART_CTLR1_PCE_Pos)
#define USART_CTLR1_PCE                         USART_CTLR1_PCE_Msk
#define USART_CTLR1_WAKE_Pos                    (11U)
#define USART_CTLR1_WAKE_Msk                    (0x01UL << USART_CTLR1_WAKE_Pos)
#define USART_CTLR1_WAKE                        USART_CTLR1_WAKE_Msk
#define USART_CTLR1_M_Pos                       (12U)
#define USART_CTLR1_M_Msk                       (0x01UL << USART_CTLR1_M_Pos)
#define USART_CTLR1_M                           USART_CTLR1_M_Msk
#define USART_CTLR1_UE_Pos                      (13U)
#define USART_CTLR1_UE_Msk                      (0x01UL << USART_CTLR1_UE_Pos)
#define USART_CTLR1_UE                          USART_CTLR1_UE_Msk

/******************  Bit definition for USART_CTLR2 register  *****************/
#define USART_CTLR2_ADD_Pos                     (0U)
#define USART_CTLR2_ADD_Msk                     (0x0FUL << USART_CTLR2_ADD_Pos)
#define USART_CTLR2_ADD                         USART_CTLR2_ADD_Msk
#define USART_CTLR2_LBDL_Pos                    (5U)
#define USART_CTLR2_LBDL_Msk                    (0x01UL << USART_CTLR2_LBDL_Pos)
#define USART_CTLR2_LBDL                        USART_CTLR2_LBDL_Msk
#define USART_CTLR2_LBDIE_Pos                   (6U)
#define USART_CTLR2_LBDIE_Msk                   (0x01UL << USART_CTLR2_LBDIE_Pos)
#define USART_CTLR2_LBDIE                       USART_CTLR2_LBDIE_Msk
#define USART_CTLR2_LBCL_Pos                    (8U)
#define USART_CTLR2_LBCL_Msk                    (0x01UL << USART_CTLR2_LBCL_Pos)
#define USART_CTLR2_LBCL                        USART_CTLR2_LBCL_Msk
#define USART_CTLR2_CPHA_Pos                    (9U)
#define USART_CTLR2_CPHA_Msk                    (0x01UL << USART_CTLR2_CPHA_Pos)
#define USART_CTLR2_CPHA                        USART_CTLR2_CPHA_Msk
#define USART_CTLR2_CPOL_Pos                    (10U)
#define USART_CTLR2_CPOL_Msk                    (0x01UL << USART_CTLR2_CPOL_Pos)
#define USART_CTLR2_CPOL                        USART_CTLR2_CPOL_Msk
#define USART_CTLR2_CLKEN_Pos                   (11U)
#define USART_CTLR2_CLKEN_Msk                   (0x01UL << USART_CTLR2_CLKEN_Pos)
#define USART_CTLR2_CLKEN                       USART_CTLR2_CLKEN_Msk
#define USART_CTLR2_STOP_Pos                    (12U)
#define USART_CTLR2_STOP_Msk                    (0x03UL << USART_CTLR2_STOP_Pos)
#define USART_CTLR2_STOP                        USART_CTLR2_STOP_Msk
#define USART_CTLR2_LINEN_Pos                   (14U)
#define USART_CTLR2_LINEN_Msk                   (0x01UL << USART_CTLR2_LINEN_Pos)
#define USART_CTLR2_LINEN                       USART_CTLR2_LINEN_Msk

/******************  Bit definition for USART_CTLR3 register  *****************/
#define USART_CTLR3_EIE_Pos                     (0U)
#define USART_CTLR3_EIE_Msk                     (0x01UL << USART_CTLR3_EIE_Pos)
#define USART_CTLR3_EIE                         USART_CTLR3_EIE_Msk
#define USART_CTLR3_IREN_Pos                    (1U)
#define USART_CTLR3_IREN_Msk                    (0x01UL << USART_CTLR3_IREN_Pos)
#define USART_CTLR3_IREN                        USART_CTLR3_IREN_Msk
#define USART_CTLR3_IRLP_Pos                    (2U)
#define USART_CTLR3_IRLP_Msk                    (0x01UL << USART_CTLR3_IRLP_Pos)
#define USART_CTLR3_IRLP                        USART_CTLR3_IRLP_Msk
#define USART_CTLR3_HDSEL_Pos                   (3U)
#define USART_CTLR3_HDSEL_Msk                   (0x01UL << USART_CTLR3_HDSEL_Pos)
#define USART_CTLR3_HDSEL                       USART_CTLR3_HDSEL_Msk
#define USART_CTLR3_NACK_Pos                    (4U)
#define USART_CTLR3_NACK_Msk                    (0x01UL << USART_CTLR3_NACK_Pos)
#define USART_CTLR3_NACK                        USART_CTLR3_NACK_Msk
#define USART_CTLR3_SCEN_Pos                    (5U)
#define USART_CTLR3_SCEN_Msk                    (0x01UL << USART_CTLR3_SCEN_Pos)
#define USART_CTLR3_SCEN                        USART_CTLR3_SCEN_Msk
#define USART_CTLR3_DMAR_Pos                    (6U)
#define USART_CTLR3_DMAR_Msk                    (0x01UL << USART_CTLR3_DMAR_Pos)
#define USART_CTLR3_DMAR                        USART_CTLR3_DMAR_Msk
#define USART_CTLR3_DMAT_Pos                    (7U)
#define USART_CTLR3_DMAT_Msk                    (0x01UL << USART_CTLR3_DMAT_Pos)
#define USART_CTLR3_DMAT                        USART_CTLR3_DMAT_Msk
#define USART_CTLR3_RTSE_Pos                    (8U)
#define USART_CTLR3_RTSE_Msk                    (0x01UL << USART_CTLR3_RTSE_Pos)
#define USART_CTLR3_RTSE                        USART_CTLR3_RTSE_Msk
#define USART_CTLR3_CTSE_Pos                    (9U)
#define USART_CTLR3_CTSE_Msk                    (0x01UL << USART_CTLR3_CTSE_Pos)
#define USART_CTLR3_CTSE                        USART_CTLR3_CTSE_Msk
#define USART_CTLR3_CTSIE_Pos                   (10U)
#define USART_CTLR3_CTSIE_Msk                   (0x01UL << USART_CTLR3_CTSIE_Pos)
#define USART_CTLR3_CTSIE                       USART_CTLR3_CTSIE_Msk

/******************  Bit definition for USART_GPR register  *******************/
#define USART_GPR_PSC_Pos                       (0U)
#define USART_GPR_PSC_Msk                       (0xFFUL << USART_GPR_PSC_Pos)
#define USART_GPR_PSC                           USART_GPR_PSC_Msk
#define USART_GPR_GT_Pos                        (8U)
#define USART_GPR_GT_Msk                        (0xFFUL << USART_GPR_GT_Pos)
#define USART_GPR_GT                            USART_GPR_GT_Msk

/******************************************************************************/
/*                              Window WATCHDOG                               */
/******************************************************************************/
/******************  Bit definition for WWDG_CTLR register  *******************/
#define WWDG_CTLR_T_Pos                         (0U)
#define WWDG_CTLR_T_Msk                         (0x7FUL << WWDG_CTLR_T_Pos)
#define WWDG_CTLR_T                             WWDG_CTLR_T_Msk
#define WWDG_CTLR_WDGA_Pos                      (7U)
#define WWDG_CTLR_WDGA_Msk                      (0x01UL << WWDG_CTLR_WDGA_Pos)
#define WWDG_CTLR_WDGA                          WWDG_CTLR_WDGA_Msk

/******************  Bit definition for WWDG_CFGR register  *******************/
#define WWDG_CFGR_W_Pos                         (0U)
#define WWDG_CFGR_W_Msk                         (0x7FUL << WWDG_CFGR_W_Pos)
#define WWDG_CFGR_W                             WWDG_CFGR_W_Msk
#define WWDG_CFGR_WDGTB_Pos                     (7U)
#define WWDG_CFGR_WDGTB_Msk                     (0x03UL << WWDG_CFGR_WDGTB_Pos)
#define WWDG_CFGR_WDGTB                         WWDG_CFGR_WDGTB_Msk
#define WWDG_CFGR_EWI_Pos                       (9U)
#define WWDG_CFGR_EWI_Msk                       (0x01UL << WWDG_CFGR_EWI_Pos)
#define WWDG_CFGR_EWI                           WWDG_CFGR_EWI_Msk

/******************  Bit definition for WWDG_STATR register  ******************/
#define WWDG_STATR_EWIF_Pos                     (0U)
#define WWDG_STATR_EWIF_Msk                     (0x01UL << WWDG_STATR_EWIF_Pos)
#define WWDG_STATR_EWIF                         WWDG_STATR_EWIF_Msk

/******************************************************************************/
/*                            Extended Function                               */
/******************************************************************************/
/******************  Bit definition for EXTEND_CTR register  ******************/
#define EXTEND_CTR_LKUPEN_Pos                   (6U)
#define EXTEND_CTR_LKUPEN_Msk                   (0x01UL << EXTEND_CTR_LKUPEN_Pos)
#define EXTEND_CTR_LKUPEN                       EXTEND_CTR_LKUPEN_Msk
#define EXTEND_CTR_LKUPRST_Pos                  (7U)
#define EXTEND_CTR_LKUPRST_Msk                  (0x01UL << EXTEND_CTR_LKUPRST_Pos)
#define EXTEND_CTR_LKUPRST                      EXTEND_CTR_LKUPRST_Msk
#define EXTEND_CTR_LDOTRIM_Pos                  (10U)
#define EXTEND_CTR_LDOTRIM_Msk                  (0x01UL << EXTEND_CTR_LDOTRIM_Pos)
#define EXTEND_CTR_LDOTRIM                      EXTEND_CTR_LDOTRIM_Msk
#define EXTEND_CTR_OPA_EN_Pos                   (16U)
#define EXTEND_CTR_OPA_EN_Msk                   (0x01UL << EXTEND_CTR_OPA_EN_Pos)
#define EXTEND_CTR_OPA_EN                       EXTEND_CTR_OPA_EN_Msk
#define EXTEND_CTR_OPA_NSEL_Pos                 (17U)
#define EXTEND_CTR_OPA_NSEL_Msk                 (0x01UL << EXTEND_CTR_OPA_NSEL_Pos)
#define EXTEND_CTR_OPA_NSEL                     EXTEND_CTR_OPA_NSEL_Msk
#define EXTEND_CTR_OPA_PSEL_Pos                 (18U)
#define EXTEND_CTR_OPA_PSEL_Msk                 (0x01UL << EXTEND_CTR_OPA_PSEL_Pos)
#define EXTEND_CTR_OPA_PSEL                     EXTEND_CTR_OPA_PSEL_Msk

#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_H */
