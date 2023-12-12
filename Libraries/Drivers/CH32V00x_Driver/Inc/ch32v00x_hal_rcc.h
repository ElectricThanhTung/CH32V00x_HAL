
#ifndef __CH32V00x_HAL_RCC_H
#define __CH32V00x_HAL_RCC_H

#include "ch32v00x_hal.h"

typedef enum {
    RCC_PLLSRC_HSI = 0x00U,
    RCC_PLLSRC_HSE = 0x01U,
    RCC_PLLSRC_DISABLE = 0x03U,
} RCC_PllSrcTypeDef;

typedef enum {
    RCC_SYSCLKSRC_HSI = 0x00U,
    RCC_SYSCLKSRC_HSE = 0x01U,
    RCC_SYSCLKSRC_PLL = 0x02U,
} RCC_SysClkSrcTypeDef;

typedef enum {
    RCC_SYSCLK_DIV1 = 0x00U,
    RCC_SYSCLK_DIV2 = 0x01U,
    RCC_SYSCLK_DIV3 = 0x02U,
    RCC_SYSCLK_DIV4 = 0x03U,
    RCC_SYSCLK_DIV5 = 0x04U,
    RCC_SYSCLK_DIV6 = 0x05U,
    RCC_SYSCLK_DIV7 = 0x06U,
    RCC_SYSCLK_DIV8 = 0x07U,
    RCC_SYSCLK_DIV16 = 0x0BU,
    RCC_SYSCLK_DIV32 = 0x0CU,
    RCC_SYSCLK_DIV64 = 0x0DU,
    RCC_SYSCLK_DIV128 = 0x0EU,
    RCC_SYSCLK_DIV256 = 0x0FU,
} RCC_SysClkDivTypeDef;

typedef enum {
    RCC_OUTPUTCLK_DISABLE = 0x00U,
    RCC_OUTPUTCLK_SYSCLK = 0x04U,
    RCC_OUTPUTCLK_HSI = 0x05U,
    RCC_OUTPUTCLK_HSE = 0x06U,
    RCC_OUTPUTCLK_PLL = 0x07
} RCC_OutputSourceTypeDef;

typedef struct {
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
} RCC_RegsTypeDef;

class RCC_HsiTypeDef {
private:
    RCC_RegsTypeDef REGS;
public:
    HAL_StatusTypeDef Enable(void);
    HAL_StatusTypeDef Disable(void);
    HAL_StateTypeDef GetState(void);
    uint32_t GetFreq(void);
private:
    RCC_HsiTypeDef(void);
    RCC_HsiTypeDef(RCC_HsiTypeDef &);
};

class RCC_HseTypeDef {
private:
    RCC_RegsTypeDef REGS;
public:
    HAL_StatusTypeDef Enable(void);
    HAL_StatusTypeDef Disable(void);
    HAL_StateTypeDef GetState(void);
    uint32_t GetFreq(void);
private:
    RCC_HseTypeDef(void);
    RCC_HseTypeDef(RCC_HseTypeDef &);
};

class RCC_PllTypeDef {
private:
    RCC_RegsTypeDef REGS;
public:
    HAL_StatusTypeDef SetSource(RCC_PllSrcTypeDef source);
    RCC_PllSrcTypeDef GetSource(void);
    uint32_t GetFreq(void);
private:
    RCC_PllTypeDef(void);
    RCC_PllTypeDef(RCC_PllTypeDef &);

    HAL_StatusTypeDef SetState(HAL_StateTypeDef state);
};

class RCC_SysClkTypeDef {
private:
    RCC_RegsTypeDef REGS;
public:
    HAL_StatusTypeDef SetSource(RCC_SysClkSrcTypeDef source);
    RCC_SysClkSrcTypeDef GetSource(void);
    uint32_t GetFreq(void);
private:
    RCC_SysClkTypeDef(void);
    RCC_SysClkTypeDef(RCC_SysClkTypeDef &);
};

class RCC_HclkTypeDef {
private:
    RCC_RegsTypeDef REGS;
public:
    void SetDiv(RCC_SysClkDivTypeDef div);
    RCC_SysClkDivTypeDef GetDiv(void);
    uint32_t GetFreq(void);
private:
    RCC_HclkTypeDef(void);
    RCC_HclkTypeDef(RCC_HclkTypeDef &);
};

class RCC_OutClkTypeDef {
private:
    RCC_RegsTypeDef REGS;
public:
    void SetSource(RCC_OutputSourceTypeDef source);
    RCC_OutputSourceTypeDef GetSource(void);
    uint32_t GetFreq(void);
private:
    RCC_OutClkTypeDef(void);
    RCC_OutClkTypeDef(RCC_OutClkTypeDef &);
};

class RCC_TypeDef {
public:
    union {
        RCC_RegsTypeDef REGS;
        RCC_HsiTypeDef HSI;
        RCC_HseTypeDef HSE;
        RCC_PllTypeDef PLL;
        RCC_SysClkTypeDef SysClk;
        RCC_HclkTypeDef HCLK;
        RCC_OutClkTypeDef OutClk;
    };
public:
    void DeInit(void);
private:
    RCC_TypeDef(void);
    RCC_TypeDef(RCC_TypeDef &);
};

#define RCC             (*(RCC_TypeDef *)RCC_BASE)

#endif /* __CH32V00x_HAL_RCC_H */
