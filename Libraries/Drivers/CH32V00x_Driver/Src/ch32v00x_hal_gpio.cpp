
#include "ch32v00x_hal_gpio.h"

/**
 * @brief  Returns the mask of the CFGLR register for the corresponding pin.
 * @param  pin specifies the pin which need to be get mask of the CFGLR register.
 *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @retval CFGLR mask for the corresponding pin.
 */
static uint32_t HAL_GPIO_GetCfgMask(uint32_t pin) {
    static const uint16_t gpioCfgMask[] = {
        0x0000, 0x000F, 0x00F0, 0x00FF, 0x0F00, 0x0F0F, 0x0FF0, 0x0FFF,
        0xF000, 0xF00F, 0xF0F0, 0xF0FF, 0xFF00, 0xFF0F, 0xFFF0, 0xFFFF
    };
    uint32_t mask = gpioCfgMask[pin & 0x0F];
    mask |= gpioCfgMask[(pin >> 4U) & 0x0F];
    return mask;
}

/**
 * @brief  Enable the GPIO peripheral clock.
 * @note   This function will use RCC module to enable clock for GPIO peripheral.
 * @retval None.
 */
void GPIO_TypeDef::EnableClock(void) {
    if(this == &GPIOA)
        RCC.REGS.APB2PCENR |= RCC_APB2PCENR_IOPAEN;
    else if(this == &GPIOC)
        RCC.REGS.APB2PCENR |= RCC_APB2PCENR_IOPCEN;
    else if(this == &GPIOD)
        RCC.REGS.APB2PCENR |= RCC_APB2PCENR_IOPDEN;
}

/**
 * @brief  Disable the GPIO peripheral clock.
 * @note   This function will use RCC module to disable clock for GPIO peripheral.
 * @retval None.
 */
void GPIO_TypeDef::DisableClock(void) {
    if(this == &GPIOA)
        RCC.REGS.APB2PCENR &= ~RCC_APB2PCENR_IOPAEN;
    else if(this == &GPIOC)
        RCC.REGS.APB2PCENR &= ~RCC_APB2PCENR_IOPCEN;
    else if(this == &GPIOD)
        RCC.REGS.APB2PCENR &= ~RCC_APB2PCENR_IOPDEN;
}

/**
 * @brief  Initialize the GPIO peripheral according to the specified parameters in the mode and speed.
 * @param  pin specifies the port bit to be written.
 *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @param  mode specifies the mode for the GPIO PIN.
 * @param  speed specifies the speed for the GPIO PIN.
 * @retval None.
 */
void GPIO_TypeDef::SetMode(uint32_t pin, GPIO_ModeTypeDef mode, GPIO_SpeedTypeDef speed) {
    uint32_t pinMode = mode & 0x0F;
    if(mode & 0x10)
        pinMode |= speed + 1U;
    pinMode |= pinMode << 4U;
    pinMode |= pinMode << 8U;

    if(mode == GPIO_MODE_INPUT_PD)
        REGS.BCR = pin;
    else if(mode == GPIO_MODE_INPUT_PU)
        REGS.BSHR = pin;

    if(pin & 0xFF) {
        uint32_t mask = HAL_GPIO_GetCfgMask(pin);
        REGS.CFGLR = (REGS.CFGLR & ~mask) | (pinMode & mask);
    }
    else if(pin & 0xFF00) {
        uint32_t mask = HAL_GPIO_GetCfgMask(pin >> 8U);
        REGS.CFGHR = (REGS.CFGHR & ~mask) | (pinMode & mask);
    }
}

/**
 * @brief  Read the specified input port pin.
 * @param  pin specifies the port bit to read.
 *         This parameter can be GPIO_PIN_x where x can be (0..15).
 * @retval The input port pin value.
 */
GPIO_StateTypeDef GPIO_TypeDef::ReadPin(uint32_t pin) {
    return ((REGS.INDR & pin) != 0U) ? GPIO_STATE_SET : GPIO_STATE_RESET;
}

/**
 * @brief  Set or clear the selected data port bit.
 * @note   This function uses GPIOx_BSHR and GPIOx_BCR registers to allow atomic read/modify
 *         accesses. In this way, there is no risk of an IRQ occurring between
 *         the read and the modify access.
 * @param  pin specifies the port bit to be written.
 *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @param  state specifies the value to be written to the selected bit.
 *         This parameter can be one of the GPIO_StateTypeDef enum values:
 * @retval None.
 */
void GPIO_TypeDef::WritePin(uint32_t pin, GPIO_StateTypeDef state) {
    if(state != GPIO_STATE_RESET)
        REGS.BSHR = pin;
    else
        REGS.BCR = pin;
}

/**
 * @brief  Set the selected data port bit.
 * @note   This function uses GPIOx_BSHR register to allow atomic read/modify
 *         accesses. In this way, there is no risk of an IRQ occurring between
 *         the read and the modify access.
 * @param  pin specifies the port bit to be written.
 *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @retval None.
 */
void GPIO_TypeDef::SetPin(uint32_t pin) {
    REGS.BSHR = pin;
}

/**
 * @brief  Clear the selected data port bit.
 * @note   This function uses GPIOx_BCR register to allow atomic read/modify
 *         accesses. In this way, there is no risk of an IRQ occurring between
 *         the read and the modify access.
 * @param  pin specifies the port bit to be written.
 *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @retval None.
 */
void GPIO_TypeDef::ResetPin(uint32_t pin) {
    REGS.BCR = pin;
}

/**
 * @brief  Toggle the specified GPIO pin.
 * @param  pin specifies the pin to be toggled.
 * @retval None.
 */
void GPIO_TypeDef::TogglePin(uint32_t pin) {
    uint32_t odr = REGS.OUTDR;
    REGS.BSHR = ((odr & pin) << 16U) | (~odr & pin);
}

/**
 * @brief  Locks GPIO Pins configuration registers.
 * @note   The locked registers are GPIOx_CFGLR and/or GPIOx_CFGHR.
 * @note   The configuration of the locked GPIO pins can no longer be modified
 *         until the next reset.
 * @param  pin specifies the port bits to be locked.
 *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 * @retval None.
 */
void GPIO_TypeDef::LockPin(uint32_t pin) {
    uint32_t tmp = 0x00010000;

    tmp |= pin;
    REGS.LCKR = tmp;
    REGS.LCKR = pin;
    REGS.LCKR = tmp;
    tmp = REGS.LCKR;
    tmp = REGS.LCKR;
}

/**
 * @brief  De-initialize the GPIO peripheral registers to their default reset values.
 * @param  pin specifies the port bit to be written.
 *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * @retval None.
 */
void GPIO_TypeDef::DeInit(uint32_t pin) {
    if(pin & 0xFF) {
        uint32_t mask = HAL_GPIO_GetCfgMask(pin);
        REGS.CFGLR = (REGS.CFGLR & ~mask) | (0x44444444 & mask);
    }
    else if(pin & 0xFF00) {
        uint32_t mask = HAL_GPIO_GetCfgMask(pin >> 8U);
        REGS.CFGHR = (REGS.CFGHR & ~mask) | (0x44444444 & mask);
    }
}
