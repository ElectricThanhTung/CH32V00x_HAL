
#ifndef __CH32V00x_HAL_DMA_H
#define __CH32V00x_HAL_DMA_H

#include "ch32v00x_hal.h"

typedef enum {
    DMA_PRIORITY_LOW = 0U << DMA_CFGR_PL_Pos,
    DMA_PRIORITY_MEDIUM = 1U << DMA_CFGR_PL_Pos,
    DMA_PRIORITY_HIGH = 2U << DMA_CFGR_PL_Pos,
    DMA_PRIORITY_VERY_HIGH = 3U << DMA_CFGR_PL_Pos
} DMA_PriorityTypeDef;

typedef enum {
    DMA_COPYMODE_BLOCKING = 0U,
    DMA_COPYMODE_NON_BLOCKING = 1U
} DMA_CopyModeTypeDef;

class DMA_ChannelTypeDef {
public:
    struct {
    public:
        __IO uint32_t CFGR;
        __IO uint32_t CNTR;
        __IO uint32_t PADDR;
        __IO uint32_t MADDR;
    } REGS;
public:
    HAL_StatusTypeDef MemCopy(void *src, void *dest, uint32_t size, DMA_CopyModeTypeDef copyMode = DMA_COPYMODE_BLOCKING);
    HAL_StatusTypeDef Setup(uint8_t *src, uint8_t *dest, uint32_t count);
    HAL_StatusTypeDef Setup(uint8_t *src, uint16_t *dest, uint32_t count);
    HAL_StatusTypeDef Setup(uint8_t *src, uint32_t *dest, uint32_t count);
    HAL_StatusTypeDef Setup(uint16_t *src, uint8_t *dest, uint32_t count);
    HAL_StatusTypeDef Setup(uint16_t *src, uint16_t *dest, uint32_t count);
    HAL_StatusTypeDef Setup(uint16_t *src, uint32_t *dest, uint32_t count);
    HAL_StatusTypeDef Setup(uint32_t *src, uint8_t *dest, uint32_t count);
    HAL_StatusTypeDef Setup(uint32_t *src, uint16_t *dest, uint32_t count);
    HAL_StatusTypeDef Setup(uint32_t *src, uint32_t *dest, uint32_t count);
    HAL_StatusTypeDef SetPriority(DMA_PriorityTypeDef priority);
    HAL_StatusTypeDef SetMINC(HAL_StateTypeDef enabled);
    HAL_StatusTypeDef SetPINC(HAL_StateTypeDef enabled);
    HAL_StatusTypeDef GetStatus(void);
    void Stop(void);
    void DeInit(void);
private:
    DMA_ChannelTypeDef(void);
    DMA_ChannelTypeDef(const DMA_ChannelTypeDef &);

    HAL_StatusTypeDef Setup(void *src, uint8_t sSize, void *dest, uint8_t dSize, uint32_t count);
};

class DMA_TypeDef {
public:
    struct {
    public:
        __IO uint32_t INTFR;
        __IO uint32_t INTFCR;
    } REGS;
    DMA_ChannelTypeDef CHANNEL1;
    DMA_ChannelTypeDef CHANNEL2;
    DMA_ChannelTypeDef CHANNEL3;
    DMA_ChannelTypeDef CHANNEL4;
    DMA_ChannelTypeDef CHANNEL5;
    DMA_ChannelTypeDef CHANNEL6;
    DMA_ChannelTypeDef CHANNEL7;
public:
    void EnableClock(void);
    void DisableClock(void);
    DMA_ChannelTypeDef *MemCopy(void *src, void *dest, uint32_t size, DMA_CopyModeTypeDef copyMode = DMA_COPYMODE_BLOCKING);
    void DeInit(void);
private:
    DMA_TypeDef(void);
    DMA_TypeDef(const DMA_TypeDef &);
};

#define DMA1            (*(DMA_TypeDef *)DMA1_BASE)

#endif /* __CH32V00x_HAL_DMA_H */
