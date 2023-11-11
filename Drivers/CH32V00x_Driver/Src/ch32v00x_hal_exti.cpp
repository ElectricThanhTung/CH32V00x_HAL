
#include "ch32v00x_hal_exti.h"

/**
 * @brief  Returns the mask of the AFIO register for the corresponding pin.
 * @param  line specifies the line which need to be get mask of the CFGLR register.
 *         This parameter can be one of EXTI_LINE_x where x can be (0..9).
 * @retval AFIO mask for the corresponding line.
 */
static uint32_t HAL_EXTI_GetAFIOMask(uint32_t line) {
    uint32_t afioMask = ((line & 0xF0) << 4U) | (line & 0x0F);
    afioMask = ((afioMask & 0x0C0C) << 2U) | (afioMask & 0x0303);
    afioMask = ((afioMask & 0x2222) << 1U) | (afioMask & 0x1111);
    afioMask |= afioMask << 1U;
    return afioMask;
}

/**
 * @brief  Initialize the EXTI according to the specified parameters in the extiInit.
 * @param  port Specifies the port to initialize.
 * @param  line Specifies the line to initialize.
 *         This parameter can be one of EXTI_LINE_x where x can be (0..9).
 * @param  mode Specifies the mode to initialize for EXIT line.
 * @param  trigger Specifies the trigger mode to initialize for EXIT line.
 * @retval None.
 */
void EXTI_TypeDef::Init(EXTI_PortTypeDef port, uint32_t line, EXTI_ModeTypeDef mode, EXTI_TriggerTypeDef trigger) {
    uint32_t afioMask = HAL_EXTI_GetAFIOMask(line);
    uint32_t portMask = ((uint32_t)port << 2U) | (uint32_t)port;
    portMask |= portMask << 4U;
    portMask |= portMask << 8U;

    AFIO.REGS.EXTICR = (AFIO.REGS.EXTICR & ~afioMask) | (port & afioMask);

    if(mode & EXTI_MODE_INTERRUPT)
        REGS.INTENR |= line;
    else
        REGS.INTENR &= ~line;

    if(mode & EXTI_MODE_EVNET)
        REGS.EVENR |= line;
    else
        REGS.EVENR &= ~line;

    if(trigger & EXTI_TRIGGER_RISING)
        REGS.RTENR |= line;
    else
        REGS.RTENR &= ~line;

    if(trigger & EXTI_TRIGGER_FALLING)
        REGS.FTENR |= line;
    else
        REGS.FTENR &= ~line;
}

/**
 * @brief  De-initialize the EXTI registers to their default reset values.
 * @param  line Specifies the line to de-initialize.
 *         This parameter can be one of EXTI_LINE_x where x can be (0..9).
 * @retval None.
 */
void EXTI_TypeDef::DeInit(uint32_t line) {
    AFIO.REGS.EXTICR &= ~HAL_EXTI_GetAFIOMask(line);
    REGS.INTENR &= ~line;
    REGS.EVENR &= ~line;
    REGS.RTENR &= ~line;
    REGS.FTENR &= ~line;
}
