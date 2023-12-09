
#include "ch32v00x_hal_pwr.h"

/**
 * @brief  Enable the PWR peripheral clock.
 * @note   This function will use PWR module to enable clock for PWR peripheral.
 * @retval None.
 */
void PWR_TypeDef::EnableClock(void) {
    if(this == &PWR)
        RCC.REGS.APB1PCENR |= RCC_APB1PCENR_PWREN;
}

/**
 * @brief  Disable the PWR peripheral clock.
 * @note   This function will use RCC module to disable clock for PWR peripheral.
 * @retval None.
 */
void PWR_TypeDef::DisableClock(void) {
    if(this == &PWR)
        RCC.REGS.APB1PCENR &= ~RCC_APB1PCENR_PWREN;
}

/**
 * @brief  Set power supply voltage monitoring function level.
 * @param  level specifies the level for PVD or disable the PVD.
 * @note   If level parameter is PWR_PVD_LEVEL_NONE it mean PVD is disabled.
 * @retval None.
 */
void PWR_TypeDef::SetPVD(PWR_PvdLevelTypeDef level) {
    if(level <= PWR_PVD_LEVEL_4V4) {
        REGS.CTLR = (REGS.CTLR & ~PWR_CTLR_PLS) | (level << PWR_CTLR_PLS_Pos);
        REGS.CTLR |= PWR_CTLR_PVDE;
    }
    else
        REGS.CTLR &= ~PWR_CTLR_PVDE;
}

/**
 * @brief  Setup parameters for auto-wakeup.
 * @param  div specifies prescaler value for AWU.
 * @param  windowValue specifies window value value for AWU. This parameter
 *         is a 6-bit value. It is used to compare with the recursive counter
 *         value and generate a wake-up signal when the counter value is
 *         equal to the window value.
 * @note   If div parameter is PWR_AWU_DIV_NONE it mean AWU is disabled
 *         and windowValue parameter will not be used.
 * @retval None.
 */
void PWR_TypeDef::SetAWU(PWR_AwuDivTypeDef div, uint8_t windowValue) {
    if(div <= PWR_AWU_DIV_61440) {
        REGS.AWUPSC = (REGS.AWUPSC & ~PWR_AWUPSC_AWUPSC) | (div << PWR_AWUPSC_AWUPSC_Pos);
        REGS.AWUWR = windowValue;
        REGS.AWUCSR |= PWR_AWUCSR_AWUEN;
    }
    else
        REGS.AWUCSR &= PWR_AWUCSR_AWUEN;
}

/**
 * @brief  Enter standby mode with mode specified by mode parameter.
 * @param  mode specifies the standby mode.
 * @retval None.
 */
void PWR_TypeDef::EnterStandbyMode(PWR_StanbyModeTypeDef mode) {
    REGS.CTLR &= ~PWR_CTLR_PDDS;
    REGS.CTLR |= PWR_CTLR_PDDS;

    NVIC->SCTLR |= PFIC_SCTLR_SLEEPDEEP;

    if(mode == PWR_STANDBY_ENTRY_WFI)
        __WFI();
    else
        __WFE();

    NVIC->SCTLR &= ~PFIC_SCTLR_SLEEPDEEP;
}

/**
 * @brief  Return the PVD0 flag from CSR register.
 * @param  mode specifies the standby mode.
 * @retval None.
 */
HAL_FlagStatusTypeDef PWR_TypeDef::GetPVD0(void) {
    return (REGS.CSR & PWR_CSR_PVD0) ? SET : RESET;
}

/**
 * @brief  De-Initialize the PWR peripheral.
 * @retval None.
 */
void PWR_TypeDef::DeInit(void) {
    if(this == &PWR) {
        RCC.REGS.APB1PRSTR |= RCC_APB1PRSTR_PWRRST;
        RCC.REGS.APB1PRSTR &= ~RCC_APB1PRSTR_PWRRST;
    }
}
