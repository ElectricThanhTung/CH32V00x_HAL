
#ifndef __CH32V00x_HAL_RCC_H
#define __CH32V00x_HAL_RCC_H

#include "ch32v00x_hal.h"

typedef enum {
    RCC_PLLSRC_HSI = 0x00,
    RCC_PLLSRC_HSE = 0x01,
    RCC_PLLSRC_DISABLE = 0x03,
} RCC_PllSrcTypeDef;

typedef enum {
    RCC_SYSCLKSRC_HSI = 0x00,
    RCC_SYSCLKSRC_HSE = 0x01,
    RCC_SYSCLKSRC_PLL = 0x02,
} RCC_SysClkSrcTypeDef;

typedef enum {
    RCC_SYSCLK_DIV1 = 0x00,
    RCC_SYSCLK_DIV2 = 0x01,
    RCC_SYSCLK_DIV3 = 0x02,
    RCC_SYSCLK_DIV4 = 0x03,
    RCC_SYSCLK_DIV5 = 0x04,
    RCC_SYSCLK_DIV6 = 0x05,
    RCC_SYSCLK_DIV7 = 0x06,
    RCC_SYSCLK_DIV8 = 0x07,
    RCC_SYSCLK_DIV16 = 0x0B,
    RCC_SYSCLK_DIV32 = 0x0C,
    RCC_SYSCLK_DIV64 = 0x0D,
    RCC_SYSCLK_DIV128 = 0x0E,
    RCC_SYSCLK_DIV256 = 0x0F,
} RCC_SysClkDivTypeDef;

typedef enum {
    RCC_AHBCLK_DIV2 = 0x00,
    RCC_AHBCLK_DIV4 = 0x08,
    RCC_AHBCLK_DIV6 = 0x10,
    RCC_AHBCLK_DIV8 = 0x18,
    RCC_AHBCLK_DIV12 = 0x14,
    RCC_AHBCLK_DIV16 = 0x1C,
    RCC_AHBCLK_DIV24 = 0x15,
    RCC_AHBCLK_DIV32 = 0x1D,
    RCC_AHBCLK_DIV48 = 0x16,
    RCC_AHBCLK_DIV64 = 0x1E,
    RCC_AHBCLK_DIV96 = 0x17,
    RCC_AHBCLK_DIV128 = 0x1F
} RCC_AdcClkDivTypeDef;

typedef enum {
    RCC_OUTPUTCLK_DISABLE = 0x00,
    RCC_OUTPUTCLK_SYSCLK = 0x04,
    RCC_OUTPUTCLK_HSI = 0x05,
    RCC_OUTPUTCLK_HSE = 0x06,
    RCC_OUTPUTCLK_PLL = 0x07
} RCC_OutputClkTypeDef;

typedef enum {
    RCC_PERIPHCLK_DMA1EN = (0UL << 30U) | RCC_AHBPCENR_DMA1EN,
    RCC_PERIPHCLK_SRAMEN = (0UL << 30U) | RCC_AHBPCENR_SRAMEN,

    RCC_PERIPHCLK_AFIOEN = (1UL << 30U) | RCC_APB2PCENR_AFIOEN,
    RCC_PERIPHCLK_IOPAEN = (1UL << 30U) | RCC_APB2PCENR_IOPAEN,
    RCC_PERIPHCLK_IOPCEN = (1UL << 30U) | RCC_APB2PCENR_IOPCEN,
    RCC_PERIPHCLK_IOPDEN = (1UL << 30U) | RCC_APB2PCENR_IOPDEN,
    RCC_PERIPHCLK_ADC1EN = (1UL << 30U) | RCC_APB2PCENR_ADC1EN,
    RCC_PERIPHCLK_TIM1EN = (1UL << 30U) | RCC_APB2PCENR_TIM1EN,
    RCC_PERIPHCLK_SPI1EN = (1UL << 30U) | RCC_APB2PCENR_SPI1EN,
    RCC_PERIPHCLK_USART1EN = (1UL << 30U) | RCC_APB2PCENR_USART1EN,

    RCC_PERIPHCLK_TIM2EN = (2UL << 30U) | RCC_APB1PCENR_TIM2EN,
    RCC_PERIPHCLK_WWDGEN = (2UL << 30U) | RCC_APB1PCENR_WWDGEN,
    RCC_PERIPHCLK_I2C1EN = (2UL << 30U) | RCC_APB1PCENR_I2C1EN,
    RCC_PERIPHCLK_PWREN = (2UL << 30U) | RCC_APB1PCENR_PWREN
} RCC_PeriphClkTypeDef;

class RCC_TypeDef {
public:
    struct {
    public:
        __IO uint32_t CTLR;
        __IO uint32_t CFGR0;
        __IO uint32_t INTR;
        __IO uint32_t APB2PRSTR;
        __IO uint32_t APB1PRSTR;
        __IO uint32_t AHBPCENR;
        __IO uint32_t APB2PCENR;
        __IO uint32_t APB1PCENR;
    private:
        __IO uint32_t RESERVED0;
    public:
        __IO uint32_t RSTSCKR;
    } REGS;
public:
    HAL_StatusTypeDef SetHSIState(HAL_StateTypeDef state);
    HAL_StatusTypeDef SetHSEState(HAL_StateTypeDef state);
    HAL_StatusTypeDef SetPLLSource(RCC_PllSrcTypeDef source);
    HAL_StatusTypeDef SetSysClock(RCC_SysClkSrcTypeDef source, RCC_SysClkDivTypeDef div = RCC_SYSCLK_DIV1);
    void SetADCCLKDivider(RCC_AdcClkDivTypeDef div);
    void SetOutputClockSource(RCC_OutputClkTypeDef source);
    void SetPeriphClockState(RCC_PeriphClkTypeDef peripheral, HAL_StateTypeDef state);
    HAL_StateTypeDef GetHSIState(void);
    HAL_StateTypeDef GetHSEState(void);
    RCC_PllSrcTypeDef GetPLLSource(void);
    RCC_OutputClkTypeDef GetOutputClockSource(void);
    HAL_StateTypeDef GetPeriphClockState(RCC_PeriphClkTypeDef peripheral);
    uint32_t GetSysClockFreq(void);
    uint32_t GetHCLKFreq(void);
    uint32_t GetOutputClockFreq(void);
    void DeInit(void);
private:
    RCC_TypeDef(void);
    RCC_TypeDef(RCC_TypeDef &);
    HAL_StatusTypeDef SetPLLState(HAL_StateTypeDef state);
    void CoreClockUpdate(void);
};

#define RCC             (*(RCC_TypeDef *)RCC_BASE)

#endif /* __CH32V00x_HAL_RCC_H */
