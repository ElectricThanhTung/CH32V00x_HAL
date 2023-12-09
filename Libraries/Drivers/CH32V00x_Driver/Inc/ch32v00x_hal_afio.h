
#ifndef __CH32V00x_HAL_AFIO_H
#define __CH32V00x_HAL_AFIO_H

#include "ch32v00x_hal.h"

typedef enum {
    AFIO_REMAP_I2C1_DISABLE = DISABLE,
    AFIO_REMAP_I2C1_1 = 1U,
    AFIO_REMAP_I2C1_2 = 2U
} AFIO_RemapI2C1TypeDef;

typedef enum {
    AFIO_REMAP_USART1_DISABLE = DISABLE,
    AFIO_REMAP_USART1_1 = 1U,
    AFIO_REMAP_USART1_2 = 2U,
    AFIO_REMAP_USART1_3 = 3U
} AFIO_RemapUSART1TypeDef;

typedef enum {
    AFIO_REMAP_TIM1_DISABLE = DISABLE,
    AFIO_REMAP_TIM1_1 = 1U,
    AFIO_REMAP_TIM1_2 = 2U,
    AFIO_REMAP_TIM1_3 = 3U
} AFIO_RemapTIM1TypeDef;

typedef enum {
    AFIO_REMAP_TIM2_DISABLE = DISABLE,
    AFIO_REMAP_TIM2_1 = 1U,
    AFIO_REMAP_TIM2_2 = 2U,
    AFIO_REMAP_TIM2_3 = 3U
} AFIO_RemapTIM2TypeDef;

class AFIO_TypeDef {
public:
    struct {
    private:
        uint32_t RESERVED0;
    public:
        __IO uint32_t PCFR1;
        __IO uint32_t EXTICR;
    } REGS;
public:
    void EnableClock(void);
    void DisableClock(void);
    void RemapSPI1(HAL_StateTypeDef remap);
    void RemapI2C1(AFIO_RemapI2C1TypeDef remap);
    void RemapUSART1(AFIO_RemapUSART1TypeDef remap);
    void RemapTIM1(AFIO_RemapTIM1TypeDef remap);
    void RemapTIM2(AFIO_RemapTIM2TypeDef remap);
    void RemapADCETRGINJ(HAL_StateTypeDef remap);
    void RemapADCETRGREG(HAL_StateTypeDef remap);
    void RemapSWD(HAL_StateTypeDef remap);
    void DeInit(void);
private:
    AFIO_TypeDef(void);
    AFIO_TypeDef(AFIO_TypeDef &);
};

#define AFIO            (*(AFIO_TypeDef *)AFIO_BASE)

#endif /* __CH32V00x_HAL_AFIO_H */
