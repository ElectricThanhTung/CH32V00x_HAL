#ifndef __CH32V00x_HAL_H
#define __CH32V00x_HAL_H

#include "ch32v00x.h"

#ifndef NULL
#define NULL            (0U)
#endif /* NULL */

#ifndef NULL_PTR
#define NULL_PTR        NULL
#endif /* NULL_PTR */

#define LENGTH(array)   (sizeof(array) / sizeof(array[0]))

typedef enum  {
    HAL_OK = 0x00U,
    HAL_ERROR = 0x01U,
    HAL_BUSY = 0x02U,
    HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

typedef FunctionalState HAL_StateTypeDef;

typedef FlagStatus HAL_FlagStatusTypeDef;

class HAL_TypeDef {
public:
    void Init(void);
    uint32_t GetTickUs(void);
    uint32_t GetTickMs(void);
    void DelayUs(uint32_t time);
    void DelayMs(uint32_t time);
    void EnabelTickIRQ(uint32_t interval);
    void DisableTickIRQ(void);
private:
    uint32_t TickIntervalMs;
    HAL_TypeDef(void) = delete;
    HAL_TypeDef(const HAL_TypeDef &) = delete;
    void operator=(const HAL_TypeDef &) = delete;
};

#define HAL             (*(HAL_TypeDef *)0U)

#if __has_include("ch32v00x_hal_conf.h")
#include "ch32v00x_hal_conf.h"
#endif

#include "ch32v00x_hal_rcc.h"
#include "ch32v00x_hal_gpio.h"
#include "ch32v00x_hal_adc.h"
#include "ch32v00x_hal_tim.h"
#include "ch32v00x_hal_afio.h"
#include "ch32v00x_hal_exti.h"
#include "ch32v00x_hal_flash.h"
#include "ch32v00x_hal_sram.h"
#include "ch32v00x_hal_usart.h"
#include "ch32v00x_hal_spi.h"
#include "ch32v00x_hal_i2c.h"
#include "ch32v00x_hal_dma.h"
#include "ch32v00x_hal_pwr.h"
#include "ch32v00x_hal_iwdg.h"
#include "ch32v00x_hal_esig.h"

#endif /* __CH32V00x_HAL_H */
