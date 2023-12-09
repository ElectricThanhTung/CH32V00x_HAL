
#include "ch32v00x_hal_rcc.h"

static uint32_t SystemCoreClock = HSI_VALUE;

/**
 * @brief  Caculate and update the HCLK frequency to the SystemCoreClock variable (in Hz).
 * @note   Each time HCLK changes, this function must be called to update the right SystemCoreClock
 *         value. Otherwise, any configuration based on SystemCoreClock value will be incorrect.
 * @note   This function will be called automatically whenever HAL_RCC_ClkInit is called.
 * @retval None.
 */
void RCC_TypeDef::CoreClockUpdate(void) {
    static const uint8_t AHBPrescTable[16] = {
        1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U
    };
    uint32_t ret = GetSysClockFreq();
    uint32_t tmp = AHBPrescTable[(REGS.CFGR0 & RCC_CFGR0_HPRE) >> 4U];

    if(((REGS.CFGR0 & RCC_CFGR0_HPRE) >> 4U) < 8U)
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
 * @brief  Enable or disable for HSI.
 * @param  state specifies the new value that needs to be updated for the HSI.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_TypeDef::SetHSIState(HAL_StateTypeDef state) {
    if(GetHSIState() == state)
        return HAL_OK;
    if(state == DISABLE) {
        REGS.CTLR &= ~RCC_CTLR_HSION;
        if(REGS.CTLR & RCC_CTLR_HSION)
            return HAL_ERROR;
        CoreClockUpdate();
        return HAL_OK;
    }
    REGS.CTLR |= RCC_CTLR_HSION;
    while(!(REGS.CTLR & RCC_CTLR_HSIRDY));
    CoreClockUpdate();
    return HAL_OK;
}

/**
 * @brief  Enable or disable for HSE.
 * @param  state specifies the new value that needs to be updated for the HSE.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_TypeDef::SetHSEState(HAL_StateTypeDef state) {
    uint32_t timeout = 0xFF;
    if(GetHSEState() == state)
        return HAL_OK;
    if(state == DISABLE) {
        REGS.CTLR &= ~RCC_CTLR_HSEON;
        AFIO.REGS.PCFR1 &= ~AFIO_PCFR1_PA12_RM;
        CoreClockUpdate();
        return HAL_OK;
    }
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
 * @brief  Enable or disable for PLL.
 * @param  state specifies the new value that needs to be updated for the PLL.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_TypeDef::SetPLLState(HAL_StateTypeDef state) {
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
HAL_StatusTypeDef RCC_TypeDef::SetPLLSource(RCC_PllSrcTypeDef source) {
    if(GetPLLSource() == source)
        return HAL_OK;
    if(source < RCC_PLLSRC_DISABLE) {
        REGS.CFGR0 = (REGS.CFGR0 & ~RCC_CFGR0_PLLSRC) | (source << RCC_CFGR0_PLLSRC_Pos);
        if(SetPLLState(ENABLE) != HAL_OK)
            return HAL_ERROR;
    }
    else if(SetPLLState(DISABLE) != HAL_OK)
        return HAL_ERROR;
    CoreClockUpdate();
    return HAL_OK;
}

/**
 * @brief  Set input clock source for PLL.
 * @param  source specifies clock source value that needs to be set for the system clock.
 * @param  div AHB clock source prescaler value.
 * @retval HAL status.
 */
HAL_StatusTypeDef RCC_TypeDef::SetSysClock(RCC_SysClkSrcTypeDef source, RCC_SysClkDivTypeDef div) {
    uint32_t timeout = 0xFF;
    REGS.CFGR0 = (REGS.CFGR0 & (RCC_CFGR0_SW | RCC_CFGR0_HPRE)) | (source << RCC_CFGR0_SW_Pos) | (div << RCC_CFGR0_HPRE_Pos);
    while(((REGS.CFGR0 & RCC_CFGR0_SWS) != (uint32_t)(source << RCC_CFGR0_SWS_Pos)) && (timeout--));
    CoreClockUpdate();
    return ((REGS.CFGR0 & RCC_CFGR0_SWS) == (uint32_t)(source << RCC_CFGR0_SWS_Pos)) ? HAL_OK : HAL_ERROR;
}

/**
 * @brief  Set output clock source according to the specified parameters in the value.
 * @param  value specifies value for output clock source.
 * @retval None.
 */
void RCC_TypeDef::SetOutputClockSource(RCC_OutputClkTypeDef source) {
    REGS.CFGR0 = (REGS.CFGR0 & ~RCC_CFGR0_MCO) | (source << RCC_CFGR0_MCO_Pos);
}

/**
 * @brief  Get the current HSI state configuration according to the
 *         internal RCC configuration registers.
 * @retval Current HSI state.
 */
HAL_StateTypeDef RCC_TypeDef::GetHSIState(void) {
    return (REGS.CTLR & RCC_CTLR_HSIRDY) ? ENABLE : DISABLE;
}

/**
 * @brief  Get the current HSE state configuration according to the
 *         internal RCC configuration registers.
 * @retval Current HSE state.
 */
HAL_StateTypeDef RCC_TypeDef::GetHSEState(void) {
    return (REGS.CTLR & RCC_CTLR_HSERDY) ? ENABLE : DISABLE;
}

/**
 * @brief  Get the current PLL clock source configuration according to the
 *         internal RCC configuration registers.
 * @retval RCC_PllSrcTypeDef.
 */
RCC_PllSrcTypeDef RCC_TypeDef::GetPLLSource(void) {
    if(!(REGS.CTLR & RCC_CTLR_PLLRDY))
        return RCC_PLLSRC_DISABLE;
    return (RCC_PllSrcTypeDef)((REGS.CFGR0 & RCC_CFGR0_PLLSRC) >> RCC_CFGR0_PLLSRC_Pos);
}

/**
 * @brief  Get the current output clock source configuration according to the
 *         internal RCC configuration registers.
 * @retval Output clock source configuration.
 */
RCC_OutputClkTypeDef RCC_TypeDef::GetOutputClockSource(void) {
    return (RCC_OutputClkTypeDef)((REGS.CFGR0 & ~RCC_CFGR0_MCO) >> RCC_CFGR0_MCO_Pos);
}

/**
 * @brief  Return SYSTEM clock frequency.
 * @note   Each time SYSTEM clock changes, this function must be called to update the right
 *         SYSTEM clock value. Otherwise, any configuration based on this function will be incorrect.
 * @retval SYSTEM clock frequency (in Hz).
 */
uint32_t RCC_TypeDef::GetSysClockFreq(void) {
    switch(REGS.CFGR0 & RCC_CFGR0_SWS) {
        case (RCC_SYSCLKSRC_HSI << RCC_CFGR0_SWS_Pos):
            return HSI_VALUE;
        case (RCC_SYSCLKSRC_HSE << RCC_CFGR0_SWS_Pos):
            return HSE_VALUE;
        case (RCC_SYSCLKSRC_PLL << RCC_CFGR0_SWS_Pos):
            return ((REGS.CFGR0 & RCC_CFGR0_PLLSRC) == 0x00) ? (HSI_VALUE * 2U) : (HSE_VALUE * 2U);
        default:
            return HSI_VALUE;
    }
}

/**
 * @brief  Returns the HCLK frequency.
 * @note   Each time HCLK changes, this function must be called to update the
 *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
 * @retval HCLK frequency (in Hz).
 */
uint32_t RCC_TypeDef::GetHCLKFreq(void) {
    return SystemCoreClock;
}

/**
 * @brief  Returns the clock frequency at the output clock pin.
 * @note   Each time output clock changes, this function must be called to update the
 *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
 * @retval Output clock frequency (in Hz).
 */
uint32_t RCC_TypeDef::GetOutputClockFreq(void) {
    switch(GetOutputClockSource()) {
        case RCC_OUTPUTCLK_SYSCLK:
            return GetSysClockFreq();
        case RCC_OUTPUTCLK_HSI:
            return (GetHSIState() == ENABLE) ? HSI_VALUE : 0U;
        case RCC_OUTPUTCLK_HSE:
            return (GetHSEState() == ENABLE) ? HSE_VALUE : 0U;
        case RCC_OUTPUTCLK_PLL: {
            switch(GetPLLSource()) {
                case RCC_PLLSRC_HSI:
                    return (GetHSIState() == ENABLE) ? (HSI_VALUE * 2U) : 0U;
                case RCC_PLLSRC_HSE:
                    return (GetHSEState() == ENABLE) ? (HSI_VALUE * 2U) : 0U;
                default:
                    return 0U;
            }
        }
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