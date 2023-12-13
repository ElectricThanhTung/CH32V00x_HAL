
#include "ch32v00x_hal_spi.h"

#define SPI_MODE_SLAVE_FULL_DUPLEX      (0U)
#define SPI_MODE_SLAVE_RECEIVE          (SPI_CTLR1_BIDIMODE | SPI_CTLR1_RXONLY)
#define SPI_MODE_MASTER_FULL_DUPLEX     (SPI_CTLR1_MSTR)
#define SPI_MODE_MASTER_HALF_DUPLEX     (SPI_CTLR1_BIDIMODE)
#define SPI_MODE_MASTER_TRANSMIT        (SPI_CTLR1_BIDIMODE | SPI_CTLR1_BIDIOE | SPI_CTLR1_MSTR)

/**
 * @brief  Set mode for SPI according to the specified parameters in the mode.
 * @param  mode specifies the mode to be set for SPI.
 * @retval None.
 */
void SPI_ModeTypeDef::SetMode(uint32_t mode) {
    REGS.CTLR1 &= ~(SPI_CTLR1_BIDIMODE | SPI_CTLR1_BIDIOE | SPI_CTLR1_RXONLY | SPI_CTLR1_MSTR);
    REGS.CTLR1 |= mode & (SPI_CTLR1_BIDIMODE | SPI_CTLR1_BIDIOE | SPI_CTLR1_RXONLY | SPI_CTLR1_MSTR);
}

/**
 * @brief  Set SPI to slave full duplex mode.
 * @retval None.
 */
void SPI_ModeTypeDef::SlaveFullDuplex(void) {
    SetMode(SPI_MODE_SLAVE_FULL_DUPLEX);
}

/**
 * @brief  Set SPI to slave receive only mode.
 * @retval None.
 */
void SPI_ModeTypeDef::SlaveReceive(void) {
    SetMode(SPI_MODE_SLAVE_RECEIVE);
}

/**
 * @brief  Set SPI to master full duplex mode.
 * @retval None.
 */
void SPI_ModeTypeDef::MasterFullDuplex(void) {
    SetMode(SPI_MODE_MASTER_FULL_DUPLEX);
}

/**
 * @brief  Set SPI to master half duplex mode.
 * @retval None.
 */
void SPI_ModeTypeDef::MasterHalfDuplex(void) {
    SetMode(SPI_MODE_MASTER_HALF_DUPLEX);
}

/**
 * @brief  Set SPI to master transmit only mode.
 * @retval None.
 */
void SPI_ModeTypeDef::MasterTransmit(void) {
    SetMode(SPI_MODE_MASTER_TRANSMIT);
}

/**
 * @brief  Set 8 bits mode data size when transmitting and receiving for SPI.
 * @retval None.
 */
void SPI_DataSizeTypeDef::Mode8Bit(void) {
    REGS.CTLR1 &= ~SPI_CTLR1_DFF;
}

/**
 * @brief  Set 16 bits mode data size when transmitting and receiving for SPI.
 * @retval None.
 */
void SPI_DataSizeTypeDef::Mode16Bit(void) {
    REGS.CTLR1 |= SPI_CTLR1_DFF;
}

/**
 * @brief  Check whether the current SPI configuration is 8-bit mode or not.
 * @retval Boolean.
 */
bool SPI_DataSizeTypeDef::IsMode8Bit(void) {
    return (REGS.CTLR1 & SPI_CTLR1_DFF) == 0U;
}

/**
 * @brief  Check whether the current SPI configuration is 16-bit mode or not.
 * @retval Boolean.
 */
bool SPI_DataSizeTypeDef::IsMode16Bit(void) {
    return (REGS.CTLR1 & SPI_CTLR1_DFF) == SPI_CTLR1_DFF;
}

/**
 * @brief  Set polarity for SPI clock signal.
 * @param  polarity specifies the polarity (CLK idle state) to be set for SPI.
 * @retval None.
 */
void SPI_ClkTypeDef::SetPolarity(SPI_PolarityTypeDef polarity) {
    REGS.CTLR1 = (REGS.CTLR1 & ~SPI_CTLR1_CPOL) | (polarity << SPI_CTLR1_CPOL_Pos);
}

/**
 * @brief  Set phase for SPI clock signal.
 * @param  phase specifies the phase (sampling point) to be set for SPI.
 * @retval None.
 */
void SPI_ClkTypeDef::SetPhase(SPI_PhaseTypeDef phase) {
    uint32_t polarity = (REGS.CTLR1 & SPI_CTLR1_CPOL) >> SPI_CTLR1_CPOL_Pos;
    REGS.CTLR1 = (REGS.CTLR1 & ~SPI_CTLR1_CPHA) | ((polarity ^ phase) << SPI_CTLR1_CPHA_Pos);
}

/**
 * @brief  Set baudrate for SPI clock signal.
 * @param  baudRate specifies the baudRate to be set for SPI.
 * @retval None.
 */
void SPI_ClkTypeDef::SetBaudRate(SPI_BaudRateTypeDef baudRate) {
    REGS.CTLR1 = (REGS.CTLR1 & ~SPI_CTLR1_BR) | (baudRate << SPI_CTLR1_BR_Pos);
}

/**
 * @brief  Disable SPI NSS PIN.
 * @retval None.
 */
