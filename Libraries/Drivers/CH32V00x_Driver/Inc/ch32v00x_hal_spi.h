
#ifndef __CH32V00x_HAL_SPI_H
#define __CH32V00x_HAL_SPI_H

#include "ch32v00x_hal.h"

typedef enum {
    HAL_SPI_STATE_RESET = 0x00U,
    HAL_SPI_STATE_READY = 0x01U,
    HAL_SPI_STATE_BUSY = 0x02U,
} SPI_StatusTypeDef;

typedef enum {
    SPI_POLARITY_LOW = 0U,
    SPI_POLARITY_HIGH = 1U
} SPI_PolarityTypeDef;

typedef enum {
    SPI_PHASE_RISING_EDGE = 0U,
    SPI_PHASE_FALLING_EDGE = 1U
} SPI_PhaseTypeDef;

typedef enum {
    SPI_BAUDRATE_DIV2 = 0u,
    SPI_BAUDRATE_DIV4 = 1U,
    SPI_BAUDRATE_DIV8 = 2U,
    SPI_BAUDRATE_DIV16 = 3U,
    SPI_BAUDRATE_DIV32 = 4U,
    SPI_BAUDRATE_DIV64 = 5U,
    SPI_BAUDRATE_DIV128 = 6U,
    SPI_BAUDRATE_DIV256 = 7U
} SPI_BaudRateTypeDef;

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
    __IO uint16_t STATR;
private:
    __IO uint16_t RESERVED2;
public:
    __IO uint16_t DATAR;
private:
    __IO uint16_t RESERVED3;
public:
    __IO uint16_t CRCR;
private:
    __IO uint16_t RESERVED4;
public:
    __IO uint16_t RCRCR;
private:
    __IO uint16_t RESERVED5;
public:
    __IO uint16_t TCRCR;
private:
    __IO uint16_t RESERVED6;
    __IO uint32_t RESERVED7;
    __IO uint32_t RESERVED8;
public:
    __IO uint16_t HSCR;
private:
    __IO uint16_t RESERVED9;
} SPI_RegsTypeDef;

class SPI_ModeTypeDef {
private:
    SPI_RegsTypeDef REGS;
public:
    void SlaveFullDuplex(void);
    void SlaveReceive(void);
    void MasterFullDuplex(void);
    void MasterHalfDuplex(void);
    void MasterTransmit(void);
private:
    SPI_ModeTypeDef(void);
    SPI_ModeTypeDef(const SPI_ModeTypeDef &);

    void SetMode(uint32_t mode);
};

class SPI_DataSizeTypeDef {
private:
    SPI_RegsTypeDef REGS;
public:
    void Mode8Bit(void);
    void Mode16Bit(void);
    bool IsMode8Bit(void);
    bool IsMode16Bit(void);
private:
    SPI_DataSizeTypeDef(void);
    SPI_DataSizeTypeDef(SPI_DataSizeTypeDef &);
};

class SPI_ClkTypeDef {
private:
    SPI_RegsTypeDef REGS;
public:
    void SetPolarity(SPI_PolarityTypeDef polarity);
    void SetPhase(SPI_PhaseTypeDef phase);
    void SetBaudRate(SPI_BaudRateTypeDef baudRate);
private:
    SPI_ClkTypeDef(void);
    SPI_ClkTypeDef(const SPI_ClkTypeDef &);
};

class SPI_NssTypeDef {
private:
    SPI_RegsTypeDef REGS;
public:
    void Disable(void);
    void ActiveLow(void);
    void ActiveHight(void);
private:
    SPI_NssTypeDef(void);
    SPI_NssTypeDef(SPI_NssTypeDef &);
};

class SPI_FirstBitTypeDef {
private:
    SPI_RegsTypeDef REGS;
public:
    void MSBFirst(void);
    void LSBFirst(void);
private:
    SPI_FirstBitTypeDef(void);
    SPI_FirstBitTypeDef(const SPI_FirstBitTypeDef &);
};

class SPI_CrcTypeDef {
private:
    SPI_RegsTypeDef REGS;
public:
    void Enable(uint32_t polynomial);
    void Disable(void);
    bool IsEnable(void);
private:
    SPI_CrcTypeDef(void);
    SPI_CrcTypeDef(const SPI_CrcTypeDef &);
};

class SPI_TypeDef {
public:
    union {
        SPI_RegsTypeDef REGS;
        SPI_ModeTypeDef Mode;
        SPI_DataSizeTypeDef DataSize;
        SPI_ClkTypeDef Clock;
        SPI_NssTypeDef NSS;
        SPI_FirstBitTypeDef FirstBit;
    };
public:
    void EnableClock(void);
    void DisableClock(void);
    void Enable(void);
    void Disable(void);
    SPI_StatusTypeDef GetStatus(void);
    HAL_StatusTypeDef Transmit(uint8_t *txData, uint16_t txLength, uint8_t *rxData, uint16_t rxLength, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Transmit(uint16_t *txData, uint16_t txLength, uint16_t *rxData, uint16_t rxLength, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Transmit(uint8_t *txData, uint16_t txLength, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Transmit(uint16_t *txData, uint16_t txLength, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Transmit(uint16_t data, uint32_t timeout);
    HAL_StatusTypeDef Receive(uint8_t *rxData, uint16_t rxLength, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Receive(uint16_t *rxData, uint16_t rxLength, uint32_t timeout = 0xFFFFFFFFUL);
    void DeInit(void);
private:
    SPI_TypeDef(void);
    SPI_TypeDef(const SPI_TypeDef &);
};

#define SPI1            (*(SPI_TypeDef *)SPI1_BASE)

#endif /* __CH32V00x_HAL_SPI_H */
