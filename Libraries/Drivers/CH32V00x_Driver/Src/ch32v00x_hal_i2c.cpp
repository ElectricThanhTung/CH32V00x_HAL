
#include "ch32v00x_hal_i2c.h"

#define I2C_SB_FLAG                             (I2C_STAR1_SB)
#define I2C_ADDR_FLAG                           (I2C_STAR1_ADDR)
#define I2C_BTF_FLAG                            (I2C_STAR1_BTF)
#define I2C_ADDR10_FLAG                         (I2C_STAR1_ADD10)
#define I2C_STOPF_FLAG                          (I2C_STAR1_STOPF)
#define I2C_RXNE_FLAG                           (I2C_STAR1_RXNE)
#define I2C_TXE_FLAG                            (I2C_STAR1_TXE)
#define I2C_BERR_FLAG                           (I2C_STAR1_BERR)
#define I2C_ARLO_FLAG                           (I2C_STAR1_ARLO)
#define I2C_AF_FLAG                             (I2C_STAR1_AF)
#define I2C_OVR_FLAG                            (I2C_STAR1_OVR)
#define I2C_PECERR_FLAG                         (I2C_STAR1_PECERR)
#define I2C_MSL_FLAG                            (I2C_STAR2_MSL << 16U)
#define I2C_BUSY_FLAG                           (I2C_STAR2_BUSY << 16U)
#define I2C_TRA_FLAG                            (I2C_STAR2_TRA << 16U)
#define I2C_GENCALL_FLAG                        (I2C_STAR2_GENCALL << 16U)
#define I2C_DUALF_FLAG                          (I2C_STAR2_DUALF << 16U)

#define I2C_MASTER_FLAG(flag)                   (I2C_MSL_FLAG | I2C_BUSY_FLAG | (flag))
#define I2C_SLAVE_FLAG(flag)                    (I2C_BUSY_FLAG | (flag))

#define I2C_GET_STATUS(flag)                    ((((((uint32_t)REGS.STAR2 << 16U) | REGS.STAR1) & (flag)) != (flag)) ? RESET : SET)

#define I2C_ADDR_WRITE(addr)                    (addr & ~0x01)
#define I2C_ADDR_READ(addr)                     (addr | 0x01)

/**
 * @brief  Set the acknowledgment for the next received byte.
 * @param  i2cRegs pointer to I2C registers (I2C_RegsTypeDef).
 * @param  ack acknowledgment value for the next received byte.
 * @retval None.
 */
static void I2C_SetACK(I2C_RegsTypeDef *i2cRegs, HAL_FlagStatusTypeDef ack) {
    i2cRegs->CTLR1 = (i2cRegs->CTLR1 & ~I2C_CTLR1_ACK) | ((ack == SET) ? I2C_CTLR1_ACK : 0U);
}

/**
 * @brief  Enable the I2C peripheral clock.
 * @note   This function will use RCC module to enable clock for I2C peripheral.
 * @retval None.
 */
void I2C_TypeDef::EnableClock(void) {
    if(this == &I2C1)
        RCC.REGS.APB1PCENR |= RCC_APB1PCENR_I2C1EN;
}

/**
 * @brief  Disable the I2C peripheral clock.
 * @note   This function will use RCC module to disable clock for I2C peripheral.
 * @retval None.
 */
void I2C_TypeDef::DisableClock(void) {
    if(this == &I2C1)
        RCC.REGS.APB1PCENR &= ~RCC_APB1PCENR_I2C1EN;
}

/**
 * @brief  Enable I2C.
 * @note   To be able to transmit and receive data, I2C must be enabled.
 * @retval None.
 */
void I2C_TypeDef::Enable(void) {
    REGS.CTLR1 |= I2C_CTLR1_PE;
}

/**
 * @brief  Disable I2C.
 * @retval None.
 */
void I2C_TypeDef::Disable(void) {
    REGS.CTLR1 &= ~I2C_CTLR1_PE;
}

