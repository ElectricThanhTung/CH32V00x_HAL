
#include "ch32v00x_hal_rcc.h"

static uint32_t SystemCoreClock = HSI_VALUE;

/**
 * @brief  Caculate and update the HCLK frequency to the SystemCoreClock variable (in Hz).
 * @note   Each time HCLK changes, this function must be called to update the right SystemCoreClock
 *         value. Otherwise, any configuration based on SystemCoreClock value will be incorrect.
 * @note   This function will be called automatically whenever HAL_RCC_ClkInit is called.
 * @retval None.
 */
void CoreClockUpdate(void) {
    static const uint8_t AHBPrescTable[16] = {
        1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U
    };
    uint32_t ret = RCC.SysClk.GetFreq();
    uint32_t tmp = AHBPrescTable[(RCC.REGS.CFGR0 & RCC_CFGR0_HPRE) >> 4U];

    if(((RCC.REGS.CFGR0 & RCC_CFGR0_HPRE) >> 4U) < 8U)
        ret /= tmp;
    else
        ret >>= tmp;

    if(SystemCoreClock != ret) {
        SystemCoreClock = ret;
        if(ret > HSI_VALUE)
            FLASH.REGS.ACTLR |= (FLASH.REGS.ACTLR & ~FLASH_ACTLR_LATENCY) | (1U << FLASH_ACTLR_LATENCY_Pos);
        else
            FLASH.REGS.ACTLR &= ~FLASH_ACTLR_LATENCY;
    }
}

/**
 * @brief  Enable the HSI.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_HsiTypeDef::Enable(void) {
    if(GetState() == ENABLE)
        return HAL_OK;
    REGS.CTLR |= RCC_CTLR_HSION;
    while(!(REGS.CTLR & RCC_CTLR_HSIRDY));
    CoreClockUpdate();
    return HAL_OK;
}

/**
 * @brief  Disable the HSI.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_HsiTypeDef::Disable(void) {
    if(GetState() == DISABLE)
        return HAL_OK;
    REGS.CTLR &= ~RCC_CTLR_HSION;
    if(REGS.CTLR & RCC_CTLR_HSION)
        return HAL_ERROR;
    CoreClockUpdate();
    return HAL_OK;
}

/**
 * @brief  Get the current HSI state configuration according to the
 *         internal RCC configuration registers.
 * @retval Current HSI state.
 */
HAL_StateTypeDef RCC_HsiTypeDef::GetState(void) {
    return (REGS.CTLR & RCC_CTLR_HSIRDY) ? ENABLE : DISABLE;
}

/**
 * @brief  Returns the HSI frequency.
 * @retval HSI frequency (in Hz).
 */
uint32_t RCC_HsiTypeDef::GetFreq(void) {
    return (GetState() == ENABLE) ? HSI_VALUE : 0U;
}

/**
 * @brief  Enable the HSE.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_HseTypeDef::Enable(void) {
    uint32_t timeout = 0xFF;
    if(GetState() == ENABLE)
        return HAL_OK;
    AFIO.REGS.PCFR1 |= AFIO_PCFR1_PA12_RM;
    REGS.CTLR |= RCC_CTLR_HSEON;
    while((!(REGS.CTLR & RCC_CTLR_HSERDY)) && (timeout--));
    if(REGS.CTLR & RCC_CTLR_HSERDY) {
        CoreClockUpdate();
        return HAL_OK;
    }
    else {
        AFIO.REGS.PCFR1 &= ~AFIO_PCFR1_PA12_RM;
        return HAL_ERROR;
    }
}

/**
 * @brief  Disable the HSE.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_HseTypeDef::Disable(void) {
    if(GetState() == DISABLE)
        return HAL_OK;
    REGS.CTLR &= ~RCC_CTLR_HSEON;
    AFIO.REGS.PCFR1 &= ~AFIO_PCFR1_PA12_RM;
    CoreClockUpdate();
    return HAL_OK;
}

/**
 * @brief  Get the current HSE state configuration according to the
 *         internal RCC configuration registers.
 * @retval Current HSE state.
 */
