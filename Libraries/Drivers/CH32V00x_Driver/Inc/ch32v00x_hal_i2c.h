
#ifndef __CH32V00x_HAL_I2C_H
#define __CH32V00x_HAL_I2C_H

#include "ch32v00x_hal.h"

typedef enum {
    I2C_BAUDRATE_100KHz = 100000U,
    I2C_BAUDRATE_200KHz = 200000U,
    I2C_BAUDRATE_400KHz = 400000U,
    I2C_BAUDRATE_1MHz = 1000000U,
    I2C_BAUDRATE_2MHz = 2000000U,
    I2C_BAUDRATE_4MHz = 4000000U,
} I2C_BaudRateTypeDef;

typedef struct {
public:
    __IO uint16_t CTLR1;
private:
    __IO uint16_t RESERVED0;
public:
    __IO uint16_t CTLR2;
private:
    __IO uint16_t RESERVED1;
public:
    __IO uint16_t OADDR1;
private:
    __IO uint16_t RESERVED2;
public:
    __IO uint16_t OADDR2;
private:
    __IO uint16_t RESERVED3;
public:
    __IO uint16_t DATAR;
private:
    __IO uint16_t RESERVED4;
public:
    __IO uint16_t STAR1;
private:
    __IO uint16_t RESERVED5;
public:
    __IO uint16_t STAR2;
private:
    __IO uint16_t RESERVED6;
public:
    __IO uint16_t CKCFGR;
private:
    __IO uint16_t RESERVED7;
} I2C_RegsTypeDef;

class I2C_MasterTypeDef {
private:
    I2C_RegsTypeDef REGS;
public:
    HAL_StatusTypeDef Transmit(uint8_t slaveAddr, uint8_t *txData, uint16_t length, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Receive(uint8_t slaveAddr, uint8_t *rxData, uint16_t length, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef MemWrite(uint8_t slaveAddr, uint8_t memAddr, uint8_t *data, uint16_t length, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef MemRead(uint8_t slaveAddr, uint8_t memAddr, uint8_t *data, uint16_t length, uint32_t timeout = 0xFFFFFFFFUL);
private:
    I2C_MasterTypeDef(void);
    I2C_MasterTypeDef(I2C_MasterTypeDef &);

    HAL_StatusTypeDef Start(uint32_t startTick, uint32_t timeout);
    HAL_StatusTypeDef SendByte(uint8_t data, uint32_t startTick, uint32_t timeout);
    HAL_StatusTypeDef SendAddress(uint8_t address, uint32_t startTick, uint32_t timeout);
    void Stop(void);
};

class I2C_SlaveTypeDef {
private:
    I2C_RegsTypeDef REGS;
public:
    void SetAddress(uint8_t addr1, uint8_t addr2 = 0xFFU);
    HAL_StatusTypeDef Transmit(uint8_t *txData, uint16_t length, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Receive(uint8_t *rxData, uint16_t length, uint32_t timeout = 0xFFFFFFFFUL);
private:
    I2C_SlaveTypeDef(void);
    I2C_SlaveTypeDef(I2C_SlaveTypeDef &);

    HAL_StatusTypeDef SendByte(uint8_t data, uint32_t startTick, uint32_t timeout);
};

class I2C_TypeDef {
public:
    union {
        I2C_RegsTypeDef REGS;
        I2C_MasterTypeDef Master;
        I2C_SlaveTypeDef Slave;
    };
public:
    void EnableClock(void);
    void DisableClock(void);
    void SetCLK(I2C_BaudRateTypeDef baudRate);
    void Enable(void);
    void Disable(void);
    void Reset(void);
    void DeInit(void);
private:
    I2C_TypeDef(void);
    I2C_TypeDef(I2C_TypeDef &);
};

#define I2C1            (*(I2C_TypeDef *)I2C1_BASE)

#endif /* __CH32V00x_HAL_I2C_H */