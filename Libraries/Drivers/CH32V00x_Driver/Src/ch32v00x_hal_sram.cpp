
#include "ch32v00x_hal_sram.h"

/**
 * @brief  Enable the SRAM clock in sleep mode.
 * @note   This function will use RCC module to enable clock in sleep mode SRAM.
 * @retval None.
 */
void SRAM_TypeDef::EnableClockInSleepMode(void) {
    if(this == &SRAM)
        RCC.REGS.AHBPCENR |= RCC_AHBPCENR_SRAMEN;
}

/**
 * @brief  Disable the SRAM clock in sleep mode.
 * @note   This function will use RCC module to disable clock in sleep mode SRAM.
 * @retval None.
 */
void SRAM_TypeDef::DisableClockInSleepMode(void) {
    if(this == &SRAM)
        RCC.REGS.AHBPCENR &= ~RCC_AHBPCENR_SRAMEN;
}
