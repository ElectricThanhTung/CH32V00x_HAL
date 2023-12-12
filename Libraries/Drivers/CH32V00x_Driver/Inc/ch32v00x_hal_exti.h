
#ifndef __CH32V00x_HAL_EXTI_H
#define __CH32V00x_HAL_EXTI_H

#include "ch32v00x_hal.h"

#define EXTI_LINE_0     (1UL << 0U)
#define EXTI_LINE_1     (1UL << 1U)
#define EXTI_LINE_2     (1UL << 2U)
#define EXTI_LINE_3     (1UL << 3U)
#define EXTI_LINE_4     (1UL << 4U)
#define EXTI_LINE_5     (1UL << 5U)
#define EXTI_LINE_6     (1UL << 6U)
#define EXTI_LINE_7     (1UL << 7U)
#define EXTI_LINE_8     (1UL << 8U)
#define EXTI_LINE_9     (1UL << 9U)
#define EXTI_LINE_ALL   (0x03FFU)

typedef enum {
    EXTI_MODE_NONE = 0x00U,
    EXTI_MODE_INTERRUPT = 0x01U,
    EXTI_MODE_EVNET = 0x02U,
    EXTI_MODE_BOTH = (EXTI_MODE_INTERRUPT | EXTI_MODE_EVNET)
} EXTI_ModeTypeDef;

typedef enum {
    EXTI_TRIGGER_NONE = 0x00U,
    EXTI_TRIGGER_RISING = 0x01U,
    EXTI_TRIGGER_FALLING = 0x02U,
    EXTI_TRIGGER_CHANGE = (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)
} EXTI_TriggerTypeDef;

typedef enum {
    EXTI_PORT_GPIOA = 0U,
    EXTI_PORT_GPIOC = 2U,
    EXTI_PORT_GPIOD = 3U
} EXTI_PortTypeDef;

class EXTI_TypeDef {
public:
    struct {
    public:
        __IO uint32_t INTENR;
        __IO uint32_t EVENR;
        __IO uint32_t RTENR;
        __IO uint32_t FTENR;
        __IO uint32_t SWIEVR;
        __IO uint32_t INTFR;
    } REGS;
public:
    void Init(EXTI_PortTypeDef port, uint32_t line, EXTI_ModeTypeDef mode = EXTI_MODE_INTERRUPT, EXTI_TriggerTypeDef trigger = EXTI_TRIGGER_CHANGE);
    void DeInit(uint32_t line = EXTI_LINE_ALL);
private:
    EXTI_TypeDef(void);
    EXTI_TypeDef(EXTI_TypeDef &);
};

#define EXTI            (*(EXTI_TypeDef *)EXTI_BASE)

#endif /* __CH32V00x_HAL_EXTI_H */
