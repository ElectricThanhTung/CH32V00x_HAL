
#ifndef __CH32V00x_HAL_SPI_H
#define __CH32V00x_HAL_SPI_H

#include "ch32v00x_hal.h"

typedef enum {
    HAL_SPI_STATE_RESET = 0x00U,
    HAL_SPI_STATE_READY = 0x01U,
    HAL_SPI_STATE_BUSY = 0x02U,
} SPI_StateTypeDef;

typedef enum {
    SPI_MODE_SLAVE_FULL_DUPLEX = 0U,
    SPI_MODE_SLAVE_RECEIVED = SPI_CTLR1_BIDIMODE | SPI_CTLR1_RXONLY,
    SPI_MODE_MASTER_FULL_DUPLEX = SPI_CTLR1_MSTR,
    SPI_MODE_MASTER_HALF_DUPLEX = SPI_CTLR1_BIDIMODE,
    SPI_MODE_MASTER_TRANSMIT = SPI_CTLR1_BIDIMODE | SPI_CTLR1_BIDIOE | SPI_CTLR1_MSTR,
} SPI_ModeTypeDef;

typedef enum {
    SPI_FIRSTBIT_MSBFIRST = 0U,
    SPI_FIRSTBIT_LSBFIRST = 1U
} SPI_FirstBitTypeDef;

typedef enum {
    SPI_DATAWIDTH_8BIT = 0U,
    SPI_DATAWIDTH_16BIT = 1U
} SPI_DataSizeTypeDef;

typedef enum {
    SPI_POLARITY_LOW = 0U,
    SPI_POLARITY_HIGH = 1U
} SPI_PolarityTypeDef;

typedef enum {
    SPI_PHASE_RISING_EDGE = 0U,
    SPI_PHASE_FALLING_EDGE = 1U
} SPI_PhaseTypeDef;

typedef enum {
    SPI_NSS_DISABLE = 0U,
    SPI_NSS_LOW = 1U,
    SPI_NSS_HIGHT = 2U
} SPI_NSSTypeDef;

typedef enum {
    SPI_BAUDRATE_HCLK_DIV2 = 0u,
    SPI_BAUDRATE_HCLK_DIV4 = 1U,
    SPI_BAUDRATE_HCLK_DIV8 = 2U,
    SPI_BAUDRATE_HCLK_DIV16 = 3U,
    SPI_BAUDRATE_HCLK_DIV32 = 4U,
    SPI_BAUDRATE_HCLK_DIV64 = 5U,
    SPI_BAUDRATE_HCLK_DIV128 = 6U,
    SPI_BAUDRATE_HCLK_DIV256 = 7U
} SPI_BaudRateTypeDef;

class SPI_TypeDef {
public:
    struct {
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
    } REGS;
public:
    void SetMode(SPI_ModeTypeDef mode);
    void SetDataSize(SPI_DataSizeTypeDef dataSize);
    void SetCLK(SPI_PolarityTypeDef polarity, SPI_PhaseTypeDef phase, SPI_BaudRateTypeDef baudRate = SPI_BAUDRATE_HCLK_DIV2);
    void SetNSS(SPI_NSSTypeDef nss);
    void SetFirstBit(SPI_FirstBitTypeDef firstBit);
    void SetCRC(HAL_StateTypeDef state, uint32_t polynomial = 0U);
    void Enabled(void);
    void Disabled(void);
    SPI_StateTypeDef GetState(void);
    HAL_StatusTypeDef Transmit(uint8_t *txData, uint16_t txLength, uint8_t *rxData, uint16_t rxLength, uint32_t timeout = 0xFFFFFFFF);
    HAL_StatusTypeDef Transmit(uint16_t *txData, uint16_t txLength, uint16_t *rxData, uint16_t rxLength, uint32_t timeout = 0xFFFFFFFF);
    HAL_StatusTypeDef Transmit(uint8_t *txData, uint16_t txLength, uint32_t timeout = 0xFFFFFFFF);
    HAL_StatusTypeDef Transmit(uint16_t *txData, uint16_t txLength, uint32_t timeout = 0xFFFFFFFF);
    HAL_StatusTypeDef Transmit(uint16_t data, uint32_t timeout);
    HAL_StatusTypeDef Receive(uint8_t *rxData, uint16_t rxLength, uint32_t timeout = 0xFFFFFFFF);
    HAL_StatusTypeDef Receive(uint16_t *rxData, uint16_t rxLength, uint32_t timeout = 0xFFFFFFFF);
    void DeInit(void);
private:
    SPI_TypeDef(void);
    SPI_TypeDef(SPI_TypeDef &);

    SPI_DataSizeTypeDef GetDataSize(void);
};

#define SPI1            (*(SPI_TypeDef *)SPI1_BASE)

#endif /* __CH32V00x_HAL_SPI_H */
