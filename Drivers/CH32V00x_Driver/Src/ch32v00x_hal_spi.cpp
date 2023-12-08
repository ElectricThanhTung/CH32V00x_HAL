
#include "ch32v00x_hal_spi.h"

/**
 * @brief  Enable the SPI peripheral clock.
 * @note   This function will use RCC module to enable clock for SPI peripheral.
 * @retval None.
 */
void SPI_TypeDef::EnableClock(void) {
    if(this == &SPI1)
        RCC.REGS.APB2PCENR |= RCC_APB2PCENR_SPI1EN;
}

/**
 * @brief  Disable the SPI peripheral clock.
 * @note   This function will use RCC module to disable clock for SPI peripheral.
 * @retval None.
 */
void SPI_TypeDef::DisableClock(void) {
    if(this == &SPI1)
        RCC.REGS.APB2PCENR &= ~RCC_APB2PCENR_SPI1EN;
}

/**
 * @brief  Set mode for SPI according to the specified parameters in the mode.
 * @param  mode specifies the mode to be set for SPI.
 * @retval None.
 */
void SPI_TypeDef::SetMode(SPI_ModeTypeDef mode) {
    REGS.CTLR1 &= ~(SPI_CTLR1_BIDIMODE | SPI_CTLR1_BIDIOE | SPI_CTLR1_RXONLY | SPI_CTLR1_MSTR);
    REGS.CTLR1 |= mode & (SPI_CTLR1_BIDIMODE | SPI_CTLR1_BIDIOE | SPI_CTLR1_RXONLY | SPI_CTLR1_MSTR);
}

/**
 * @brief  Set data size when transmitting and receiving for SPI according to the
 *         specified parameters in the dataSize.
 * @param  dataSize specifies the data size to be set for SPI when transmitting and
 *         receiving.
 * @retval None.
 */
void SPI_TypeDef::SetDataSize(SPI_DataSizeTypeDef dataSize) {
    REGS.CTLR1 = (REGS.CTLR1 & ~SPI_CTLR1_DFF) | ((dataSize << SPI_CTLR1_DFF_Pos) & SPI_CTLR1_DFF);
}

/**
 * @brief  Set parameters for SPI Clock signal.
 * @param  polarity specifies the polarity (CLK idle state) to be set for SPI.
 * @param  phase specifies the phase (sampling point) to be set for SPI.
 * @param  baudRate specifies the baudRate to be set for SPI.
 * @retval None.
 */
void SPI_TypeDef::SetCLK(SPI_PolarityTypeDef polarity, SPI_PhaseTypeDef phase, SPI_BaudRateTypeDef baudRate) {
    uint32_t temp = REGS.CTLR1 & ~(SPI_CTLR1_BR | SPI_CTLR1_CPOL | SPI_CTLR1_CPHA);
    temp |= ((polarity << SPI_CTLR1_CPOL_Pos) & SPI_CTLR1_CPOL);
    temp |= (((polarity ^ phase) << SPI_CTLR1_CPHA_Pos) & SPI_CTLR1_CPHA);
    temp |= (baudRate << SPI_CTLR1_BR_Pos) & SPI_CTLR1_BR;
    REGS.CTLR1 = temp;
}

/**
 * @brief  Set logic level for SPI NSS PIN.
 * @param  nss specifies the logic level to be set for SPI NSS PIN.
 * @retval None.
 */
void SPI_TypeDef::SetNSS(SPI_NSSTypeDef nss) {
    if(nss != SPI_NSS_DISABLE) {
        REGS.CTLR1 &= ~SPI_CTLR1_SSM;
        REGS.CTLR2 |= SPI_CTLR2_SSOE;
        if(nss == SPI_NSS_HIGHT)
            REGS.CTLR1 |= SPI_CTLR1_SSI;
        else
            REGS.CTLR1 &= ~SPI_CTLR1_SSI;
    }
    else {
        REGS.CTLR1 |= SPI_CTLR1_SSM;
        REGS.CTLR2 &= ~SPI_CTLR2_SSOE;
    }
}

/**
 * @brief  Decide which bit will be transmitted first.
 * @param  firstBit specifies MSB or LBS will be transmitted first.
 * @retval None.
 */
void SPI_TypeDef::SetFirstBit(SPI_FirstBitTypeDef firstBit) {
    REGS.CTLR1 = (REGS.CTLR1 & ~SPI_CTLR1_LSBFIRST) | ((firstBit << SPI_CTLR1_LSBFIRST_Pos) & SPI_CTLR1_LSBFIRST);
}

/**
 * @brief  Enable or disabe hardware CRC checksum.
 * @param  state specifies the state enable or disabe for CRC.
 * @param  polynomial specifies the polynomial for the CRC calculation.
 * @retval None.
 */
void SPI_TypeDef::SetCRC(HAL_StateTypeDef state, uint32_t polynomial) {
    if(state != DISABLE) {
        REGS.CTLR1 |= SPI_CTLR1_CRCEN;
        REGS.CRCR = polynomial;
    }
    else
        REGS.CTLR1 &= ~SPI_CTLR1_CRCEN;
}

/**
 * @brief  Enable SPI.
 * @note   To be able to transmit and receive data, SPI must be enabled.
 * @retval None.
 */
void SPI_TypeDef::Enabled(void) {
    REGS.CTLR1 |= SPI_CTLR1_SPE;
}

/**
 * @brief  Disable SPI.
 * @retval None.
 */
void SPI_TypeDef::Disabled(void) {
    REGS.CTLR1 &= SPI_CTLR1_SPE;
}

/**
 * @brief  Get current SPI state.
 * @retval SPI state.
 */
