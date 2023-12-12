
#include "ch32v00x_hal_iwdg.h"

#define IWDG_NONE                   0x0000U
#define IWDG_FEED                   0xAAAAU
#define IWDG_WRITE_ACCESS           0x5555U
#define IWDG_START                  0xCCCCU

/**
 * @brief  Set prescaler for IWDG according to the specified parameters in the div.
 * @param  div specifies the prescaler value for IWDG.
 * @retval None.
 */
void IWDG_TypeDef::SetPrescaler(IWDG_DivTypeDef div) {
    REGS.CTLR = IWDG_WRITE_ACCESS;
    REGS.PSCR = div;
    REGS.CTLR = IWDG_NONE;
}

/**
 * @brief  Set reload value for IWDG.
 * @param  value specifies the value to be set for RLDR register.
 * @retval None.
 */
void IWDG_TypeDef::SetReload(uint16_t value) {
    REGS.CTLR = IWDG_WRITE_ACCESS;
    REGS.RLDR = value;
    REGS.CTLR = IWDG_NONE;
}

/**
 * @brief  Feed the dog. Loading of the RLDR register
 *         value into the independent watchdog counter.
 * @retval None.
 */
void IWDG_TypeDef::Reset(void) {
    REGS.CTLR = IWDG_FEED;
    REGS.CTLR = IWDG_NONE;
}

/**
 * @brief  Start the IWDG.
 * @retval None.
 */
void IWDG_TypeDef::Start(void) {
    REGS.CTLR = IWDG_START;
    REGS.CTLR = IWDG_NONE;
}
