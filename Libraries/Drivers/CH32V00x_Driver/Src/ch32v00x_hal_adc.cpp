
#include "ch32v00x_hal_adc.h"

/**
 * @brief  Enable the ADC peripheral clock.
 * @note   This function will use RCC module to enable clock for ADC peripheral.
 * @retval None.
 */
void ADC_TypeDef::EnableClock(void) {
    if(this == &ADC1)
        RCC.REGS.APB2PCENR |= RCC_APB2PCENR_ADC1EN;
}

/**
 * @brief  Disable the ADC peripheral clock.
 * @note   This function will use RCC module to disable clock for ADC peripheral.
 * @retval None.
 */
void ADC_TypeDef::DisableClock(void) {
    if(this == &ADC1)
        RCC.REGS.APB2PCENR &= ~RCC_APB2PCENR_ADC1EN;
}

/**
 * @brief  Disable or enable and set ADC clock source prescaler value.
 * @param  div ADC clock source prescaler value. If div parameter is
 *         ADC_DIV_NONE it mean ADC is disabled.
 * @note   This function will use RCC module to set clock source prescaler
 *         for ADC peripheral.
 * @retval None.
 */
void ADC_TypeDef::SetCLK(ADC_ClkDivTypeDef div) {
    if(this == &ADC1) {
        if(div <= ADC_CLK_AHB_DIV128) {
            RCC.REGS.CFGR0 = (RCC.REGS.CFGR0 & ~RCC_CFGR0_ADCPRE) | (div << RCC_CFGR0_ADCPRE_Pos);
            REGS.CTLR2 |= ADC_CTLR2_ADON;
        }
        else
            REGS.CTLR2 &= ~ADC_CTLR2_ADON;
    }
}

/**
 * @brief  Set ADC channels for injected sequence.
 * @param  ch1th Specifies the first channel of the sequence.
 * @retval None.
 */
void ADC_InjectedTypeDef::SetSequence(ADC_ChannelTypeDef ch1th) {
    REGS.ISQR = (ch1th << ADC_ISQR_JSQ1_Pos) | (0U << ADC_ISQR_JL_Pos);
}

/**
 * @brief  Set ADC channels for injected sequence.
 * @param  ch1th Specifies the first channel of the sequence.
 * @param  ch2th Specifies the seconds channel of the sequence.
 * @retval None.
 */
void ADC_InjectedTypeDef::SetSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th) {
    REGS.ISQR = (ch1th << ADC_ISQR_JSQ1_Pos) | (1U << ADC_ISQR_JL_Pos);
    REGS.ISQR |= (ch2th << ADC_ISQR_JSQ2_Pos);
}

/**
 * @brief  Set ADC channels for injected sequence.
 * @param  ch1th Specifies the first channel of the sequence.
 * @param  ch2th Specifies the seconds channel of the sequence.
 * @param  ch3th Specifies the third channel of the sequence.
 * @retval None.
 */
void ADC_InjectedTypeDef::SetSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th, ADC_ChannelTypeDef ch3th) {
    REGS.ISQR = (ch1th << ADC_ISQR_JSQ1_Pos) | (2U << ADC_ISQR_JL_Pos);
    REGS.ISQR |= (ch2th << ADC_ISQR_JSQ2_Pos);
    REGS.ISQR |= (ch3th << ADC_ISQR_JSQ3_Pos);
}

/**
 * @brief  Set ADC channels for injected sequence.
 * @param  ch1th Specifies the first channel of the sequence.
 * @param  ch2th Specifies the seconds channel of the sequence.
 * @param  ch3th Specifies the third channel of the sequence.
 * @param  ch4th Specifies the fourth channel of the sequence.
 * @retval None.
 */
void ADC_InjectedTypeDef::SetSequence(ADC_ChannelTypeDef ch1th, ADC_ChannelTypeDef ch2th, ADC_ChannelTypeDef ch3th, ADC_ChannelTypeDef ch4th) {
    REGS.ISQR = (ch1th << ADC_ISQR_JSQ1_Pos) | (3U << ADC_ISQR_JL_Pos);
    REGS.ISQR |= (ch2th << ADC_ISQR_JSQ2_Pos);
    REGS.ISQR |= (ch3th << ADC_ISQR_JSQ3_Pos);
    REGS.ISQR |= (ch4th << ADC_ISQR_JSQ4_Pos);
}

/**
 * @brief  Trigger start injected conversion by software.
 * @note   This function will also clear the JEOC bit.
 * @retval None.
 */
void ADC_InjectedTypeDef::SoftwareStart(void) {
    REGS.STATR &= ~ADC_STATR_JEOC;
    REGS.CTLR2 |= ADC_CTLR2_JSWSTART;
}

/**
 * @brief  Return the injected conversion status.
 * @retval HAL flag status.
 */
HAL_FlagStatusTypeDef ADC_InjectedTypeDef::GetStatus(void) {
    return (REGS.STATR & ADC_STATR_JEOC) ? SET : RESET;
}

/**
 * @brief  Get the injected value from IDATARx register.
 * @param  index Specifies index of IDATARx register.
 * @retval IDATARx value.
 */
int16_t ADC_InjectedTypeDef::GetValue(ADC_InjectedIndexTypeDef index) {
    return ((uint32_t *)&REGS.IDATAR1)[index];
}

/**
 * @brief  Start software convert, wait and get conversion results
 *         of ADC channel specified parameters in the channel.
 * @param  channel Specify the channel to be converted.
 * @retval ADC value from RDATAR register.
 */
int16_t ADC_RegularTypeDef::Convert(ADC_ChannelTypeDef channel) {
    if(REGS.CTLR2 & ADC_CTLR2_ADON) {
        REGS.RSQR3 = (channel << ADC_RSQR3_SQ1_Pos);
        REGS.RSQR1 = (0U << ADC_RSQR1_L_Pos);
        REGS.STATR &= ~ADC_STATR_EOC;
        REGS.CTLR2 |= ADC_CTLR2_ADON;
        while(!(REGS.STATR & ADC_STATR_EOC));
        return REGS.RDATAR;
    }
    return -1;
}

/**
 * @brief  De-Initialize the SPI peripheral.
 * @retval None.
 */
void ADC_TypeDef::DeInit(void) {
    if(this == &ADC1) {
        RCC.REGS.APB2PRSTR |= RCC_APB2PRSTR_ADC1RST;
        RCC.REGS.APB2PRSTR &= ~RCC_APB2PRSTR_ADC1RST;
    }
}
