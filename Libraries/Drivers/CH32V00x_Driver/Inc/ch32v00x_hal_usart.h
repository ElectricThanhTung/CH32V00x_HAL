
#ifndef __CH32C00x_HAL_USART_H
#define __CH32C00x_HAL_USART_H

#include "ch32v00x_hal.h"

typedef struct {
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
} USART_RegsTypeDef;

class USART_RxModeTypeDef {
private:
    USART_RegsTypeDef REGS;
public:
    void Enable(void);
    void Disable(void);
private:
    USART_RxModeTypeDef(void);
    USART_RxModeTypeDef(USART_RxModeTypeDef &);
};

class USART_TxModeTypeDef {
private:
    USART_RegsTypeDef REGS;
public:
    void Enable(void);
    void Disable(void);
private:
    USART_TxModeTypeDef(void);
    USART_TxModeTypeDef(USART_TxModeTypeDef &);
};

class USART_BaudrateTypeDef {
private:
    USART_RegsTypeDef REGS;
public:
    uint32_t SetValue(uint32_t baudRate);
    uint32_t GetValue(void);
private:
    USART_BaudrateTypeDef(void);
    USART_BaudrateTypeDef(USART_BaudrateTypeDef &);
};

class USART_WordLengthTypeDef {
private:
    USART_RegsTypeDef REGS;
public:
    void Mode8Bit(void);
    void Mode9Bit(void);
    bool IsMode8Bit(void);
    bool IsMode9Bit(void);
private:
    USART_WordLengthTypeDef(void);
    USART_WordLengthTypeDef(USART_WordLengthTypeDef &);
};

class USART_ParityTypeDef {
private:
    USART_RegsTypeDef REGS;
public:
    void Disable(void);
    void Even(void);
    void Odd(void);
private:
    USART_ParityTypeDef(void);
    USART_ParityTypeDef(USART_ParityTypeDef &);
};

class USART_TypeDef {
public:
    union {
        USART_RegsTypeDef REGS;
        USART_RxModeTypeDef RxMode;
        USART_TxModeTypeDef TxMode;
        USART_BaudrateTypeDef BaudRate;
        USART_WordLengthTypeDef WordLength;
        USART_ParityTypeDef Parity;
    };
public:
    void EnableClock(void);
    void DisableClock(void);
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
