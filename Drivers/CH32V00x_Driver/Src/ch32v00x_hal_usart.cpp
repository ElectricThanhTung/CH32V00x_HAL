
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

void USART_TypeDef::SetMode(USART_ModeTypeDef mode) {
    REGS.CTLR1 = (REGS.CTLR1 & ~(USART_CTLR1_TE | USART_CTLR1_RE)) | mode;
}

uint32_t USART_TypeDef::SetBaudRate(uint32_t baudRate) {
    uint32_t hclk = RCC.GetHCLKFreq();
    uint32_t brr = (hclk + (baudRate / 2)) / baudRate;
    REGS.BRR = brr;
    return hclk / brr;
}

void USART_TypeDef::SetWordLength(USART_WordLengthTypeDef wordLength) {
    REGS.CTLR1 = (REGS.CTLR1 & ~USART_CTLR1_M) | wordLength;
}

void USART_TypeDef::SetParity(USART_ParityTypeDef parity) {
    REGS.CTLR1 = (REGS.CTLR1 & ~(USART_CTLR1_PCE | USART_CTLR1_PS)) | parity;
}

HAL_StatusTypeDef USART_TypeDef::Transmit(uint8_t *txData, uint16_t txLength, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if(!(REGS.CTLR1 & USART_CTLR1_TE))
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

HAL_StatusTypeDef USART_TypeDef::Transmit(uint16_t *txData, uint16_t txLength, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if(!(REGS.CTLR1 & USART_CTLR1_TE))
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