HAL_StateTypeDef RCC_HseTypeDef::GetState(void) {
    return (REGS.CTLR & RCC_CTLR_HSERDY) ? ENABLE : DISABLE;
}

/**
 * @brief  Returns the HSE frequency.
 * @retval HSE frequency (in Hz).
 */
uint32_t RCC_HseTypeDef::GetFreq(void) {
    return (GetState() == ENABLE) ? HSE_VALUE : 0U;
}

/**
 * @brief  Enable or disable for PLL.
 * @param  state specifies the new value that needs to be updated for the PLL.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_PllTypeDef::SetState(HAL_StateTypeDef state) {
    uint32_t timeout = 0xFF;
    if(state == DISABLE) {
        REGS.CTLR &= ~RCC_CTLR_PLLON;
        return HAL_OK;
    }
    REGS.CTLR |= RCC_CTLR_PLLON;
    while((!(REGS.CTLR & RCC_CTLR_PLLRDY)) && (timeout--));
    return (REGS.CTLR & RCC_CTLR_PLLRDY) ? HAL_OK : HAL_ERROR;
}

/**
 * @brief  Set input clock source for PLL.
 * @param  source specifies clock source value that needs to be set for the PLL.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_PllTypeDef::SetSource(RCC_PllSrcTypeDef source) {
    if(GetSource() == source)
        return HAL_OK;
    if(source < RCC_PLLSRC_DISABLE) {
        REGS.CFGR0 = (REGS.CFGR0 & ~RCC_CFGR0_PLLSRC) | (source << RCC_CFGR0_PLLSRC_Pos);
        if(SetState(ENABLE) != HAL_OK)
            return HAL_ERROR;
    }
    else if(SetState(DISABLE) != HAL_OK)
        return HAL_ERROR;
    CoreClockUpdate();
    return HAL_OK;
}

/**
 * @brief  Get the current PLL clock source configuration according to the
 *         internal RCC configuration registers.
 * @retval RCC_PllSrcTypeDef.
 */
RCC_PllSrcTypeDef RCC_PllTypeDef::GetSource(void) {
    if(!(REGS.CTLR & RCC_CTLR_PLLRDY))
        return RCC_PLLSRC_DISABLE;
    return (RCC_PllSrcTypeDef)((REGS.CFGR0 & RCC_CFGR0_PLLSRC) >> RCC_CFGR0_PLLSRC_Pos);
}

/**
 * @brief  Returns the PLL output frequency.
 * @retval PLL output frequency (in Hz).
 */
uint32_t RCC_PllTypeDef::GetFreq(void) {
    switch(GetSource()) {
        case RCC_PLLSRC_HSI:
            return HSI_VALUE * 2U;
        case RCC_PLLSRC_HSE:
            return HSE_VALUE * 2U;
        default:
            return 0U;
    }
    return HSE_VALUE;
}

/**
 * @brief  Set input clock source for system clock.
 * @param  source specifies clock source value that needs to be set for the system clock.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_SysClkTypeDef::SetSource(RCC_SysClkSrcTypeDef source) {
    uint32_t timeout = 0xFF;
    REGS.CFGR0 = (REGS.CFGR0 & ~RCC_CFGR0_SW) | (source << RCC_CFGR0_SW_Pos);
    while(((REGS.CFGR0 & RCC_CFGR0_SWS) != (uint32_t)(source << RCC_CFGR0_SWS_Pos)) && (timeout--));
    CoreClockUpdate();
    return ((REGS.CFGR0 & RCC_CFGR0_SWS) == (uint32_t)(source << RCC_CFGR0_SWS_Pos)) ? HAL_OK : HAL_ERROR;
}

/**
 * @brief  Get the current system clock source configuration according to the
 *         internal RCC configuration registers.
 * @retval RCC_SysClkSrcTypeDef.
 */
RCC_SysClkSrcTypeDef RCC_SysClkTypeDef::GetSource(void) {
    return (RCC_SysClkSrcTypeDef)((REGS.CFGR0 & RCC_CFGR0_SWS) >> RCC_CFGR0_SWS_Pos);
}

