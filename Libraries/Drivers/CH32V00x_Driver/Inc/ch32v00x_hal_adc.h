
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
    ADC_AHBCLK_DIV2 = 0x00,
    ADC_AHBCLK_DIV4 = 0x08,
    ADC_AHBCLK_DIV6 = 0x10,
    ADC_AHBCLK_DIV8 = 0x18,
    ADC_AHBCLK_DIV12 = 0x14,
    ADC_AHBCLK_DIV16 = 0x1C,
    ADC_AHBCLK_DIV24 = 0x15,
    ADC_AHBCLK_DIV32 = 0x1D,
    ADC_AHBCLK_DIV48 = 0x16,
    ADC_AHBCLK_DIV64 = 0x1E,
    ADC_AHBCLK_DIV96 = 0x17,
    ADC_AHBCLK_DIV128 = 0x1F
} ADC_ClkDivTypeDef;

class ADC_TypeDef {
public:
    struct {
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
    } REGS;
public:
    void EnableClock(void);
    void DisableClock(void);
    void Enable(void);
    void Disable(void);
    void SetCLK(ADC_ClkDivTypeDef div = ADC_AHBCLK_DIV2);
    void SetInjectedSequence(ADC_ChannelTypeDef ch1th);
    void SetInjectedSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th);
    void SetInjectedSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th, ADC_ChannelTypeDef ch3th);
    void SetInjectedSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th, ADC_ChannelTypeDef ch3th, ADC_ChannelTypeDef ch4th);
    void SoftwareStartInjected(void);
    HAL_FlagStatusTypeDef GetInjectedStatus(void);
    int16_t GetInjectedValue(ADC_InjectedIndexTypeDef index);
    int16_t RegularConvert(ADC_ChannelTypeDef channel);
    void DeInit(void);
private:
    ADC_TypeDef(void);
    ADC_TypeDef(ADC_TypeDef &);
};

#define ADC1            (*(ADC_TypeDef *)ADC1_BASE)

#endif /* __CH32V00x_HAL_ADC_H */
