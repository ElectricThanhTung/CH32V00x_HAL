
#ifndef __CH32V00x_HAL_ADC_H
#define __CH32V00x_HAL_ADC_H

#include "ch32v00x_hal.h"

typedef enum {
    ADC_CHANNEL_0 = 0U,
    ADC_CHANNEL_1 = 1U,
    ADC_CHANNEL_2 = 2U,
    ADC_CHANNEL_3 = 3U,
    ADC_CHANNEL_4 = 4U,
    ADC_CHANNEL_5 = 5U,
    ADC_CHANNEL_6 = 6U,
    ADC_CHANNEL_7 = 7U,
} ADC_ChannelTypeDef;

typedef enum {
    ADC_INJECTED_INDEX_1 = 0U,
    ADC_INJECTED_INDEX_2 = 1U,
    ADC_INJECTED_INDEX_3 = 2U,
    ADC_INJECTED_INDEX_4 = 3U,
} ADC_InjectedIndexTypeDef;

typedef enum {
    ADC_CLK_NONE = 0xFFU,
    ADC_CLK_AHB_DIV2 = 0x00U,
    ADC_CLK_AHB_DIV4 = 0x08U,
    ADC_CLK_AHB_DIV6 = 0x10U,
    ADC_CLK_AHB_DIV8 = 0x18U,
    ADC_CLK_AHB_DIV12 = 0x14U,
    ADC_CLK_AHB_DIV16 = 0x1CU,
    ADC_CLK_AHB_DIV24 = 0x15U,
    ADC_CLK_AHB_DIV32 = 0x1DU,
    ADC_CLK_AHB_DIV48 = 0x16U,
    ADC_CLK_AHB_DIV64 = 0x1EU,
    ADC_CLK_AHB_DIV96 = 0x17U,
    ADC_CLK_AHB_DIV128 = 0x1FU
} ADC_ClkDivTypeDef;

typedef struct {
public:
    __IO uint32_t STATR;
    __IO uint32_t CTLR1;
    __IO uint32_t CTLR2;
    __IO uint32_t SAMPTR1;
    __IO uint32_t SAMPTR2;
    __IO uint32_t IOFR1;
    __IO uint32_t IOFR2;
    __IO uint32_t IOFR3;
    __IO uint32_t IOFR4;
    __IO uint32_t WDHTR;
    __IO uint32_t WDLTR;
    __IO uint32_t RSQR1;
    __IO uint32_t RSQR2;
    __IO uint32_t RSQR3;
    __IO uint32_t ISQR;
    __IO uint32_t IDATAR1;
    __IO uint32_t IDATAR2;
    __IO uint32_t IDATAR3;
    __IO uint32_t IDATAR4;
    __IO uint32_t RDATAR;
    __IO uint32_t DLYR;
} ADC_RegsTypeDef;

class ADC_InjectedTypeDef {
private:
    ADC_RegsTypeDef REGS;
public:
    void SetSequence(ADC_ChannelTypeDef ch1th);
    void SetSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th);
    void SetSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th, ADC_ChannelTypeDef ch3th);
    void SetSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th, ADC_ChannelTypeDef ch3th, ADC_ChannelTypeDef ch4th);
    void SoftwareStart(void);
    HAL_FlagStatusTypeDef GetStatus(void);
    int16_t GetValue(ADC_InjectedIndexTypeDef index);
private:
    ADC_InjectedTypeDef(void);
    ADC_InjectedTypeDef(const ADC_InjectedTypeDef &);
};

class ADC_RegularTypeDef {
private:
    ADC_RegsTypeDef REGS;
public:
    int16_t Convert(ADC_ChannelTypeDef channel);
private:
    ADC_RegularTypeDef(void);
    ADC_RegularTypeDef(ADC_InjectedTypeDef &);
};

class ADC_TypeDef {
public:
    union {
        ADC_RegsTypeDef REGS;
        ADC_InjectedTypeDef Injected;
        ADC_RegularTypeDef Regular;
    };
public:
    void EnableClock(void);
    void DisableClock(void);
    void SetPrescaler(ADC_ClkDivTypeDef div);
    void DeInit(void);
private:
    ADC_TypeDef(void);
    ADC_TypeDef(const ADC_TypeDef &);
};

#define ADC1            (*(ADC_TypeDef *)ADC1_BASE)

#endif /* __CH32V00x_HAL_ADC_H */