/**
 * @brief  Set baudrate for I2C clock signal.
 * @param  baudRate specifies the baudRate to be set for I2C.
 * @retval None.
 */
void I2C_TypeDef::SetCLK(I2C_BaudRateTypeDef baudRate) {
    uint32_t hclk = RCC.HCLK.GetFreq();
    REGS.CTLR2 = (REGS.CTLR2 & ~I2C_CTLR2_FREQ) | ((hclk / 1000000) << I2C_CTLR2_FREQ_Pos);
    REGS.CKCFGR = (uint16_t)(hclk / (baudRate << 1));
}

/**
 * @brief  Software reset the I2C peripheral.
 * @note   Make sure the pins of the  I2C bus are released
 *         and the bus is idle before the reset.
 * @retval None.
 */
void I2C_TypeDef::Reset(void) {
    REGS.CTLR1 |= I2C_CTLR1_SWRST;
}

/**
 * @brief  De-Initialize the I2C peripheral.
 * @retval None.
 */
void I2C_TypeDef::DeInit(void) {
    if(this == &I2C1) {
        RCC.REGS.APB1PRSTR |= RCC_APB1PRSTR_I2C1RST;
        RCC.REGS.APB1PRSTR &= ~RCC_APB1PRSTR_I2C1RST;
    }
}

/**
 * @brief  Start generation in blocking mode.
 * @param  startTick used as a reference point to calculate timeout.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_MasterTypeDef::Start(uint32_t startTick, uint32_t timeout) {
    while(I2C_GET_STATUS(I2C_BUSY_FLAG)) {
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    REGS.CTLR1 |= I2C_CTLR1_START;
    while(!I2C_GET_STATUS(I2C_MASTER_FLAG(I2C_SB_FLAG))) {
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    return HAL_OK;
}

/**
 * @brief  Transmit in master mode one byte in blocking mode.
 * @param  data pointer to transmission data buffer.
 * @param  startTick used as a reference point to calculate timeout.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_MasterTypeDef::SendByte(uint8_t data, uint32_t startTick, uint32_t timeout) {
    while(1U) {
        if(I2C_GET_STATUS(I2C_MASTER_FLAG(I2C_TXE_FLAG | I2C_TRA_FLAG))) {
            REGS.DATAR = data;
            break;
        }
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    return HAL_OK;
}

/**
 * @brief  Transmit in master mode 7 bits address in blocking mode.
 * @param  address target device address. The device 7 bits address value
 *         in datasheet must be shifted to the left before calling the interface.
 * @param  startTick used as a reference point to calculate timeout.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_MasterTypeDef::SendAddress(uint8_t address, uint32_t startTick, uint32_t timeout) {
    HAL_StatusTypeDef ret;
    uint32_t flag = I2C_ADDR_FLAG | ((address & 0x01) ? 0U : I2C_TRA_FLAG);
    if((ret = SendByte(address, startTick, timeout)) != HAL_OK)
        return ret;
    while(!I2C_GET_STATUS(I2C_MASTER_FLAG(flag))) {
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    return HAL_OK;
}

/**
 * @brief  Stop generation.
 * @retval None.
 */
void I2C_MasterTypeDef::Stop(void) {
    REGS.CTLR1 |= I2C_CTLR1_STOP;
}