SPI_StateTypeDef SPI_TypeDef::GetState(void) {
    if(REGS.STATR & SPI_STATR_BSY)
        return HAL_SPI_STATE_BUSY;
    if(!(REGS.CTLR1 & SPI_CTLR1_SPE))
        return HAL_SPI_STATE_RESET;
    return HAL_SPI_STATE_READY;
}

/**
 * @brief  Get the current SPI data size configuration according to the
 *         internal SPI configuration registers.
 * @retval SPI data size.
 */
SPI_DataSizeTypeDef SPI_TypeDef::GetDataSize(void) {
    return (REGS.CTLR1 & SPI_CTLR1_DFF) ? SPI_DATAWIDTH_16BIT : SPI_DATAWIDTH_8BIT;
}

/**
 * @brief  Transmit an amount of uint8_t data in blocking mode.
 * @param  txData pointer to transmission data buffer.
 * @param  txLength the length of the data array to be transmitted.
 * @param  timeout timeout duration.
 * @note   The data size for SPI must be set to SPI_DATAWIDTH_8BIT. Otherwise,
 *         this function cannot be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Transmit(uint8_t *txData, uint16_t txLength, uint32_t timeout) {
    return Transmit(txData, txLength, NULL_PTR, 0U, timeout);
}

/**
 * @brief  Transmit an amount of uint16_t data in blocking mode.
 * @param  txData pointer to transmission data buffer.
 * @param  txLength the length of the data array to be transmitted.
 * @param  timeout timeout duration.
 * @note   The data size for SPI must be set to SPI_DATAWIDTH_16BIT. Otherwise,
 *         this function cannot be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Transmit(uint16_t *txData, uint16_t txLength, uint32_t timeout) {
    return Transmit(txData, txLength, NULL_PTR, 0U, timeout);
}

/**
 * @brief  Transmit and receive an amount of uint8_t data in blocking mode.
 * @param  txData pointer to transmission data buffer.
 * @param  txLength the length of the data array to be transmitted.
 * @param  rxData pointer to reception data buffer.
 * @param  rxLength the length of the data array to be received.
 * @param  timeout timeout duration.
 * @note   The data size for SPI must be set to SPI_DATAWIDTH_8BIT. Otherwise,
 *         this function cannot be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Transmit(uint8_t *txData, uint16_t txLength, uint8_t *rxData, uint16_t rxLength, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if((GetDataSize() != SPI_DATAWIDTH_8BIT) || ((txData == NULL_PTR) && (rxData == NULL_PTR)) || (txLength == 0U) | (timeout == 0U))
        return HAL_ERROR;
    if(txData == 0U)
        txLength = 0;
    if(rxData == NULL_PTR)
        rxLength = 0;
    while(txLength || rxLength) {
        if(REGS.STATR & SPI_STATR_TXE) {
            if(txLength) {
                REGS.DATAR = *txData;
                txData++;
                txLength--;
            }
            else
                REGS.DATAR = 0xFF;
        }
        if(rxLength && (REGS.STATR & SPI_STATR_RXNE)) {
            *rxData = REGS.DATAR;
            rxData++;
            rxLength--;
        }
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    return HAL_OK;
}

/**
 * @brief  Transmit and receive an amount of uint16_t data in blocking mode.
 * @param  txData pointer to transmission data buffer.
 * @param  txLength the length of the data array to be transmitted.
 * @param  rxData pointer to reception data buffer.
 * @param  rxLength the length of the data array to be received.
 * @param  timeout timeout duration.
 * @note   The data size for SPI must be set to SPI_DATAWIDTH_16BIT. Otherwise,
 *         this function cannot be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Transmit(uint16_t *txData, uint16_t txLength, uint16_t *rxData, uint16_t rxLength, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if((GetDataSize() != SPI_DATAWIDTH_16BIT) || ((txData == NULL_PTR) && (rxData == NULL_PTR)) || (txLength == 0U) | (timeout == 0U))
        return HAL_ERROR;
    if(txData == 0U)
        txLength = 0;
    if(rxData == 0U)
        rxLength = 0;
    while(txLength || rxLength) {
        if(REGS.STATR & SPI_STATR_TXE) {
            if(txLength) {
                REGS.DATAR = *txData;
                txData++;
                txLength--;
            }
            else
                REGS.DATAR = 0xFFFF;
        }
        if(rxLength && (REGS.STATR & SPI_STATR_RXNE)) {
            *rxData = REGS.DATAR;
            rxData++;
            rxLength--;
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
HAL_StatusTypeDef SPI_TypeDef::Transmit(uint16_t data, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    while(1U) {
        if(REGS.STATR & SPI_STATR_TXE) {
            REGS.DATAR = data;
            return HAL_OK;
        }
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
}

/**
 * @brief  Receive an amount of data in blocking mode.
 * @param  rxData pointer to reception data buffer.
 * @param  rxLength the length of the data array to be received.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Receive(uint8_t *rxData, uint16_t rxLength, uint32_t timeout) {
    return Transmit(NULL_PTR, 0U, rxData, rxLength, timeout);
}

/**
 * @brief  Receive an amount of data in blocking mode.
 * @param  rxData pointer to reception data buffer.
 * @param  rxLength the length of the data array to be received.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Receive(uint16_t *rxData, uint16_t rxLength, uint32_t timeout) {
    return Transmit(NULL_PTR, 0U, rxData, rxLength, timeout);
}

/**
 * @brief  De-Initialize the SPI peripheral.
 * @retval HAL status.
 */
void SPI_TypeDef::DeInit(void) {
    REGS.CTLR1 = 0x00;
    REGS.CTLR2 = 0x00;
    REGS.CRCR = 0x07;
    REGS.DATAR;
    REGS.STATR = 0x00;
}