/**
 * @brief  Return system clock frequency.
 * @note   Each time system clock changes, this function must be called to update the right
 *         system clock value. Otherwise, any configuration based on this function will be incorrect.
 * @retval System clock frequency (in Hz).
 */
uint32_t RCC_SysClkTypeDef::GetFreq(void) {
    switch(GetSource()) {
        case RCC_SYSCLKSRC_HSI:
            return HSI_VALUE;
        case RCC_SYSCLKSRC_HSE:
            return HSE_VALUE;
        case RCC_SYSCLKSRC_PLL:
            return ((REGS.CFGR0 & RCC_CFGR0_PLLSRC) == 0x00) ? (HSI_VALUE * 2U) : (HSE_VALUE * 2U);
        default:
            return HSI_VALUE;
    }
}

/**
 * @brief  Set input clock source for PLL.
 * @param  div AHB clock source prescaler value.
 * @retval HAL status.
 */
void RCC_HclkTypeDef::SetDiv(RCC_SysClkDivTypeDef div) {
    REGS.CFGR0 = (REGS.CFGR0 & ~RCC_CFGR0_HPRE) | (div << RCC_CFGR0_HPRE_Pos);
    CoreClockUpdate();
}

/**
 * @brief  Get the HCLK prescaler configuration according to the
 *         internal RCC configuration registers.
 * @retval RCC_SysClkSrcTypeDef.
 */
RCC_SysClkDivTypeDef RCC_HclkTypeDef::GetDiv(void) {
    return (RCC_SysClkDivTypeDef)((REGS.CFGR0 & RCC_CFGR0_HPRE) >> RCC_CFGR0_HPRE_Pos);
}

/**
 * @brief  Returns the HCLK frequency.
 * @retval HCLK frequency (in Hz).
 */
uint32_t RCC_HclkTypeDef::GetFreq(void) {
    return SystemCoreClock;
}

/**
 * @brief  Set output clock source according to the specified parameters in the value.
 * @param  value specifies value for output clock source.
 * @retval None.
 */
void RCC_OutClkTypeDef::SetSource(RCC_OutputSourceTypeDef source) {
    REGS.CFGR0 = (REGS.CFGR0 & ~RCC_CFGR0_MCO) | (source << RCC_CFGR0_MCO_Pos);
}

/**
 * @brief  Get the current output clock source configuration according to the
 *         internal RCC configuration registers.
 * @retval Output clock source configuration.
 */
RCC_OutputSourceTypeDef RCC_OutClkTypeDef::GetSource(void) {
    return (RCC_OutputSourceTypeDef)((REGS.CFGR0 & ~RCC_CFGR0_MCO) >> RCC_CFGR0_MCO_Pos);
}

/**
 * @brief  Returns the clock frequency at the output clock pin.
 * @note   Each time output clock changes, this function must be called to update the
 *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
 * @retval Output clock frequency (in Hz).
 */
uint32_t RCC_OutClkTypeDef::GetFreq(void) {
    switch(GetSource()) {
        case RCC_OUTPUTCLK_SYSCLK:
            return RCC.SysClk.GetFreq();
        case RCC_OUTPUTCLK_HSI:
            return RCC.HSI.GetFreq();
        case RCC_OUTPUTCLK_HSE:
            return RCC.HSE.GetFreq();
        case RCC_OUTPUTCLK_PLL:
            return RCC.PLL.GetFreq();
        default:
            return 0U;
    }
}

/**
 * @brief  Resets the RCC clock configuration to the default reset state.
 * @retval None.
 */
void RCC_TypeDef::DeInit(void) {
    REGS.CTLR |= (uint32_t)0x00000001;
    REGS.CFGR0 &= (uint32_t)0xFCFF0000;
    REGS.CTLR &= (uint32_t)0xFEF6FFFF;
    REGS.CTLR &= (uint32_t)0xFFFBFFFF;
    REGS.CFGR0 &= (uint32_t)0xFFFEFFFF;
    REGS.INTR = 0x009F0000;
    SystemCoreClock = HSI_VALUE;
}