/**
 * @brief  Transmits in master mode an amount of data in blocking mode
 * @param  slaveAddr target device address. The device 7 bits address value
 *         in datasheet must be shifted to the left before calling the interface.
 * @param  txData pointer to transmission data buffer.
 * @param  length the length of the data array to be transmitted.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_MasterTypeDef::Transmit(uint8_t slaveAddr, uint8_t *txData, uint16_t length, uint32_t timeout) {
    HAL_StatusTypeDef ret;
    uint32_t startTick = HAL.GetTickMs();
    do {
        if((ret = Start(startTick, timeout)) != HAL_OK)
            break;
        if((ret = SendAddress(I2C_ADDR_WRITE(slaveAddr), startTick, timeout)) != HAL_OK)
            break;
        while(length) {
            if((ret = SendByte(*txData, startTick, timeout)) == HAL_OK) {
                txData++;
                length--;
            }
            else
                break;
        }
        if(ret != HAL_OK)
            break;
        while(!I2C_GET_STATUS(I2C_MASTER_FLAG(I2C_BTF_FLAG))) {
            if((HAL.GetTickMs() - startTick) >= timeout) {
                ret = HAL_TIMEOUT;
                break;
            }
        }
    } while(0U);
    Stop();
    return ret;
}

/**
 * @brief  Receives in master mode an amount of data in blocking mode.
 * @param  slaveAddr target device address. The device 7 bits address value
 *         in datasheet must be shifted to the left before calling the interface.
 * @param  rxData pointer to reception data buffer.
 * @param  length the length of the data array to be received.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_MasterTypeDef::Receive(uint8_t slaveAddr, uint8_t *rxData, uint16_t length, uint32_t timeout) {
    HAL_StatusTypeDef ret;
    uint32_t startTick = HAL.GetTickMs();
    do {
        I2C_SetACK(&REGS, SET);
        if((ret = Start(startTick, timeout)) != HAL_OK)
            break;
        if((ret = SendAddress(I2C_ADDR_READ(slaveAddr), startTick, timeout)) != HAL_OK)
            break;
        while(length) {
            if(I2C_GET_STATUS(I2C_MASTER_FLAG(I2C_RXNE_FLAG))) {
                length--;
                I2C_SetACK(&REGS, length ? SET : RESET);
                *rxData = REGS.DATAR;
                rxData++;
            }
            if((HAL.GetTickMs() - startTick) >= timeout) {
                ret = HAL_TIMEOUT;
                break;
            }
        }
    } while(0U);
    Stop();
    return HAL_OK;
}

/**
 * @brief  Write an amount of data in blocking mode to a specific memory address.
 * @param  slaveAddr target device address. The device 7 bits address value
 *         in datasheet must be shifted to the left before calling the interface.
 * @param  memAddr internal memory address.
 * @param  data pointer to data buffer.
 * @param  length the length of the data array to be sent.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_MasterTypeDef::MemWrite(uint8_t slaveAddr, uint8_t memAddr, uint8_t *data, uint16_t length, uint32_t timeout) {
    HAL_StatusTypeDef ret;
    uint32_t startTick = HAL.GetTickMs();
    do {
        if((ret = Start(startTick, timeout)) != HAL_OK)
            break;
        if((ret = SendAddress(I2C_ADDR_WRITE(slaveAddr), startTick, timeout)) != HAL_OK)
            break;
        if((ret = SendByte(memAddr, startTick, timeout)) != HAL_OK)
            break;
        while(length) {
            if((ret = SendByte(*data, startTick, timeout)) == HAL_OK) {
                data++;
                length--;
            }
            else
                break;
        }
        if(ret != HAL_OK)
            break;
        while(!I2C_GET_STATUS(I2C_MASTER_FLAG(I2C_BTF_FLAG))) {
            if((HAL.GetTickMs() - startTick) >= timeout) {
                ret = HAL_TIMEOUT;
                break;
            }
        }
    } while(0U);
    Stop();
    return HAL_OK;
}

/**
 * @brief  Read an amount of data in blocking mode from a specific memory address.
 * @param  slaveAddr target device address. The device 7 bits address value
 *         in datasheet must be shifted to the left before calling the interface.
 * @param  memAddr internal memory address.
 * @param  data pointer to data buffer.
 * @param  length the length of the data array to be sent.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_MasterTypeDef::MemRead(uint8_t slaveAddr, uint8_t memAddr, uint8_t *data, uint16_t length, uint32_t timeout) {
    HAL_StatusTypeDef ret;
    uint32_t startTick = HAL.GetTickMs();
    do {
        if((ret = Start(startTick, timeout)) != HAL_OK)
            break;
        if((ret = SendAddress(I2C_ADDR_WRITE(slaveAddr), startTick, timeout)) != HAL_OK)
            break;
        if((ret = SendByte(memAddr, startTick, timeout)) != HAL_OK)
            break;
        I2C_SetACK(&REGS, length ? SET : RESET);
        if((ret = Start(startTick, timeout)) != HAL_OK)
            break;
        if((ret = SendAddress(I2C_ADDR_READ(slaveAddr), startTick, timeout)) != HAL_OK)
            break;
        while(length) {
            if(I2C_GET_STATUS(I2C_MASTER_FLAG(I2C_RXNE_FLAG))) {
                length--;
                I2C_SetACK(&REGS, length ? SET : RESET);
                *data = REGS.DATAR;
                data++;
            }
            if((HAL.GetTickMs() - startTick) >= timeout) {
                ret = HAL_TIMEOUT;
                break;
            }
        }
    } while(0U);
    Stop();
    return HAL_OK;
}

/**
 * @brief  Transmit in slave mode one byte in blocking mode.
 * @param  data pointer to transmission data buffer.
 * @param  startTick used as a reference point to calculate timeout.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_SlaveTypeDef::SendByte(uint8_t data, uint32_t startTick, uint32_t timeout) {
    while(1U) {
        if(I2C_GET_STATUS(I2C_SLAVE_FLAG(I2C_TXE_FLAG | I2C_TRA_FLAG))) {
            REGS.DATAR = data;
            break;
        }
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    return HAL_OK;
}

/**
 * @brief  Set address for slave mode.
 * @param  addr1 7 bits own address 1. The 7 bits address value
 *         must be shifted to the left before calling the interface.
 * @param  addr2 used as a reference point to calculate timeout. The
 *         7 bits address value must be shifted to the left
 *         before calling the interface.
 * @retval HAL status.
 */
