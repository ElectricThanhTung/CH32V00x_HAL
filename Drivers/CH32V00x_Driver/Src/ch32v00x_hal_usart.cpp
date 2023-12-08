
#include "ch32v00x_hal_usart.h"

/**
 * @brief  Enable the USART1 peripheral clock.
 * @note   This function will use RCC module to enable clock for USART1 peripheral.
 * @retval None.
 */
void USART_TypeDef::EnableClock(void) {
    if(this == &USART1)
        RCC.REGS.APB2PCENR |= RCC_APB2PCENR_USART1EN;
}

/**
 * @brief  Disable the USART1 peripheral clock.
 * @note   This function will use RCC module to disable clock for USART1 peripheral.
 * @retval None.
 */
void USART_TypeDef::DisableClock(void) {
    if(this == &USART1)
        RCC.REGS.APB2PCENR &= ~RCC_APB2PCENR_USART1EN;
}

/**
 * @brief  Set mode for USART according to the specified parameters in the mode.
 * @param  mode specifies the mode to be set for USART.
 * @retval None.
 */
void USART_TypeDef::SetMode(USART_ModeTypeDef mode) {
    REGS.CTLR1 = (REGS.CTLR1 & ~(USART_CTLR1_TE | USART_CTLR1_RE)) | mode;
}

/**
 * @brief  Set baudrate for USART according to the specified parameters in the baudRate.
 * @param  baudRate specifies the baudRate used for USART.
 * @note   This function will automatically calculate the best value to assign to the
 *         USARTx_BRR register based on the input baudrate parameter. It will also return
 *         the actual baudrate value based on the currently configured BRR value.
 * @retval Actual baudrate value.
 */
uint32_t USART_TypeDef::SetBaudRate(uint32_t baudRate) {
    uint32_t hclk = RCC.GetHCLKFreq();
    uint32_t brr = (hclk + (baudRate / 2)) / baudRate;
    REGS.BRR = brr;
    return hclk / brr;
}

/**
 * @brief  Set word length 8 bits or 9 bits data for USART according to the specified
 *         parameters in the wordLength.
 * @param  wordLength specifies the word length of 8 bits or 9 bits data for for USART.
 * @retval None.
 */
void USART_TypeDef::SetWordLength(USART_WordLengthTypeDef wordLength) {
    REGS.CTLR1 = (REGS.CTLR1 & ~USART_CTLR1_M) | wordLength;
}

/**
 * @brief  Set parity for USART according to the specified parameters in the parity.
 * @param  parity specifies the parity to be set for USART.
 * @retval None.
 */
void USART_TypeDef::SetParity(USART_ParityTypeDef parity) {
    REGS.CTLR1 = (REGS.CTLR1 & ~(USART_CTLR1_PCE | USART_CTLR1_PS)) | parity;
}

/**
 * @brief  Transmit an amount of 8 bits array data in blocking mode.
 * @param  txData pointer to transmission data buffer.
 * @param  txLength the length of the data array to be transmitted.
 * @param  timeout timeout duration.
 * @note   Transmit mode must be enabled and the word length for USART must
 *         be set to USART_WORD_LENGTH_8. Otherwise, this function cannot
 *         be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef USART_TypeDef::Transmit(uint8_t *txData, uint16_t txLength, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if(!(REGS.CTLR1 & USART_CTLR1_TE) || (REGS.CTLR1 & USART_CTLR1_M))
        return HAL_ERROR;
    while(txLength) {
        if(REGS.STATR & USART_STATR_TXE) {
            REGS.DATAR = *txData;
            txData++;
            txLength--;
        }
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    return HAL_OK;
}

/**
 * @brief  Transmit an amount of 9 bits array data in blocking mode.
 * @param  txData pointer to transmission data buffer.
 * @param  txLength the length of the data array to be transmitted.
 * @param  timeout timeout duration.
 * @note   Transmit mode must be enabled and the word length for USART must
 *         be set to USART_WORD_LENGTH_9. Otherwise, this function cannot
 *         be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef USART_TypeDef::Transmit(uint16_t *txData, uint16_t txLength, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if(!(REGS.CTLR1 & USART_CTLR1_TE) || !(REGS.CTLR1 & USART_CTLR1_M))
        return HAL_ERROR;
    while(txLength) {
        if(REGS.STATR & USART_STATR_TXE) {
            REGS.DATAR = *txData;
            txData++;
            txLength--;
        }
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    return HAL_OK;
}

/**
 * @brief  Transmit data in blocking mode.
 * @param  data data to be transmitted.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef USART_TypeDef::Transmit(uint16_t txData, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if(!(REGS.CTLR1 & USART_CTLR1_TE))
        return HAL_ERROR;
    while(1U) {
        if(REGS.STATR & USART_STATR_TXE) {
            REGS.DATAR = txData;
            return HAL_OK;
        }
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
}

/**
 * @brief  De-Initialize the USART peripheral.
 * @retval None.
 */
void USART_TypeDef::DeInit(void) {
    if(this == &USART1) {
        RCC.REGS.APB2PRSTR |= RCC_APB2PRSTR_USART1RST;
        RCC.REGS.APB2PRSTR &= ~RCC_APB2PRSTR_USART1RST;
    }
}
