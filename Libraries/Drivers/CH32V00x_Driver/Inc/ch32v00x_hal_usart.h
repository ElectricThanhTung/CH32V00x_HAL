
#ifndef __CH32C00x_HAL_USART_H
#define __CH32C00x_HAL_USART_H

#include "ch32v00x_hal.h"

typedef enum {
    USART_MODE_RX = USART_CTLR1_TE,
    USART_MODE_TX = USART_CTLR1_RE,
    USART_MODE_TX_RX = USART_MODE_RX | USART_MODE_TX
} USART_ModeTypeDef;

typedef enum {
    USART_WORD_LENGTH_8 = 0U,
    USART_WORD_LENGTH_9 = USART_CTLR1_M
} USART_WordLengthTypeDef;

typedef enum {
    USART_PARITY_NONE = 0U,
    USART_PARITY_EVEN = USART_CTLR1_PCE,
    USART_PARITY_ODD = USART_CTLR1_PCE | USART_CTLR1_PS
} USART_ParityTypeDef;

class USART_TypeDef {
public:
    struct {
    public:
        __IO uint16_t STATR;
    private:
        __IO uint16_t RESERVED0;
    public:
        __IO uint16_t DATAR;
    private:
        __IO uint16_t RESERVED1;
    public:
        __IO uint16_t BRR;
    private:
        __IO uint16_t RESERVED2;
    public:
        __IO uint16_t CTLR1;
    private:
        __IO uint16_t RESERVED3;
    public:
        __IO uint16_t CTLR2;
    private:
        __IO uint16_t RESERVED4;
    public:
        __IO uint16_t CTLR3;
    private:
        __IO uint16_t RESERVED5;
    public:
        __IO uint16_t GPR;
    private:
        __IO uint16_t RESERVED6;
    } REGS;
public:
    void EnableClock(void);
    void DisableClock(void);
    void SetMode(USART_ModeTypeDef mode);
    uint32_t SetBaudRate(uint32_t baudRate);
    void SetWordLength(USART_WordLengthTypeDef wordLength);
    void SetParity(USART_ParityTypeDef parity);
    HAL_StatusTypeDef Transmit(uint8_t *txData, uint16_t txLength, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Transmit(uint16_t *txData, uint16_t txLength, uint32_t timeout = 0xFFFFFFFFUL);
    HAL_StatusTypeDef Transmit(uint16_t txData, uint32_t timeout = 0xFFFFFFFFUL);
    void DeInit(void);
private:
    USART_TypeDef(void);
    USART_TypeDef(USART_TypeDef &);
};

#define USART1          (*(USART_TypeDef *)USART1_BASE)

#endif /* __CH32C00x_HAL_USART_H */