void I2C_SlaveTypeDef::SetAddress(uint8_t addr1, uint8_t addr2) {
    REGS.OADDR1 = addr1 & 0xFEU;
    REGS.OADDR2 = (addr2 != 0xFFU) ? (addr2 | I2C_OADDR2_ENDUAL) : 0U;
}

/**
 * @brief  Transmits in slave mode an amount of data in blocking mode
 * @param  txData pointer to transmission data buffer.
 * @param  length the length of the data array to be transmitted.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_SlaveTypeDef::Transmit(uint8_t *txData, uint16_t length, uint32_t timeout) {
    HAL_StatusTypeDef ret;
    uint32_t startTick = HAL.GetTickMs();
    while(length) {
        if((ret = SendByte(*txData, startTick, timeout)) == HAL_OK) {
            txData++;
            length--;
        }
        else
            return ret;
    }
    return HAL_OK;
}

/**
 * @brief  Receives in slave mode an amount of data in blocking mode.
 * @param  rxData pointer to reception data buffer.
 * @param  length the length of the data array to be received.
 * @param  timeout timeout duration.
 * @retval HAL status.
 */
HAL_StatusTypeDef I2C_SlaveTypeDef::Receive(uint8_t *rxData, uint16_t length, uint32_t timeout) {
    uint32_t startTick = HAL.GetTickMs();
    I2C_SetACK(&REGS, length ? SET : RESET);
    while(length) {
        if(I2C_GET_STATUS(I2C_SLAVE_FLAG(I2C_RXNE_FLAG))) {
            length--;
            I2C_SetACK(&REGS, length ? SET : RESET);
            *rxData = REGS.DATAR;
            rxData++;
        }
        if((HAL.GetTickMs() - startTick) >= timeout)
            return HAL_TIMEOUT;
    }
    return HAL_OK;
}