void SPI_NssTypeDef::Disable(void) {
    REGS.CTLR1 |= SPI_CTLR1_SSM;
    REGS.CTLR2 &= ~SPI_CTLR2_SSOE;
}

/**
 * @brief  Set active logic low level for SPI NSS PIN.
 * @retval None.
 */
void SPI_NssTypeDef::ActiveLow(void) {
    REGS.CTLR1 &= ~SPI_CTLR1_SSM;
    REGS.CTLR2 |= SPI_CTLR2_SSOE;
    REGS.CTLR1 &= ~SPI_CTLR1_SSI;
}

/**
 * @brief  Set active logic hight level for SPI NSS PIN.
 * @retval None.
 */
void SPI_NssTypeDef::ActiveHight(void) {
    REGS.CTLR1 &= ~SPI_CTLR1_SSM;
    REGS.CTLR2 |= SPI_CTLR2_SSOE;
    REGS.CTLR1 |= SPI_CTLR1_SSI;
}

/**
 * @brief  Set MSB will be sent first.
 * @retval None.
 */
void SPI_FirstBitTypeDef::MSBFirst(void) {
    REGS.CTLR1 &= ~SPI_CTLR1_LSBFIRST;
}

/**
 * @brief  Set LSB will be sent first.
 * @retval None.
 */
void SPI_FirstBitTypeDef::LSBFirst(void) {
    REGS.CTLR1 |= SPI_CTLR1_LSBFIRST;
}

/**
 * @brief  Enable hardware CRC checksum.
 * @param  polynomial specifies the polynomial for the CRC calculation.
 * @retval None.
 */
void SPI_CrcTypeDef::Enable(uint32_t polynomial) {
    REGS.CTLR1 |= SPI_CTLR1_CRCEN;
    REGS.CRCR = polynomial;
}

/**
 * @brief  Disabe hardware CRC checksum.
 * @retval None.
 */
void SPI_CrcTypeDef::Disable(void) {
    REGS.CTLR1 &= ~SPI_CTLR1_CRCEN;
}

/**
 * @brief  Return state of CRC.
 * @retval Boolean.
 */
bool SPI_CrcTypeDef::IsEnable(void) {
    return (REGS.CTLR1 & SPI_CTLR1_CRCEN) == SPI_CTLR1_CRCEN;
}

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
 * @brief  Enable SPI.
 * @note   To be able to transmit and receive data, SPI must be enabled.
 * @retval None.
 */
void SPI_TypeDef::Enable(void) {
    REGS.CTLR1 |= SPI_CTLR1_SPE;
}

/**
 * @brief  Disable SPI.
 * @retval None.
 */
void SPI_TypeDef::Disable(void) {
    REGS.CTLR1 &= ~SPI_CTLR1_SPE;
}

/**
 * @brief  Get current SPI status.
 * @retval SPI status.
 */
SPI_StatusTypeDef SPI_TypeDef::GetStatus(void) {
    if(REGS.STATR & SPI_STATR_BSY)
        return HAL_SPI_STATE_BUSY;
    if(!(REGS.CTLR1 & SPI_CTLR1_SPE))
        return HAL_SPI_STATE_RESET;
    return HAL_SPI_STATE_READY;
}

/**
 * @brief  Transmit an amount of uint8_t data in blocking mode.
 * @param  txData pointer to transmission data buffer.
 * @param  txLength the length of the data array to be transmitted.
 * @param  timeout timeout duration.
 * @note   The data size for SPI must be set to 8-bit mode. Otherwise,
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
 * @note   The data size for SPI must be set to 16-bit mode. Otherwise,
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
 * @note   The data size for SPI must be set to 8-bit mode. Otherwise,
 *         this function cannot be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Transmit(uint8_t *txData, uint16_t txLength, uint8_t *rxData, uint16_t rxLength, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if(!DataSize.IsMode8Bit() || ((txData == NULL_PTR) && (rxData == NULL_PTR)) || (txLength == 0U) | (timeout == 0U))
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
                REGS.DATAR = 0xFFU;
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
 * @note   The data size for SPI must be set to 16-bit mode. Otherwise,
 *         this function cannot be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Transmit(uint16_t *txData, uint16_t txLength, uint16_t *rxData, uint16_t rxLength, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    if(!DataSize.IsMode16Bit() || ((txData == NULL_PTR) && (rxData == NULL_PTR)) || (txLength == 0U) | (timeout == 0U))
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
                REGS.DATAR = 0xFFFFU;
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
 * @note   The data size for SPI must be set to 8-bit mode. Otherwise,
 *         this function cannot be executed and will return HAL_ERROR.
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
 * @note   The data size for SPI must be set to 16-bit mode. Otherwise,
 *         this function cannot be executed and will return HAL_ERROR.
 * @retval HAL status.
 */
HAL_StatusTypeDef SPI_TypeDef::Receive(uint16_t *rxData, uint16_t rxLength, uint32_t timeout) {
    return Transmit(NULL_PTR, 0U, rxData, rxLength, timeout);
}

/**
 * @brief  De-Initialize the SPI peripheral.
 * @retval None.
 */
void SPI_TypeDef::DeInit(void) {
    if(this == &SPI1) {
        RCC.REGS.APB2PRSTR |= RCC_APB2PRSTR_SPI1RST;
        RCC.REGS.APB2PRSTR &= ~RCC_APB2PRSTR_SPI1RST;
    }
}
